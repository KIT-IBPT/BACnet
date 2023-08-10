/*
 * BACnetEnumTxRxEr.cpp
 *
 *  Created on: Sep 24, 2018
 *      Author: 8w4
 */

#include "BACnetEnumTxRxEr.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>


BACnetTxRxErChoice::BACnetTxRxErChoice(uint16_t const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_TxRxEr_CHOICE) {
		stringstream ss;

		ss << "\tError: BACnetTxRxErChoice::BACnetTxRxErChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Enum Tx/Rx/Er Choice is 0-" << MAX_TxRxEr_CHOICE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetTxRxErChoice::~BACnetTxRxErChoice() {
	// TODO Auto-generated destructor stub
}

BACnetTxRxErChoice const BACnetEnumTxRxEr::TX = BACnetTxRxErChoice(0, "TX");
BACnetTxRxErChoice const BACnetEnumTxRxEr::RX = BACnetTxRxErChoice(1, "RX");
BACnetTxRxErChoice const BACnetEnumTxRxEr::ER = BACnetTxRxErChoice(2, "ER");

std::map<uint16_t, BACnetTxRxErChoice const *> BACnetEnumTxRxEr::objectMap = BACnetEnumTxRxEr::init_map();


std::map<uint16_t, BACnetTxRxErChoice const *> BACnetEnumTxRxEr::init_map() {

	std::map<uint16_t, BACnetTxRxErChoice const *> lmap;

	lmap[TX.getValue()] = (BACnetTxRxErChoice const *) &TX;
	lmap[RX.getValue()] = (BACnetTxRxErChoice const *) &RX;
	lmap[ER.getValue()] = (BACnetTxRxErChoice const *) &ER;

	return lmap;
}

BACnetTxRxErChoice const &BACnetEnumTxRxEr::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetTxRxErChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumTxRxEr::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}

BACnetTxRxErChoice const &BACnetEnumTxRxEr::getEnumByName(const string &nameStr) {

	std::map<uint16_t, BACnetTxRxErChoice const *>::const_iterator itr = objectMap.begin();

	/** Temporary string for upper case.*/
	string tempStr;

	/** Convert the string to upper case*/
	for(int i=0; i<2; i++) {
		tempStr.push_back(toupper(nameStr[i]));
	}

	/** Search the map for the enumeration name*/
	while(itr != objectMap.end()) {
		if((*itr).second->getName().compare(tempStr) == 0) {
			return *(*itr).second;
		}
		itr++;
	}

	ostringstream os;
	os << "Invalid Enum Name (" << nameStr << ") Enum Not Found: BACnetEnumTxRxEr::getEnumByValue(const string &nameStr)\n";
	throw std::invalid_argument(os.str());

}




