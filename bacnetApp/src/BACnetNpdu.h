/*
 * BACnetNpdu.h
 *
 *  Created on: Sep 8, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETNPDU_H_
#define BACNETAPP_SRC_BACNETNPDU_H_

#include <iostream>

#include "BACnetDefs.h"
#include "BACnetApdu.h"
#include "BACnetDeviceAddress.h"
#include "BACnetBuffer.h"

using namespace std;

class BACnetNpdu {
private:

	static uint8_t const BACNET_PROTOCOL_VERSION = 0x01;	/** This is the current protocol version.*/
	static uint8_t const BACNET_DEFAULT_HOP_COUNT = 0xFF;

	BACnetDeviceAddress srcAddr;
	BACnetDeviceAddress destAddr;

	BACnetApdu *apdu;

	BACnetMessagePriority const *messagePriority;

	bool dataExpectingReply;

public:
	BACnetNpdu();
	BACnetNpdu(BACnetDeviceAddress &srcAddr, BACnetDeviceAddress &destAddr, BACnetApdu *apdu,
			BACnetMessagePriority const *networkPriority, bool dataExpectingReply);
	virtual ~BACnetNpdu();

	/** Get the length of encoding */
	size_t get_length(void) const;

	/** Encode this whoIs service into a buffer */
	int encode(BACnetBuffer &buff);
	int decode(BACnetBuffer &buff);

	bool hasSourceSpecifier(void) const;
	int getSourceAddress(BACnetDeviceAddress &addr) const;


};

#endif /* BACNETAPP_SRC_BACNETNPDU_H_ */
