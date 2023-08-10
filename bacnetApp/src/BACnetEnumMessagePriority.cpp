/*
 * BACnetEnumMessagePriority.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: 8w4
 */

#include <stdexcept>
#include <iostream>
#include <sstream>

#include <BACnetEnumMessagePriority.h>

BACnetMessagePriority::BACnetMessagePriority(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_MESSAGE_PRIORITY) {
		stringstream ss;

		ss << "\tError: BACnetMessagePriority::BACnetMessagePriority(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Message Priority is 0-" << MAX_MESSAGE_PRIORITY << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetMessagePriority::~BACnetMessagePriority() {
	// TODO Auto-generated destructor stub
}

BACnetMessagePriority const BACnetEnumMessagePriority::NORMAL = BACnetMessagePriority(0, "NORMAL");
BACnetMessagePriority const BACnetEnumMessagePriority::URGENT = BACnetMessagePriority(1, "URGENT");
BACnetMessagePriority const BACnetEnumMessagePriority::CRITICAL_EQUIPMENT = BACnetMessagePriority(2, "CRITICAL_EQUIPMENT");
BACnetMessagePriority const BACnetEnumMessagePriority::LIFE_SAFETY = BACnetMessagePriority(3, "LIFE_SAFETY");

std::map<uint8_t, BACnetMessagePriority const *> BACnetEnumMessagePriority::objectMap = BACnetEnumMessagePriority::init_map();


std::map<uint8_t, BACnetMessagePriority const *> BACnetEnumMessagePriority::init_map() {

	std::map<uint8_t, BACnetMessagePriority const *> lmap;

	lmap[NORMAL.getValue()] = (BACnetMessagePriority const *) &NORMAL;
	lmap[URGENT.getValue()] = (BACnetMessagePriority const *) &URGENT;
	lmap[CRITICAL_EQUIPMENT.getValue()] = (BACnetMessagePriority const *) &CRITICAL_EQUIPMENT;
	lmap[LIFE_SAFETY.getValue()] = (BACnetMessagePriority const *) &LIFE_SAFETY;

	return lmap;
}

BACnetMessagePriority const &BACnetEnumMessagePriority::getEnumByValue(uint8_t enumValue) {

	std::map<uint8_t, BACnetMessagePriority const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumMessagePriority::get_supported_object_type(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




