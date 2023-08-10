/*
 * BACnetObjIdentifier.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: 8w4
 */

#include "BACnetObjIdentifier.h"

#include <sstream>
#include <cstring>

BACnetObjIdentifier::BACnetObjIdentifier()
:obj_type(NULL), obj_instance()
{

}

BACnetObjIdentifier::BACnetObjIdentifier(const BACnetObjIdentifier &objid)
:obj_type(objid.obj_type), obj_instance(objid.obj_instance)
{

}

BACnetObjIdentifier::BACnetObjIdentifier(uint16_t objType, uint32_t objInstance)
:obj_type(&BACnetEnumObjectType::getEnumByValue(objType)), obj_instance(objInstance)
{

}

BACnetObjIdentifier::BACnetObjIdentifier(BACnetObjectType const &objType, uint32_t objInstance)
:obj_type(&objType), obj_instance(objInstance)
{

}

BACnetObjIdentifier::~BACnetObjIdentifier() {
	// TODO Auto-generated destructor stub
}

void BACnetObjIdentifier::clear(void) {
	this->obj_type = NULL;
	this->obj_instance.setToNullInstance();
}

void BACnetObjIdentifier::setObjectType(BACnetObjectType const &objType) {
	this->obj_type = &objType;
}

void BACnetObjIdentifier::setObjectInstance(uint32_t objInstance) {
	this->obj_instance.setInstance(objInstance);
}

const string BACnetObjIdentifier::getObjectName(void) const {
	if(this->obj_type != NULL) {
		return this->obj_type->getName();
	}
	return "Null";
}

BACnetObjectType const *BACnetObjIdentifier::getObjectType(void) const {
	return obj_type;
}

void BACnetObjIdentifier::getObjectId(BACnetObjIdentifier &objId) const {
	copyObjectId(objId, *this);
}

void BACnetObjIdentifier::copyObjectId(BACnetObjIdentifier &copyTo, BACnetObjIdentifier const &copyFrom) {

	copyTo.obj_type = copyFrom.obj_type;
	copyTo.obj_instance.instance = copyFrom.obj_instance.instance;
}

BACnetInstance const &BACnetObjIdentifier::getObjectInstance(void) const {
	return obj_instance;
}

uint32_t BACnetObjIdentifier::getObjectInstanceAsUint32_t(void) const {
	return this->obj_instance.instance;
}

void BACnetObjIdentifier::decode(BACnetBuffer &buff) {

	/**
	 *
	 * 31    ...    22  21    ...    0
	 * |---|---|---|---|---|...|---|---|
	 * |  Object Type  |Instance Number|
	 * |---|---|---|---|---|...|---|---|
	 *  <----- 10 ---->  <---- 22 ---->
	 * */

	const uint32_t OBJ_TYPE = 0xFFC00000U;	/** Upper 10-bits */
	const uint32_t OBJ_INST = 0x003FFFFFU;	/** Lower 22-bits */

	/** Get 4-bytes from buffer */
	const uint32_t UI32 = buff.get_ui32();

	/** Decode Object Type in upper 10-bits. */
	const uint16_t OBJTYP = (UI32 & OBJ_TYPE) >> 22;

	/** getEnumByValue will throw if the object-type can't be found.*/
	this->obj_type = &BACnetEnumObjectType::getEnumByValue(OBJTYP);

	/** Decode Object Instance in lower 22-bits */

	this->obj_instance.setInstance((UI32 & OBJ_INST));

}

uint8_t const *BACnetObjIdentifier::decode(uint8_t const *buff) {

	/**
	 *
	 * 31    ...    22  21    ...    0
	 * |---|---|---|---|---|...|---|---|
	 * |  Object Type  |Instance Number|
	 * |---|---|---|---|---|...|---|---|
	 *  <----- 10 ---->  <---- 22 ---->
	 * */

	if(buff == NULL) {
		return 0;
	}

	const uint32_t OBJ_TYPE = 0xFFC00000U;	/** Upper 10-bits */
	const uint32_t OBJ_INST = 0x003FFFFFU;	/** Lower 22-bits */

	uint32_t objId = 0;

	/** Get 4-bytes from buffer */
	objId = *(buff++) << 24;
	objId |= *(buff++) << 16;
	objId |= *(buff++) << 8;
	objId |= *(buff++);

	/** Decode Object Type in upper 10-bits. */
	const uint16_t OBJTYP = (objId & OBJ_TYPE) >> 22;

	this->obj_type = &BACnetEnumObjectType::getEnumByValue(OBJTYP);

	/** Decode Object Instance in lower 22-bits */

	this->obj_instance.setInstance((objId & OBJ_INST));

	return buff;
}

size_t BACnetObjIdentifier::encode(BACnetBuffer &buff) const {
	/**
	 *
	 * 31    ...    22  21    ...    0
	 * |---|---|---|---|---|...|---|---|
	 * |  Object Type  |Instance Number|
	 * |---|---|---|---|---|...|---|---|
	 *  <----- 10 ---->  <---- 22 ---->
	 * */

	uint32_t ui32 = 0;

	ui32 = ((this->obj_type->getValue() & 0x3ff) << 22);
	ui32 |= (this->obj_instance.get_instance() & 0x3FFFFF);

	buff.encode_ui32(ui32);

	return 4;
}

std::ostream& operator<< (std::ostream &out, const BACnetObjIdentifier &bacObjId)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.

    out << "BACnetObjIdentifier {" << endl;
    out << "\tObject-Type: " << bacObjId.getObjectType()->getName() << " (" << bacObjId.getObjectType()->getValue() <<
    		")" << endl;
    out << "\tObject Instance: " << bacObjId.getObjectInstance().get_instance() << endl;
    out << "\t} BACnetObjIdentifier" << endl;

    return out;
}

/** Return (0) if equal. Return (-1) if left is less than right. Return (1) if left is greater than right.*/
int BACnetObjIdentifier::compare(const BACnetObjIdentifier &left, const BACnetObjIdentifier &right) const {
	/** See if they have the same address in memory...*/
	if(&left == &right) {
		return 0;
	}
	else if(left.obj_type == right.obj_type) {
		if(left.obj_instance == right.obj_instance) {
			return 0;
		}
		else if(left.obj_instance < right.obj_instance) {
			return -1;
		}
		else
			return 1;
	}
	else if(left.obj_type < right.obj_type) {
		return -1;
	}
	else
		return 1;
}

bool BACnetObjIdentifier::operator == (const BACnetObjIdentifier &right) const {

	if(compare(*this, right) == 0) {
		return true;
	}
	else
		return false;
}

bool BACnetObjIdentifier::operator != (const BACnetObjIdentifier &right) const {
	if(compare(*this, right) != 0) {
		return true;
	}
	else
		return false;
}

bool BACnetObjIdentifier::operator < (const BACnetObjIdentifier &rhs) const {

	if(this->obj_type != NULL) {
		if(this->obj_type == rhs.obj_type) {
			return this->getObjectInstanceAsUint32_t() < rhs.getObjectInstanceAsUint32_t();
		}
		else {
			return this->obj_type < rhs.obj_type;
		}
	}
	return false;
}

void BACnetObjIdentifier::getBytes(uint8_t *copyTo) const {

	uint32_t ui32 = 0;

	if(copyTo) {
		if(this->obj_type) {
			ui32 = ((this->obj_type->getValue() & 0x3ff) << 22);
		}
		ui32 |= (this->obj_instance.get_instance() & 0x3FFFFF);
		memcpy(copyTo, &ui32, 4);
	}
	else {
		cout << "ERROR! BACnetObjIdentifier::getBytes: copyTo parameter is NULL" << endl;
	}
}

uint32_t BACnetObjIdentifier::getBytesAsUint32t(void) const {

	uint32_t ui32 = 0;

	if(this->obj_type) {
		ui32 = ((this->obj_type->getValue() & 0x3ff) << 22);
	}
	ui32 |= (this->obj_instance.get_instance() & 0x3FFFFF);

	return ui32;

}

string BACnetObjIdentifier::toString(void) {
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

void BACnetObjIdentifier::printData(void) {
	cout << this->toString();
}


