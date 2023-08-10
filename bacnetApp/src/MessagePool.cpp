/*
 * MessagePool.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: 8w4
 */

#include "MessagePool.h"

MessagePool::MessagePool(size_t size) {
	cout << "MessagePool::MessagePool(size_t size) " << size << endl;
	msg = new MessageIn[size];

	for(unsigned int i=0; i<(size-1); i++) {
		msg[i].setNext(&msg[i+1]);
	}
	poolHead = &msg[0];
	msg[size-1].setNext(NULL);

}

MessagePool::~MessagePool() {
	delete[] msg;
}

MessageIn *MessagePool::create(BACnetDeviceAddress &srcAddr, BACnetBuffer &buff) {

	/** Two lists: The main pool from which all tsms come from and then there is the Active-List
	 * which is a list of TSMs that are actively in use...*/

	MessageIn *nuMsg = poolHead;
	if(poolHead != NULL) {
		nuMsg->setAddress(srcAddr);
		nuMsg->setBuffer(buff);
		poolHead = nuMsg->getNext();
	}
	return nuMsg;
}

void MessagePool::freeMsg(MessageIn *freeMsg) {

	/** Remove from active-list first.*/

	if(freeMsg == NULL) {
		return;
	}

	freeMsg->clearData();
	freeMsg->setNext(poolHead);
	poolHead = freeMsg;
	return;
}

