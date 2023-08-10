/*
 * BACnetEnumBvlcFunction.cpp
 *
 *  Created on: Sep 7, 2016
 *      Author: 8w4
 */

#include <stdexcept>
#include <iostream>
#include <sstream>

#include <BACnetEnumBvlcFunction.h>

BACnetBvlcFunction::BACnetBvlcFunction(unsigned int const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{
	if(enumValue > MAX_BVLC_FUNCTION) {
		stringstream ss;

		ss << "\tError: BACnetBvlcFunction::BACnetBvlcFunction(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet BVLC function is 0-" << MAX_BVLC_FUNCTION << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetBvlcFunction::~BACnetBvlcFunction() {
	// TODO Auto-generated destructor stub
}

BACnetBvlcFunction const BACnetEnumBvlcFunction::RESULT = BACnetBvlcFunction(0, "RESULT");
BACnetBvlcFunction const BACnetEnumBvlcFunction::WRITE_BROADCAST_DISTRIBUTION_TABLE = BACnetBvlcFunction(1, "WRITE_BROADCAST_DISTRIBUTION_TABLE");
BACnetBvlcFunction const BACnetEnumBvlcFunction::READ_BROADCAST_DIST_TABLE = BACnetBvlcFunction(2, "READ_BROADCAST_DIST_TABLE");
BACnetBvlcFunction const BACnetEnumBvlcFunction::READ_BROADCAST_DIST_TABLE_ACK = BACnetBvlcFunction(3, "READ_BROADCAST_DIST_TABLE_ACK");
BACnetBvlcFunction const BACnetEnumBvlcFunction::FORWARDED_NPDU = BACnetBvlcFunction(4, "FORWARDED_NPDU");
BACnetBvlcFunction const BACnetEnumBvlcFunction::REGISTER_FOREIGN_DEVICE = BACnetBvlcFunction(5, "REGISTER_FOREIGN_DEVICE");
BACnetBvlcFunction const BACnetEnumBvlcFunction::READ_FOREIGN_DEVICE_TABLE = BACnetBvlcFunction(6, "READ_FOREIGN_DEVICE_TABLE");
BACnetBvlcFunction const BACnetEnumBvlcFunction::READ_FOREIGN_DEVICE_TABLE_ACK = BACnetBvlcFunction(7, "READ_FOREIGN_DEVICE_TABLE_ACK");
BACnetBvlcFunction const BACnetEnumBvlcFunction::DELETE_FOREIGN_DEVICE_TABLE_ENTRY = BACnetBvlcFunction(8, "DELETE_FOREIGN_DEVICE_TABLE_ENTRY");
BACnetBvlcFunction const BACnetEnumBvlcFunction::DISTRIBUTE_BROADCAST_TO_NETWORK = BACnetBvlcFunction(9, "DISTRIBUTE_BROADCAST_TO_NETWORK");
BACnetBvlcFunction const BACnetEnumBvlcFunction::ORIGINAL_UNICAST_NPDU = BACnetBvlcFunction(10, "ORIGINAL_UNICAST_NPDU");
BACnetBvlcFunction const BACnetEnumBvlcFunction::ORIGINAL_BROADCAST_NPDU = BACnetBvlcFunction(11, "ORIGINAL_BROADCAST_NPDU");

std::map<uint8_t, BACnetBvlcFunction const *> BACnetEnumBvlcFunction::objectMap = BACnetEnumBvlcFunction::init_map();


std::map<uint8_t, BACnetBvlcFunction const *> BACnetEnumBvlcFunction::init_map() {

	std::map<uint8_t, BACnetBvlcFunction const *> lmap;

	lmap[RESULT.getValue()] = (BACnetBvlcFunction const *) &RESULT;
	lmap[WRITE_BROADCAST_DISTRIBUTION_TABLE.getValue()] = (BACnetBvlcFunction const *) &WRITE_BROADCAST_DISTRIBUTION_TABLE;
	lmap[READ_BROADCAST_DIST_TABLE.getValue()] = (BACnetBvlcFunction const *) &READ_BROADCAST_DIST_TABLE;
	lmap[READ_BROADCAST_DIST_TABLE_ACK.getValue()] = (BACnetBvlcFunction const *) &READ_BROADCAST_DIST_TABLE_ACK;
	lmap[FORWARDED_NPDU.getValue()] = (BACnetBvlcFunction const *) &FORWARDED_NPDU;
	lmap[REGISTER_FOREIGN_DEVICE.getValue()] = (BACnetBvlcFunction const *) &REGISTER_FOREIGN_DEVICE;
	lmap[READ_FOREIGN_DEVICE_TABLE.getValue()] = (BACnetBvlcFunction const *) &READ_FOREIGN_DEVICE_TABLE;
	lmap[READ_FOREIGN_DEVICE_TABLE_ACK.getValue()] = (BACnetBvlcFunction const *) &READ_FOREIGN_DEVICE_TABLE_ACK;
	lmap[DELETE_FOREIGN_DEVICE_TABLE_ENTRY.getValue()] = (BACnetBvlcFunction const *) &DELETE_FOREIGN_DEVICE_TABLE_ENTRY;
	lmap[DISTRIBUTE_BROADCAST_TO_NETWORK.getValue()] = (BACnetBvlcFunction const *) &DISTRIBUTE_BROADCAST_TO_NETWORK;
	lmap[ORIGINAL_UNICAST_NPDU.getValue()] = (BACnetBvlcFunction const *) &ORIGINAL_UNICAST_NPDU;
	lmap[ORIGINAL_BROADCAST_NPDU.getValue()] = (BACnetBvlcFunction const *) &ORIGINAL_BROADCAST_NPDU;

	return lmap;
}

BACnetBvlcFunction const &BACnetEnumBvlcFunction::getEnumByValue(uint8_t enumValue) {

	std::map<uint8_t, BACnetBvlcFunction const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumBvlcFunction::get_supported_object_type(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}




