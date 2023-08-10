/*
 * BACnetEnumSegmentation.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: 8w4
 */

#include <stdexcept>
#include <iostream>
#include <sstream>

#include <BACnetEnumSegmentation.h>

BACnetSegmentation::BACnetSegmentation(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_SEGMENTATION) {
		stringstream ss;

		ss << "\tError: BACnetSegmentation::BACnetSegmentation(uint16_t const enumValue, string const name):"
				" The valid range for a BACnet Segmentation is 0-" << MAX_SEGMENTATION << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetSegmentation::~BACnetSegmentation() {
	// TODO Auto-generated destructor stub
}

BACnetSegmentation const BACnetEnumSegmentation::SEGMENTED_BOTH = BACnetSegmentation(0, "SEGMENTED_BOTH");
BACnetSegmentation const BACnetEnumSegmentation::SEGMENTED_TRANSMIT = BACnetSegmentation(1, "SEGMENTED_TRANSMIT");
BACnetSegmentation const BACnetEnumSegmentation::SEGMENTED_RECEIVE = BACnetSegmentation(2, "SEGMENTED_RECEIVE");
BACnetSegmentation const BACnetEnumSegmentation::NO_SEGMENTATION = BACnetSegmentation(3, "NO_SEGMENTATION");

std::map<uint16_t, BACnetSegmentation const *> BACnetEnumSegmentation::objectMap = BACnetEnumSegmentation::init_map();


std::map<uint16_t, BACnetSegmentation const *> BACnetEnumSegmentation::init_map() {

	std::map<uint16_t, BACnetSegmentation const *> lmap;

	lmap[SEGMENTED_BOTH.getValue()] = (BACnetSegmentation const *) &SEGMENTED_BOTH;
	lmap[SEGMENTED_TRANSMIT.getValue()] = (BACnetSegmentation const *) &SEGMENTED_TRANSMIT;
	lmap[SEGMENTED_RECEIVE.getValue()] = (BACnetSegmentation const *) &SEGMENTED_RECEIVE;
	lmap[NO_SEGMENTATION.getValue()] = (BACnetSegmentation const *) &NO_SEGMENTATION;

	return lmap;
}

BACnetSegmentation const &BACnetEnumSegmentation::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetSegmentation const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumSegmentation::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




