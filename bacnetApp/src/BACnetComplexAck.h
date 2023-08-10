/*
 * BACnetComplexAck.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETCOMPLEXACK_H_
#define BACNETAPP_SRC_BACNETCOMPLEXACK_H_

#include "BACnetBuffer.h"
#include "BACnetApdu.h"
#include "BACnetObjIdentifier.h"
#include "BACnetDefs.h"
#include "BACnetApplicationData.h"

using namespace std;

class BACnetComplexAck  : public BACnetApdu {
private:
	Confirmed_Req_PCI pci;
	BACnetConfSvcChoice const *cSvcChoice;
	BACnetObjIdentifier objId;
	BACnetPropertyType const *propId;
	int arrayIndex;

public:
	BACnetComplexAck();
	virtual ~BACnetComplexAck();

	/** Get the length of encoding */
	size_t get_length(void) const;


	/** Encode this whoIs service into a buffer */
	int encode(BACnetBuffer &buff);

	void decode(BACnetBuffer &buff);

	uint8_t getInvokeId(void) const;
	BACnetConfSvcChoice const *getServiceChoice(void) const;

	BACnetObjIdentifier const &getObjectId(void) const;
	BACnetPropertyType const *getPropertyId(void) const;
};

#endif /* BACNETAPP_SRC_BACNETCOMPLEXACK_H_ */
