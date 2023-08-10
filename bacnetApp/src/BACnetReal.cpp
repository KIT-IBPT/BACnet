/*
 * BACnetReal.cpp
 *
 *  Created on: Jun 27, 2018
 *      Author: 8w4
 */

#include "BACnetReal.h"

#include <sstream>
#include <cstring>
#include <iomanip>

#include "BACnetTag.h"

BACnetReal::BACnetReal()
:BACnetAppDataType(BACnetEnumApplicationDataType::REAL), value(0)
{
	// TODO Auto-generated constructor stub

}

BACnetReal::~BACnetReal() {
	// TODO Auto-generated destructor stub
}

void BACnetReal::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		uint8_t const *p = appData.getData();

		float f = 0;
		uint8_t ui[4];

		/** Reverse the bytes...*/
		ui[3] = p[0];
		ui[2] = p[1];
		ui[1] = p[2];
		ui[0] = p[3];

		memcpy(&f, &ui, sizeof(f));
		this->value = f;

		this->clearNullFlag();
	}

	this->unlock();
}

void BACnetReal::encode(BACnetBuffer &buff) {

	BACnetTag tag;
	tag.encodeApplicationTag(this->getDataType().getValue(), 4, buff);

	uint8_t ui[4];
	memcpy(&ui, &value, sizeof(ui));
	reverseBytes(ui);
	buff.encode_buffer(ui, 0, 4);

}

void BACnetReal::reverseBytes(uint8_t *pUi8) {

	uint8_t tempBytes[4];

	tempBytes[0] = pUi8[0];
	tempBytes[1] = pUi8[1];
	tempBytes[2] = pUi8[2];
	tempBytes[3] = pUi8[3];

	pUi8[0] = tempBytes[3];
	pUi8[1] = tempBytes[2];
	pUi8[2] = tempBytes[1];
	pUi8[3] = tempBytes[0];

}

void BACnetReal::setValue(float val) {
	this->value = val;
}

float BACnetReal::getValue(void) const {
	return value;
}
string BACnetReal::toString(void) {
	stringstream ss;

	ss << "BACnetReal: Value = ";

	if(this->isNull()) {
		ss << "\"NULL\"";
	}
	else {
		ss << this->value;
	}
	ss << endl;

	return ss.str();
}

size_t BACnetReal::toCString(char *toStr, size_t maxSizeOfToStr) const {

	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << this->value;
	}
	string str = ss.str();
	size_t maxLen = std::min(str.size(), (maxSizeOfToStr-1));

	size_t cLen = str.copy(toStr,maxLen, 0);
	toStr[cLen] = '\0';

	return cLen;
}

void BACnetReal::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetReal::getLength(void) {
	return 4;
}

string BACnetReal::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << this->value;
	}
	return ss.str();
}

