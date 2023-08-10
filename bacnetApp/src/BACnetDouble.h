/*
 * BACnetDouble.h
 *
 *  Created on: Jun 27, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETDOUBLE_H_
#define BACNETAPP_SRC_BACNETDOUBLE_H_

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"
#include "BACnetNull.h"

using namespace std;

class BACnetDouble : public BACnetAppDataType {
private:
	double value;

	void reverseBytes(uint8_t *pUi8);

public:
	BACnetDouble();
	virtual ~BACnetDouble();

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	double getValue(void) const;
	void setValue(double val);
	string toString(void);
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);
};

#endif /* BACNETAPP_SRC_BACNETDOUBLE_H_ */
