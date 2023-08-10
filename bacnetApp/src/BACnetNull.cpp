/*
 * BACnetNull.cpp
 *
 *  Created on: Jul 2, 2018
 *      Author: 8w4
 */

#include "BACnetNull.h"

#include <sstream>
#include "BACnetTag.h"

BACnetNull *BACnetNull::Null = new BACnetNull();

BACnetNull::BACnetNull()
:BACnetAppDataType(BACnetEnumApplicationDataType::NNULL), strNull("Null")
{
	//cout << "Creating new NULL" << endl;

}

BACnetNull::~BACnetNull() {
	// TODO Auto-generated destructor stub

}

void BACnetNull::decode(BACnetApplicationData const &appData) {
	/** cout << "BACnetNull::decode" << endl;*/
}

void BACnetNull::encode(BACnetBuffer &buff) {

	/**
	 * 20.2.2 Encoding of a Null Value
	 * The encoding of a Null value shall be primitive, with no contents octet.
	 * */
	BACnetTag tag;
	tag.encodeApplicationTag((uint8_t) this->getDataType().getValue(), 0, buff);

}

string BACnetNull::toString(void) {
	stringstream ss;

	ss << "NULL" << endl;
	return ss.str();
}

size_t BACnetNull::toCString(char *toStr, size_t maxSizeOfToStr) {

	size_t maxLen = std::min(strNull.size(), (maxSizeOfToStr-1));
	size_t cLen = this->strNull.copy(&toStr[0], maxLen, 0);
	toStr[cLen] = '\0';

	return cLen;
}

void BACnetNull::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetNull::getLength(void) {
	return 0;
}

string BACnetNull::getValAsStr() {
	return "Null";
}

