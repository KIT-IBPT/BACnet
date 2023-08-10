/*
 * BACnetApdu.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: 8w4
 */

#include "BACnetApdu.h"

BACnetApdu::BACnetApdu(BACnetEnumSingle const *pduT, BACnetEnumSingle const *svcT)
:pduType(pduT), svcChoice(svcT)
{

}

BACnetApdu::~BACnetApdu() {

}

BACnetEnumSingle const *BACnetApdu::getPduType(void) const {
	return pduType;
}

BACnetEnumSingle const *BACnetApdu::getServiceChoice(void) const {
	return svcChoice;
}



