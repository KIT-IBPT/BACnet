/*
 * BACnetUnsignedInt.h
 *
 *  Created on: Jul 2, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETUNSIGNEDINT_H_
#define BACNETAPP_SRC_BACNETUNSIGNEDINT_H_

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

class BACnetUnsignedInt : public BACnetAppDataType {
private:
	uint32_t value;

public:
	BACnetUnsignedInt();
	virtual ~BACnetUnsignedInt();

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

#endif /* BACNETAPP_SRC_BACNETUNSIGNEDINT_H_ */
