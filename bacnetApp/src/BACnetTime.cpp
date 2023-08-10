/*
 * BACnetTime.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: 8w4
 */

#include "BACnetTime.h"

#include <sstream>
#include <cstring>

BACnetTime::BACnetTime()
:BACnetAppDataType(BACnetEnumApplicationDataType::TIME), hour(0), minute(0), second(0), secFrac(0)
{
	// TODO Auto-generated constructor stub

}

BACnetTime::~BACnetTime() {
	// TODO Auto-generated destructor stub
}

void BACnetTime::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		/** Length of time must be equal to 4*/
		if(appData.getDataLength() != 4) {
			return;
		}

		uint8_t const *ptr = appData.getData();

		hour = *(ptr++);
		minute = *(ptr++);
		second = *(ptr++);
		secFrac = *(ptr++);

		this->clearNullFlag();
	}
	this->unlock();
}

void BACnetTime::encode(BACnetBuffer &buff) {

}

uint32_t BACnetTime::getTimeAsUnsignedInt(void) const {

	uint32_t val = 0;

	val = (hour << 24);
	val |= (minute << 16);
	val |= (second << 8);
	val |= secFrac;

	return val;
}

string BACnetTime::toString(void) {
	stringstream ss;

	ss << "BACnetTime: Value = ";

	if(this->isNull()) {
		ss << "\"NULL\"";
	}
	else {
		ss << (unsigned int) hour << ":" << (unsigned int) minute << ":" <<
				(unsigned int) second << "." << (unsigned int) secFrac;
	}
	ss << endl;
	return ss.str();
}

size_t BACnetTime::toCString(char *toStr, size_t maxSizeOfToStr) const {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << (unsigned int) hour << ":" << (unsigned int) minute << ":" <<
				(unsigned int) second << "." << (unsigned int) secFrac;
	}
	string str = ss.str();
	size_t maxLen = std::min(str.size(), (maxSizeOfToStr-1));

	size_t cLen = str.copy(toStr,maxLen, 0);
	toStr[cLen] = '\0';

	return cLen;
}

void BACnetTime::printData(void) {
	cout << this->toString();
}

size_t BACnetTime::getLength(void) {
	return 4;
}

string BACnetTime::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << (unsigned int) hour << ":" << (unsigned int) minute << ":" <<
				(unsigned int) second << "." << (unsigned int) secFrac;
	}
	return ss.str();
}
