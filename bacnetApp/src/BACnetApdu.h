/*
 * BACnetApdu.h
 *
 *  Created on: Sep 8, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETAPDU_H_
#define BACNETAPP_SRC_BACNETAPDU_H_

#include <iostream>

#include "BACnetBuffer.h"
#include "BACnetEnumSingle.h"

using namespace std;

class BACnetApdu {
private:
	BACnetEnumSingle const *pduType;
	BACnetEnumSingle const *svcChoice;

public:

	BACnetApdu(BACnetEnumSingle const *pduT, BACnetEnumSingle const *svcT);
	virtual ~BACnetApdu();

	virtual int encode(BACnetBuffer &buff) = 0;
	virtual size_t get_length(void) const = 0;

	BACnetEnumSingle const *getPduType(void) const;
	BACnetEnumSingle const *getServiceChoice(void) const;
};

#endif /* BACNETAPP_SRC_BACNETAPDU_H_ */
