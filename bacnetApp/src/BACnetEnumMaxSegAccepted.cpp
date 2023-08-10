/*
 * BACnetEnumMaxSegAccepted.cpp
 *
 *  Created on: Dec 19, 2017
 *      Author: 8w4
 */

#include "BACnetEnumMaxSegAccepted.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

BACnetMaxSegmentsAccepted::BACnetMaxSegmentsAccepted(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_SEGMENT_ACCEPTED) {
		stringstream ss;

		ss << "\tError: BACnetMaxSegmentsAccepted::BACnetMaxSegmentsAccepted(uint16_t const enumValue, string const name):"
				" The valid range for a BACnet MAX-Segmentation is 0-" << MAX_SEGMENT_ACCEPTED << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetMaxSegmentsAccepted::~BACnetMaxSegmentsAccepted() {
	// TODO Auto-generated destructor stub
}

BACnetMaxSegmentsAccepted const BACnetEnumMaxSegAccepted::UNSPECIFIED = BACnetMaxSegmentsAccepted(0, "UNSPECIFIED");
BACnetMaxSegmentsAccepted const BACnetEnumMaxSegAccepted::TWO = BACnetMaxSegmentsAccepted(1, "TWO");
BACnetMaxSegmentsAccepted const BACnetEnumMaxSegAccepted::FOUR = BACnetMaxSegmentsAccepted(2, "FOUR");
BACnetMaxSegmentsAccepted const BACnetEnumMaxSegAccepted::EIGHT = BACnetMaxSegmentsAccepted(3, "EIGHT");
BACnetMaxSegmentsAccepted const BACnetEnumMaxSegAccepted::SIXTEEN = BACnetMaxSegmentsAccepted(4, "SIXTEEN");
BACnetMaxSegmentsAccepted const BACnetEnumMaxSegAccepted::THIRTY_TWO = BACnetMaxSegmentsAccepted(5, "THIRTY_TWO");
BACnetMaxSegmentsAccepted const BACnetEnumMaxSegAccepted::SIXTY_FOUR = BACnetMaxSegmentsAccepted(6, "SIXTY_FOUR");
BACnetMaxSegmentsAccepted const BACnetEnumMaxSegAccepted::GREATER_THAN_64 = BACnetMaxSegmentsAccepted(7, "GREATER_THAN_64");

std::map<uint8_t, BACnetMaxSegmentsAccepted const *> BACnetEnumMaxSegAccepted::objectMap = BACnetEnumMaxSegAccepted::init_map();


std::map<uint8_t, BACnetMaxSegmentsAccepted const *> BACnetEnumMaxSegAccepted::init_map() {

	std::map<uint8_t, BACnetMaxSegmentsAccepted const *> lmap;

	lmap[UNSPECIFIED.getValue()] = (BACnetMaxSegmentsAccepted const *) &UNSPECIFIED;
	lmap[TWO.getValue()] = (BACnetMaxSegmentsAccepted const *) &TWO;
	lmap[FOUR.getValue()] = (BACnetMaxSegmentsAccepted const *) &FOUR;
	lmap[EIGHT.getValue()] = (BACnetMaxSegmentsAccepted const *) &EIGHT;
	lmap[SIXTEEN.getValue()] = (BACnetMaxSegmentsAccepted const *) &SIXTEEN;
	lmap[THIRTY_TWO.getValue()] = (BACnetMaxSegmentsAccepted const *) &THIRTY_TWO;
	lmap[SIXTY_FOUR.getValue()] = (BACnetMaxSegmentsAccepted const *) &SIXTY_FOUR;
	lmap[GREATER_THAN_64.getValue()] = (BACnetMaxSegmentsAccepted const *) &GREATER_THAN_64;

	return lmap;
}

BACnetMaxSegmentsAccepted const &BACnetEnumMaxSegAccepted::getEnumByValue(uint8_t enumValue) {

	std::map<uint8_t, BACnetMaxSegmentsAccepted const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumMaxSegAccepted::get_supported_object_type(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




