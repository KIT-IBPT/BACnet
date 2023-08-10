/*
 * BACnetDate.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: 8w4
 */

#include "BACnetDate.h"

#include <sstream>
#include <cstring>

BACnetDate::BACnetDate()
:BACnetAppDataType(BACnetEnumApplicationDataType::DATE), year(0), month(0), dayOfMonth(0), dayOfWeek(0)
{
	// TODO Auto-generated constructor stub

}

BACnetDate::~BACnetDate() {
	// TODO Auto-generated destructor stub
}

void BACnetDate::decode(BACnetApplicationData const &appData) {

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

		year = (*(ptr++) + 1900);
		month = *(ptr++);
		dayOfMonth = *(ptr++);
		dayOfWeek = *(ptr++);

		this->clearNullFlag();
	}
	this->unlock();
}

void BACnetDate::encode(BACnetBuffer &buff) {

}

uint32_t BACnetDate::getDateAsUnsignedInt(void) const {

	uint32_t val = 0;

	val = ((year-1900) << 24);
	val |= (month << 16);
	val |= (dayOfMonth << 8);
	val |= dayOfWeek;

	return val;
}

string BACnetDate::toString(void) {
	stringstream ss;

	ss << "BACnetDate: Value = ";

	if(this->isNull()) {
		ss << "\"NULL\"";
	}
	else {
		ss << (unsigned int) year << ":" << (unsigned int) month << ":" <<
				(unsigned int) dayOfMonth << "." << (unsigned int) dayOfWeek << endl;
	}
	return ss.str();
}

size_t BACnetDate::toCString(char *toStr, size_t maxSizeOfToStr) const {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << (unsigned int) year << ":" << (unsigned int) month << ":" <<
				(unsigned int) dayOfMonth << ":" << (unsigned int) dayOfWeek;
	}
	string str = ss.str();
	size_t maxLen = std::min(str.size(), (maxSizeOfToStr-1));

	size_t cLen = str.copy(toStr,maxLen, 0);
	toStr[cLen] = '\0';

	return cLen;
}

void BACnetDate::printData(void) {
	cout << this->toString();
}

size_t BACnetDate::getLength(void) {
	return 4;
}

string BACnetDate::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << (unsigned int) year << ":" << (unsigned int) month << ":" <<
				(unsigned int) dayOfMonth << ":" << (unsigned int) dayOfWeek;
	}
	return ss.str();
}

