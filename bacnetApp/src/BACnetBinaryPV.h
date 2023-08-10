/*
 * BACnetBinaryPV.h
 *
 *  Created on: Jul 2, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETBINARYPV_H_
#define BACNETAPP_SRC_BACNETBINARYPV_H_

#include "BACnetEnumBinary.h"
#include "BACnetEnumerated.h"

using namespace std;

class BACnetBinaryPV : public BACnetEnumerated {
public:
	BACnetBinaryPV();
	virtual ~BACnetBinaryPV();

	bool getValue(void);

	string toString(void) const;
	void printData(void);
	size_t getLength(void);
};

#endif /* BACNETAPP_SRC_BACNETBINARYPV_H_ */
