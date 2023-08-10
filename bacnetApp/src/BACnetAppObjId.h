/*
 * BACnetAppObjId.h
 *
 *  Created on: Jul 30, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETAPPOBJID_H_
#define BACNETAPP_SRC_BACNETAPPOBJID_H_

#include "BACnetObjIdentifier.h"

class BACnetAppObjId : public BACnetObjIdentifier, public BACnetAppDataType {

public:
	BACnetAppObjId();
	virtual ~BACnetAppObjId();

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	string toString(void);
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);
};

#endif /* BACNETAPP_SRC_BACNETAPPOBJID_H_ */
