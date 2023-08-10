/*
 * BACnetAppObjId.cpp
 *
 *  Created on: Jul 30, 2018
 *      Author: 8w4
 */

#include "BACnetAppObjId.h"

#include <sstream>
#include <cstring>

BACnetAppObjId::BACnetAppObjId()
:BACnetObjIdentifier(), BACnetAppDataType(BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER)
{
	// TODO Auto-generated constructor stub
}

BACnetAppObjId::~BACnetAppObjId() {
	// TODO Auto-generated destructor stub
}

void BACnetAppObjId::decode(BACnetApplicationData const &appData) {

	this->lock();

	if(*appData.getAppDataType() == BACnetEnumApplicationDataType::NNULL) {
		this->setNullFlag();
	}
	else {
		uint8_t const *p = appData.getData();
		this->BACnetObjIdentifier::decode(p);
		this->clearNullFlag();
	}
	this->unlock();
}

void BACnetAppObjId::encode(BACnetBuffer &buff) {

}

string BACnetAppObjId::toString(void) {
	stringstream ss;

	if(this->obj_type) {
		ss << this->obj_type->getName() << " : ";
	}
	else {
		ss << "NULL_OBJECT_TYPE : ";
	}
	ss << this->obj_instance.get_instance() << endl;
	return ss.str();
}

size_t BACnetAppObjId::toCString(char *toStr, size_t maxSizeOfToStr) const {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		if(this->obj_type) {
			ss << this->obj_type->getName() << ":";
		}
		else {
			ss << "NULL_OBJECT_TYPE:";
		}
		ss << this->obj_instance.get_instance();
	}
	string str = ss.str();
	size_t maxLen = std::min(str.size(), (maxSizeOfToStr-1));

	size_t cLen = str.copy(toStr,maxLen, 0);
	toStr[cLen] = '\0';

	return cLen;
}

void BACnetAppObjId::printData(void) {
	cout << this->toString();
}

size_t BACnetAppObjId::getLength(void) {

	if(this->obj_type) {
		return 4;
	}
	return 0;
}

string BACnetAppObjId::getValAsStr(void) {
	stringstream ss;

	if(isNull()) {
		ss << "Null";
	}
	else {
		if(this->obj_type) {
			ss << this->obj_type->getName() << ":";
		}
		else {
			ss << "NULL_OBJECT_TYPE:";
		}
		ss << this->obj_instance.get_instance();
	}
	return ss.str();
}

