/*
 * BACnetEnumErrorClass.cpp
 *
 *  Created on: Aug 9, 2018
 *      Author: 8w4
 */

#include "BACnetEnumErrorClass.h"

#include <iostream>
#include <sstream>
#include <stdexcept>


BACnetErrClassChoice::BACnetErrClassChoice(uint16_t const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_ERROR_CLASS_CHOICE) {
		stringstream ss;

		ss << "\tError: BACnetVarFuncChoice::BACnetVarFuncChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Error-Class Choice is 0-" << MAX_ERROR_CLASS_CHOICE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetErrClassChoice::~BACnetErrClassChoice() {
	// TODO Auto-generated destructor stub
}

BACnetErrClassChoice const BACnetEnumErrorClass::DEVICE = BACnetErrClassChoice(0, "DEVICE");
BACnetErrClassChoice const BACnetEnumErrorClass::OBJECT = BACnetErrClassChoice(1, "OBJECT");
BACnetErrClassChoice const BACnetEnumErrorClass::PROPERTY = BACnetErrClassChoice(2, "PROPERTY");
BACnetErrClassChoice const BACnetEnumErrorClass::RESOURCES = BACnetErrClassChoice(3, "RESOURCES");
BACnetErrClassChoice const BACnetEnumErrorClass::SECURITY = BACnetErrClassChoice(4, "SECURITY");
BACnetErrClassChoice const BACnetEnumErrorClass::SERVICES = BACnetErrClassChoice(5, "SERVICES");
BACnetErrClassChoice const BACnetEnumErrorClass::VT = BACnetErrClassChoice(6, "VT");
BACnetErrClassChoice const BACnetEnumErrorClass::COMMUNICATION = BACnetErrClassChoice(7, "COMMUNICATION");

std::map<uint16_t, BACnetErrClassChoice const *> BACnetEnumErrorClass::objectMap = BACnetEnumErrorClass::init_map();


std::map<uint16_t, BACnetErrClassChoice const *> BACnetEnumErrorClass::init_map() {

	std::map<uint16_t, BACnetErrClassChoice const *> lmap;

	lmap[DEVICE.getValue()] = (BACnetErrClassChoice const *) &DEVICE;
	lmap[OBJECT.getValue()] = (BACnetErrClassChoice const *) &OBJECT;
	lmap[PROPERTY.getValue()] = (BACnetErrClassChoice const *) &PROPERTY;
	lmap[RESOURCES.getValue()] = (BACnetErrClassChoice const *) &RESOURCES;
	lmap[SECURITY.getValue()] = (BACnetErrClassChoice const *) &SECURITY;
	lmap[SERVICES.getValue()] = (BACnetErrClassChoice const *) &SERVICES;
	lmap[VT.getValue()] = (BACnetErrClassChoice const *) &VT;
	lmap[COMMUNICATION.getValue()] = (BACnetErrClassChoice const *) &COMMUNICATION;

	return lmap;
}

BACnetErrClassChoice const &BACnetEnumErrorClass::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetErrClassChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumErrorClass::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}

