/*
 * BACnetDevice.cpp
 *
 *  Created on: May 5, 2017
 *      Author: 8w4
 */

#include "BACnetDevice.h"

#include <sstream>
#include <stdexcept>
#include <cstring>

#include "BACnetWhoIsRequest.h"
#include "BACnetNpdu.h"
#include "BACnetBuffer.h"
#include "BACnetBVLLOrigBcastNPDU.h"
#include "BACnetBvllOrigUnicastNpdu.h"
#include "BACnetComplexAck.h"
#include "BACnetErrorPdu.h"
#include "BACnetStringUtil.h"
#include "BACnetNull.h"

int BACnet_verbosity = 1;

addrToDevMap_t BACnetDevice::addrToDevMap;
instToDevMap_t BACnetDevice::instToDevMap;
nameToDevMap_t BACnetDevice::nameToDevMap;

epicsEvent *BACnetDevice::pevent1 = new epicsEvent;
epicsEvent *BACnetDevice::pevent2 = new epicsEvent;

BACnetDevice::BACnetDevice()
:name("NoName"), objId(), maxApduLengthAccepted(0), segmentationSupported(&BACnetEnumSegmentation::NO_SEGMENTATION),
 vendorId(0), addr(), transport(NULL), lock(), rcvQue(255, sizeof(void *)), whois(), rps(), rpmReq(NULL), wps(),
 TimeoutMilliseconds(DEFAULT_APDU_TIMEOUT), NumberOfRetries(DEFAULT_APDU_RETRIES), rpmBufferLimit(0),
 rpmDisable(false), bindStatus(UNBOUND), serviceSupStatus(UNINITIALIZED), rpmState(ZERO), invokeId(0),
 tx(0), rx(0), er(0)
{
	BACnetObjPropRef ref = BACnetObjPropRef(objId, BACnetEnumPropertyIdentifier::PROP_PROTOCOL_SERVICES_SUPPORTED);
	protoSvsSup = new BACnetVariable(BACnetEnumVarFunc::READ, ref, *this);

	this->tsmp = new TsmPool(255, TimeoutMilliseconds, NumberOfRetries, transport, *this);
	this->msgp = new MessagePool(255);
}

BACnetDevice::BACnetDevice(string const &devName, uint32_t devInst, string const &ifName, uint16_t devPort)
:name(devName), objId(BACnetEnumObjectType::OBJECT_DEVICE, devInst), maxApduLengthAccepted(0),
 segmentationSupported(&BACnetEnumSegmentation::NO_SEGMENTATION), vendorId(0), addr(), lock(), rcvQue(255, sizeof(void *)),
 whois(devInst), rps(), rpmReq(NULL), wps(), TimeoutMilliseconds(DEFAULT_APDU_TIMEOUT),
 NumberOfRetries(DEFAULT_APDU_RETRIES), rpmBufferLimit(0), rpmDisable(false), bindStatus(UNBOUND),
 serviceSupStatus(UNINITIALIZED), rpmState(ZERO), invokeId(0), tx(0), rx(0), er(0)
{
	BACnetObjPropRef ref = BACnetObjPropRef(objId, BACnetEnumPropertyIdentifier::PROP_PROTOCOL_SERVICES_SUPPORTED);
	protoSvsSup = new BACnetVariable(BACnetEnumVarFunc::READ, ref, *this);

	/** Add the device instance to the map*/
	registerInstance(devInst);

	registerEpicsName(devName);

	/** Create call connect implicitly.*/
	this->transport = BACnetConnection::create(ifName, devPort, 1);
	this->tsmp = new TsmPool(255, TimeoutMilliseconds, NumberOfRetries, transport, *this);
	this->msgp = new MessagePool(255);
}

BACnetDevice::~BACnetDevice() {
	//cout << "~BACnetDevice()" << endl;
	BACnetConnection::release(this->transport, 1);
	this->transport = NULL;

	delete protoSvsSup;
	delete tsmp;
	delete msgp;
	delete rpmReq;

	//delete rcvQue; //TODO Maybe Call delete on this? I didn't call 'new'

	std::list<BACnetVariable *>::iterator itr = vars.begin();
	while(itr != vars.end()) {
		if((*itr)) {
			delete (*itr);
		}
		itr++;
	}
}

void BACnetDevice::registerInstance(uint32_t devInst) {

	/** for printing errors...*/
	ostringstream errstr;

	std::map<uint32_t, BACnetDevice *>::iterator itrInst = instToDevMap.find(devInst);

	/** Check to see if the device instance has already been defined...*/
	if(itrInst != instToDevMap.end()) {
		errstr << " -> Error! BACnetDevice::registerInstance: Device instance \"" << devInst << "\" has already been added to map."  << endl;
		throw std::invalid_argument(errstr.str());
	}

	/** Return variable to hold the status of the map.insert */
	std::pair<std::map<uint32_t, BACnetDevice *>::iterator,bool> ret;

	/** Try to insert the map (key, value) */
	ret = instToDevMap.insert(std::pair<uint32_t, BACnetDevice *>(devInst, this));

	/** Check to see if map.insert succeeded.*/
	if(ret.second == false) {
		errstr << " -> Error! BACnetDevice::registerInstance: instToDevMap.insert Failed!" << endl;
		throw std::invalid_argument(errstr.str());
	}

}

void BACnetDevice::registerAddress(string devAddrStr) {

	/** for printing errors...*/
	ostringstream errstr;

	std::map<string, BACnetDevice *>::iterator itrAddr = addrToDevMap.find(devAddrStr);

	/** Check to see if the device instance has already been defined...*/
	if(itrAddr != addrToDevMap.end()) {
		errstr << " -> Error! BACnetDevice::registerAddress: Device address \"" << devAddrStr << "\" has already been added to map."  << endl;
		throw std::invalid_argument(errstr.str());
	}

	/** Return variable to hold the status of the map.insert */
	std::pair<std::map<string, BACnetDevice *>::iterator,bool> ret;

	/** Try to insert the map (key, value) */
	ret = addrToDevMap.insert(std::pair<string, BACnetDevice *>(devAddrStr, this));

	/** Check to see if map.insert succeeded.*/
	if(ret.second == false) {
		errstr << " -> Error! BACnetDevice::registerAddress: addrToDevMap.insert Failed!" << endl;
		throw std::invalid_argument(errstr.str());
	}

}

void BACnetDevice::registerEpicsName(string devNameStr) {

	/** for printing errors...*/
	ostringstream errstr;

	std::map<string, BACnetDevice *>::iterator itrAddr = nameToDevMap.find(devNameStr);

	/** Check to see if the device instance has already been defined...*/
	if(itrAddr != nameToDevMap.end()) {
		errstr << " -> Error! BACnetDevice::registerEpicsName: Device name \"" << devNameStr << "\" has already been added to map."  << endl;
		throw std::invalid_argument(errstr.str());
	}

	/** Return variable to hold the status of the map.insert */
	std::pair<std::map<string, BACnetDevice *>::iterator,bool> ret;

	/** Try to insert the map (key, value) */
	ret = nameToDevMap.insert(std::pair<string, BACnetDevice *>(devNameStr, this));

	/** Check to see if map.insert succeeded.*/
	if(ret.second == false) {
		errstr << " -> Error! BACnetDevice::registerEpicsName: addrToDevMap.insert Failed!" << endl;
		throw std::invalid_argument(errstr.str());
	}

}

void BACnetDevice::verifyDeviceName(string const namestr) {

	/** for printing errors...*/
	ostringstream errstr;

	/** Names must start with a letter and after that can contain numbers, dashes and underscores only.*/

	/** Check for empty name...*/
	if(namestr.length() == 0) {
		errstr << " -> Error! BACnetDevice::verifyDeviceName: Name parameter must not be empty!"  << endl;
		throw std::invalid_argument(errstr.str());
	}

	std::string::const_iterator it = namestr.begin();

	/** First character must be alphabetic */
	if(!isalpha((*it))) {
		errstr << " -> Error! BACnetDevice::verifyDeviceName: Name parameter must start with an alphabetic character!"  << endl;
		throw std::invalid_argument(errstr.str());
	}

	/** Next character, please...*/
	it++;

	/** The rest of the name can be letters, numbers, underscores ('_') and dashes ('-') only.*/
	while(it != namestr.end()) {

		if(!isalnum((*it))) {

			/** if it is not a letter or a number then it can only be a dash '-' or an underscore '_' as
			 * a separator. */
			if((*it) != '_' && (*it) != '-') {
				errstr << " -> Error! BACnetDevice::verifyDeviceName: Invalid character \'" << (*it) <<
						"\' in name parameter!"  << endl;
				errstr << "Names can only contain letters, numbers, underscores and dashes!" << endl;
				throw std::invalid_argument(errstr.str());
			}
		}
		it++;
	}

}

void BACnetDevice::decodeIamData(BACnetDeviceAddress const &srcAddr, BACnetIamService const &iAm) {

	this->lock.lock();

	this->addr.setAddressData(srcAddr);
	this->maxApduLengthAccepted = iAm.getMaxApduAccepted();
	this->segmentationSupported = iAm.getSegmentationSupported();
	this->vendorId = iAm.getVendorId();

	registerAddress(this->addr.getAddressAsString());

	this->bindStatus = BOUND;

	this->lock.unlock();
}

void BACnetDevice::makeGlobalBroadcastAddress(BACnetDeviceAddress &addr) const {
	addr.makeGlobalBroadcast(this->transport->getBroadcastAddress(NULL), this->transport->getPortAsHostByteOrder());

}

BACnetDeviceAddress const *BACnetDevice::getAddressData(void) const {
	return &this->addr;
}

string BACnetDevice::getDeviceName() const {
	return this->name;
}

uint32_t BACnetDevice::getDeviceInstanceId() const {
	return this->objId.getObjectInstance().get_instance();
}

uint16_t BACnetDevice::getDevicePort() const {
	return this->transport->getPortAsNetworkByteOrder();
}

uint32_t BACnetDevice::getMaxApduLengthAccepted(void) const {
	return this->maxApduLengthAccepted;
}

BACnetSegmentation const *BACnetDevice::getSegmentationSupported(void) const {
	return this->segmentationSupported;
}

uint16_t BACnetDevice::getVendorId(void) const {
	return this->vendorId;
}

int BACnetDevice::sendTo(BACnetBVLL &bip, BACnetDeviceAddress const &dest) const {
	return this->transport->sendBip(bip, dest);
}

int BACnetDevice::recvFrom(BACnetDeviceAddress &src, BACnetBuffer &buff) const {
	return this->transport->recvFrom(src, buff);
}

uint32_t BACnetDevice::getInstanceId(void) const {
	return this->objId.getObjectInstance().get_instance();
}

BACnetObjIdentifier const *BACnetDevice::getObjectId(void) const {
	return &this->objId;
}

bool BACnetDevice::isBound(void) const {
	return this->addr.isBound();
}

void BACnetDevice::bindAddress(void) {
	sendWhoIsReqGlobal();
}

void BACnetDevice::sendWhoIsReqGlobal(void) {

	/** The Destination Address*/
	BACnetDeviceAddress destAddr = BACnetDeviceAddress();

	/** Because this is a Global request we need to format the destination address to broadcast
	 * on ALL networks... */
	this->makeGlobalBroadcastAddress(destAddr);

	/** Create the source address. This is us, should be zero.empty.*/
	BACnetDeviceAddress srcAddr = BACnetDeviceAddress();

	/** -------- The Network Layer --------*/

	/** Create a Network Protocol Data Unit (NPDU) with an APDU (The whoIs...) attached.
	 * BACnetNpdu(source-address, destination-address, apdu, message-priority, data-expecting-reply);
	 * */
	BACnetNpdu npdu = BACnetNpdu(srcAddr, destAddr, &whois, &BACnetEnumMessagePriority::NORMAL, false);

	/** -------- The IP Layer --------*/

	/** Because this is a Global request we need a BROADCAST NPDU BVLL message*/
	BACnetBVLLOrigBcastNPDU bacNetIpMsg = BACnetBVLLOrigBcastNPDU(&npdu);


	/** Trying this new method of putting items to be sent on a queue...*/
	BACnetBuffer b;
	bacNetIpMsg.encode(b);

	Tsm *tsm = this->tsmp->createUnconfirmed(destAddr, npdu, whois, b);
	this->transport->sendTsm(tsm);
	bindStatus = WAITING_TO_BIND;
}

void BACnetDevice::sendReadPropProtocolServicesSupported(void) {

	uint8_t invokeId = 0;
	//rps.makeUnsegmentedRequest(invokeId, this->objId, BACnetEnumPropertyIdentifier::PROP_PROTOCOL_SERVICES_SUPPORTED);
	rps.makeUnsegmentedRequest(invokeId, protoSvsSup->getObjectPropertyReference());

	/** Create the source address. This is us, should be zero.empty.*/
	BACnetDeviceAddress srcAddr = BACnetDeviceAddress();

	/** Create a Network Protocol Data Unit (NPDU) with an APDU (The whoIs...) attached.
	 * BACnetNpdu(source-address, destination-address, apdu, message-priority, data-expecting-reply);
	 * */
	BACnetNpdu npdu = BACnetNpdu(srcAddr, addr, &rps, &BACnetEnumMessagePriority::NORMAL, true);

	/** -------- The IP Layer --------*/

	/** Because this is a Global request we need a BROADCAST NPDU BVLL message*/
	BACnetBvllOrigUnicastNpdu bip = BACnetBvllOrigUnicastNpdu(&npdu);

	BACnetBuffer b;
	bip.encode(b);

	Tsm *tsm = this->tsmp->createConfirmed(*protoSvsSup, invokeId, addr, npdu, rps, b);

	this->transport->sendTsm(tsm);
	this->serviceSupStatus = WAITING_FOR_REPLY;
}

BACnetConnection * const BACnetDevice::getTransport(void) const {
	return this->transport;
}

void BACnetDevice::report(void) const {

	stringstream ss;

	ss << "BACnet-Device Report for: \"" << this->name << "\" {" << endl;
	ss << "Device Info:" << endl;
	ss << " EPICS Name: " << this->name << endl;
	ss << " Object-Id: " << this->objId.getObjectType()->getName() << ":" << this->objId.getObjectInstance().get_instance() << endl;
	ss << " Max APDU Length Accepted: " << this->maxApduLengthAccepted << endl;
	ss << " Segmentation Supported: " << this->segmentationSupported->getName() << endl;
	ss << " Vendor-Id: " << this->vendorId << endl;

	ss << endl;

	ss << "Network Address Info:" << endl;
	ss << " IPv4 Address: " << this->getAddressData()->getIpAddressAsString() << ":"
			<< this->getAddressData()->getPortAsString() << endl;
	ss << " Remote Network: " << this->getAddressData()->getRemoteNetwork() << endl;
	ss << " Remote Address: " << this->getAddressData()->getRemoteAddressAsString() << endl;
	ss << "}" << endl << endl;;
	cout << ss.str();
}

BACnetDevice *BACnetDevice::create(string const &devName, uint32_t devInst, string const &ifName, uint16_t devPort) {

	/** for printing errors...*/
	ostringstream errstr;

	BACnetDevice *dev = NULL;

	/** Name string can't be empty or start with a number */
	BACnetDevice::verifyDeviceName(devName);

	dev = new BACnetDevice(devName, devInst, ifName, devPort);

	return dev;
}

BACnetDevice *BACnetDevice::findDeviceByInst(uint32_t devInst) {

	std::map<uint32_t, BACnetDevice *>::iterator itrInst = instToDevMap.find(devInst);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itrInst != instToDevMap.end()) {
		return itrInst->second;
	}
	return NULL;
}

BACnetDevice *BACnetDevice::findDeviceByAddress(BACnetDeviceAddress const &addr) {

	if(BACnet_verbosity > 1) {
		cout << "BACnetDevice::findDeviceByAddress: Looking for this: " << addr.getAddressAsString() << endl;
	}
	std::map<string, BACnetDevice *>::iterator itrInst = addrToDevMap.find(addr.getAddressAsString());

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itrInst != addrToDevMap.end()) {
		return itrInst->second;
	}

	return NULL;
}

BACnetDevice *BACnetDevice::findDeviceByName(string const &epicsName) {

	if(BACnet_verbosity > 1) {
		cout << "BACnetDevice::findDeviceByName: Looking for this: " << epicsName << endl;
	}
	std::map<string, BACnetDevice *>::iterator itrInst = nameToDevMap.find(epicsName);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itrInst != nameToDevMap.end()) {
		return itrInst->second;
	}

	return NULL;
}

size_t BACnetDevice::getInstMapSize(void) {
	return instToDevMap.size();
}

size_t BACnetDevice::getAddrMapSize(void) {
	return addrToDevMap.size();
}

instToDevMap_t const *BACnetDevice::getDeviceList(void) {
	return &BACnetDevice::instToDevMap;
}

void BACnetDevice::start(void) {

	epicsThreadCreate("processDevs", epicsThreadPriorityHigh, epicsThreadGetStackSize(epicsThreadStackMedium), &procDevListThread, NULL);
}

void BACnetDevice::stop(void) {

	pevent1->signal();
	pevent2->wait();

	instToDevMap_t::const_iterator itrInst = BACnetDevice::instToDevMap.begin();

	while(itrInst != BACnetDevice::instToDevMap.end()) {
		if((*itrInst).second) {
			delete (*itrInst).second;
		}
		itrInst++;
	}

	delete pevent1;
	delete pevent2;

}

void BACnetDevice::initialize(void) {

	instToDevMap_t::const_iterator itrInst = BACnetDevice::instToDevMap.begin();

	while(itrInst != BACnetDevice::instToDevMap.end()) {
		(*itrInst).second->initReadList();
		itrInst++;
	}

}

void BACnetDevice::procDevListThread(void *p) {

	instToDevMap_t::const_iterator itrInst;

	while(true) {
		if(pevent1->tryWait()) {
			cout << "Stopping Device thread..." << endl;
			pevent2->signal();
			return;
		}
		itrInst = BACnetDevice::instToDevMap.begin();
		while(itrInst != BACnetDevice::instToDevMap.end()) {
			try {
				(*itrInst).second->process();
			} catch (exception &e) {

				/** An error happened somewhere down below. Print it to the console and keep going.*/
				cout << "ERROR for device \"" << (*itrInst).second->getDeviceName() << "\" in method BACnetDevice::procDevListThread(void *p):" << endl;
				cout << e.what() << endl;
			}
			itrInst++;
		}
		epicsThreadSleep(0.01);
	}
}

void BACnetDevice::process(void) {

	if(BACnet_verbosity > 1) {
		cout << "This device, \"" << this->name << "\" is processing my things to do..." << endl;
	}

	MessageIn *msgIn = NULL;
	stringstream ss;

	/** See if there are any messages in the inbox first...*/
	while(rcvQue.pending() > 0) {
		rcvQue.receive(&msgIn, sizeof(void *), 0.1);

		//: do something with messageIn...
		if(msgIn) {
			incRx();
			try {
				processMessageIn(*msgIn);
			} catch (exception &e) {
				cout << "ERROR for device \"" << this->name << "\" in method BACnetDevice::process(void):" << endl;
				cout << e.what() << endl;
			}
			/** Whether pass or fail, free this message it will stay forever...*/
			this->msgp->freeMsg(msgIn);
		}
		else {
			cout << "ERROR for device \"" << this->name << "\" in method BACnetDevice::process(void):" << endl;
			cout << "rcvQue.pending() was greater than zero (0) but the message was NULL" << endl;
		}
	}

	if(!isBound() && bindStatus == UNBOUND) {
		bindAddress();
	}

	/** need to read 'BACnetEnumPropertyIdentifier::PROP_PROTOCOL_SERVICES_SUPPORTED' to figure out what
	 * BACnet services the device supports.*/
	if(bindStatus == BOUND && serviceSupStatus == UNINITIALIZED) {

		/** Read services supported*/
		sendReadPropProtocolServicesSupported();
	}

	if(bindStatus == BOUND && serviceSupStatus == INITIALIZED) {

		/** Do we have any variables defined from EPICS records?*/
		if(this->vars.size() > 0) {

			if(!this->rpmDisable &&
					isServiceSupported(BACnetEnumSvcSupChoice::SERVICE_SUPPORTED_READ_PROP_MULTIPLE)) {

				/** process multiple lists: RPM, RP and WP (Read-Property-Multiple, Read-Property and Write-Property)*/
				processRpmRpWp();
			}
			else {
				/** Process only RP and WP: Read-Property and Write-Property */
				processRpWp();
			}
		}
	}

	/** Process TSMs*/
	tsmp->process();
}

void BACnetDevice::queMsgIn(BACnetDeviceAddress &srcAddr, BACnetBuffer &buff)
{
	//MessageIn *msgIn = new MessageIn(srcAddr, buff);
	MessageIn *msgIn = this->msgp->create(srcAddr, buff);
	rcvQue.send(&msgIn, sizeof(void *));
}

void BACnetDevice::tsmApduTimeoutHandler(Tsm &tsm) {
	cout << "**** BACnetDevice::tsmApduTimeoutHandler: BACnet device: \"" << this->name << "\", Invoke-Id: \'" <<
			tsm.getInvokeId() << "\', Service Type: \"" << tsm.getApdu()->getServiceChoice()->getName() << "\"" <<
			endl << "Buffer Contents: " << endl << tsm.getBuffer().hex_dump() << endl;

	if(*tsm.getApdu()->getServiceChoice() == BACnetEnumUnconfirmedService::WHO_IS) {
		/** So the device never responded to our WHO-IS request... Where is it? Does it really exist?
		 * Set the devices bindStatus back to UNBOUND and let's keep sending WHO-IS until it responds
		 * or the user realizes that they made a mistake and removes this instance from the definition file*/
		this->bindStatus = UNBOUND;
	}
	cout << "Freeing TSM..." << endl << endl;
	this->tsmp->freeTsm(&tsm);
}

BACnetVariable const *BACnetDevice::registerObjectProperty(BACnetVarFuncChoice const &func,
		BACnetObjPropRef const &ref, BACnetApplicationDataTypeChoice const &dataType) {

	/** This constructor will create a variable with a data-type. Used for writing...*/
	BACnetVariable *var = new BACnetVariable(func, ref, dataType, *this);
	vars.push_back(var);
	return var;
}

BACnetVariable const *BACnetDevice::registerObjectProperty(BACnetVarFuncChoice const &func, BACnetObjPropRef const &ref) {

	/** This constructor will create a variable without a data-type. Used for reading...*/
	BACnetVariable *var = new BACnetVariable(func, ref, *this);
	vars.push_back(var);
	return var;
}

BACnetVariable const *BACnetDevice::registerObjectProperty(BACnetVarFuncChoice const &func,
		BACnetObjectType const &objTyp, uint32_t objInst, BACnetPropertyType const &propId, int arrayIndex) {

	BACnetObjPropRef ref = BACnetObjPropRef(objTyp, objInst, propId, arrayIndex);
	return registerObjectProperty(func, ref);
}

BACnetVariable const *BACnetDevice::registerObjectProperty(BACnetVarFuncChoice const &func,
		BACnetObjectType const &objTyp, uint32_t objInst, BACnetPropertyType const &propId) {

	/** -1 indicates that the optional array specifier was not given...*/
	return registerObjectProperty(func, objTyp, objInst, propId, -1);
}

void BACnetDevice::listVariables(void) {

	std::list<BACnetVariable *>::iterator it = vars.begin();
	while(it != vars.end()) {
		cout << "list: " << (*it)->getObjectType().getName() << ":" <<
				(*it)->getObjectInstance() << endl;
		it++;
	}

}

void BACnetDevice::sendReadPropertyReq(uint8_t invokeId, BACnetVariable &var) {

	rps.makeUnsegmentedRequest(invokeId, var.getObjectPropertyReference());

	/** Create the source address. This is us, should be zero.empty.*/
	BACnetDeviceAddress srcAddr = BACnetDeviceAddress();

	/** Create a Network Protocol Data Unit (NPDU) with an APDU (The whoIs...) attached.
	 * BACnetNpdu(source-address, destination-address, apdu, message-priority, data-expecting-reply);
	 * */
	BACnetNpdu npdu = BACnetNpdu(srcAddr, addr, &rps, &BACnetEnumMessagePriority::NORMAL, true);

	/** -------- The IP Layer --------*/

	/** Because this is a Global request we need a BROADCAST NPDU BVLL message*/
	BACnetBvllOrigUnicastNpdu bip = BACnetBvllOrigUnicastNpdu(&npdu);

	BACnetBuffer b;
	bip.encode(b);

	Tsm *tsm = this->tsmp->createConfirmed(var, invokeId, addr, npdu, rps, b);

	this->transport->sendTsm(tsm);
}

void BACnetDevice::sendReadPropertyMult(uint8_t invokeId, const std::list<BACnetVariable *> &rpmLst) {

	rpmReq->makeUnsegmentedRequest(invokeId, rpmLst);

	/** Create the source address. This is us, should be zero.empty.*/
	BACnetDeviceAddress srcAddr = BACnetDeviceAddress();

	/** Create a Network Protocol Data Unit (NPDU) with an APDU (The whoIs...) attached.
	 * BACnetNpdu(source-address, destination-address, apdu, message-priority, data-expecting-reply);
	 * */
	BACnetNpdu npdu = BACnetNpdu(srcAddr, addr, rpmReq, &BACnetEnumMessagePriority::NORMAL, true);

	/** -------- The IP Layer --------*/

	/** Because this is a Global request we need a BROADCAST NPDU BVLL message*/
	BACnetBvllOrigUnicastNpdu bip = BACnetBvllOrigUnicastNpdu(&npdu);

	BACnetBuffer b;
	bip.encode(b);

	Tsm *tsm = this->tsmp->createConfirmed(rpmLst, invokeId, addr, npdu, *rpmReq, b);

	this->transport->sendTsm(tsm);
}

void BACnetDevice::sendWritePropertyReq(uint8_t invokeId, BACnetVariable &var) {

	propValList_t mylist = var.getPropValList();

	BACnetAppDataType *appData = (*mylist.begin());

	wps.makeUnsegmentedRequest(invokeId, var.getObjectPropertyReference(), appData);

	/** Create the source address. This is us, should be zero.empty.*/
	BACnetDeviceAddress srcAddr = BACnetDeviceAddress();

	/** Create a Network Protocol Data Unit (NPDU) with an APDU (The whoIs...) attached.
	 * BACnetNpdu(source-address, destination-address, apdu, message-priority, data-expecting-reply);
	 * */
	BACnetNpdu npdu = BACnetNpdu(srcAddr, addr, &wps, &BACnetEnumMessagePriority::NORMAL, true);

	/** -------- The IP Layer --------*/

	/** Because this is a Global request we need a BROADCAST NPDU BVLL message*/
	BACnetBvllOrigUnicastNpdu bip = BACnetBvllOrigUnicastNpdu(&npdu);

	BACnetBuffer b;
	bip.encode(b);

	Tsm *tsm = this->tsmp->createConfirmed(var, invokeId, addr, npdu, wps, b);

	this->transport->sendTsm(tsm);
}

ListOfBacVarList_t::const_iterator &BACnetDevice::processRpm(ListOfBacVarList_t::const_iterator &itr) {

	/** Before we can send another read/write command, we need to make sure that our last
	 * read/write command has been acknowledged. So check this some how. Only thing I know
	 * to do is to check the TSM Pool and see if there are any outstanding TSMs*/

	if(this->tsmp->getActiveListSize()) {
		if(BACnet_verbosity > 1) {
			cout << this->name << ":processVariables: Can't process because there is an active TSM" << endl;
		}
		return itr;
	}

	sendReadPropertyMult(requestInvokeId(), (*itr));

	return ++itr;
}

BACnetVariableList_t::const_iterator &BACnetDevice::processRp(BACnetVariableList_t::const_iterator &itr) {

	/** Before we can send another read/write command, we need to make sure that our last
	 * read/write command has been acknowledged. So check this some how. Only thing I know
	 * to do is to check the TSM Pool and see if there are any outstanding TSMs*/

	if(this->tsmp->getActiveListSize()) {
		if(BACnet_verbosity > 1) {
			cout << this->name << ":processVariables: Can't process because there is an active TSM" << endl;
		}
		return itr;
	}

	sendReadPropertyReq(requestInvokeId(), *(*itr));

	return ++itr;
}

BACnetVariableList_t::const_iterator &BACnetDevice::processWp(BACnetVariableList_t::const_iterator &itr) {

	/** Before we can send another read/write command, we need to make sure that our last
	 * read/write command has been acknowledged. So check this some how. Only thing I know
	 * to do is to check the TSM Pool and see if there are any outstanding TSMs*/

	if(this->tsmp->getActiveListSize()) {
		if(BACnet_verbosity > 1) {
			cout << this->name << ":processVariables: Can't process because there is an active TSM" << endl;
		}
		return itr;
	}

	if((*itr)->getDoWrite()) {
		sendWritePropertyReq(requestInvokeId(), *(*itr));
		(*itr)->clearWriteFlag();
	}

	return ++itr;
}

void BACnetDevice::processRpmRpWp(void) {

	/**
	 * This is a sequence; walk thru each state.
	 * */

	/** Initialize the read-iterator */
	if(rpmState == ZERO) {
		readIter = varReadList.begin();
		rpmState = ONE;
	}

	/** Do that first-pass "thang" to get all of the data-types. When firstPass() has iterated
	 * thru all of the readList elements then it changes rpmState to TWO to signal to build
	 * the Read-Property-Multiple list(s)*/
	if(rpmState == ONE) {
		readIter = firstPass(readIter);
		if(readIter == varReadList.end()) {
			rpmState = TWO;
		}
	}

	if(rpmState == TWO) {
		/** Build the RPM-List */
		createRpmList(varReadList, listOfRpmLists);
		rpmState = THREE;
	}
	if(rpmState == THREE) {
		/** Encode and send the RPM-List */
		if(this->rpmReq == NULL) {
			this->rpmReq = new BACnetRpmReq();
		}

		/** Main list: which is a list of lists*/
		listOfRpmListsItr = listOfRpmLists.begin();

		rpmState = FOUR;
	}
	if(rpmState == FOUR) {

		if(listOfRpmListsItr != listOfRpmLists.end()) {
			listOfRpmListsItr = processRpm(listOfRpmListsItr);
		}
		else {
			/** Setup for next state...*/
			rpmState = FIVE;
			readIter = varReadList.begin();
		}
	}
	if(rpmState == FIVE) {
		if(readIter != varReadList.end()) {
			readIter = processRp(readIter);
		}
		else {
			/** Setup for next state...*/
			rpmState = SIX;
			wpIter = varWriteList.begin();
		}
	}
	if(rpmState == SIX) {
		if(wpIter != varWriteList.end()) {
			wpIter = processWp(wpIter);
		}
		else {
			/** Setup for next state... Go back and process RPMs*/
			rpmState = FOUR;
			listOfRpmListsItr = listOfRpmLists.begin();
		}
	}
}

void BACnetDevice::processRpWp(void) {

	/**
	 * This is a sequence; walk thru each state.
	 * */

	if(rpmState == ZERO) {
		rpmState = FIVE;
		readIter = varReadList.begin();
	}
	if(rpmState == FIVE) {
		if(readIter != varReadList.end()) {
			readIter = processRp(readIter);
		}
		else {
			/** Setup for next state...*/
			rpmState = SIX;
			wpIter = varWriteList.begin();
		}
	}
	if(rpmState == SIX) {
		if(wpIter != varWriteList.end()) {
			wpIter = processWp(wpIter);
		}
		else {
			/** Setup for next state... Go back and process RPMs*/
			rpmState = FIVE;
			readIter = varReadList.begin();
		}
	}
}

void BACnetDevice::incTx(void) {
	this->tx++;
}

void BACnetDevice::incRx(void) {
	this->rx++;
}

void BACnetDevice::incEr(void) {
	this->er++;
}

uint8_t BACnetDevice::requestInvokeId(void) {
	if(invokeId == 0) {
		invokeId++;
	}
	return invokeId++;
}

void BACnetDevice::processMessageIn(MessageIn &msgIn) {

	/** copy the contents of the source address and the buffer from the MessageIn class
	 * to the independent classes*/
	BACnetDeviceAddress &addr = msgIn.getAddress();
	BACnetBuffer &buff = msgIn.getBuffer();

	/** TODO: Maybe check that the network address is valid? and not 0.0.0.0*/

	if(BACnet_verbosity > 1) {
		cout << this->name << ": I have a message in my inbox" << endl;
	}

	/** Get a peek at the first octet... it determines where we go from here...*/
	uint8_t const *peekOct = buff.getReadPointer();

	/** Get the PDU-Type */
	BACnetPDUChoice const &PDU_CHOICE = BACnetEnumPDUChoice::getEnumByValue((*peekOct++) >> 4);

	/** I will support BACnetEnumPDUChoice::ERROR*/
	if(PDU_CHOICE == BACnetEnumPDUChoice::ERROR) {
		/** Hide all the decoding in this method...*/
		bacnetErrorHandler(buff);
	}

	/** I will support BACnetEnumPDUChoice::COMPLEX_ACK*/
	if(PDU_CHOICE == BACnetEnumPDUChoice::COMPLEX_ACK) {

		/** Hide all the decoding in this method...*/
		complexAckHandler(buff);
	}

	/** I will support BACnetEnumPDUChoice::SIMPLE_ACK*/
	if(PDU_CHOICE == BACnetEnumPDUChoice::SIMPLE_ACK) {
		simpleAckHandler(buff);
	}

	/** I will support BACnetEnumPDUChoice::UNCONFIRMED_REQUEST*/
	if(PDU_CHOICE == BACnetEnumPDUChoice::UNCONFIRMED_REQUEST) {

		/** Entering this handler pointing to PDU-TYPE */
		unconfirmedReqHandler(buff, addr);
	}

	/** Finished with the message now free it*/
	this->msgp->freeMsg(&msgIn);
}

void BACnetDevice::bacnetErrorHandler(BACnetBuffer &buff) {

	incEr();

	BACnetErrorPdu errPdu;
	errPdu.decode(buff);
	BACnetVariable *bVar = NULL;

	/** Find TSM by invoke-Id and see if this is a reply to one of our requests...*/
	Tsm *tsm = this->tsmp->findByInvokeId(errPdu.getInvokeId());

	if(tsm) {
		bVar = tsm->getCallbackVariable();
		if(bVar) {
			bVar->setError(errPdu);
			this->tsmp->freeTsm(tsm);
		}
	}
}

void BACnetDevice::unconfirmedReqHandler(BACnetBuffer &buff, BACnetDeviceAddress &addr) {

	/** As of right now we enter this method with a pointer to PDU-TYPE. */
	uint8_t const *peekOct = buff.getReadPointer();

	/** So increment the pointer to the next octet which is the service type octet.*/
	peekOct++;

	BACnetUnconfirmedServiceChoice const &UNCONF_CHOICE = BACnetEnumUnconfirmedService::getEnumByValue((*peekOct++));

	/** I will support BACnetEnumUnconfirmedService::I_AM */
	if(UNCONF_CHOICE == BACnetEnumUnconfirmedService::I_AM) {
		iAmAckHandler(buff, addr);
	}
}

void BACnetDevice::iAmAckHandler(BACnetBuffer &buff, BACnetDeviceAddress &addr) {

	/** Decode I-AM */
	BACnetIamService iam;
	iam.decode(buff);

	/** See if this I-AM message is a response to a WHO-IS request that we sent out or
	 * if this is just an unsolicited I-AM message from the device. */
	Tsm *tsm = tsmp->findWhoIs(iam.getObjectIstance());

	/** If this is an I-AM response to our WHO-IS request then free the TSM*/
	if(tsm) {
		decodeIamData(addr, iam);
		tsmp->freeTsm(tsm);
	}
	else {
		/** This I-AM is unsolicited... Devices can send these on power-ups sometimes, so this could
		 * be from a power-up or someone could have changed the device's MAC, so we better see if
		 * this devices MAC-ID has changed and reload it if so. */
		decodeIamData(addr, iam);
	}
}

void BACnetDevice::simpleAckHandler(BACnetBuffer &buff) {

	/** First octet should be pointing to the PDU-TYPE. We've already verified that,
	 * that is how we got here... so skip it! */
	buff.get_ui8();

	/** Next octet must be invoke-id*/
	uint8_t const INVOKE_ID = buff.get_ui8();

	/** Find TSM by invoke-Id and see if this is a reply to one of our requests...*/
	Tsm *tsm = this->tsmp->findByInvokeId(INVOKE_ID);

	if(tsm) {

		/** Ok. This appears to be a reply to one of our requests... Maybe do further checking or
		 * just accept it? */

		/** Decode the SIMPLE_ACK */

		/** Move to next octet to see what the service type is...*/
		BACnetEnumSingle const &MSG_SVC_CHOICE = BACnetEnumConfSvc::getEnumByValue(buff.get_ui8());

		stringstream ss;
		if(tsm->getApdu()->getPduType() == NULL) {
			ss << "ERROR! BACnetDevice::simpleAckHandler(BACnetBuffer &buff): Service-Choice parameter of "
					"Tsm with Invoke-Id (" << (unsigned int) INVOKE_ID << ") is NULL and therefore can't match"
							" up the response with the request." << endl;
			throw std::invalid_argument(ss.str());
		}

		BACnetEnumSingle const &TSM_SVC_CHOICE = *tsm->getApdu()->getServiceChoice();

		/** If the response's invoke-id matches our request's invoke-id AND the response's service-choice
		 * matches our request's service-choice then this is indeed a response to our request so free the Tsm.*/
		if(MSG_SVC_CHOICE == TSM_SVC_CHOICE) {
			this->tsmp->freeTsm(tsm);
		}
		else {
			ss << "ERROR! BACnetDevice::simpleAckHandler(BACnetBuffer &buff): The BACnet-SimpleACK with "
					"Invoke-Id (" << (unsigned int) INVOKE_ID << ") found a matching Tsm, by Invoke-Id, "
							"but the Service-Choice parameters do not match." << endl;
			ss << "ERROR! BACnet-SimpleACK Service-Choice = \"" << MSG_SVC_CHOICE.getName() << "\", " <<
					"Tsm Service-Choice = \"" << TSM_SVC_CHOICE.getName() << "\"" << endl;
			throw std::invalid_argument(ss.str());
		}
	}
	else {
		/** Tsm couldn't be found so this message must not be meant for us...*/
	}
}

void BACnetDevice::complexAckHandler(BACnetBuffer &buff) {

	BACnetComplexAck cak;
	cak.decode(buff);

	stringstream ss;
	if(cak.getServiceChoice() == NULL) {
		ss << "ERROR! BACnetDevice::complexAckHandler(BACnetBuffer &buff): Service-Choice parameter of "
				"complex acknowledge class is NULL" << endl;
		throw std::invalid_argument(ss.str());
	}

	BACnetConfSvcChoice const &CONF_SVC_CHOICE = *cak.getServiceChoice();

	if(CONF_SVC_CHOICE == BACnetEnumConfSvc::READ_PROPERTY) {
		readPropertyAckHandler(buff, cak);
	}

	if(CONF_SVC_CHOICE == BACnetEnumConfSvc::READ_PROP_MULTIPLE) {
		readPropMultAckHandler(buff, cak);
	}

}

void BACnetDevice::readPropertyAckHandler(BACnetBuffer &buff, BACnetComplexAck &cak) {

	/** See if this invoke-id matches one of our request invoke-ids. If not then discard.*/

	/** Find TSM by invoke-Id and see if this is a reply to one of our requests...*/
	Tsm *tsm = this->tsmp->findByInvokeId(cak.getInvokeId());

	if(tsm) {

		BACnetReadPropAck rpack;
		rpack.decode(buff);


		BACnetVariable *var = tsm->getCallbackVariable();

		if(var) {
			var->decode(rpack.getAppDataList());

			if(BACnet_verbosity > 1) {
				var->printData();
			}

			/** Special case to handle our local copy of ProtocolServicesSupported */
			if(var == this->protoSvsSup) {
				/** Temporary flag just to signify second step in startup...*/
				serviceSupStatus = INITIALIZED;
			}

			this->tsmp->freeTsm(tsm);
		}
		else {
			stringstream ss;
			if(cak.getServiceChoice() == NULL) {
				ss << "ERROR! BACnetDevice::readPropertyAckHandler(BACnetBuffer &buff, BACnetComplexAck &cak): "
						"BACnetVariable returned from Tsm::getCallbackVariable() is NULL" << endl;
				throw std::invalid_argument(ss.str());
			}
		}
	}
	else {
		/** Tsm couldn't be found so this message must not be meant for us...*/
	}
}

void BACnetDevice::readPropMultAckHandler(BACnetBuffer &buff, BACnetComplexAck &cak) {

	stringstream ss;

	/** See if this invoke-id matches one of our request invoke-ids. If not then discard.*/

	/** Find TSM by invoke-Id and see if this is a reply to one of our requests...*/
	Tsm *tsm = this->tsmp->findByInvokeId(cak.getInvokeId());


	if(tsm) {

		/** Decode the Read-Property-Multiple Ack.*/
		BACnetRpmAck rpmack;
		rpmack.decode(buff);

		/**
		 * Get the correct RPM-Variable-List that was linked to the request.
		 * This makes a local copy of the list... could just use pointer to actual list but not sure yet.
		 * */
		const BACnetVariableList_t rpmvarlist = *tsm->getRpmCallbackVariable();

		/** Get an iterator so we can walk thru the list*/
		BACnetVariableList_t::const_iterator rpmvarItr = rpmvarlist.begin();

		/** The number of property-values returned in the read-property-multiple response MUST match
		 * the number of properties in the request. */
		if(rpmvarlist.size() != rpmack.getNumberOfResultItems()) {
			ss << "ERROR! BACnetDevice::readPropMultAckHandler: Size mismatch! The number of properties returned "
					"in the Read-Property-Multiple result does not match the number of properties in the "
					"Read-Property-Multiple request." << endl;
			ss << "Number of properties requested: " << rpmvarlist.size() <<
					", Number of properties returned: " << rpmack.getNumberOfResultItems() << endl;
			throw std::invalid_argument(ss.str());
		}

		/**
		 * Iterate over the object-identifiers and properties associated with the object-identifiers.
		 * Each object-identifier can have multiple properties associated with it. See the example below.
		 * The RPM Request-1 has a total of 6-properties. So, the response must have a total of 6-properties, too.
		 * And the response's order of properties must match the order of the request.
		 *
		 *Example: Read-Property-Multiple Request-1	|	Example: Read-Property-Multiple Response-1
		 *											|
		 * Object-id: ANALOG-INPUT-01				|	Object-id:	ANALOG-INPUT-01
		 * 		Property:	OUT_OF_SERVICE			|		The value for property: OUT_OF_SERVICE
		 * 		Property:	PRESENT_VALUE			|		The value for property: PRESENT_VALUE
		 * 		Property:	STATUS_FLAGS			|		The value for property: STATUS_FLAGS
		 * 		Property:	UNITS					|		The value for property: UNITS
		 *											|
		 * Object-id: ANALOG-OUTPUT-01				|	Object-id:	ANALOG-OUTPUT-01
		 * 		Property:	PRESENT_VALUE			|		The value for property: PRESENT_VALUE
		 * 		Property:	PRIORITY_ARRAY [16]		|		The value for property: PRIORITY_ARRAY [16]
		 *
		 * */

		rpmResultList_t::const_iterator rsltItr = rpmack.getIteratorToResultBegin();
		rpmResultList_t::const_iterator rsltEnd = rpmack.getIteratorToResultEnd();

		while(rpmvarItr != rpmvarlist.end() && rsltItr != rsltEnd) {

			/** Could be lots of properties for a single object-identifier... so get an iterator
			 * to the list of properties. */
			propRefValLst_t::const_iterator propListItr = (*rsltItr).getPropRefValueListBegin();
			propRefValLst_t::const_iterator propListEnd = (*rsltItr).getPropRefValueListEnd();

			appDataList_t::const_iterator propValue;/* = (*propListItr).getDataListEnd();*/

			/** Now iterate thru all of the properties in the response and decode them into the BACnetVariable */
			while(rpmvarItr != rpmvarlist.end() && propListItr != propListEnd) {

				/** Verify that the object and property identifiers match between the request and the result. */
				verifyRpmResult(*(*rpmvarItr), (*rsltItr).getObjectId(),
						*(*propListItr).getPropertyId(), (*propListItr).getArrayIndex());

				propValue = (*propListItr).getDataListBegin();

				if(propValue == (*propListItr).getDataListEnd()) {
					ss << "ERROR! BACnetDevice::readPropMultAckHandler(...): The property-value returned for ";

					ss << "Object-Identifier: " << (*rpmvarItr)->getObjectIdentifier().getObjectName() <<
							":" << (*rpmvarItr)->getObjectIdentifier().getObjectInstanceAsUint32_t() <<
							", Property-Identifier: " << (*rpmvarItr)->getObjectProperty().getName() <<
							"is not present! " << endl;
					throw std::invalid_argument(ss.str());
				}

				/** Decode the property-value from the response into the matching/requesting BACnetVariable.*/
				(*rpmvarItr)->decode((*propValue));

				/** Increment the iterators to the next property-value*/
				rpmvarItr++;
				propListItr++;
			}
			/** Increment the iterators object-identifier */
			rsltItr++;
		}

		this->tsmp->freeTsm(tsm);

	}
	else {
		/** Tsm couldn't be found so this message must not be meant for us...*/
	}
}

void BACnetDevice::verifyRpmResult(const BACnetVariable &bacVar, const BACnetObjIdentifier &objId,
		const BACnetPropertyType &propId, int arrayIndx) {

	stringstream ss;

	/** The BACnetVariable object-identifier and the result object-identifier must equal*/
	if(bacVar.getObjectIdentifier() != objId) {
		ss << "ERROR! BACnetDevice::readPropMultAckHandler(...):"
				" The Object-Identifier for the Read-Property-Multiple request"
				" and for what is being decoded in the Read-Property-Multiple result do not match" << endl;

		ss << "BACnetVariable: Object-Identifier: " << bacVar.getObjectIdentifier().getObjectName() <<
				":" << bacVar.getObjectIdentifier().getObjectInstanceAsUint32_t() << endl;

		ss << "RPM-Result: " << objId.getObjectName() << ":" << objId.getObjectInstanceAsUint32_t() << endl;
		throw std::invalid_argument(ss.str());
	}
	if(bacVar.getObjectProperty() != propId) {
		ss << "ERROR! BACnetDevice::BACnetDevice::readPropMultAckHandler(...):"
				" The Property-Identifier for the Read-Property-Multiple request"
				" and for what is being decoded in the Read-Property-Multiple result do not match" << endl;

		ss << "BACnetVariable: Object-Identifier: " << bacVar.getObjectIdentifier().getObjectName() <<
				":" << bacVar.getObjectIdentifier().getObjectInstanceAsUint32_t() <<
				", Property-Identifier: " << bacVar.getObjectProperty().getName() << endl;

		ss << "RPM-Result: " << objId.getObjectName() << ":" << objId.getObjectInstanceAsUint32_t() <<
				", Property-Identifier: " << propId.getName() << endl;
		throw std::invalid_argument(ss.str());
	}
	/** Array-Index is an optional parameter. Have to check against the sentinal to see
	 * if it exists or not...*/
	if(bacVar.getArrayIndex() > (-1)) {
		if(bacVar.getArrayIndex() != arrayIndx) {
			ss << "ERROR! BACnetDevice::BACnetDevice::readPropMultAckHandler(...):"
					" The Property-Array-Index for the Read-Property-Multiple request"
					" and for what is being decoded in the Read-Property-Multiple result do not match" << endl;

			ss << "BACnetVariable: Object-Identifier: " << bacVar.getObjectIdentifier().getObjectName() <<
					":" << bacVar.getObjectIdentifier().getObjectInstanceAsUint32_t() <<
					", Property-Identifier: " << bacVar.getObjectProperty().getName() <<
					", Array-Index: " << bacVar.getArrayIndex() << endl;

			ss << "RPM-Result: " << objId.getObjectName() << ":" << objId.getObjectInstanceAsUint32_t() <<
					", Property-Identifier: " << propId.getName() <<
					", Array-Index: " << arrayIndx << endl;
			throw std::invalid_argument(ss.str());
		}
	}
}

void BACnetDevice::initReadList(void) {

	std::list<BACnetVariable *>::const_iterator itr = vars.begin();

	while(itr != vars.end()) {

		if((*itr)->getVariableFunction() == BACnetEnumVarFunc::READ) {
			varReadList.push_back((*itr));
		}
		else if((*itr)->getVariableFunction() == BACnetEnumVarFunc::WRITE) {
			varWriteList.push_back((*itr));
		}
		itr++;
	}

	/** Now sort the list by object type...AI=0, AO=1, AV=2, etc. */
	varReadList.sort(sortVarsByObjIdProp);

}

bool BACnetDevice::isServiceSupported(BACnetSvcSupChoice const &bacService) const {

	if(this->protoSvsSup) {

		propValList_t::const_iterator itr = protoSvsSup->getPropValList().begin();

		ProtocolSvcSupported *pssup = dynamic_cast<ProtocolSvcSupported *>((*itr));

		if(pssup) {
			return pssup->checkBit(bacService.getValue());
		}
	}

	return false;
}

bool BACnetDevice::sortVarsByObjIdProp(const BACnetVariable *first, const BACnetVariable *second) {

	return first->getObjectPropertyReference() < second->getObjectPropertyReference();
}

void BACnetDevice::listDevices(void) {

	ostringstream oss;
	bool tmpBool = false;

	instToDevMap_t::const_iterator itr = instToDevMap.begin();

	oss << endl;

	while(itr != instToDevMap.end()) {

		oss << (*itr).second->name << " {"<< endl;

		oss << " BACnet Instance: " << (*itr).second->objId.getObjectInstanceAsUint32_t() << endl;
		oss << " Network Address: ";

		if((*itr).second->isBound()) {
			oss << (*itr).second->addr.getAddressAsString() << "  //[ip-address]:[port]:[remote-network]:[network-address]";
		}
		else {
			oss << "UNBOUND";
		}

		oss << endl;

		oss << " Maximum-APDU-Length Accepted: " << (*itr).second->maxApduLengthAccepted << endl;

		oss << " Services Supported: {";
		tmpBool = (*itr).second->isServiceSupported(BACnetEnumSvcSupChoice::SERVICE_SUPPORTED_READ_PROPERTY);
		oss << "Read-Property(" << (tmpBool ? "TRUE" : "FALSE") << "), ";

		tmpBool = (*itr).second->isServiceSupported(BACnetEnumSvcSupChoice::SERVICE_SUPPORTED_READ_PROP_MULTIPLE);
		oss << "Read-Property-Multiple(" << (tmpBool ? "TRUE" : "FALSE") << "), ";

		tmpBool = (*itr).second->isServiceSupported(BACnetEnumSvcSupChoice::SERVICE_SUPPORTED_WRITE_PROPERTY);
		oss << "Write-Property(" << (tmpBool ? "TRUE" : "FALSE") << "), ";

		tmpBool = (*itr).second->isServiceSupported(BACnetEnumSvcSupChoice::SERVICE_SUPPORTED_WHO_IS);
		oss << "Who-Is(" << (tmpBool ? "TRUE" : "FALSE") << "), ";

		tmpBool = (*itr).second->isServiceSupported(BACnetEnumSvcSupChoice::SERVICE_SUPPORTED_I_AM);
		oss << "I-AM(" << (tmpBool ? "TRUE" : "FALSE") << ")}";

		oss << endl;

		oss << " Network Statistics: Tx: " << (*itr).second->tx << ", Rx: " << (*itr).second->rx <<
				", Err: " << (*itr).second->er << endl;

		oss << "}" << endl;

		cout << oss.str() << endl;

		itr++;
		oss.str("");
		oss.clear();
	}

}

BACnetVariableList_t::const_iterator &BACnetDevice::firstPass(BACnetVariableList_t::const_iterator &itr) {

	/** We should not ever get to this point. Once end is reached we change the RPM-state and we should
	 * never return to this.*/
	if(itr == varReadList.end()) {
		return itr;
	}

	/** Before we can send another read/write command, we need to make sure that our last
	 * read/write command has been acknowledged. So check this some how. Only thing I know
	 * to do is to check the TSM Pool and see if there are any outstanding TSMs*/

	if(this->tsmp->getActiveListSize()) {
		if(BACnet_verbosity > 1) {
			cout << this->name << ":processVariables: Can't process because there is an active TSM" << endl;
		}
		return itr;
	}

	uint8_t ivkId = requestInvokeId();

	sendReadPropertyReq(ivkId, *(*itr));

	return ++itr;
}

void BACnetDevice::createRpmList(BACnetVariableList_t &listIn, ListOfBacVarList_t &listOut) {

	/** All the stuff I roughly know about...*/
	const int _BVLL = 4;
	const int _CMPLX_ACK = 5;		//TODO: 5 is worse case, could get closer on actual size...

	/** Minimum length is 2 octets: One octet for the protocol version, and one octet for the control octet*/
	int _NPDU = 2;

	if(this->addr.getRemoteNetwork() > 0) {
		/** 2-Octets for network number*/
		_NPDU += 2;

		/** 1-Octet for SLEN*/
		_NPDU += 1;

		/** SADR*/
		_NPDU += this->addr.getRemoteNetworkAddressLength();
	}

	/** Should be starting around 30 bytes long*/
	size_t len = _BVLL + _NPDU + _CMPLX_ACK;

	/**
	 * Table 6-1. Maximum NPDU Lengths When Routing Through Different BACnet Data Link Layers
	 * |------------------------------------------------------------------------------------|
	 * |				Data Link Technology			|		Maximum NPDU Length			|
	 * |------------------------------------------------|-----------------------------------|
	 * |ISO 8802-3 ("Ethernet"), as defined in Clause 7	|			1497 octets				|
	 * |ARCNET, as defined in Clause 8					|			501 octets				|
	 * |MS/TP, as defined in Clause 9					|			501 octets				|
	 * |Point-To-Point, as defined in Clause 10			|			501 octets				|
	 * |LonTalk, as defined in Clause 11				|			228 octets				|
	 * |BACnet/IP, as defined in Annex J				|			1497 octets				|
	 * |ZigBee, as defined in Annex O					|			501 octets				|
	 *---------------------------------------------------------------------------------------
	 *
	 * */

	size_t _MYLIMIT = 0;

	if(this->rpmBufferLimit > 0) {
		_MYLIMIT = this->rpmBufferLimit;
	}
	else {
		/** is this an MSTP link? If so there is around a 500-byte limit on MSTP networks.*/
		if(this->addr.getRemoteNetworkAddressLength() > 0) {
			/** Trimming 10% for unexpected sizes/growth.*/
			_MYLIMIT = (std::min(this->maxApduLengthAccepted, (uint32_t) 501) * 0.90);
		}
		else {
			/** Set the limit to 90% of the max APDU length that the device can accept*/
			_MYLIMIT = this->maxApduLengthAccepted * 0.90;
		}
	}

	int appDataSize = 0;
	int tempSize = 0;

	/** ListId is only used for the console output/report so the viewer can distinguish between multiple lists.*/
	int listId = 1;

	const BACnetApplicationDataTypeChoice *dataT = NULL;
	const BACnetObjPropRef *opRef = NULL;
	const BACnetPropertyType *prop = NULL;

	std::list<BACnetVariable *>::iterator listInItr = listIn.begin();
	std::list<BACnetVariable *> tmpList;

	while(listInItr != listIn.end()) {

		tempSize = 0;
		appDataSize = 0;

		if((*listInItr)->hasDataInPropValList()) {

			opRef = &(*listInItr)->getObjectPropertyReference();
			dataT = (*listInItr)->getAppDataType();
			prop = opRef->getPropertyId();

			if(isRpmType(*dataT, *prop, appDataSize)) {

				/** Context-Tag [0] object-identifier is 4-bytes, plus tag*/
				tempSize += 5;

				/** Context-Tag [1] a pair of opening and closing tags ([1E] & [1F]) to hold the whole sequence
				 * [1E] marks the beginning of the listOfResults and [1F] marks the end of the listOfResults.*/
				tempSize += 2;

				/** Context-Tag [2] a property-identifier, plus its tag */
				tempSize += prop->getLength() + 1;

				/** Context-Tag [3] an optional array-index, plus its tag, if present*/
				if((*listInItr)->hasArrayIndex()) {
					tempSize += 2;
				}

				/** Context-Tag [4] a pair of opening and closing tags ([4E] & [4F]) to hold the whole sequence
				 * [4E] marks the beginning of the readResult and [4F] marks the end of the readResult.*/
				tempSize += 2;

				if((len + tempSize + appDataSize) < _MYLIMIT) {

					tmpList.push_back((*listInItr));

					/** The following statement advances/increments the iterator.*/
					listInItr = listIn.erase(listInItr);

					len += tempSize + appDataSize;

					/** check the next variable, because if it is the same object-identifier but different property
					 * then it needs to be accounted for here.
					 *
					 * Note: itr has already advanced to the next variable with the .erase() method. Make sure we did not
					 * reach the end of our list...
					 * */

					if(listInItr != listIn.end()) {
						/** Loop thru contiguous properties of the same object-identifier
						 * The BACnetVariables have already been sorted in void initReadList(void),
						 * so same object-ids should be grouped together.
						 * */

						while((*listInItr)->getObjectIdentifier() == opRef->getObjectId()) {

							if((*listInItr)->hasDataInPropValList()) {

								appDataSize = 0;
								tempSize = 0;

								opRef = &(*listInItr)->getObjectPropertyReference();
								dataT = (*listInItr)->getAppDataType();
								prop = opRef->getPropertyId();

								if(isRpmType(*dataT, *prop, appDataSize)) {

									/** Context-Tag [2] a property-identifier, plus its tag */
									tempSize = prop->getLength() + 1;

									/** Context-Tag [3] an optional array-index, plus its tag, if present*/
									if((*listInItr)->hasArrayIndex()) {
										tempSize += 2;
									}

									/** Context-Tag [4] a pair of opening and closing tags ([4E] & [4F]) to hold the whole sequence
									 * [4E] marks the beginning of the readResult and [4F] marks the end of the readResult.*/
									tempSize += 2;

									if((len + tempSize + appDataSize) < _MYLIMIT) {

										tmpList.push_back((*listInItr));
										listInItr = listIn.erase(listInItr);
										len += tempSize + appDataSize;

										/** Check for list.end() since we incremented the iterator with the list.erase() function.*/
										if(listInItr == listIn.end()) {
											/** Just break out of this inner while loop...*/
											break;
										}
									}
									else {
										/**
										 * Starting a new list... TODO: Maybe limit the number of lists that can be created
										 * just in case this gets stuck in a loop and never exits.
										 * */

										ostringstream oss;
										oss << "FYI! BACnetDevice::createRpmList(void): Has created a new RPM-List!"
												" However, an additional list is required for the remaining properties,"
												" creating it now..." << endl;

										oss << "RPM-List Details {" << endl;
										oss << " Device Name: \"" << this->name << "\"" << endl;
										oss << " List-Id: " << listId++ << endl;

										oss << " len: " << len << endl;
										oss << " tempSize: " << tempSize << endl;
										oss << " appDataSize: " << appDataSize << endl;
										oss << " _MYLIMIT: " << _MYLIMIT << endl;
										oss << " tmpList.size(): " << tmpList.size() << endl;
										oss << " tmpList Contents {" << endl;

										std::list<BACnetVariable *>::iterator tIt = tmpList.begin();
										int i = 0;
										while(tIt != tmpList.end()) {
											oss << "  [" << i++ << "] " << (*tIt)->getObjectType().getName() << ":";
											oss << (*tIt)->getObjectInstance() << ":";
											oss << (*tIt)->getObjectProperty().getName() << endl;
											tIt++;
										}
										oss << " }" << endl;
										oss << " listOut.size(): " << listOut.size() << endl;
										oss << "}" << endl << endl;

										cout << oss.str();

										listOut.push_back(tmpList);
										tmpList.clear();
										len = _BVLL + _NPDU + _CMPLX_ACK;
										tempSize = 0;
										appDataSize = 0;
									}
								}
								else {
									listInItr++;
								}
							}
							else {
								listInItr++;
							}
						} /** while((*listInItr)->getObjectIdentifier() == opRef->getObjectId()) {*/

					} /** if(listInItr != listIn.end()) {*/
				} /** if((len + tempSize + appDataSize) < _MYLIMIT) {*/
				else {
					/**
					 *
					 * */

					ostringstream oss;
					oss << "FYI! BACnetDevice::createRpmList(void): Has created a new RPM-List!"
							" However, an additional list is required for the remaining properties,"
							" creating it now..." << endl;

					oss << "RPM-List Details {" << endl;
					oss << " Device Name: \"" << this->name << "\"" << endl;
					oss << " List-Id: " << listId++ << endl;

					oss << " len: " << len << endl;
					oss << " tempSize: " << tempSize << endl;
					oss << " appDataSize: " << appDataSize << endl;
					oss << " _MYLIMIT: " << _MYLIMIT << endl;
					oss << " tmpList.size(): " << tmpList.size() << endl;
					oss << " tmpList Contents {" << endl;

					std::list<BACnetVariable *>::iterator tIt = tmpList.begin();
					int i = 0;
					while(tIt != tmpList.end()) {
						oss << "  [" << i++ << "] " << (*tIt)->getObjectType().getName() << ":";
						oss << (*tIt)->getObjectInstance() << ":";
						oss << (*tIt)->getObjectProperty().getName() << endl;
						tIt++;
					}
					oss << " }" << endl;
					oss << " listOut.size(): " << listOut.size() << endl;
					oss << "}" << endl << endl;

					cout << oss.str();

					listOut.push_back(tmpList); ///
					tmpList.clear(); ///
					len = _BVLL + _NPDU + _CMPLX_ACK;
					tempSize = 0;
					appDataSize = 0;
					//listInItr++;
				}
			} /** if(isRpmType(*dataT, *prop, appDataSize)) {*/
			else {
				listInItr++;
			}
		} /** if((*listInItr)->hasDataInPropValList()) {*/
		else {
			listInItr++;
		}
	}

	ostringstream oss;
	oss << "FYI! BACnetDevice::createRpmList(void): Has created a new RPM-List! No more lists are required!" << endl;
	oss << "RPM-List Details {" << endl;
	oss << " Device Name: \"" << this->name << "\"" << endl;
	oss << " List-Id: " << listId << endl;

	oss << " len: " << len << endl;
	oss << " _MYLIMIT: " << _MYLIMIT << endl;
	oss << " tmpList.size(): " << tmpList.size() << endl;
	oss << " tmpList Contents {" << endl;

	std::list<BACnetVariable *>::iterator tIt = tmpList.begin();
	int i = 0;
	while(tIt != tmpList.end()) {
		oss << "  [" << i++ << "] " << (*tIt)->getObjectType().getName() << ":";
		oss << (*tIt)->getObjectInstance() << ":";
		oss << (*tIt)->getObjectProperty().getName() << endl;
		tIt++;
	}
	oss << " }" << endl;
	oss << " listOut.size(): " << listOut.size() << endl;
	oss << "}" << endl << endl;

	cout << oss.str();
	if(tmpList.size() > 0) {
		listOut.push_back(tmpList);
	}
}

bool BACnetDevice::isRpmType(const BACnetApplicationDataTypeChoice &dataT,
		const BACnetPropertyType &prop, int &dataSize) {

	if(dataT == BACnetEnumApplicationDataType::BOOLEAN) {
		/** Length is just the tag. The boolean value is encoded into the tag-LVT*/
		dataSize = 1;
		return true;
	}
	if(dataT == BACnetEnumApplicationDataType::UNSIGNED_INTEGER) {
		/** Worse case is 4-bytes long, plus the tag*/
		dataSize = 5;
		return true;
	}
	if(dataT == BACnetEnumApplicationDataType::SIGNED_INTEGER) {
		/** Worse case is 4-bytes long, plus the tag*/
		dataSize = 5;
		return true;
	}
	if(dataT == BACnetEnumApplicationDataType::REAL) {
		/** 4-bytes long, plus the tag*/
		dataSize = 5;
		return true;
	}
	if(dataT == BACnetEnumApplicationDataType::DOUBLE) {
		/** 8-bytes long, plus the tag*/
		dataSize = 9;
		return true;
	}
	if(dataT == BACnetEnumApplicationDataType::OCTET_STRING) {
		/** Not gonna support this yet because it seems like it is not
		 * a fixed size and can grow, so how could I guarantee not to
		 * go over the MAX-APDU length?*/
		dataSize = 0;
		return false;
	}
	if(dataT == BACnetEnumApplicationDataType::CHARACTER_STRING) {
		/** Not gonna support this yet because it seems like it is not
		 * a fixed size and can grow, so how could I guarantee not to
		 * go over the MAX-APDU length?*/
		dataSize = 0;
		return false;
	}
	if(dataT == BACnetEnumApplicationDataType::BIT_STRING) {
		/** Not gonna support this yet because it seems like it is not
		 * a fixed size and can grow, so how could I guarantee not to
		 * go over the MAX-APDU length?*/

		/** Unless this is a PROP_STATUS_FLAGS property then I will support it*/
		if(prop == BACnetEnumPropertyIdentifier::PROP_STATUS_FLAGS) {
			dataSize = 2;
			return true;
		}
		dataSize = 0;
		return false;
	}
	if(dataT == BACnetEnumApplicationDataType::ENUMERATED) {
		/** Worse case is 4-bytes long, plus the tag*/
		dataSize = 5;
		return true;
	}
	if(dataT == BACnetEnumApplicationDataType::DATE) {
		/** is 4-bytes long, plus the tag*/
		dataSize = 5;
		return true;
	}
	if(dataT == BACnetEnumApplicationDataType::TIME) {
		/** is 4-bytes long, plus the tag*/
		dataSize = 5;
		return true;
	}
	if(dataT == BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER) {
		/** is 4-bytes long, plus the tag*/
		dataSize = 5;
		return true;
	}

	dataSize = 0;
	return false;
}

void BACnetDevice::setIocShArgs(const string &argStr) {

	/** parse the args into a list.*/
	std::list<bacIocShArgs> shArgLst = parseIocShArgs(argStr);

	/** Get an iterator to the list of args */
	std::list<bacIocShArgs>::const_iterator itr = shArgLst.begin();

	while(itr != shArgLst.end()) {

		if((*itr).argName == "apdu_timeout") {
			setApduTimeout((*itr).argValue);
		}
		else if((*itr).argName == "apdu_retries") {
			setApduRetries((*itr).argValue);
		}
		else if((*itr).argName == "rpm_buffer_limit") {
			setRpmBufferLimit((*itr).argValue);
		}
		else if((*itr).argName == "rpm_disable") {
			setRpmDisable((*itr).argValue);
		}
		else {
			cout << "ERROR! BACnetDevice::setIocShArgs: Unsupported argument name: \"" << (*itr).argName << "\"" << endl;
		}

		itr++;
	}
}

void BACnetDevice::setApduTimeout(const string &strVal) {

	stringstream ss;
	uint32_t oldValue = this->TimeoutMilliseconds;

	try {

		uint32_t nuValue = strToUint32(strVal);
		if(nuValue < DEFAULT_APDU_TIMEOUT) {
			ss << "The value for APDU-Timeout must not be less than the default value of \'" <<
					DEFAULT_APDU_TIMEOUT << "\'" << endl;
			throw std::invalid_argument(ss.str());
		}

		this->TimeoutMilliseconds = nuValue;
		this->tsmp->setApduTimeout(this->TimeoutMilliseconds);

		cout << "APDU Timeout was changed successfully for device \"" << this->name << "\"" << endl;
		cout << "Old APDU Timeout: \"" << oldValue << "\"" << endl;
		cout << "New APDU Timeout: \"" << (unsigned int) this->TimeoutMilliseconds << "\"" << endl;
	} catch (exception &e) {
		cout << "ERROR! BACnetDevice::setApduTimeout: " << e.what() << endl;
		cout << "Old APDU Timeout: \"" << oldValue << "\"" << endl;
		cout << "New APDU Timeout: \"" << (unsigned int) this->TimeoutMilliseconds << "\"" << endl;
	}
}

void BACnetDevice::setApduRetries(const string &strVal) {

	stringstream ss;
	uint32_t oldValue = this->NumberOfRetries;

	try {

		uint32_t nuValue = strToUint32(strVal);
		if(nuValue < DEFAULT_APDU_RETRIES) {
			ss << "The value for APDU-Retry-count must not be less than the default value of \'" <<
					DEFAULT_APDU_RETRIES << "\'" << endl;
			throw std::invalid_argument(ss.str());
		}

		this->NumberOfRetries = nuValue;
		this->tsmp->setApduRetries(this->NumberOfRetries);

		cout << "APDU Retry Count was changed successfully for device \"" << this->name << "\"" << endl;
		cout << "Old APDU Retry Count: \"" << oldValue << "\"" << endl;
		cout << "New APDU Retry Count: \"" << (unsigned int) this->NumberOfRetries << "\"" << endl;
	} catch (exception &e) {
		cout << "ERROR! BACnetDevice::setApduRetries: " << e.what() << endl;
		cout << "Old APDU Retry Count: \"" << oldValue << "\"" << endl;
		cout << "New APDU Retry Count: \"" << (unsigned int) this->NumberOfRetries << "\"" << endl;
	}
}

void BACnetDevice::setRpmBufferLimit(const string &strVal) {
	uint32_t oldValue = this->rpmBufferLimit;
	try {
		this->rpmBufferLimit = strToUint32(strVal);
		cout << "RPM Buffer Limit was changed successfully for device \"" << this->name << "\"" << endl;
		cout << "Old RPM Buffer Limit: \"" << oldValue << "\"" << endl;
		cout << "New RPM Buffer Limit: \"" << (unsigned int) this->rpmBufferLimit << "\"" << endl;
	} catch (exception &e) {
		cout << "ERROR! BACnetDevice::setRpmBufferLimit: " << e.what() << endl;
		cout << "Old RPM Buffer Limit: \"" << oldValue << "\"" << endl;
		cout << "New RPM Buffer Limit: \"" << (unsigned int) this->rpmBufferLimit << "\"" << endl;
	}
}

void BACnetDevice::setRpmDisable(const string &strVal) {
	bool oldValue = this->rpmDisable;
	if(strVal[0] == 't' || strVal[0] == 'T' || strVal[0] == '1') {
		this->rpmDisable = true;
	}
	else {
		this->rpmDisable = false;
	}
	cout << "RPM-Disable was changed successfully for device \"" << this->name << "\"" << endl;
	cout << "Old RPM-Disable Value: \"" << (oldValue ? "TRUE" : "FALSE") << "\"" << endl;
	cout << "New RPM-Disable Value: \"" << (this->rpmDisable ? "TRUE" : "FALSE") << "\"" << endl;

}

uint32_t BACnetDevice::getTx(void) const {
	return this->tx;
}

uint32_t BACnetDevice::getRx(void) const {
	return this->rx;
}

uint32_t BACnetDevice::getEr(void) const {
	return this->er;
}





