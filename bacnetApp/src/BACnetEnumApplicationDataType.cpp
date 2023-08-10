/*
 * BACnetEnumApplicationDataType.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: 8w4
 */

#include "BACnetEnumApplicationDataType.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

BACnetApplicationDataTypeChoice::BACnetApplicationDataTypeChoice(unsigned int enumValue, string const obj_name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, obj_name)
{

	if(enumValue > MAX_APPDATA_TYPE) {
		stringstream ss;

		ss << "\tError: BACnetApplicationDataTypeChoice::BACnetApplicationDataTypeChoice(uint8_t enumValue, string const obj_name):"
				" The valid range for a BACnet Application Data Type is 0-" << MAX_APPDATA_TYPE << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetApplicationDataTypeChoice::~BACnetApplicationDataTypeChoice() {
	// TODO Auto-generated destructor stub
}

BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::NNULL = BACnetApplicationDataTypeChoice(0, "NULL");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::BOOLEAN = BACnetApplicationDataTypeChoice(1, "BOOLEAN");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::UNSIGNED_INTEGER = BACnetApplicationDataTypeChoice(2, "UNSIGNED_INTEGER");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::SIGNED_INTEGER = BACnetApplicationDataTypeChoice(3, "SIGNED_INTEGER");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::REAL = BACnetApplicationDataTypeChoice(4, "REAL");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::DOUBLE = BACnetApplicationDataTypeChoice(5, "DOUBLE");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::OCTET_STRING = BACnetApplicationDataTypeChoice(6, "OCTET_STRING");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::CHARACTER_STRING = BACnetApplicationDataTypeChoice(7, "CHARACTER_STRING");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::BIT_STRING = BACnetApplicationDataTypeChoice(8, "BIT_STRING");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::ENUMERATED = BACnetApplicationDataTypeChoice(9, "ENUMERATED");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::DATE = BACnetApplicationDataTypeChoice(10, "DATE");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::TIME = BACnetApplicationDataTypeChoice(11, "TIME");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER = BACnetApplicationDataTypeChoice(12, "BACNET_OBJECT_IDENTIFIER");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::ASHRAE_RESERVED_13 = BACnetApplicationDataTypeChoice(13, "ASHRAE_RESERVED_13");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::ASHRAE_RESERVED_14 = BACnetApplicationDataTypeChoice(14, "ASHRAE_RESERVED_14");
BACnetApplicationDataTypeChoice const BACnetEnumApplicationDataType::ASHRAE_RESERVED_15 = BACnetApplicationDataTypeChoice(15, "ASHRAE_RESERVED_15");


std::map<uint8_t, BACnetApplicationDataTypeChoice const *> BACnetEnumApplicationDataType::objectMap = BACnetEnumApplicationDataType::init_map();


std::map<uint8_t, BACnetApplicationDataTypeChoice const *> BACnetEnumApplicationDataType::init_map() {

	std::map<uint8_t, BACnetApplicationDataTypeChoice const *> lmap;

	lmap[NNULL.getValue()] = (BACnetApplicationDataTypeChoice const *) &NNULL;
	lmap[BOOLEAN.getValue()] = (BACnetApplicationDataTypeChoice const *) &BOOLEAN;
	lmap[UNSIGNED_INTEGER.getValue()] = (BACnetApplicationDataTypeChoice const *) &UNSIGNED_INTEGER;
	lmap[SIGNED_INTEGER.getValue()] = (BACnetApplicationDataTypeChoice const *) &SIGNED_INTEGER;
	lmap[REAL.getValue()] = (BACnetApplicationDataTypeChoice const *) &REAL;
	lmap[DOUBLE.getValue()] = (BACnetApplicationDataTypeChoice const *) &DOUBLE;
	lmap[OCTET_STRING.getValue()] = (BACnetApplicationDataTypeChoice const *) &OCTET_STRING;
	lmap[CHARACTER_STRING.getValue()] = (BACnetApplicationDataTypeChoice const *) &CHARACTER_STRING;
	lmap[BIT_STRING.getValue()] = (BACnetApplicationDataTypeChoice const *) &BIT_STRING;
	lmap[ENUMERATED.getValue()] = (BACnetApplicationDataTypeChoice const *) &ENUMERATED;
	lmap[DATE.getValue()] = (BACnetApplicationDataTypeChoice const *) &DATE;
	lmap[TIME.getValue()] = (BACnetApplicationDataTypeChoice const *) &TIME;
	lmap[BACNET_OBJECT_IDENTIFIER.getValue()] = (BACnetApplicationDataTypeChoice const *) &BACNET_OBJECT_IDENTIFIER;
	lmap[ASHRAE_RESERVED_13.getValue()] = (BACnetApplicationDataTypeChoice const *) &ASHRAE_RESERVED_13;
	lmap[ASHRAE_RESERVED_14.getValue()] = (BACnetApplicationDataTypeChoice const *) &ASHRAE_RESERVED_14;
	lmap[ASHRAE_RESERVED_15.getValue()] = (BACnetApplicationDataTypeChoice const *) &ASHRAE_RESERVED_15;

	return lmap;
}

BACnetApplicationDataTypeChoice const &BACnetEnumApplicationDataType::getEnumByValue(uint8_t enumValue) {

	std::map<uint8_t, BACnetApplicationDataTypeChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumApplicationDataType::get_supported_object_type(uint8_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}

