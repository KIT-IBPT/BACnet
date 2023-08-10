/*
 * BACnetConfSvcChoice.cpp
 *
 *  Created on: Dec 20, 2017
 *      Author: 8w4
 */

#include "BACnetConfSvcChoice.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

BACnetConfSvcChoice::BACnetConfSvcChoice(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_CONFIRMED_SERVICE) {
		stringstream ss;

		ss << "\tError: BACnetConfSvcChoice::BACnetConfSvcChoice(uint16_t const enumValue, string const name):"
				" The valid range for a BACnet Unconfirmed Service Choice is 0-" << MAX_CONFIRMED_SERVICE << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetConfSvcChoice::~BACnetConfSvcChoice() {
	// TODO Auto-generated destructor stub
}

