/*
 * BACnetEnumTsmState.cpp
 *
 *  Created on: May 24, 2018
 *      Author: 8w4
 */

#include "BACnetEnumTsmState.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

BACnetTsmState::BACnetTsmState(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{
	if(enumValue > MAX_TSM_STATE) {
		stringstream ss;

		ss << "\tError: BACnetTsmState::BACnetTsmState(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet TSM State is 0-" << MAX_TSM_STATE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetTsmState::~BACnetTsmState() {
	// TODO Auto-generated destructor stub
}

BACnetTsmState const BACnetEnumTsmState::IDLE = BACnetTsmState(0, "IDLE");
BACnetTsmState const BACnetEnumTsmState::AWAIT_CONFIRMATION = BACnetTsmState(1, "AWAIT_CONFIRMATION");
BACnetTsmState const BACnetEnumTsmState::AWAIT_RESPONSE = BACnetTsmState(2, "AWAIT_RESPONSE");
BACnetTsmState const BACnetEnumTsmState::SEGMENTED_REQUEST = BACnetTsmState(3, "SEGMENTED_REQUEST");
BACnetTsmState const BACnetEnumTsmState::SEGMENTED_CONFIRMATION = BACnetTsmState(4, "SEGMENTED_CONFIRMATION");
BACnetTsmState const BACnetEnumTsmState::AWAIT_IAM = BACnetTsmState(5, "AWAIT_IAM");

std::map<uint8_t, BACnetTsmState const *> BACnetEnumTsmState::objectMap = BACnetEnumTsmState::init_map();


std::map<uint8_t, BACnetTsmState const *> BACnetEnumTsmState::init_map() {

	std::map<uint8_t, BACnetTsmState const *> lmap;

	lmap[IDLE.getValue()] = (BACnetTsmState const *) &IDLE;
	lmap[AWAIT_CONFIRMATION.getValue()] = (BACnetTsmState const *) &AWAIT_CONFIRMATION;
	lmap[AWAIT_RESPONSE.getValue()] = (BACnetTsmState const *) &AWAIT_RESPONSE;
	lmap[SEGMENTED_REQUEST.getValue()] = (BACnetTsmState const *) &SEGMENTED_REQUEST;
	lmap[SEGMENTED_CONFIRMATION.getValue()] = (BACnetTsmState const *) &SEGMENTED_CONFIRMATION;
	lmap[AWAIT_IAM.getValue()] = (BACnetTsmState const *) &AWAIT_IAM;

	return lmap;
}

BACnetTsmState const &BACnetEnumTsmState::getEnumByValue(uint8_t enumValue) {

	std::map<uint8_t, BACnetTsmState const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumTsmState::get_supported_object_type(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




