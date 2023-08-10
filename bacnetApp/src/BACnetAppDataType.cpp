/*
 * BACnetAppDataType.cpp
 *
 *  Created on: Jun 27, 2018
 *      Author: 8w4
 */

#include "BACnetAppDataType.h"

BACnetAppDataType::BACnetAppDataType(BACnetApplicationDataTypeChoice const &dataTYPE)
:dataType(dataTYPE), nullFlag(true)
{
	// TODO Auto-generated constructor stub

}

BACnetAppDataType::~BACnetAppDataType() {
	// TODO Auto-generated destructor stub
}

const BACnetApplicationDataTypeChoice &BACnetAppDataType::getDataType(void) const {
	return this->dataType;
}

void BACnetAppDataType::setNullFlag(void) {
	this->nullFlag = true;
}

void BACnetAppDataType::clearNullFlag(void) {
	this->nullFlag = false;
}

bool BACnetAppDataType::isNull(void) const {
	return this->nullFlag;
}

void BACnetAppDataType::lock(void) {
	this->mutx.lock();
}

void BACnetAppDataType::unlock(void) {
	this->mutx.unlock();
}

bool BACnetAppDataType::tryLock(void) {
	return this->mutx.tryLock();
}


