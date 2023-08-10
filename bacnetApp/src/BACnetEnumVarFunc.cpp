/*
 * BACnetEnumVarFunc.cpp
 *
 *  Created on: Jun 28, 2018
 *      Author: 8w4
 */

#include <BACnetEnumVarFunc.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

BACnetVarFuncChoice::BACnetVarFuncChoice(uint16_t const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_VARFUNC_CHOICE) {
		stringstream ss;

		ss << "\tError: BACnetVarFuncChoice::BACnetVarFuncChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Variable Function Choice is 0-" << MAX_VARFUNC_CHOICE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetVarFuncChoice::~BACnetVarFuncChoice() {
	// TODO Auto-generated destructor stub
}

BACnetVarFuncChoice const BACnetEnumVarFunc::READ = BACnetVarFuncChoice(0, "READ");
BACnetVarFuncChoice const BACnetEnumVarFunc::WRITE = BACnetVarFuncChoice(1, "WRITE");

std::map<uint16_t, BACnetVarFuncChoice const *> BACnetEnumVarFunc::objectMap = BACnetEnumVarFunc::init_map();


std::map<uint16_t, BACnetVarFuncChoice const *> BACnetEnumVarFunc::init_map() {

	std::map<uint16_t, BACnetVarFuncChoice const *> lmap;

	lmap[READ.getValue()] = (BACnetVarFuncChoice const *) &READ;
	lmap[WRITE.getValue()] = (BACnetVarFuncChoice const *) &WRITE;

	return lmap;
}

BACnetVarFuncChoice const &BACnetEnumVarFunc::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetVarFuncChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumVarFunc::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}

