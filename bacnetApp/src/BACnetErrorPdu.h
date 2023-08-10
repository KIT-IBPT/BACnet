/*
 * BACnetErrorPdu.h
 *
 *  Created on: Aug 9, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETERRORPDU_H_
#define BACNETAPP_SRC_BACNETERRORPDU_H_

#include "BACnetBuffer.h"
#include "BACnetEnumConfSvc.h"
#include "BACnetEnumErrorClass.h"
#include "BACnetEnumErrorCode.h"

using namespace std;

class BACnetErrorPdu {
private:
	uint8_t invokeId;
	BACnetConfSvcChoice const *errChoice;
	BACnetErrClassChoice const *errClass;
	BACnetErrCodeChoice const *errCode;

public:
	BACnetErrorPdu();
	BACnetErrorPdu(const BACnetErrorPdu &rhs);
	virtual ~BACnetErrorPdu();

	BACnetErrorPdu &operator = (const BACnetErrorPdu &rhs);
	void clearData(void);

	void decode(BACnetBuffer &buff);

	uint8_t getInvokeId(void) const;
	BACnetConfSvcChoice const *getErrorChoice(void) const;
	BACnetErrClassChoice const *getErrorClass(void) const;
	BACnetErrCodeChoice const *getErrorCode(void) const;
	string toString(void) const;
};

#endif /* BACNETAPP_SRC_BACNETERRORPDU_H_ */
