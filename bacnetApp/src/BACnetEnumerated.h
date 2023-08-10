/*
 * BACnetEnumerated.h
 *
 *  Created on: Jul 2, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMERATED_H_
#define BACNETAPP_SRC_BACNETENUMERATED_H_

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"
#include "BACnetEnum.h"

using namespace std;

class BACnetEnumerated : public BACnetAppDataType {
private:
	uint32_t value;

	BACnetEnum const *enumm;

public:
	BACnetEnumerated();
	BACnetEnumerated(BACnetEnum const &enm);
	virtual ~BACnetEnumerated();

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	uint32_t getValue(void) const;
	void setValue(uint32_t val);
	string toString(void);
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);
};

#endif /* BACNETAPP_SRC_BACNETENUMERATED_H_ */
