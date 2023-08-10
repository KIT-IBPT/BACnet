/*
 * BACnetNull.h
 *
 *  Created on: Jul 2, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETNULL_H_
#define BACNETAPP_SRC_BACNETNULL_H_

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

class BACnetNull : public BACnetAppDataType {
private:
	const string strNull;

public:
	BACnetNull();
	virtual ~BACnetNull();

	static BACnetNull *Null;

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	string toString(void);
	size_t toCString(char *toStr, size_t sizeOfToStr);
	void printData(void);
	size_t getLength(void);
	string getValAsStr();
};

#endif /* BACNETAPP_SRC_BACNETNULL_H_ */
