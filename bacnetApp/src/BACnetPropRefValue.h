/*
 * BACnetPropRefValue.h
 *
 *  Created on: Aug 17, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETPROPREFVALUE_H_
#define BACNETAPP_SRC_BACNETPROPREFVALUE_H_

#include "BACnetApplicationData.h"

using namespace std;

typedef std::list<BACnetApplicationData> appDataList_t;

class BACnetPropRefValue {
private:
	const BACnetPropertyType *propId;
	int arrayIndx;
	appDataList_t dataLst;

public:
	BACnetPropRefValue();
	virtual ~BACnetPropRefValue();

	void setData(uint32_t propertyId, int arrIndx, appDataList_t &dataLst);
	void clearData(void);

	const BACnetPropertyType *getPropertyId(void) const;
	int getArrayIndex(void) const;
	appDataList_t::const_iterator getDataListBegin(void) const;
	appDataList_t::const_iterator getDataListEnd(void) const;

};

#endif /* BACNETAPP_SRC_BACNETPROPREFVALUE_H_ */
