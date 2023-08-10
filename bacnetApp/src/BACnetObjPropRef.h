/*
 * BACnetObjPropRef.h
 *
 *  Created on: Jun 26, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETOBJPROPREF_H_
#define BACNETAPP_SRC_BACNETOBJPROPREF_H_

#include "BACnetObjIdentifier.h"
#include "BACnetEnumPropertyIdentifier.h"

class BACnetObjPropRef {
private:
	BACnetObjIdentifier objId;
	BACnetPropertyType const *propId;
	int arrayIndex;
	int writePriority;

public:
	BACnetObjPropRef();
	BACnetObjPropRef(BACnetObjectType const &objTyp, uint32_t objInst,
			BACnetPropertyType const &propId, int arrayIndex);

	BACnetObjPropRef(BACnetObjIdentifier const &objId, BACnetPropertyType const &propId);
	BACnetObjPropRef(BACnetObjIdentifier const &objId, BACnetPropertyType const &propId, int arrayIndex, int writePri);

	BACnetObjIdentifier const &getObjectId(void) const;
	BACnetObjectType const *getObjectType(void) const;
	BACnetPropertyType const *getPropertyId(void) const;
	int getArrayIndex(void) const;
	int getWritePriority(void) const;

	bool operator < (const BACnetObjPropRef &rhs) const;

	virtual ~BACnetObjPropRef();
};

#endif /* BACNETAPP_SRC_BACNETOBJPROPREF_H_ */
