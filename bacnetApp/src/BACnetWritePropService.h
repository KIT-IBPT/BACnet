/*
 * BACnetWritePropService.h
 *
 *  Created on: Jul 31, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETWRITEPROPSERVICE_H_
#define BACNETAPP_SRC_BACNETWRITEPROPSERVICE_H_

#include "BACnetBuffer.h"
#include "BACnetApdu.h"
#include "BACnetObjIdentifier.h"
#include "BACnetDefs.h"
#include "BACnetObjPropRef.h"

using namespace std;

class BACnetWritePropService : public BACnetApdu {
private:
	Confirmed_Req_PCI pci;
	BACnetObjIdentifier objId;
	BACnetPropertyType const *propId;
	int arrayIndex;
	int writePriority;
	BACnetAppDataType *appData;

public:
	BACnetWritePropService();

	virtual ~BACnetWritePropService();

	/** Get the length of encoding */
	size_t get_length(void) const;

	/** Encode this whoIs service into a buffer */
	int encode(BACnetBuffer &buff);

	void makeUnsegmentedRequest(uint8_t invokeId, BACnetObjPropRef const &objProp, BACnetAppDataType *appData);

};

#endif /* BACNETAPP_SRC_BACNETWRITEPROPSERVICE_H_ */
