/*
 * BACnetEnumUnconfirmedService.cpp
 *
 *  Created on: Aug 8, 2016
 *      Author: 8w4
 */

#include <stdexcept>
#include <iostream>
#include <sstream>

#include <BACnetEnumUnconfirmedService.h>

BACnetUnconfirmedServiceChoice::BACnetUnconfirmedServiceChoice(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_UNCONFIRMED_SERVICE) {
		stringstream ss;

		ss << "\tError: BACnetUnconfirmedServiceChoice::BACnetUnconfirmedServiceChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Unconfirmed Service Choice is 0-" << MAX_UNCONFIRMED_SERVICE << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetUnconfirmedServiceChoice::~BACnetUnconfirmedServiceChoice() {
	// TODO Auto-generated destructor stub
}

BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::I_AM = BACnetUnconfirmedServiceChoice(0, "I_AM");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::I_HAVE = BACnetUnconfirmedServiceChoice(1, "I_HAVE");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::COV_NOTIFICATION = BACnetUnconfirmedServiceChoice(2, "COV_NOTIFICATION");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::EVENT_NOTIFICATION = BACnetUnconfirmedServiceChoice(3, "EVENT_NOTIFICATION");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::PRIVATE_TRANSFER = BACnetUnconfirmedServiceChoice(4, "PRIVATE_TRANSFER");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::TEXT_MESSAGE = BACnetUnconfirmedServiceChoice(5, "TEXT_MESSAGE");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::TIME_SYNCHRONIZATION = BACnetUnconfirmedServiceChoice(6, "TIME_SYNCHRONIZATION");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::WHO_HAS = BACnetUnconfirmedServiceChoice(7, "WHO_HAS");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::WHO_IS = BACnetUnconfirmedServiceChoice(8, "WHO_IS");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::UTC_TIME_SYNCHRONIZATION = BACnetUnconfirmedServiceChoice(9, "UTC_TIME_SYNCHRONIZATION");
BACnetUnconfirmedServiceChoice const BACnetEnumUnconfirmedService::WRITE_GROUP = BACnetUnconfirmedServiceChoice(10, "WRITE_GROUP");

std::map<uint8_t, BACnetUnconfirmedServiceChoice const *> BACnetEnumUnconfirmedService::objectMap = BACnetEnumUnconfirmedService::init_map();


std::map<uint8_t, BACnetUnconfirmedServiceChoice const *> BACnetEnumUnconfirmedService::init_map() {

	std::map<uint8_t, BACnetUnconfirmedServiceChoice const *> lmap;

	lmap[I_AM.getValue()] = (BACnetUnconfirmedServiceChoice const *) &I_AM;
	lmap[I_HAVE.getValue()] = (BACnetUnconfirmedServiceChoice const *) &I_HAVE;
	lmap[COV_NOTIFICATION.getValue()] = (BACnetUnconfirmedServiceChoice const *) &COV_NOTIFICATION;
	lmap[EVENT_NOTIFICATION.getValue()] = (BACnetUnconfirmedServiceChoice const *) &EVENT_NOTIFICATION;
	lmap[PRIVATE_TRANSFER.getValue()] = (BACnetUnconfirmedServiceChoice const *) &PRIVATE_TRANSFER;
	lmap[TEXT_MESSAGE.getValue()] = (BACnetUnconfirmedServiceChoice const *) &TEXT_MESSAGE;
	lmap[TIME_SYNCHRONIZATION.getValue()] = (BACnetUnconfirmedServiceChoice const *) &TIME_SYNCHRONIZATION;
	lmap[WHO_HAS.getValue()] = (BACnetUnconfirmedServiceChoice const *) &WHO_HAS;
	lmap[WHO_IS.getValue()] = (BACnetUnconfirmedServiceChoice const *) &WHO_IS;
	lmap[UTC_TIME_SYNCHRONIZATION.getValue()] = (BACnetUnconfirmedServiceChoice const *) &UTC_TIME_SYNCHRONIZATION;
	lmap[WRITE_GROUP.getValue()] = (BACnetUnconfirmedServiceChoice const *) &WRITE_GROUP;

	return lmap;
}

BACnetUnconfirmedServiceChoice const &BACnetEnumUnconfirmedService::getEnumByValue(uint8_t emValue) {

	std::map<uint8_t, BACnetUnconfirmedServiceChoice const *>::iterator itr = objectMap.find(emValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) emValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetUnconfirmedServiceChoice const &BACnetEnumUnconfirmedService::getEnumByValue(uint8_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




