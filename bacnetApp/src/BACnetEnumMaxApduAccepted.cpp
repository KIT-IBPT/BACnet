/*
 * BACnetEnumMaxApduAccepted.cpp
 *
 *  Created on: Dec 19, 2017
 *      Author: 8w4
 */

#include "BACnetEnumMaxApduAccepted.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

BACnetMaxApduLenAccepted::BACnetMaxApduLenAccepted(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_APDU_LEN_ACCEPTED) {
		stringstream ss;

		ss << "\tError: BACnetMaxApduLenAccepted::BACnetMaxApduLenAccepted(uint16_t const enumValue, string const name):"
				" The valid range for a BACnet MAX-APDU-Length is 0-" << MAX_APDU_LEN_ACCEPTED << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetMaxApduLenAccepted::~BACnetMaxApduLenAccepted() {
	// TODO Auto-generated destructor stub
}

BACnetMaxApduLenAccepted const BACnetEnumMaxApduAccepted::UP_TO_50_OCTETS = BACnetMaxApduLenAccepted(0, "UP_TO_50_OCTETS");
BACnetMaxApduLenAccepted const BACnetEnumMaxApduAccepted::UP_TO_128_OCTETS = BACnetMaxApduLenAccepted(1, "UP_TO_128_OCTETS");
BACnetMaxApduLenAccepted const BACnetEnumMaxApduAccepted::UP_TO_206_OCTETS = BACnetMaxApduLenAccepted(2, "UP_TO_206_OCTETS");
BACnetMaxApduLenAccepted const BACnetEnumMaxApduAccepted::UP_TO_480_OCTETS = BACnetMaxApduLenAccepted(3, "UP_TO_480_OCTETS");
BACnetMaxApduLenAccepted const BACnetEnumMaxApduAccepted::UP_TO_1024_OCTETS = BACnetMaxApduLenAccepted(4, "UP_TO_1024_OCTETS");
BACnetMaxApduLenAccepted const BACnetEnumMaxApduAccepted::UP_TO_1476_OCTETS = BACnetMaxApduLenAccepted(5, "UP_TO_1476_OCTETS");

std::map<uint8_t, BACnetMaxApduLenAccepted const *> BACnetEnumMaxApduAccepted::objectMap = BACnetEnumMaxApduAccepted::init_map();


std::map<uint8_t, BACnetMaxApduLenAccepted const *> BACnetEnumMaxApduAccepted::init_map() {

	std::map<uint8_t, BACnetMaxApduLenAccepted const *> lmap;

	lmap[UP_TO_50_OCTETS.getValue()] = (BACnetMaxApduLenAccepted const *) &UP_TO_50_OCTETS;
	lmap[UP_TO_128_OCTETS.getValue()] = (BACnetMaxApduLenAccepted const *) &UP_TO_128_OCTETS;
	lmap[UP_TO_206_OCTETS.getValue()] = (BACnetMaxApduLenAccepted const *) &UP_TO_206_OCTETS;
	lmap[UP_TO_480_OCTETS.getValue()] = (BACnetMaxApduLenAccepted const *) &UP_TO_480_OCTETS;
	lmap[UP_TO_1024_OCTETS.getValue()] = (BACnetMaxApduLenAccepted const *) &UP_TO_1024_OCTETS;
	lmap[UP_TO_1476_OCTETS.getValue()] = (BACnetMaxApduLenAccepted const *) &UP_TO_1476_OCTETS;

	return lmap;
}

BACnetMaxApduLenAccepted const &BACnetEnumMaxApduAccepted::getEnumByValue(uint8_t enumValue) {

	std::map<uint8_t, BACnetMaxApduLenAccepted const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumMaxApduAccepted::get_supported_object_type(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




