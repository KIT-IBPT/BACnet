/*
 * BACnetRpmAck.h
 *
 *  Created on: Aug 15, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETRPMACK_H_
#define BACNETAPP_SRC_BACNETRPMACK_H_

#include "BACnetBuffer.h"
#include "BACnetObjIdentifier.h"
#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetRpmResult.h"

using namespace std;

typedef std::list<BACnetApplicationData> appDataList_t;
typedef std::list<BACnetRpmResult> rpmResultList_t;

class BACnetRpmAck {
private:

	rpmResultList_t readResult;

	const uint8_t *decodeObjectId(BACnetBuffer &buff, BACnetObjIdentifier &objId);
	const uint8_t *decodePropertyId(BACnetBuffer &buff, uint32_t &propId);
	const uint8_t *decodeArrayIndex(BACnetBuffer &buff, int &arrayIndex);
	bool isArrayIndex(const uint8_t *ptr);
	const uint8_t *decodeReadResult(BACnetBuffer &buff, appDataList_t &ackData);
	const uint8_t *decodeContextSpecificOpeningTag(BACnetBuffer &buff, int tagNumber);
	const uint8_t *decodeContextSpecificClosingTag(BACnetBuffer &buff, int tagNumber);

	const uint8_t *decodeListOfResults(BACnetBuffer &buff, uint32_t &pid, int &arrayIndx,
			appDataList_t &ackData);

	const uint8_t *decodeListOfResults(BACnetBuffer &buff, BACnetPropRefValue &prefvalue);

public:
	BACnetRpmAck();
	virtual ~BACnetRpmAck();

	void decode(BACnetBuffer &buff);
	rpmResultList_t &getRpmResultList(void);
	size_t getNumberOfResultItems(void);
	size_t getNumberOfObjectIds(void) const;

	rpmResultList_t::const_iterator getIteratorToResultBegin(void) const;
	rpmResultList_t::const_iterator getIteratorToResultEnd(void) const;

};

#endif /* BACNETAPP_SRC_BACNETRPMACK_H_ */
