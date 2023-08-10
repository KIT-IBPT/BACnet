/*
 * BACnetBoolean.cpp
 *
 *  Created on: Jun 29, 2018
 *      Author: 8w4
 */

#include "BACnetBoolean.h"

#include <sstream>

#include "BACnetTag.h"
#include "BACnetNull.h"

BACnetBoolean::BACnetBoolean()
:BACnetAppDataType(BACnetEnumApplicationDataType::BOOLEAN), value(false)
{
	// TODO Auto-generated constructor stub

}

BACnetBoolean::~BACnetBoolean() {
	// TODO Auto-generated destructor stub
}

void BACnetBoolean::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		this->value = appData.getDataLength() ? true : false;
		this->clearNullFlag();
	}

	this->unlock();
}

void BACnetBoolean::encode(BACnetBuffer &buff) {

	BACnetTag tag;
	tag.encodeApplicationTag((uint8_t) this->getDataType().getValue(), this->value, buff);
}

void BACnetBoolean::setValue(bool val) {
	this->value = val;
}

bool BACnetBoolean::getValue(void) const {
	return value;
}
string BACnetBoolean::toString(void) {
	stringstream ss;

	ss << "BACnetBoolean: Value = " << (isNull() ? "\"NULL\"" : (value ? "TRUE (1)" : "FALSE (0)")) << endl;
	return ss.str();
}

size_t BACnetBoolean::toCString(char *toStr, size_t maxSizeOfToStr) const {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << (this->value ? "True(1)" : "False(0)");
	}
	string str = ss.str();
	size_t maxLen = std::min(str.size(), (maxSizeOfToStr-1));

	size_t cLen = str.copy(toStr,maxLen, 0);
	toStr[cLen] = '\0';

	return cLen;
}

void BACnetBoolean::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetBoolean::getLength(void) {

	/** Maybe always return zero because a BACnet Application Tag Boolean has no length octets and gets encoded in the
	 * tag portion of l/v/t*/
	return 0;
}

string BACnetBoolean::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << (this->value ? "True(1)" : "False(0)");
	}
	return ss.str();
}

