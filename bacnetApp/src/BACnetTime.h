/*
 * BACnetTime.h
 *
 *  Created on: Jul 3, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETTIME_H_
#define BACNETAPP_SRC_BACNETTIME_H_

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

class BACnetTime : public BACnetAppDataType {
private:
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t secFrac;

public:
	BACnetTime();
	virtual ~BACnetTime();

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	uint32_t getTimeAsUnsignedInt(void) const;

	string toString(void);
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);
};

#endif /* BACNETAPP_SRC_BACNETTIME_H_ */
