/*
 * BACnetDate.h
 *
 *  Created on: Jul 3, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETDATE_H_
#define BACNETAPP_SRC_BACNETDATE_H_

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

class BACnetDate : public BACnetAppDataType {
private:
	uint16_t year; /** minus 1900 */
	uint8_t month;
	uint8_t dayOfMonth;
	uint8_t dayOfWeek;

public:
	BACnetDate();
	virtual ~BACnetDate();

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	uint32_t getDateAsUnsignedInt(void) const;

	string toString(void);
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);
};

#endif /* BACNETAPP_SRC_BACNETDATE_H_ */
