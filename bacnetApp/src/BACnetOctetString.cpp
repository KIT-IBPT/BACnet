/*
 * BACnetOctetString.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: 8w4
 */

#include "BACnetOctetString.h"

#include <sstream>
#include <cstring>
#include <iomanip>

BACnetOctetString::BACnetOctetString()
:BACnetAppDataType(BACnetEnumApplicationDataType::OCTET_STRING), length(0)
{
	/** Zero it out.*/
	memset(value, 0, MAX_OCTET_STRING_BYTES);
}

BACnetOctetString::~BACnetOctetString() {
	// TODO Auto-generated destructor stub
}

uint32_t BACnetOctetString::getBytesAsUint32t(void) const {

	uint32_t ui32 = 0;

	switch (this->length) {

	case 0:
		ui32 = 0;
		break;
	case 1:
		ui32 = this->value[0];
		break;
	case 2:
		ui32 = (this->value[0] << 8);
		ui32 |= this->value[1];
		break;
	case 3:
		ui32 = (this->value[0] << 16);
		ui32 |= (this->value[1] << 8);
		ui32 |= this->value[2];
		break;
	default:
		ui32 = (this->value[0] << 24);
		ui32 |= (this->value[1] << 16);
		ui32 |= (this->value[2] << 8);
		ui32 |= this->value[3];
		break;
	}

	return ui32;
}

void BACnetOctetString::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		uint8_t const *ptr = appData.getData();

		this->length = appData.getDataLength();

		if(this->length < MAX_OCTET_STRING_BYTES) {
			memcpy(&value, ptr, this->length);
		}
		else {
			this->length = 0;
			/** Zero it out.*/
			memset(value, 0, MAX_OCTET_STRING_BYTES);
			cout << "ERROR! BACnetOctetString::decode: octet-string length (" <<
					this->length << ") exceeds the MAX_OCTET_STRING_BYTES (" << MAX_OCTET_STRING_BYTES << endl;
		}

		this->clearNullFlag();
	}
	this->unlock();
}

void BACnetOctetString::encode(BACnetBuffer &buff) {

}

string BACnetOctetString::toString(void) const {

	stringstream ss;

	ss << "BACnetBitString {" ;

	if(this->isNull()) {
		ss << "\"NULL\"}" << endl;
		return ss.str();
	}


	ss << endl << "}";

	return ss.str();
}

size_t BACnetOctetString::toCString(char *toStr, size_t maxSizeOfToStr) const {

	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {

		for(unsigned int i=0; i < this->length && (i*4) < (maxSizeOfToStr-1); i++) {
			ss << "[" << std::setfill('0') << std::setw(2) << std::hex << this->value[i] << "]";
		}
	}
	string str = ss.str();
	size_t maxLen = std::min(str.size(), (maxSizeOfToStr-1));

	size_t cLen = str.copy(toStr,maxLen, 0);
	toStr[cLen] = '\0';

	return cLen;
}

void BACnetOctetString::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetOctetString::getLength(void) {
	return this->length;
}

string BACnetOctetString::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {

		for(unsigned int i=0; i < this->length; i++) {
			ss << "[" << std::setfill('0') << std::setw(2) << std::hex << this->value[i] << "]";
		}
	}
	return ss.str();
}

