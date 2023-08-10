/*
 * BACnetPropRefValue.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: 8w4
 */

#include "BACnetPropRefValue.h"

BACnetPropRefValue::BACnetPropRefValue()
:propId(NULL), arrayIndx(-1), dataLst()
{
	// TODO Auto-generated constructor stub

}

BACnetPropRefValue::~BACnetPropRefValue() {
	// TODO Auto-generated destructor stub
}


void BACnetPropRefValue::setData(uint32_t propertyId, int arrIndx, appDataList_t &dataLst) {
	this->propId = &BACnetEnumPropertyIdentifier::getEnumByValue(propertyId);
	this->arrayIndx = arrIndx;
	this->dataLst = dataLst;
}

void BACnetPropRefValue::clearData(void) {
	this->propId = NULL;
	this->arrayIndx = (-1);
	this->dataLst.clear();

}

const BACnetPropertyType *BACnetPropRefValue::getPropertyId(void) const {
	return this->propId;
}

int BACnetPropRefValue::getArrayIndex(void) const {
	return this->arrayIndx;
}

appDataList_t::const_iterator BACnetPropRefValue::getDataListBegin(void) const {
	return this->dataLst.begin();
}

appDataList_t::const_iterator BACnetPropRefValue::getDataListEnd(void) const {
	return this->dataLst.end();
}
















