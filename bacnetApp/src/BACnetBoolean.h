/*
 * BACnetBoolean.h
 *
 *  Created on: Jun 29, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETBOOLEAN_H_
#define BACNETAPP_SRC_BACNETBOOLEAN_H_

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

class BACnetBoolean : public BACnetAppDataType {
private:
	bool value;

public:
	BACnetBoolean();
	virtual ~BACnetBoolean();

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);

	void setValue(bool val);
	bool getValue(void) const;
	string toString(void);
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);
};

#endif /* BACNETAPP_SRC_BACNETBOOLEAN_H_ */
