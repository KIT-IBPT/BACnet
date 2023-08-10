/*
 * BACnetUnsignedInt.cpp
 *
 *  Created on: Jul 2, 2018
 *      Author: 8w4
 */

#include "BACnetUnsignedInt.h"

#include <sstream>
#include <cstring>

#include "BACnetTag.h"


BACnetUnsignedInt::BACnetUnsignedInt()
:BACnetAppDataType(BACnetEnumApplicationDataType::UNSIGNED_INTEGER), value(0)
{
	// TODO Auto-generated constructor stub

}

BACnetUnsignedInt::~BACnetUnsignedInt() {
	// TODO Auto-generated destructor stub
}

void BACnetUnsignedInt::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		uint32_t len = appData.getDataLength();
		uint8_t const *p = appData.getData();

		if(len < 1 || len > 4) {
			cout << "Error while decoding BACnet BACnetUnsignedInt: Data length (" << len <<
					") must be greater than 0 and less than 4." << endl;
			return;
		}

		if(len == 4) {
			p = BACnetBuffer::get_ui32(p, this->value);
		}
		else if(len == 3) {
			p = BACnetBuffer::get_ui24(p, this->value);
		}
		else if(len == 2) {
			p = BACnetBuffer::get_ui16(p, this->value);
		}
		else if(len == 1) {
			p = BACnetBuffer::get_ui8(p, this->value);
		}
		this->clearNullFlag();
	}

	this->unlock();
}

void BACnetUnsignedInt::encode(BACnetBuffer &buff) {

	/** Get the length right off the bat!*/
	size_t len = this->getLength();

	/** Encode it into an Application tag*/
	BACnetTag tag;
	tag.encodeApplicationTag((uint8_t) this->getDataType().getValue(), len, buff);

	/** Now encode the value portion*/
	/** The length has to be between 1 and 4, so no real reason to check for this... just roll with it.*/
	switch (len) {
	case 1:
		buff.encode_ui8(this->value);
		break;
	case 2:
		buff.encode_ui16(this->value);
		break;
	case 3:
		buff.encode_ui24(this->value);
		break;
	case 4:
		buff.encode_ui32(this->value);
		break;
	default:
		break;
	}
}

uint32_t BACnetUnsignedInt::getValue(void) const {
	return value;
}

void BACnetUnsignedInt::setValue(uint32_t val) {
	this->value = val;
}

string BACnetUnsignedInt::toString(void) {
	stringstream ss;

	ss << "BACnetUnsignedInt: Value = ";
	if(this->isNull()) {
		ss << "\"NULL\"";
	}
	else {
		ss << this->value;
	}
	ss << endl;

	return ss.str();
}

size_t BACnetUnsignedInt::toCString(char *toStr, size_t maxSizeOfToStr) const {

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

void BACnetUnsignedInt::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetUnsignedInt::getLength(void) {
	size_t len = 0;

	if(value < 0x100UL) {
		len = 1;
	}
	else if(value < 0x10000UL) {
		len = 2;
	}
	else if(value < 0x1000000UL) {
		len = 3;
	}
	else if(value < 0x100000000UL) {
		len = 4;
	}
	return len;
}

string BACnetUnsignedInt::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		ss << this->value;
	}
	return ss.str();
}
