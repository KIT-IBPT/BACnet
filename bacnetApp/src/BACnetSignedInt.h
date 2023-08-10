/*
 * BACnetSignedInt.h
 *
 *  Created on: Jul 2, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETSIGNEDINT_H_
#define BACNETAPP_SRC_BACNETSIGNEDINT_H_

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

class BACnetSignedInt : public BACnetAppDataType {
private:
	int32_t value;

public:
	BACnetSignedInt();
	virtual ~BACnetSignedInt();

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	int32_t getValue(void) const;
	void setValue(int32_t val);
	string toString(void);
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);
};

#endif /* BACNETAPP_SRC_BACNETSIGNEDINT_H_ */
