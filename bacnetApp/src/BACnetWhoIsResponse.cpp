/*
 * BACnetWhoIsResponse.cpp
 *
 *  Created on: Sep 25, 2017
 *      Author: 8w4
 */

#include "BACnetWhoIsResponse.h"

BACnetWhoIsResponse::BACnetWhoIsResponse() {
	// TODO Auto-generated constructor stub

}

BACnetWhoIsResponse::BACnetWhoIsResponse(BACnetDeviceAddress &src, BACnetBuffer &buff) {
	decode(src, buff);
}

BACnetWhoIsResponse::~BACnetWhoIsResponse() {
	// TODO Auto-generated destructor stub
}

void BACnetWhoIsResponse::decode(BACnetDeviceAddress &src, BACnetBuffer &buff) {
	this->addr = src;
	this->iam.decode(buff);
}

void BACnetWhoIsResponse::getDeviceAddress(BACnetDeviceAddress &addr) const {
	this->addr.getAddressData(addr);
}

void BACnetWhoIsResponse::getIamData(BACnetObjIdentifier &objId, uint32_t *maxApduLengthAcc,
		BACnetSegmentation const **segmentSupported, uint16_t *vendorId) const {


	BACnetObjIdentifier::copyObjectId(objId, *this->getObjectId());

	if(maxApduLengthAcc) {
		*maxApduLengthAcc = this->getMaxApduLengthAccepted();
	}
	if(segmentSupported) {
		*segmentSupported = this->getSegmentationSupported();
	}
	if(vendorId) {
		*vendorId = this->getVendorId();
	}


}

BACnetObjIdentifier const *BACnetWhoIsResponse::getObjectId(void) const {
	return this->iam.getObjectId();
}

uint32_t BACnetWhoIsResponse::getMaxApduLengthAccepted(void) const {
	return this->iam.getMaxApduAccepted();
}

BACnetSegmentation const *BACnetWhoIsResponse::getSegmentationSupported(void) const {
	return this->iam.getSegmentationSupported();
}

uint16_t BACnetWhoIsResponse::getVendorId(void) const {
	return this->iam.getVendorId();
}

