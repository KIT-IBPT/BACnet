/*
 * MessageIn.cpp
 *
 *  Created on: Jun 5, 2018
 *      Author: 8w4
 */

#include "MessageIn.h"

MessageIn::MessageIn()
:addr(), buff(), next(0)
{
	// TODO Auto-generated constructor stub

}

MessageIn::MessageIn(BACnetDeviceAddress &srcAddr, BACnetBuffer &srcBuff)
:addr(srcAddr), buff(srcBuff), next(0)
{

}

MessageIn::~MessageIn() {
	// TODO Auto-generated destructor stub
}

BACnetDeviceAddress &MessageIn::getAddress(void) {
	return addr;
}

BACnetBuffer &MessageIn::getBuffer(void) {
	return buff;
}

void MessageIn::setAddress(BACnetDeviceAddress &addr) {
	this->addr = addr;
}

void MessageIn::setBuffer(BACnetBuffer &nuBuff) {
	this->buff = nuBuff;
}

void MessageIn::clearData(void) {
	this->addr.clear();
	this->buff.clear_buffer();
	this->next = NULL;
}

void MessageIn::setNext(MessageIn *next) {
	this->next = next;
}

MessageIn *MessageIn::getNext(void) {
	return this->next;
}


