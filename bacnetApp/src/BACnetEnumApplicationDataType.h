/*
 * BACnetEnumApplicationDataType.h
 *
 *  Created on: Sep 14, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMAPPLICATIONDATATYPE_H_
#define BACNETAPP_SRC_BACNETENUMAPPLICATIONDATATYPE_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"
//#include "BACnetApplicationDataTypeChoice.h"

using namespace std;

#define MAX_APPDATA_TYPE 0x0F

class BACnetApplicationDataTypeChoice : public BACnetEnumSingle {

public:
	BACnetApplicationDataTypeChoice(unsigned int enumValue, string const obj_name);
	virtual ~BACnetApplicationDataTypeChoice();
};

class BACnetEnumApplicationDataType {

private:
	static std::map<uint8_t, BACnetApplicationDataTypeChoice const *> objectMap;

	static std::map<uint8_t, BACnetApplicationDataTypeChoice const *> init_map(void);

public:

	static BACnetApplicationDataTypeChoice const NNULL;
	static BACnetApplicationDataTypeChoice const BOOLEAN;
	static BACnetApplicationDataTypeChoice const UNSIGNED_INTEGER;
	static BACnetApplicationDataTypeChoice const SIGNED_INTEGER;
	static BACnetApplicationDataTypeChoice const REAL;
	static BACnetApplicationDataTypeChoice const DOUBLE;
	static BACnetApplicationDataTypeChoice const OCTET_STRING;
	static BACnetApplicationDataTypeChoice const CHARACTER_STRING;
	static BACnetApplicationDataTypeChoice const BIT_STRING;
	static BACnetApplicationDataTypeChoice const ENUMERATED;
	static BACnetApplicationDataTypeChoice const DATE;
	static BACnetApplicationDataTypeChoice const TIME;
	static BACnetApplicationDataTypeChoice const BACNET_OBJECT_IDENTIFIER;
	static BACnetApplicationDataTypeChoice const ASHRAE_RESERVED_13;
	static BACnetApplicationDataTypeChoice const ASHRAE_RESERVED_14;
	static BACnetApplicationDataTypeChoice const ASHRAE_RESERVED_15;

	static BACnetApplicationDataTypeChoice const &getEnumByValue(uint8_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMAPPLICATIONDATATYPE_H_ */
