/*
 * BACnetEnumTagChoice.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: 8w4
 */
#include <stdexcept>
#include <iostream>
#include <sstream>

#include <BACnetEnumTagChoice.h>

BACnetTagClassChoice::BACnetTagClassChoice(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_TAG_CHOICE) {
		stringstream ss;

		ss << "\tError: Cannot create BACnetTagClassChoice. The enumValue (" << enumValue << ") parameter is out of range."
				" The valid range is 0-" << MAX_TAG_CHOICE << "." << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetTagClassChoice::~BACnetTagClassChoice() {
	// TODO Auto-generated destructor stub
}

BACnetTagClassChoice const BACnetEnumTagChoice::APPLICATION_TAG = BACnetTagClassChoice(0, "APPLICATION_TAG");
BACnetTagClassChoice const BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG = BACnetTagClassChoice(1, "CONTEXT_SPECIFIC_TAG");

std::map<uint16_t, BACnetTagClassChoice const *> BACnetEnumTagChoice::objectMap = BACnetEnumTagChoice::init_map();


std::map<uint16_t, BACnetTagClassChoice const *> BACnetEnumTagChoice::init_map() {

	std::map<uint16_t, BACnetTagClassChoice const *> lmap;

	lmap[APPLICATION_TAG.getValue()] = (BACnetTagClassChoice const *) &APPLICATION_TAG;
	lmap[CONTEXT_SPECIFIC_TAG.getValue()] = (BACnetTagClassChoice const *) &CONTEXT_SPECIFIC_TAG;

	return lmap;
}

BACnetTagClassChoice const &BACnetEnumTagChoice::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetTagClassChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumTagChoice::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




