/*
 * BACnetIamService.h
 *
 *  Created on: Sep 13, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETIAMSERVICE_H_
#define BACNETAPP_SRC_BACNETIAMSERVICE_H_

#include <iostream>
#include <stdint.h>

#include "BACnetBuffer.h"
#include "BACnetObjIdentifier.h"
#include "BACnetDefs.h"

using namespace std;

class BACnetIamService {
private:
	BACnetObjIdentifier objectId;
	uint32_t maxApduLengthAccepted;
	BACnetSegmentation const *segmentationSupported;
	uint16_t vendorId;

public:
	BACnetIamService();
	virtual ~BACnetIamService();

	BACnetObjIdentifier const *getObjectId(void) const;
	uint32_t getObjectIstance(void) const;
	uint32_t getMaxApduAccepted(void) const;
	BACnetSegmentation const *getSegmentationSupported(void) const;
	uint16_t getVendorId(void) const;

	void decode(BACnetBuffer &buff);

	friend std::ostream& operator<< (std::ostream &out, const BACnetIamService &bacIam);
};

#endif /* BACNETAPP_SRC_BACNETIAMSERVICE_H_ */
