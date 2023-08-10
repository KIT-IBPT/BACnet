/*
 * BACnetEnumBinary.h
 *
 *  Created on: Jun 29, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMBINARY_H_
#define BACNETAPP_SRC_BACNETENUMBINARY_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_BINARY_CHOICE 0x01

class BACnetBinaryChoice : public BACnetEnumSingle {

public:
	BACnetBinaryChoice(uint16_t const enumValue, string const name);
	virtual ~BACnetBinaryChoice();
};

class BACnetEnumBinary {
private:
	static std::map<uint16_t, BACnetBinaryChoice const *> objectMap;

	static std::map<uint16_t, BACnetBinaryChoice const *> init_map(void);
public:
	static BACnetBinaryChoice const INACTIVE;
	static BACnetBinaryChoice const ACTIVE;

	static BACnetBinaryChoice const &getEnumByValue(uint16_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMBINARY_H_ */
