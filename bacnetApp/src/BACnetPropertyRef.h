/*
 * BACnetPropertyRef.h
 *
 *  Created on: Aug 13, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETPROPERTYREF_H_
#define BACNETAPP_SRC_BACNETPROPERTYREF_H_

#include "BACnetEnumPropertyIdentifier.h"

using namespace std;

class BACnetPropertyRef {
private:
	const BACnetPropertyType *propType;
	int arrayIndex;

public:
	BACnetPropertyRef(const BACnetPropertyType &propT);
	BACnetPropertyRef(const BACnetPropertyType &propT, int arrIndx);
	virtual ~BACnetPropertyRef();

	const BACnetPropertyType *getPropRef(void);
	int getArrayIndex(void);
};

#endif /* BACNETAPP_SRC_BACNETPROPERTYREF_H_ */
