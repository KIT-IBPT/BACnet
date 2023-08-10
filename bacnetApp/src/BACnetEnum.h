/*
 * BACnetEnum.h
 *
 *  Created on: Jul 12, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUM_H_
#define BACNETAPP_SRC_BACNETENUM_H_

#include "BACnetEnumSingle.h"

class BACnetEnum {
public:
	BACnetEnum();
	virtual ~BACnetEnum();

	virtual BACnetEnumSingle const &getEnumByValue(unsigned int enumValue) const = 0;
};

#endif /* BACNETAPP_SRC_BACNETENUM_H_ */
