/*
 * BACnetEnumBinary.cpp
 *
 *  Created on: Jun 29, 2018
 *      Author: 8w4
 */

#include <BACnetEnumBinary.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


BACnetBinaryChoice::BACnetBinaryChoice(uint16_t const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_BINARY_CHOICE) {
		stringstream ss;

		ss << "\tError: BACnetBinaryChoice::BACnetBinaryChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Binary Choice is 0-" << MAX_BINARY_CHOICE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetBinaryChoice::~BACnetBinaryChoice() {
	// TODO Auto-generated destructor stub
}

BACnetBinaryChoice const BACnetEnumBinary::INACTIVE = BACnetBinaryChoice(0, "INACTIVE");
BACnetBinaryChoice const BACnetEnumBinary::ACTIVE = BACnetBinaryChoice(1, "ACTIVE");

std::map<uint16_t, BACnetBinaryChoice const *> BACnetEnumBinary::objectMap = BACnetEnumBinary::init_map();


std::map<uint16_t, BACnetBinaryChoice const *> BACnetEnumBinary::init_map() {

	std::map<uint16_t, BACnetBinaryChoice const *> lmap;

	lmap[INACTIVE.getValue()] = (BACnetBinaryChoice const *) &INACTIVE;
	lmap[ACTIVE.getValue()] = (BACnetBinaryChoice const *) &ACTIVE;

	return lmap;
}

BACnetBinaryChoice const &BACnetEnumBinary::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetBinaryChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumBinary::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}

