/*
 * BACnetWhoIsRequest.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: 8w4
 */

#include "BACnetWhoIsRequest.h"

#include "BACnetNpdu.h"
#include "BACnetBuffer.h"
#include "BACnetBVLLOrigBcastNPDU.h"
#include "BACnetIamService.h"


BACnetWhoIsRequest::BACnetWhoIsRequest() {

}

BACnetWhoIsRequest::~BACnetWhoIsRequest() {
	// TODO Auto-generated destructor stub
}

int BACnetWhoIsRequest::sendWhoIsReqGlobal(BACnetDevice &bacDev) {

	BACnetWhoIsService whois = BACnetWhoIsService(bacDev.getDeviceInstanceId());

	/** The Destination Address*/
	BACnetDeviceAddress destAddr = BACnetDeviceAddress();

	/** Because this is a Global request we need to format the destination address to broadcast
	 * on ALL networks... */
	bacDev.makeGlobalBroadcastAddress(destAddr);

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

	/** Send to the socket...*/
	int sent = bacDev.sendTo(bacNetIpMsg, destAddr);

	cout << "Bytes Sent: " << sent << endl;

	return sent;
}



