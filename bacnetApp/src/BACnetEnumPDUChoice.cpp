/*
 * BACnetEnumPDUChoice.cpp
 *
 *  Created on: Aug 8, 2016
 *      Author: 8w4
 */

#include <stdexcept>
#include <iostream>
#include <sstream>

#include <BACnetEnumPDUChoice.h>

BACnetPDUChoice::BACnetPDUChoice(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_PDU_CHOICE) {
		stringstream ss;

		ss << "\tError: BACnetPDUChoice::BACnetPDUChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet PDU Choice is 0-" << MAX_PDU_CHOICE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetPDUChoice::~BACnetPDUChoice() {
	// TODO Auto-generated destructor stub
}

BACnetPDUChoice const BACnetEnumPDUChoice::CONFIRMED_REQUEST = BACnetPDUChoice(0, "CONFIRMED_REQUEST");
BACnetPDUChoice const BACnetEnumPDUChoice::UNCONFIRMED_REQUEST = BACnetPDUChoice(1, "UNCONFIRMED_REQUEST");
BACnetPDUChoice const BACnetEnumPDUChoice::SIMPLE_ACK = BACnetPDUChoice(2, "SIMPLE_ACK");
BACnetPDUChoice const BACnetEnumPDUChoice::COMPLEX_ACK = BACnetPDUChoice(3, "COMPLEX_ACK");
BACnetPDUChoice const BACnetEnumPDUChoice::SEGMENT_ACK = BACnetPDUChoice(4, "SEGMENT_ACK");
BACnetPDUChoice const BACnetEnumPDUChoice::ERROR = BACnetPDUChoice(5, "ERROR");
BACnetPDUChoice const BACnetEnumPDUChoice::REJECT = BACnetPDUChoice(6, "REJECT");
BACnetPDUChoice const BACnetEnumPDUChoice::ABORT = BACnetPDUChoice(7, "ABORT");

std::map<uint8_t, BACnetPDUChoice const *> BACnetEnumPDUChoice::objectMap = BACnetEnumPDUChoice::init_map();


std::map<uint8_t, BACnetPDUChoice const *> BACnetEnumPDUChoice::init_map() {

	std::map<uint8_t, BACnetPDUChoice const *> lmap;

	lmap[CONFIRMED_REQUEST.getValue()] = (BACnetPDUChoice const *) &CONFIRMED_REQUEST;
	lmap[UNCONFIRMED_REQUEST.getValue()] = (BACnetPDUChoice const *) &UNCONFIRMED_REQUEST;
	lmap[SIMPLE_ACK.getValue()] = (BACnetPDUChoice const *) &SIMPLE_ACK;
	lmap[COMPLEX_ACK.getValue()] = (BACnetPDUChoice const *) &COMPLEX_ACK;
	lmap[SEGMENT_ACK.getValue()] = (BACnetPDUChoice const *) &SEGMENT_ACK;
	lmap[ERROR.getValue()] = (BACnetPDUChoice const *) &ERROR;
	lmap[REJECT.getValue()] = (BACnetPDUChoice const *) &REJECT;
	lmap[ABORT.getValue()] = (BACnetPDUChoice const *) &ABORT;

	return lmap;
}

BACnetPDUChoice const &BACnetEnumPDUChoice::getEnumByValue(uint8_t enumValue) {

	std::map<uint8_t, BACnetPDUChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumPDUChoice::getEnumByValue(uint8_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




