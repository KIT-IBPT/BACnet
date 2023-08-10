/*
 * BACnetPropertyRef.cpp
 *
 *  Created on: Aug 13, 2018
 *      Author: 8w4
 */

#include "BACnetPropertyRef.h"

BACnetPropertyRef::BACnetPropertyRef(const BACnetPropertyType &propT)
:propType(&propT), arrayIndex(-1)
{
	// TODO Auto-generated constructor stub

}

BACnetPropertyRef::BACnetPropertyRef(const BACnetPropertyType &propT, int arrIndx)
:propType(&propT), arrayIndex(arrIndx)
{

}

BACnetPropertyRef::~BACnetPropertyRef() {
	// TODO Auto-generated destructor stub
}

const BACnetPropertyType *BACnetPropertyRef::getPropRef(void) {
	return this->propType;
}

int BACnetPropertyRef::getArrayIndex(void) {
	return this->arrayIndex;
}


