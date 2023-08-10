/*
 * BACnetEnumCharSet.h
 *
 *  Created on: Jul 3, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMCHARSET_H_
#define BACNETAPP_SRC_BACNETENUMCHARSET_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_CHARACTER_CHOICE 0x05

class BACnetCharChoice : public BACnetEnumSingle {

public:
	BACnetCharChoice(uint16_t const enumValue, string const name);
	virtual ~BACnetCharChoice();
};

class BACnetEnumCharSet {
private:
	static std::map<uint16_t, BACnetCharChoice const *> objectMap;

	static std::map<uint16_t, BACnetCharChoice const *> init_map(void);
public:

	static BACnetCharChoice const CHARACTER_UTF8;
	static BACnetCharChoice const CHARACTER_MS_DBCS;
	static BACnetCharChoice const CHARACTER_JISC_6226;
	static BACnetCharChoice const CHARACTER_UCS4;
	static BACnetCharChoice const CHARACTER_UCS2;
	static BACnetCharChoice const CHARACTER_ISO8859;


	static BACnetCharChoice const &getEnumByValue(uint16_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMCHARSET_H_ */
