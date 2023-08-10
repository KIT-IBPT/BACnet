/*
 * BACnetBitString.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: 8w4
 */

#include "BACnetBitString.h"

#include <sstream>
#include <cstring>

BACnetBitString::BACnetBitString()
:BACnetAppDataType(BACnetEnumApplicationDataType::BIT_STRING)
{
	bitsUsed = 0;
	memset(&value, 0, sizeof(value));
}

BACnetBitString::~BACnetBitString() {
	// TODO Auto-generated destructor stub
}

uint8_t BACnetBitString::reverseBits(uint8_t byteIn) {

	/** 1010 1010 */
	/** 0101 0101 */

	uint8_t byteOut = 0;
	const uint8_t MAXBITS = 8;

	for(int i=0; i<MAXBITS; i++) {
		if(((byteIn >> i) & 0x01)) {
			byteOut |= 1 << ((MAXBITS-1)-i);
		}
	}

	return byteOut;
}

void BACnetBitString::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		/** Subtract for first octet being number of unused bits and not the data itself*/
		size_t const len = appData.getDataLength()-1;
		uint8_t const *p = appData.getData();

		/** the first octet should be the number of unused bits (if any).*/
		uint8_t const unusedBits = *(p++);

		/** Now should be pointing at the data which is encoded backwards and bits need to be reversed */

		for(uint8_t i=0; i<len; i++) {
			this->value[i] = reverseBits(*(p++));
		}

		this->bitsUsed = (len * 8) - unusedBits;
		this->clearNullFlag();
	}
	this->unlock();
}

void BACnetBitString::encode(BACnetBuffer &buff) {

}

size_t BACnetBitString::getByteLength(void) const {

	size_t numOfBytes = 0;

	if((bitsUsed % 8) > 0) {
		numOfBytes = (bitsUsed/8) +1;
	}
	else {
		numOfBytes = bitsUsed/8;
	}

	return numOfBytes;
}

string BACnetBitString::toString(void) const {

	stringstream ss;

	uint16_t numOfBytes = 0;

	ss << "BACnetBitString {" ;

	if(this->isNull()) {
		ss << "\"NULL\"}" << endl;
		return ss.str();
	}

	if((bitsUsed % 8) > 0) {
		numOfBytes = (bitsUsed/8) +1;
	}
	else
		numOfBytes = bitsUsed/8;

	/** Initial line is zero*/
	ss << endl;
	ss << "Number of Bits Used: " << bitsUsed << endl;
	ss << "Number of Bytes Used: " << numOfBytes << endl;

	ss << "Byte[0]: ";

	for(int i=0; i<numOfBytes; i++) {
		for(int j=0; j<8; j++) {

			if(i*8+j < bitsUsed) {
				ss << ((value[i]>>j) & 0x01);
			}
			else {
				ss << ".";
			}

			/** Put a space after every 4-bits...*/
			if(j==3) {
				ss << " ";
			}
		}

		/** Proper spacing and formatting...*/
		if((i+1)<numOfBytes) {

			/** Start a new line every 4-bytes*/
			if(((i+1) % 4) == 0) {
				ss << endl;
				ss << "Byte[" << i+1 << "]: ";
			}
			/** Seperate each byte with a double space...*/
			else {
				ss << "  ";
			}
		}
	}

	ss << endl << "}";

	return ss.str();
}

size_t BACnetBitString::toCString(char *toStr, size_t maxSizeOfToStr) const {
	stringstream ss;

	uint16_t numOfBytes = 0;

	if((bitsUsed % 8) > 0) {
		numOfBytes = (bitsUsed/8) +1;
	}
	else {
		numOfBytes = bitsUsed/8;
	}

	if(isNull()) {
		ss << "Null";
	}
	else {
		for(unsigned int i=0; i<numOfBytes; i++) {
			for(unsigned int j=0; j<8; j++) {

				if(i*8+j < bitsUsed) {
					ss << ((value[i]>>j) & 0x01);
				}
				else {
					ss << ".";
				}

//				/** Put a space after every 8-bits...*/
//				if(j==7) {
//					//ss << " ";
//				}
			}
		}
	}

	string str = ss.str();
	size_t maxLen = std::min(str.size(), (maxSizeOfToStr-1));

	size_t cLen = str.copy(toStr,maxLen, 0);
	toStr[cLen] = '\0';

	return cLen;
}

bool BACnetBitString::checkBit(uint8_t bit) const {

	bool retVal = false;

	/** Which byte?*/
	uint8_t byteNum = bit/8;
	uint8_t bmask = 1;

	if(bit < (MAX_BITSTRING_BYTES*8)) {
		bmask = bmask << (bit - (byteNum*8));
		if(this->value[byteNum] & bmask)
			retVal = true;
	}

	return retVal;
}

uint32_t BACnetBitString::getBytesAsUint32t() const {

	uint32_t ui32 = 0;

	size_t sz = getByteLength();


	switch (sz) {

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

void BACnetBitString::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetBitString::getLength(void) {
	return getByteLength();
}

string BACnetBitString::getValAsStr(void) {
	stringstream ss;

	uint16_t numOfBytes = 0;

	if((bitsUsed % 8) > 0) {
		numOfBytes = (bitsUsed/8) +1;
	}
	else {
		numOfBytes = bitsUsed/8;
	}

	if(isNull()) {
		ss << "Null";
	}
	else {
		for(unsigned int i=0; i<numOfBytes; i++) {
			for(unsigned int j=0; j<8; j++) {

				if(i*8+j < bitsUsed) {
					ss << ((value[i]>>j) & 0x01);
				}
				else {
					ss << ".";
				}

//				/** Put a space after every 8-bits...*/
//				if(j==7) {
//					//ss << " ";
//				}
			}
		}
	}

	return ss.str();
}
