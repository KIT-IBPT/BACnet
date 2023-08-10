/*
 * MessageIn.h
 *
 *  Created on: Jun 5, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_MESSAGEIN_H_
#define BACNETAPP_SRC_MESSAGEIN_H_

//System
#include <stdint.h>
#include <string>


#include "BACnetBuffer.h"
#include "BACnetDeviceAddress.h"

using namespace std;

class MessageIn {

private:
	BACnetDeviceAddress addr;
	BACnetBuffer buff;

	MessageIn *next;

public:
	MessageIn();
	MessageIn(BACnetDeviceAddress &srcAddr, BACnetBuffer &buff);
	virtual ~MessageIn();

	BACnetDeviceAddress &getAddress(void);
	BACnetBuffer &getBuffer(void);

	void setAddress(BACnetDeviceAddress &addr);
	void setBuffer(BACnetBuffer &buff);
	void clearData(void);

	void setNext(MessageIn *next);
	MessageIn *getNext(void);

};

#endif /* BACNETAPP_SRC_MESSAGEIN_H_ */
