/*
 * BACnetEnumCharSet.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: 8w4
 */

#include <BACnetEnumCharSet.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

BACnetCharChoice::BACnetCharChoice(uint16_t const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_CHARACTER_CHOICE) {
		stringstream ss;

		ss << "\tError: BACnetCharChoice::BACnetCharChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Character Choice is 0-" << MAX_CHARACTER_CHOICE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetCharChoice::~BACnetCharChoice() {
	// TODO Auto-generated destructor stub
}

BACnetCharChoice const BACnetEnumCharSet::CHARACTER_UTF8 = BACnetCharChoice(0, "CHARACTER_UTF8");
BACnetCharChoice const BACnetEnumCharSet::CHARACTER_MS_DBCS = BACnetCharChoice(1, "CHARACTER_MS_DBCS");
BACnetCharChoice const BACnetEnumCharSet::CHARACTER_JISC_6226 = BACnetCharChoice(2, "CHARACTER_JISC_6226");
BACnetCharChoice const BACnetEnumCharSet::CHARACTER_UCS4 = BACnetCharChoice(3, "CHARACTER_UCS4");
BACnetCharChoice const BACnetEnumCharSet::CHARACTER_UCS2 = BACnetCharChoice(4, "CHARACTER_UCS2");
BACnetCharChoice const BACnetEnumCharSet::CHARACTER_ISO8859 = BACnetCharChoice(5, "CHARACTER_ISO8859");

std::map<uint16_t, BACnetCharChoice const *> BACnetEnumCharSet::objectMap = BACnetEnumCharSet::init_map();


std::map<uint16_t, BACnetCharChoice const *> BACnetEnumCharSet::init_map() {

	std::map<uint16_t, BACnetCharChoice const *> lmap;

	lmap[CHARACTER_UTF8.getValue()] = (BACnetCharChoice const *) &CHARACTER_UTF8;
	lmap[CHARACTER_MS_DBCS.getValue()] = (BACnetCharChoice const *) &CHARACTER_MS_DBCS;
	lmap[CHARACTER_JISC_6226.getValue()] = (BACnetCharChoice const *) &CHARACTER_JISC_6226;
	lmap[CHARACTER_UCS4.getValue()] = (BACnetCharChoice const *) &CHARACTER_UCS4;
	lmap[CHARACTER_UCS2.getValue()] = (BACnetCharChoice const *) &CHARACTER_UCS2;
	lmap[CHARACTER_ISO8859.getValue()] = (BACnetCharChoice const *) &CHARACTER_ISO8859;

	return lmap;
}

BACnetCharChoice const &BACnetEnumCharSet::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetCharChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumCharSet::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}

