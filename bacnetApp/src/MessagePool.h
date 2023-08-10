/*
 * MessagePool.h
 *
 *  Created on: Jun 11, 2018
 *      Author: 8w4
 */

#include "MessageIn.h"


using namespace std;

#ifndef BACNETAPP_SRC_MESSAGEPOOL_H_
#define BACNETAPP_SRC_MESSAGEPOOL_H_

class MessagePool {
private:
	MessageIn *msg;
	MessageIn *poolHead;

public:
	MessagePool(size_t size);
	virtual ~MessagePool();

	MessageIn *create(BACnetDeviceAddress &srcAddr, BACnetBuffer &buff);
	void freeMsg(MessageIn *oldMsg);
};

#endif /* BACNETAPP_SRC_MESSAGEPOOL_H_ */
