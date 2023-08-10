/*
 * whoisMain.cpp
 *
 *  Created on: Sep 27, 2018
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
#include "BACnetBuffer.h"
#include "BACnetIamService.h"

using namespace std;

#define DEFAULT_PORT 0xBAC0
#define DEFAULT_IFACE "eth0"

static BACnetConnection *con = NULL;

class BacSmDev {
public:

	BacSmDev();
	virtual ~BacSmDev();

	void decode(const BACnetDeviceAddress &srcAddr, BACnetBuffer &buff);
	string toString(void);
	uint32_t getInstanceAsUint32();

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

BacSmDev::~BacSmDev() {

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
	if(this->segmentationSupported == NULL) {
		ss << " Segmentation Supported: Null" << endl;
	}
	else
		ss << " Segmentation Supported: " << this->segmentationSupported->getName() << endl;
	ss << " Vendor-Identifier: " << this->vendorId << endl;
	ss << "}" << endl;

	return ss.str();
}

uint32_t BacSmDev::getInstanceAsUint32() {
	return this->objectId.getObjectInstanceAsUint32_t();
}

int getInputParm(const std::list<string> &inpl, string &iface, int &port, int &netwrk, int &lowInst, int &highInst) {

	int n = inpl.size();
	std::list<string>::const_iterator itr = inpl.begin();
	stringstream ss;

	/** Switches are present?
	 * Loop thru the optional switches first: -i, -p, -n
	 * */
	int rem = 0;

	while(itr != inpl.end() && (*itr)[0] == '-') {

		rem = std::distance(itr, inpl.end());

		if(itr != inpl.end() && (*itr).compare("-i") == 0) {
			if(rem > 1) {
				itr++;
				ss << (*itr);
				ss >> iface;
				ss << "";
				ss.clear();
				itr++;
				rem = std::distance(itr, inpl.end());
			}
			else
				return -1;
		}

		if(itr != inpl.end() && (*itr).compare("-p") == 0) {
			if(rem > 1) {
				itr++;
				ss << (*itr);
				ss >> port;
				ss << "";
				ss.clear();
				itr++;
				rem = std::distance(itr, inpl.end());
			}
			else
				return -1;
		}

		if(itr != inpl.end() && (*itr).compare("-n") == 0) {
			if(rem > 1) {
				itr++;
				ss << (*itr);
				ss >> netwrk;
				ss << "";
				ss.clear();
				itr++;
				rem = std::distance(itr, inpl.end());
			}
			else
				return -1;
		}
	}

	/** Low instance is present...*/
	if(itr != inpl.end()) {
		ss << (*itr);
		ss >> lowInst;
		ss << "";
		ss.clear();
		itr++;
	}

	/** High instance is present...*/
	if(itr != inpl.end()) {
		ss << (*itr);
		ss >> highInst;
		ss << "";
		ss.clear();
		itr++;
	}

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

int getDeviceList(std::list<BacSmDev> &dlist, int lowInst, int highInst) {

	if(con == NULL) {
		throw;
	}

	/** align the range if a user only enters a lowInst value*/
	if(lowInst > highInst) {
		highInst = lowInst;
	}

	std::list<int> instList;

	if(lowInst > (-1)) {
		for(int i = lowInst; i <= highInst; i++) {
			instList.push_back(i);
		}
	}

	/** Wait at least 5-seconds for a reply all the replies to succeed...*/
	time_t start_time = time(NULL);
	time_t current_time = time(NULL);
	const double timeout = 5.0;

	BACnetDeviceAddress srcAddr;
	BACnetBuffer buff;

	while((current_time-start_time) < timeout) {

		int bytes = con->recvFrom(srcAddr, buff);

		if(bytes > 0) {
			start_time = time(NULL);
			//cout << buff.hex_dump() << endl;

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
						if(lowInst == (-1) && highInst == (-1)) {
							dlist.push_back(dev);
						}
						else if(dev.getInstanceAsUint32() >= (uint32_t) lowInst &&
								dev.getInstanceAsUint32() <= (uint32_t) highInst) {
							dlist.push_back(dev);
							instList.remove(dev.getInstanceAsUint32());
							if(instList.size() <= 0) {
								return dlist.size();
							}
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
	return dlist.size();
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
			cout << "[-i Network Interface Name] [-p Port] [-n Remote Network Number] "
					"[Instance Range: [low instance] [high instance]]" << endl << endl;
			cout << "Examples:" << endl << endl;
			cout << "To send whois request to devices with instance numbers between 0 and 100:" << endl;
			cout << "./whois -i eth0 -p 47808 0 100" << endl << endl;

			cout << "To send whois request to ALL devices:" << endl;
			cout << "./whois -i eth0 -p 47808" << endl << endl;
			return 0;
		}
	}

	int remNet = -1;
	int lowInst = -1;
	int highInst = -1;
	string iface;
	int port = -1;
	int n = 0;

	if(argList.size() > 0) {
		n = getInputParm(argList, iface, port, remNet, lowInst, highInst);
	}

	(void) n;

	cout << "iface: " << iface << ", port: " << port << ", remNet: " << remNet <<
			", lowInst: " << lowInst << ", highInst: " << highInst << endl << endl;

	if(iface.length() < 1) {
		iface = DEFAULT_IFACE;
	}

	if(port == (-1)) {
		port = DEFAULT_PORT;
	}

	try {

		con = BACnetConnection::create(iface, port, 0);
		sendWhoIs(remNet, lowInst, highInst);

		std::list<BacSmDev> devList;
		int n = getDeviceList(devList, lowInst, highInst);

		(void) n;

		std::list<BacSmDev>::iterator itr = devList.begin();
		while(itr != devList.end()) {
			cout << (*itr).toString() << endl;
			itr++;
		}


	} catch (exception &e) {
		cout << e.what() << endl;
	}


	if(con) {
		BACnetConnection::release(con, 0);
	}



}

