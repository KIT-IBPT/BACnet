/*
 * BACnetReadPropertyService.h
 *
 *  Created on: Dec 19, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETREADPROPERTYSERVICE_H_
#define BACNETAPP_SRC_BACNETREADPROPERTYSERVICE_H_

#include "BACnetBuffer.h"
#include "BACnetApdu.h"
#include "BACnetObjIdentifier.h"
#include "BACnetDefs.h"
#include "BACnetObjPropRef.h"

using namespace std;

class BACnetReadPropertyService : public BACnetApdu {

private:
	Confirmed_Req_PCI pci;
	BACnetObjIdentifier objId;
	BACnetPropertyType const *propId;
	int arrayIndex;

public:
	BACnetReadPropertyService();

	virtual ~BACnetReadPropertyService();

	/** Get the length of encoding */
	size_t get_length(void) const;

	/** Encode this whoIs service into a buffer */
	int encode(BACnetBuffer &buff);

	void makeUnsegmentedRequest(uint8_t invokeId, BACnetObjPropRef const &objProp);

};

#endif /* BACNETAPP_SRC_BACNETREADPROPERTYSERVICE_H_ */
