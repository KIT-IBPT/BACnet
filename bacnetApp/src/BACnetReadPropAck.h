/*
 * BACnetReadPropAck.h
 *
 *  Created on: Aug 2, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETREADPROPACK_H_
#define BACNETAPP_SRC_BACNETREADPROPACK_H_

#include "BACnetBuffer.h"
#include "BACnetObjIdentifier.h"
#include "BACnetDefs.h"
#include "BACnetApplicationData.h"

using namespace std;

typedef std::list<BACnetApplicationData> appDataList_t;

class BACnetReadPropAck {
private:
	BACnetObjIdentifier objId;
	BACnetPropertyType const *propId;
	int arrayIndex;
	appDataList_t appdata;

public:
	BACnetReadPropAck();
	virtual ~BACnetReadPropAck();

	void decode(BACnetBuffer &buff);

	BACnetObjIdentifier const &getObjectId(void) const;
	BACnetPropertyType const *getPropertyId(void) const;
	int getArrayIndex(void) const;
	appDataList_t &getAppDataList(void);
};

#endif /* BACNETAPP_SRC_BACNETREADPROPACK_H_ */
