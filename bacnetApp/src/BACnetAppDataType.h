/*
 * BACnetAppDataType.h
 *
 *  Created on: Jun 27, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETAPPDATATYPE_H_
#define BACNETAPP_SRC_BACNETAPPDATATYPE_H_

#include "BACnetEnumApplicationDataType.h"
#include "BACnetApplicationData.h"
#include "epicsMutex.h"

using namespace std;

class BACnetAppDataType {
private:
	BACnetApplicationDataTypeChoice const &dataType;
	bool nullFlag;
	epicsMutex mutx;

public:
	BACnetAppDataType(BACnetApplicationDataTypeChoice const &dataTYPE);
	virtual ~BACnetAppDataType();

	const BACnetApplicationDataTypeChoice &getDataType(void) const;

	void setNullFlag(void);
	void clearNullFlag(void);
	bool isNull(void) const;

	void lock(void);
	void unlock(void);
	bool tryLock(void);

	virtual string getValAsStr(void) = 0;
	virtual void printData(void) = 0;
	virtual void decode(BACnetApplicationData const &appData) = 0;
	virtual void encode(BACnetBuffer &buff) = 0;
	virtual size_t getLength(void) = 0;
};

#endif /* BACNETAPP_SRC_BACNETAPPDATATYPE_H_ */
