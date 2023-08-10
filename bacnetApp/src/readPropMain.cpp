/*
 * readPropMain.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: 8w4
 */

#include <iostream>
#include <string>
#include <stdint.h>
#include <list>

#include "BACnetStringUtil.h"
#include "BACnetConnection.h"
#include "BACnetWhoIsService.h"
#include "BACnetNpdu.h"
#include "BACnetDeviceAddress.h"
#include "BACnetBVLLOrigBcastNPDU.h"
#include "BACnetBvllOrigUnicastNpdu.h"
#include "BACnetBuffer.h"
#include "BACnetIamService.h"
#include "BACnetReadPropertyService.h"
#include "BACnetComplexAck.h"
#include "BACnetReadPropAck.h"
#include "BACnetNull.h"
#include "BACnetBoolean.h"
#include "BACnetUnsignedInt.h"
#include "BACnetSignedInt.h"
#include "BACnetReal.h"
#include "BACnetDouble.h"
#include "BACnetOctetString.h"
#include "BACnetCharacterString.h"
#include "BACnetBitString.h"
#include "BACnetEnumerated.h"
#include "BACnetDate.h"
#include "BACnetTime.h"
#include "BACnetAppObjId.h"

using namespace std;

#define DEFAULT_PORT 0xBAC0
#define DEFAULT_IFACE "eth0"

static BACnetConnection *con = NULL;

class BacSmDev {
public:

	BacSmDev();
	BacSmDev(const BacSmDev &dev);
	virtual ~BacSmDev();

	uint32_t getInstanceAsUint32() const;
	BACnetDeviceAddress getAddress() const;
	void decode(const BACnetDeviceAddress &srcAddr, BACnetBuffer &buff);
	string toString(void);

private:
	BACnetDeviceAddress addr;
	BACnetObjIdentifier objectId;
	uint32_t maxApduLengthAccepted;
	BACnetSegmentation const *segmentationSupported;
	uint16_t vendorId;
};

BacSmDev::BacSmDev()
: addr(), objectId(), maxApduLengthAccepted(0), segmentationSupported(0), vendorId(0)
{

}

BacSmDev::BacSmDev(const BacSmDev &dev)
: addr(dev.addr), objectId(dev.objectId), maxApduLengthAccepted(dev.maxApduLengthAccepted),
  segmentationSupported(dev.segmentationSupported), vendorId(dev.vendorId)
{

}

BacSmDev::~BacSmDev() {
	this->segmentationSupported = NULL;
}

uint32_t BacSmDev::getInstanceAsUint32() const {

	return this->objectId.getObjectInstanceAsUint32_t();

}

BACnetDeviceAddress BacSmDev::getAddress() const {
	return this->addr;
}

void BacSmDev::decode(const BACnetDeviceAddress &srcAddr, BACnetBuffer &buff) {
	this->addr = srcAddr;

	/** Decode I-AM */
	BACnetIamService iam;
	iam.decode(buff);

	this->addr.setAddressData(srcAddr);
	this->objectId = *iam.getObjectId();
	this->maxApduLengthAccepted = iam.getMaxApduAccepted();
	this->segmentationSupported = iam.getSegmentationSupported();
	this->vendorId = iam.getVendorId();

}

string BacSmDev::toString(void) {

	stringstream ss;

	ss << this->objectId.getObjectName() << "-" << this->objectId.getObjectInstanceAsUint32_t() << " {" << endl;
	ss << " Network Address: " << this->addr.getAddressAsString() << endl;
	ss << " Object-Identifier: " << this->objectId.getObjectName() << ":" << this->objectId.getObjectInstanceAsUint32_t() << endl;
	ss << " Max APDU Length Accepted: " << this->maxApduLengthAccepted << endl;
	ss << " Segmentation Supported: " << this->segmentationSupported->getName() << endl;
	ss << " Vendor-Identifier: " << this->vendorId << endl;
	ss << "}" << endl;

	return ss.str();
}

class apduWrapper {
public:

	apduWrapper();
	virtual ~apduWrapper();

	const BACnetPDUChoice *getPduType(void);
	BACnetComplexAck &getComplextAck(void);
	BACnetErrorPdu &getBACnetError(void);

	BACnetComplexAck &decodeCmplxAck(BACnetBuffer &buff);
	BACnetErrorPdu &decodeBACnetError(BACnetBuffer &buff);


private:
	BACnetComplexAck cak;
	BACnetErrorPdu errpdu;

	const BACnetPDUChoice *pduType;
};

apduWrapper::apduWrapper()
: cak(), errpdu(), pduType(NULL)
{

}

apduWrapper::~apduWrapper() {

}

const BACnetPDUChoice *apduWrapper::getPduType() {
	return this->pduType;
}

BACnetComplexAck &apduWrapper::getComplextAck() {
	return this->cak;
}

BACnetErrorPdu &apduWrapper::getBACnetError() {
	return this->errpdu;
}

BACnetComplexAck &apduWrapper::decodeCmplxAck(BACnetBuffer &buff) {
	this->cak.decode(buff);
	this->pduType = &BACnetEnumPDUChoice::COMPLEX_ACK;
	return this->cak;
}

BACnetErrorPdu &apduWrapper::decodeBACnetError(BACnetBuffer &buff) {
	this->errpdu.decode(buff);
	this->pduType = &BACnetEnumPDUChoice::ERROR;
	return this->errpdu;
}


bool getIfaceParm(std::list<string> &inpl, string &iface) {

	stringstream ss;
	std::list<string>::iterator itr = inpl.begin();

	/** Look for and strip out the switch-parameters first*/
	while(itr != inpl.end()) {

		if((*itr).compare("-i") == 0) {
			/** Check for at least two parameters... I.e., the switch and the value...*/
			if(std::distance(itr, inpl.end()) < 2) {
				cout << "There is an \"i\" switch but no parameters following..." << endl;
				return false;
			}
			itr = inpl.erase(itr); // The -i
			ss << (*itr);
			itr = inpl.erase(itr); // The iface
			ss >> iface;
			return true;
		}
		itr++;
	}
	return false;
}

bool getPortParm(std::list<string> &inpl, int &port) {

	stringstream ss;
	std::list<string>::iterator itr = inpl.begin();

	/** Look for and strip out the switch-parameters first*/
	while(itr != inpl.end()) {

		if((*itr).compare("-p") == 0) {
			/** Check for at least two parameters... I.e., the switch and the value...*/
			if(std::distance(itr, inpl.end()) < 2) {
				cout << "There is an \"p\" switch but no parameters following..." << endl;
				return false;
			}
			itr = inpl.erase(itr); // The -p
			ss << (*itr);
			itr = inpl.erase(itr); // The port
			ss >> port;
			return true;
		}
		itr++;
	}
	return false;
}

// ./readprop [-i "eth0"] [-p 47808] devId objTyp objInst objProp [arrIndx]
int getInputParm(const std::list<string> &inpl, string &iface, int &port, int &devInst,
		int &objTyp, int &objInst, int &objProp, int &arrIndx) {

	int n = inpl.size();

	std::list<string> tempList = inpl;

	/** Look for and strip out the switch-parameters first*/
	getIfaceParm(tempList, iface);
	getPortParm(tempList, port);

	/** Now get the mandatory parameters: device-instance, object-type, object-instance, object-property,
	 * and optional array index.*/

	if(tempList.size() < 4) {
		cout << "ERROR! Not enough input parameters supplied." << endl;
		return -1;
	}

	stringstream ss;
	std::list<string>::iterator itr = tempList.begin();
	itr = tempList.begin();

	/** Device Instance...*/
	ss << (*itr++);
	ss >> devInst;
	ss << "";
	ss.clear();

	/** Object Type...*/
	ss << (*itr++);
	ss >> objTyp;
	ss << "";
	ss.clear();

	/** Object Instance...*/
	ss << (*itr++);
	ss >> objInst;
	ss << "";
	ss.clear();

	/** Object Property...*/
	ss << (*itr++);
	ss >> objProp;
	ss << "";
	ss.clear();

	if(itr == tempList.end()) {
		return n;
	}

	/** Property Array-Index...*/
	if((*itr).size() < 3) {
		cout << "ERROR! Not enough characters for array-index format... "
				"Array-Index must be enclosed with a left \'[\' and right \']\'" << endl;
		return -1;
	}

	if((*itr).at(0) != '[') {
		cout << "ERROR! Array-Index must be enclosed with a left \'[\' and right \']\'" << endl;
		return -1;
	}

	arrIndx = parse_array_element(*itr);

	return n;
}

void sendWhoIs(const int remNet, const int lowInst, const int highInst) {

	BACnetWhoIsService whois = BACnetWhoIsService(lowInst, highInst);


	/** The Destination Address*/
	BACnetDeviceAddress destAddr = BACnetDeviceAddress();

	if(con == NULL) {
		cout << "ERROR! sendWhoIs(...): Connection is NULL" << endl;
		throw;
	}

	con->getBroadcastAddress(destAddr);
	destAddr.setIpPortAs_htons(con->getPortAsHostByteOrder());

	if(remNet > (-1)) {
		destAddr.setRemoteNetwork(remNet);
	}
	else
		destAddr.setRemoteNetwork(0xFFFF);	//TODO Handle the local, global and remote broadcast better than this.

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

	con->sendBuffer(b, destAddr);

}

BacSmDev *getDevice(int devInstance) {

	sendWhoIs(-1, devInstance, devInstance);

	if(con == NULL) {
		throw;
	}

	/** Wait at least 5-seconds for a reply all the replies to succeed...*/
	time_t start_time = time(NULL);
	time_t current_time = time(NULL);
	const double timeout = 5.0;

	BACnetDeviceAddress srcAddr;
	BACnetBuffer buff;
	BacSmDev *pDev = NULL;

	while((current_time-start_time) < timeout) {

		int bytes = con->recvFrom(srcAddr, buff);

		if(bytes > 0) {
			start_time = time(NULL);

			/** Only Handle I-AM messages */

			/** Get a peek at the first octet... it determines where we go from here...*/
			uint8_t const *peekOct = buff.getReadPointer();

			try {
				/** Get the PDU-Type */
				BACnetPDUChoice const &PDU_CHOICE = BACnetEnumPDUChoice::getEnumByValue((*peekOct++) >> 4);

				/** I will support BACnetEnumPDUChoice::UNCONFIRMED_REQUEST*/
				if(PDU_CHOICE == BACnetEnumPDUChoice::UNCONFIRMED_REQUEST) {

					BACnetUnconfirmedServiceChoice const &UNCONF_CHOICE = BACnetEnumUnconfirmedService::getEnumByValue((*peekOct++));

					/** I will support BACnetEnumUnconfirmedService::I_AM */
					if(UNCONF_CHOICE == BACnetEnumUnconfirmedService::I_AM) {
						BacSmDev dev;
						dev.decode(srcAddr, buff);

						/** See if this is actually the device we are looking for... Check the instance
						 * sent and returned...*/
						if(dev.getInstanceAsUint32() == (uint32_t) devInstance) {
							pDev = new BacSmDev(dev);
							return pDev;
						}
					}
				}
			} catch (exception &e) {
				cout << e.what() << endl;
			}
		}
		current_time = time(NULL);
		srcAddr.clear();
		buff.clear_buffer();
	}
	return pDev;
}

void sendReadProperty(const BacSmDev &dev, const BACnetObjPropRef &objPropRef, const uint8_t invkId) {
	BACnetReadPropertyService rps;
	rps.makeUnsegmentedRequest(invkId, objPropRef);

	/** Create the source address. This is us, should be zero.empty.*/
	BACnetDeviceAddress srcAddr = BACnetDeviceAddress();
	BACnetDeviceAddress destAddr = dev.getAddress();

	/** Create a Network Protocol Data Unit (NPDU) with an APDU (The whoIs...) attached.
	 * BACnetNpdu(source-address, destination-address, apdu, message-priority, data-expecting-reply);
	 * */
	BACnetNpdu npdu = BACnetNpdu(srcAddr, destAddr, &rps, &BACnetEnumMessagePriority::NORMAL, true);

	/** -------- The IP Layer --------*/

	/** Because this is a Global request we need a BROADCAST NPDU BVLL message*/
	BACnetBvllOrigUnicastNpdu bip = BACnetBvllOrigUnicastNpdu(&npdu);

	BACnetBuffer b;
	bip.encode(b);
	con->sendBuffer(b, destAddr);
}

void bacnetErrorHandler(BACnetBuffer &buff, apduWrapper &wrapper) {

	BACnetErrorPdu &errPdu = wrapper.decodeBACnetError(buff);

	stringstream ss;

	ss << "BACnet-Error Returned!" << endl << endl;
	ss << "BACnet-Error PDU {" << endl;
	ss << " Invoke ID: \'" << (unsigned int) errPdu.getInvokeId() << "\'" << endl;
	ss << " Service Choice: \'" << errPdu.getErrorChoice()->getName() << "\'" << endl;
	ss << " Error Class: \'" << errPdu.getErrorClass()->getName() << "\'" << endl;
	ss << " Error Code: \'" << errPdu.getErrorCode()->getName() << "\'" << endl;
	ss << "}" << endl;
	cout << ss.str() << endl;
}

void processMessageIn(BACnetBuffer &buff, apduWrapper &wrapper) {

	/** Get a peek at the first octet... it determines where we go from here...*/
	uint8_t const *peekOct = buff.getReadPointer();

	/** Get the PDU-Type */
	BACnetPDUChoice const &PDU_CHOICE = BACnetEnumPDUChoice::getEnumByValue((*peekOct++) >> 4);

	/** I will support BACnetEnumPDUChoice::ERROR*/
	if(PDU_CHOICE == BACnetEnumPDUChoice::ERROR) {
		/** Hide all the decoding in this method...*/
		wrapper.decodeBACnetError(buff);
		//bacnetErrorHandler(buff, wrapper);
	}

	/** I will support BACnetEnumPDUChoice::COMPLEX_ACK*/
	if(PDU_CHOICE == BACnetEnumPDUChoice::COMPLEX_ACK) {
		/** Hide all the decoding in this method...*/
		wrapper.decodeCmplxAck(buff);
		//complexAckHandler(buff, wrapper);
	}
}

BACnetAppDataType *createDataType(BACnetApplicationDataTypeChoice const *dataType) {

	BACnetAppDataType *pv = NULL;

	if(dataType) {

		if(*dataType == BACnetEnumApplicationDataType::NNULL) {

			/** Static Null*/
			pv = BACnetNull::Null;
		}
		if(*dataType == BACnetEnumApplicationDataType::BOOLEAN) {
			pv = new BACnetBoolean();
		}
		if(*dataType == BACnetEnumApplicationDataType::UNSIGNED_INTEGER) {
			pv = new BACnetUnsignedInt();
		}
		if(*dataType == BACnetEnumApplicationDataType::SIGNED_INTEGER) {
			pv = new BACnetSignedInt();
		}
		if(*dataType == BACnetEnumApplicationDataType::REAL) {
			pv = new BACnetReal();
		}
		if(*dataType == BACnetEnumApplicationDataType::DOUBLE) {
			pv = new BACnetDouble();
		}
		if(*dataType == BACnetEnumApplicationDataType::OCTET_STRING) {
			pv = new BACnetOctetString();
		}
		if(*dataType == BACnetEnumApplicationDataType::CHARACTER_STRING) {
			pv = new BACnetCharacterString();
		}
		if(*dataType == BACnetEnumApplicationDataType::BIT_STRING) {
			pv = new BACnetBitString();
		}
		if(*dataType == BACnetEnumApplicationDataType::ENUMERATED) {
			pv = new BACnetEnumerated();
		}
		if(*dataType == BACnetEnumApplicationDataType::DATE) {
			pv = new BACnetDate();
		}
		if(*dataType == BACnetEnumApplicationDataType::TIME) {
			pv = new BACnetTime();
		}
		if(*dataType == BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER) {
			pv = new BACnetAppObjId();
		}
	}

	return pv;

}

std::list<BACnetAppDataType *> *getProperty(const BacSmDev &dev, const BACnetObjPropRef &objPropRef) {

	uint8_t invkId = 1;
	sendReadProperty(dev, objPropRef, invkId);

	/** Wait at least 5-seconds for a reply all the replies to succeed...*/
	time_t start_time = time(NULL);
	time_t current_time = time(NULL);
	const double timeout = 5.0;

	BACnetDeviceAddress srcAddr;
	BACnetBuffer buff;
	std::list<BACnetAppDataType *> *pvAppDataTypLst = NULL;

	while((current_time-start_time) < timeout) {

		int bytes = con->recvFrom(srcAddr, buff);


		/** Are there any bytes in the buffer?*/
		if(bytes > 0) {
			/** Is this our device that we assume we are talking to?*/
			if(srcAddr == dev.getAddress()) {
				/** If this is our device, then is this the reply that we expect from our request?*/

				apduWrapper awrap;
				processMessageIn(buff, awrap);

				if(awrap.getPduType() != NULL) {
					if(awrap.getPduType() == &BACnetEnumPDUChoice::COMPLEX_ACK) {
						BACnetComplexAck &cak = awrap.getComplextAck();
						/** Ok, if this is a reply from our device then does the invoke-id in this reply
						 * match the invoke-id of our request?*/
						if(cak.getInvokeId() == invkId) {
							if(cak.getServiceChoice() == &BACnetEnumConfSvc::READ_PROPERTY) {
								BACnetReadPropAck rpack;
								rpack.decode(buff);

								/** Get a copy of the data or list of data...*/
								appDataList_t x = rpack.getAppDataList();
								appDataList_t::iterator itr = x.begin();
								BACnetAppDataType *pv = NULL;

								/** Iterate thru the datalist and create the appropriate BACnet Data-Types...*/
								while(itr != x.end()) {
									pv = createDataType((*itr).getAppDataType());
									if(pv) {
										pv->decode((*itr));
										if(pvAppDataTypLst == NULL) {
											pvAppDataTypLst = new std::list<BACnetAppDataType *>();
										}
										pvAppDataTypLst->push_back(pv);
									}
									itr++;
								}
								return pvAppDataTypLst;
							}
						}
					}
					else if(awrap.getPduType() == &BACnetEnumPDUChoice::ERROR) {
						BACnetErrorPdu &errPdu = awrap.getBACnetError();

						stringstream ss;

						ss << "BACnet-Error Returned!" << endl << endl;
						ss << "BACnet-Error PDU {" << endl;
						ss << " Invoke ID: \'" << (unsigned int) errPdu.getInvokeId() << "\'" << endl;
						ss << " Service Choice: \'" << errPdu.getErrorChoice()->getName() << "\'" << endl;
						ss << " Error Class: \'" << errPdu.getErrorClass()->getName() << "\'" << endl;
						ss << " Error Code: \'" << errPdu.getErrorCode()->getName() << "\'" << endl;
						ss << "}" << endl;
						cout << ss.str() << endl;
						return NULL;
					}
				}
			}
		}
		current_time = time(NULL);
	}
	return pvAppDataTypLst;
}

void printPriorityArray(BACnetObjPropRef &objPropRef, std::list<BACnetAppDataType *> *myList) {
	stringstream ss;

	if(objPropRef.getArrayIndex() == (-1) && myList->size() == 16) {
		ss << objPropRef.getPropertyId()->getName() << " {" << endl;

		std::list<BACnetAppDataType *>::iterator itr = myList->begin();
		for(int i=0; i<16; i++, itr++) {
			ss << " [" << i+1 << "] = \'" << (*itr)->getValAsStr() << "\'" << endl;
		}
		ss << "}" << endl;
	}
	else {
		ss << objPropRef.getPropertyId()->getName() << "[" <<
				objPropRef.getArrayIndex() << "]: \'" << (*myList->begin())->getValAsStr() << "\'" << endl;
	}

	cout << ss.str();
}

void printListData(BACnetObjPropRef &objPropRef, std::list<BACnetAppDataType *> *myList) {

	stringstream ss;

	std::list<BACnetAppDataType *>::iterator itr = myList->begin();

	ss << objPropRef.getPropertyId()->getName() << " {" << endl;

	while(itr != myList->end()) {
		ss << " (" << (std::distance(myList->begin(), itr) + 1) <<
				") " << (*itr)->getDataType().getName() << ": \'" << (*itr)->getValAsStr() << "\'" << endl;
		itr++;
	}

	ss << "}" << endl;
	cout << ss.str();
}

void printData(BACnetObjPropRef &objPropRef, std::list<BACnetAppDataType *> *myList) {

	if(objPropRef.getPropertyId() == &BACnetEnumPropertyIdentifier::PROP_PRIORITY_ARRAY) {
		printPriorityArray(objPropRef, myList);
	}
	else if(myList->size() > 1) {
		printListData(objPropRef, myList);
	}
	else {
		cout << objPropRef.getObjectType()->getName() << ":" <<
				objPropRef.getObjectId().getObjectInstanceAsUint32_t() << " " <<
				objPropRef.getPropertyId()->getName() << ": \'" << (*myList->begin())->getValAsStr() << "\'" << endl;
	}
}

void freeListData(std::list<BACnetAppDataType *> *myList) {

	std::list<BACnetAppDataType *>::iterator itr = myList->begin();

	while(itr != myList->end()) {
		delete (*itr);
		itr++;
	}

	delete myList;
}

int main(int argc, char **argv) {

	/** */
	std::list<string> argList;

	/** Skip element zero (0) because it is the program name*/
	for(int i=1; i<argc; i++) {
		argList.push_back(argv[i]);
	}

	/** Print the help message.*/

	if(argList.size() > 0) {
		string fStr = (*argList.begin());
		if(fStr.compare("-h") == 0 || fStr.compare("--help") == 0) {
			cout << "Usage:" << endl;
			cout << "[-i Network Interface Name] [-p Port] "
					"Device-Instance Object-Type Object-Instance Property-Id [[Array-Index]]" << endl << endl;
			cout << "Examples:" << endl << endl;
			cout << "To read the Present-Value of Analog-Input-1 from device-11:" << endl;
			cout << "./readprop -i eth0 -p 47808 11 0 1 85" << endl << endl;

			cout << "To read the value of Priority-Array element 16 of Analog-Output-1 from device-11:" << endl;
			cout << "./readprop -i eth0 -p 47808 11 1 1 87 [16]" << endl << endl;

			cout << "To read the list of objects from device-11:" << endl;
			cout << "./readprop -i eth0 -p 47808 11 8 11 76" << endl << endl;
			return 0;
		}
	}

	string iface;
	int port = -1;
	int devInst = -1;
	int objType = -1;
	int objInst = -1;
	int objProp = -1;
	int arrIndx = -1;
	int n = 0;

	/**
	 * ./readprop 11 0 1 85 [8]
	 * ./readprop [device-id object-type, object-instance, object-property, and optional array-index]
	 * */
	if(argList.size() > 0) {
		n = getInputParm(argList, iface, port, devInst, objType, objInst, objProp, arrIndx);
	}

	/** Suppress that dumb warning about using n*/
	(void) n;

	if(iface.length() < 1) {
		iface = DEFAULT_IFACE;
	}

	if(port == (-1)) {
		port = DEFAULT_PORT;
	}

	BacSmDev *smlDev = NULL;
	std::list<BACnetAppDataType *> *readRsult = NULL;

	try {

		con = BACnetConnection::create(iface, port, 0);

		smlDev = getDevice(devInst);

		if(smlDev) {
			//cout << smlDev->toString();
			const BACnetObjectType &objT = BACnetEnumObjectType::getEnumByValue(objType);
			const BACnetPropertyType &propT = BACnetEnumPropertyIdentifier::getEnumByValue(objProp);
			BACnetObjPropRef objPropRef = BACnetObjPropRef(objT, objInst, propT, arrIndx);

			readRsult = getProperty(*smlDev, objPropRef);

			if(readRsult != NULL) {
				printData(objPropRef, readRsult);
			}
		}
		else {
			cout << "device: \"" << devInst << "\" was not found!" << endl;
		}


	} catch (exception &e) {
		cout << e.what() << endl;
	}

	if(con) {
		BACnetConnection::release(con, 0);
	}
	if(smlDev) {
		delete smlDev;
	}
	if(readRsult) {
		freeListData(readRsult);
	}
	if(BACnetNull::Null) {
		delete BACnetNull::Null;
	}

}


