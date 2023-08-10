/*
 * BACnetDouble.cpp
 *
 *  Created on: Jun 27, 2018
 *      Author: 8w4
 */

#include "BACnetDouble.h"

#include <sstream>
#include <cstring>

#include "BACnetTag.h"

BACnetDouble::BACnetDouble()
:BACnetAppDataType(BACnetEnumApplicationDataType::DOUBLE), value(0)
{
	// TODO Auto-generated constructor stub

}

BACnetDouble::~BACnetDouble() {
	// TODO Auto-generated destructor stub
}

void BACnetDouble::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		uint8_t const *p = appData.getData();

		double dval = 0;
		uint8_t ui[8];

		/** Reverse the bytes...*/
		ui[7] = p[0];
		ui[6] = p[1];
		ui[5] = p[2];
		ui[4] = p[3];
		ui[3] = p[4];
		ui[2] = p[5];
		ui[1] = p[6];
		ui[0] = p[7];

		memcpy(&dval, &ui, sizeof(dval));
		this->value = dval;

		this->clearNullFlag();
	}

	this->unlock();
}

void BACnetDouble::encode(BACnetBuffer &buff) {

	BACnetTag tag;
	tag.encodeApplicationTag(this->getDataType().getValue(), 8, buff);

	uint8_t ui[8];
	memcpy(&ui, &value, sizeof(ui));
	reverseBytes(ui);
	buff.encode_buffer(ui, 0, 8);
}

void BACnetDouble::reverseBytes(uint8_t *pUi8) {

	uint8_t tempBytes[8];

	tempBytes[0] = pUi8[0];
	tempBytes[1] = pUi8[1];
	tempBytes[2] = pUi8[2];
	tempBytes[3] = pUi8[3];
	tempBytes[4] = pUi8[4];
	tempBytes[5] = pUi8[5];
	tempBytes[6] = pUi8[6];
	tempBytes[7] = pUi8[7];

	pUi8[0] = tempBytes[7];
	pUi8[1] = tempBytes[6];
	pUi8[2] = tempBytes[5];
	pUi8[3] = tempBytes[4];
	pUi8[4] = tempBytes[3];
	pUi8[5] = tempBytes[2];
	pUi8[6] = tempBytes[1];
	pUi8[7] = tempBytes[0];

}

double BACnetDouble::getValue(void) const {
	return value;
}

void BACnetDouble::setValue(double val) {
	this->value = val;
}

string BACnetDouble::toString(void) {
	stringstream ss;

	ss << "BACnetDouble: Value = ";

	if(this->isNull()) {
		ss << "\"NULL\"";
	}
	else {
		ss << this->value;
	}
	ss << endl;

	return ss.str();
}

size_t BACnetDouble::toCString(char *toStr, size_t maxSizeOfToStr) const {

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

void BACnetDouble::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetDouble::getLength(void) {
	return 8;
}

string BACnetDouble::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << this->value;
	}
	return ss.str();
}

