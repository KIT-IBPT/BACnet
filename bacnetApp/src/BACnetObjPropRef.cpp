/*
 * BACnetObjPropRef.cpp
 *
 *  Created on: Jun 26, 2018
 *      Author: 8w4
 */

#include "BACnetObjPropRef.h"

BACnetObjPropRef::BACnetObjPropRef()
:objId(), propId(NULL), arrayIndex(-1), writePriority(-1)
{
	// TODO Auto-generated constructor stub

}

BACnetObjPropRef::BACnetObjPropRef(BACnetObjectType const &objTyp, uint32_t objInst,
			BACnetPropertyType const &propertyId, int arrayIndex)
:objId(objTyp, objInst), propId(&propertyId), arrayIndex(arrayIndex), writePriority(-1)
{

}

BACnetObjPropRef::BACnetObjPropRef(BACnetObjIdentifier const &objectId, BACnetPropertyType const &propertyId)
:objId(objectId), propId(&propertyId), arrayIndex(-1), writePriority(-1)
{

}

BACnetObjPropRef::BACnetObjPropRef(BACnetObjIdentifier const &objectId, BACnetPropertyType const &propertyId,
		int arrIndex, int writePri)
:objId(objectId), propId(&propertyId), arrayIndex(arrIndex), writePriority(writePri)
{

}

BACnetObjPropRef::~BACnetObjPropRef() {
	// TODO Auto-generated destructor stub
}

BACnetObjIdentifier const &BACnetObjPropRef::getObjectId(void) const {
	return objId;
}

BACnetObjectType const *BACnetObjPropRef::getObjectType(void) const {
	return objId.getObjectType();
}

BACnetPropertyType const *BACnetObjPropRef::getPropertyId(void) const {
	return propId;
}

int BACnetObjPropRef::getArrayIndex(void) const {
	return arrayIndex;
}

int BACnetObjPropRef::getWritePriority(void) const {
	return writePriority;
}

bool BACnetObjPropRef::operator < (const BACnetObjPropRef &rhs) const {

	if(this->objId < rhs.objId) {
		return true;
	}
	else if(this->objId == rhs.objId) {
		return this->propId < rhs.propId;
	}

	return false;
}

