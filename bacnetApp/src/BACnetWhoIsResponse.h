/*
 * BACnetWhoIsResponse.h
 *
 *  Created on: Sep 25, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETWHOISRESPONSE_H_
#define BACNETAPP_SRC_BACNETWHOISRESPONSE_H_

#include <iostream>
#include <string>
#include <stdint.h>

#include "BACnetDefs.h"
#include "BACnetBuffer.h"
#include "BACnetDeviceAddress.h"
#include "BACnetIamService.h"


using namespace std;

class BACnetWhoIsResponse {
private:

	BACnetDeviceAddress addr;
	BACnetIamService iam;

public:
	BACnetWhoIsResponse();
	BACnetWhoIsResponse(BACnetDeviceAddress &src, BACnetBuffer &buff);

	virtual ~BACnetWhoIsResponse();

	void decode(BACnetDeviceAddress &src, BACnetBuffer &buff);

	void getDeviceAddress(BACnetDeviceAddress &addr) const;
	void getIamData(BACnetObjIdentifier &objId, uint32_t *maxApduLengthAcc,
			BACnetSegmentation const **segmentSupported, uint16_t *vendorId) const;

	BACnetObjIdentifier const *getObjectId(void) const;
	uint32_t getMaxApduLengthAccepted(void) const;
	BACnetSegmentation const *getSegmentationSupported(void) const;
	uint16_t getVendorId(void) const;

};

#endif /* BACNETAPP_SRC_BACNETWHOISRESPONSE_H_ */
