/*
 * BACnetRpmResult.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: 8w4
 */

#include "BACnetRpmResult.h"

BACnetRpmResult::BACnetRpmResult()
:objId(), propRefVal()
{
	// TODO Auto-generated constructor stub

}

BACnetRpmResult::~BACnetRpmResult() {
	// TODO Auto-generated destructor stub
}

void BACnetRpmResult::setData(BACnetObjIdentifier &objId, std::list<BACnetPropRefValue> &pRefLst) {

	this->objId = objId;
	this->propRefVal = pRefLst;
}

void BACnetRpmResult::clearData(void) {
	this->objId.clear();
	this->propRefVal.clear();
}

size_t BACnetRpmResult::getPropRefValListSize(void) const {
	return this->propRefVal.size();
}

BACnetObjIdentifier const &BACnetRpmResult::getObjectId(void) const {
	return this->objId;
}

propRefValLst_t::const_iterator BACnetRpmResult::getPropRefValueListBegin(void) const {
	return this->propRefVal.begin();
}

propRefValLst_t::const_iterator BACnetRpmResult::getPropRefValueListEnd(void) const {
	return this->propRefVal.end();
}

