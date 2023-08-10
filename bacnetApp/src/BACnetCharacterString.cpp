/*
 * BACnetCharacterString.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: 8w4
 */

#include "BACnetCharacterString.h"

#include <sstream>
#include <cstring>
#include <iomanip>

BACnetCharacterString::BACnetCharacterString()
:BACnetAppDataType(BACnetEnumApplicationDataType::CHARACTER_STRING), encoding(0), length(0)
{
	/** Zero it out.*/
	memset(Value, 0, MAX_CHAR_STRING_BYTES);
}

BACnetCharacterString::~BACnetCharacterString() {
	// TODO Auto-generated destructor stub
}

uint32_t BACnetCharacterString::getBytesAsUint32t(void) const {

	uint32_t ui32 = 0;

	switch (this->length) {

	case 0:
		ui32 = 0;
		break;
	case 1:
		ui32 = this->Value[0];
		break;
	case 2:
		ui32 = (this->Value[0] << 8);
		ui32 |= this->Value[1];
		break;
	case 3:
		ui32 = (this->Value[0] << 16);
		ui32 |= (this->Value[1] << 8);
		ui32 |= this->Value[2];
		break;
	default:
		ui32 = (this->Value[0] << 24);
		ui32 |= (this->Value[1] << 16);
		ui32 |= (this->Value[2] << 8);
		ui32 |= this->Value[3];
		break;
	}

	return ui32;
}

void BACnetCharacterString::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		uint8_t const *ptr = appData.getData();

		BACnetCharChoice const *encoding = &BACnetEnumCharSet::getEnumByValue(*(ptr++));

		if(encoding) {
			/** Only supporting CHARACTER_UTF8 for now.*/
			if(*encoding == BACnetEnumCharSet::CHARACTER_UTF8) {
				this->encoding = encoding;
				this->length = (appData.getDataLength()-1);

				if(this->length < MAX_CHAR_STRING_BYTES) {
					memcpy(&Value, ptr, this->length);

					/** Is null terminated needed? */
					this->Value[this->length] = '\0';
				}
			}
			else {
				this->length = 0;
				this->encoding = NULL;
				this->Value[this->length] = '\0';
			}
		}
		else {
			this->length = 0;
			this->encoding = NULL;
			this->Value[this->length] = '\0';
		}

		this->clearNullFlag();
	}
	this->unlock();
}

void BACnetCharacterString::encode(BACnetBuffer &buff) {

}

string BACnetCharacterString::toString(void) const {

	return string(Value);
}

size_t BACnetCharacterString::toCString(char *toStr, size_t maxSizeOfToStr) const {

	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		size_t len = std::min(this->length, (maxSizeOfToStr-1));

		for(unsigned int i=0; i < len; i++) {
			ss << this->Value[i];
		}
	}
	string str = ss.str();
	size_t len = str.copy(toStr,str.size(), 0);
	toStr[len] = '\0';
	return len;
}

void BACnetCharacterString::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetCharacterString::getLength(void) {
	return this->length;
}

string BACnetCharacterString::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		for(unsigned int i=0; i < this->length; i++) {
			ss << this->Value[i];
		}
	}
	return ss.str();
}


