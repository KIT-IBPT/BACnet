/*
 * BACnetEnumObjectType.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: 8w4
 */

#include <stdexcept>
#include <iostream>
#include <sstream>

#include "BACnetEnumObjectType.h"

BACnetObjectType::BACnetObjectType(unsigned int enumValue, string const obj_name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, obj_name)
{

	if(value > MAX_OBJECT_TYPE) {
		stringstream ss;

		ss << "\tError: BACnetObjectType::BACnetObjectType(uint16_t enumValue, string const obj_name):"
				" The valid range for a BACnet Object Type is 0-" << MAX_OBJECT_TYPE << endl;
		throw std::invalid_argument(ss.str());
	}
}


BACnetObjectType::~BACnetObjectType() {
	// TODO Auto-generated destructor stub
}

/** Instantiate static Enum Objects.*/
BACnetObjectType const BACnetEnumObjectType::OBJECT_ANALOG_INPUT = BACnetObjectType(0, "ANALOG_INPUT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ANALOG_OUTPUT = BACnetObjectType(1, "ANALOG_OUTPUT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ANALOG_VALUE = BACnetObjectType(2, "ANALOG_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_BINARY_INPUT = BACnetObjectType(3, "BINARY_INPUT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_BINARY_OUTPUT = BACnetObjectType(4, "BINARY_OUTPUT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_BINARY_VALUE = BACnetObjectType(5, "BINARY_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_CALENDAR = BACnetObjectType(6, "CALENDAR");
BACnetObjectType const BACnetEnumObjectType::OBJECT_COMMAND = BACnetObjectType(7, "COMMAND");
BACnetObjectType const BACnetEnumObjectType::OBJECT_DEVICE = BACnetObjectType(8, "DEVICE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_EVENT_ENROLLMENT = BACnetObjectType(9, "EVENT_ENROLLMENT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_FILE = BACnetObjectType(10, "FILE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_GROUP = BACnetObjectType(11, "GROUP");
BACnetObjectType const BACnetEnumObjectType::OBJECT_LOOP = BACnetObjectType(12, "LOOP");
BACnetObjectType const BACnetEnumObjectType::OBJECT_MULTI_STATE_INPUT = BACnetObjectType(13, "MULTI_STATE_INPUT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_MULTI_STATE_OUTPUT = BACnetObjectType(14, "MULTI_STATE_OUTPUT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_NOTIFICATION_CLASS = BACnetObjectType(15, "NOTIFICATION_CLASS");
BACnetObjectType const BACnetEnumObjectType::OBJECT_PROGRAM = BACnetObjectType(16, "PROGRAM");
BACnetObjectType const BACnetEnumObjectType::OBJECT_SCHEDULE = BACnetObjectType(17, "SCHEDULE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_AVERAGING = BACnetObjectType(18, "AVERAGING");
BACnetObjectType const BACnetEnumObjectType::OBJECT_MULTI_STATE_VALUE = BACnetObjectType(19, "MULTI_STATE_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_TRENDLOG = BACnetObjectType(20, "TRENDLOG");
BACnetObjectType const BACnetEnumObjectType::OBJECT_LIFE_SAFETY_POINT = BACnetObjectType(21, "LIFE_SAFETY_POINT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_LIFE_SAFETY_ZONE = BACnetObjectType(22, "LIFE_SAFETY_ZONE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ACCUMULATOR = BACnetObjectType(23, "ACCUMULATOR");
BACnetObjectType const BACnetEnumObjectType::OBJECT_PULSE_CONVERTER = BACnetObjectType(24, "PULSE_CONVERTER");
BACnetObjectType const BACnetEnumObjectType::OBJECT_EVENT_LOG = BACnetObjectType(25, "EVENT_LOG");
BACnetObjectType const BACnetEnumObjectType::OBJECT_GLOBAL_GROUP = BACnetObjectType(26, "GLOBAL_GROUP");
BACnetObjectType const BACnetEnumObjectType::OBJECT_TREND_LOG_MULTIPLE = BACnetObjectType(27, "TREND_LOG_MULTIPLE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_LOAD_CONTROL = BACnetObjectType(28, "LOAD_CONTROL");
BACnetObjectType const BACnetEnumObjectType::OBJECT_STRUCTURED_VIEW = BACnetObjectType(29, "STRUCTURED_VIEW");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ACCESS_DOOR = BACnetObjectType(30, "ACCESS_DOOR");
BACnetObjectType const BACnetEnumObjectType::OBJECT_31_UNASSIGNED = BACnetObjectType(31, "31_UNASSIGNED");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ACCESS_CREDENTIAL = BACnetObjectType(32, "ACCESS_CREDENTIAL");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ACCESS_POINT = BACnetObjectType(33, "ACCESS_POINT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ACCESS_RIGHTS = BACnetObjectType(34, "ACCESS_RIGHTS");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ACCESS_USER = BACnetObjectType(35, "ACCESS_USER");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ACCESS_ZONE = BACnetObjectType(36, "ACCESS_ZONE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_CREDENTIAL_DATA_INPUT = BACnetObjectType(37, "CREDENTIAL_DATA_INPUT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_NETWORK_SECURITY = BACnetObjectType(38, "NETWORK_SECURITY");
BACnetObjectType const BACnetEnumObjectType::OBJECT_BITSTRING_VALUE = BACnetObjectType(39, "BITSTRING_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_CHARACTERSTRING_VALUE = BACnetObjectType(40, "CHARACTERSTRING_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_DATE_PATTERN_VALUE = BACnetObjectType(41, "DATE_PATTERN_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_DATE_VALUE = BACnetObjectType(42, "DATE_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_DATETIME_PATTERN_VALUE = BACnetObjectType(43, "DATETIME_PATTERN_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_DATETIME_VALUE = BACnetObjectType(44, "DATETIME_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_INTEGER_VALUE = BACnetObjectType(45, "INTEGER_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_LARGE_ANALOG_VALUE = BACnetObjectType(46, "LARGE_ANALOG_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_OCTETSTRING_VALUE = BACnetObjectType(47, "OCTETSTRING_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_POSITIVE_INTEGER_VALUE = BACnetObjectType(48, "POSITIVE_INTEGER_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_TIME_PATTERN_VALUE = BACnetObjectType(49, "TIME_PATTERN_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_TIME_VALUE = BACnetObjectType(50, "TIME_VALUE");
BACnetObjectType const BACnetEnumObjectType::OBJECT_NOTIFICATION_FORWARDER = BACnetObjectType(51, "NOTIFICATION_FORWARDER");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ALERT_ENROLLMENT = BACnetObjectType(52, "ALERT_ENROLLMENT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_CHANNEL = BACnetObjectType(53, "CHANNEL");
BACnetObjectType const BACnetEnumObjectType::OBJECT_LIGHTING_OUTPUT = BACnetObjectType(54, "LIGHTING_OUTPUT");
BACnetObjectType const BACnetEnumObjectType::OBJECT_ASHRAE_UNDEFINED = BACnetObjectType(55, "ASHRAE_UNDEFINED");
BACnetObjectType const BACnetEnumObjectType::OBJECT_VENDOR_PROPRIETARY = BACnetObjectType(128, "VENDOR_PROPRIETARY");

/** Initialize the map object to hold the enumerations. */
std::map<uint16_t, BACnetObjectType const *> BACnetEnumObjectType::objectMap = BACnetEnumObjectType::init_map();

/** Search and return the BACnet object by Enum Value */
BACnetObjectType const &BACnetEnumObjectType::getEnumByValue(uint16_t enumValue) {

	ostringstream oss;

	/** map.find() either returns a pointer to the object found, or a pointer to object.end()
	 * if the object was NOT found...*/
	std::map<uint16_t, BACnetObjectType const *>::iterator itr = objectMap.end();

	if(enumValue >= OBJECT_ANALOG_INPUT.getValue() && enumValue <= OBJECT_LIGHTING_OUTPUT.getValue()) {

		/** Object type is a "defined" ASHRAE supported type. */

		/** Supported Objects have already been created, so search for it...*/
		itr = objectMap.find(enumValue);

		/** There is a problem if it was not found in the list, tho... You need to check your map initializer list...*/
		if(itr == objectMap.end()) {
			oss << enumValue;
			std::string errstr = "Failure! BACnetEnumObjectType::getEnumByValue(uint16_t enumValue)"
					" failed to find BACnetObjectType by enum value (" + oss.str() + ")\n";
			throw std::invalid_argument(errstr);
		}

		/** return the found BACnet Object */
		return *itr->second;

	}
	else if(enumValue >= OBJECT_ASHRAE_UNDEFINED_START && enumValue < OBJECT_PROPRIETARY_START) {
		// Object type is an "undefined" ASHRAE type.
		ostringstream start;
		ostringstream stop;

		start << OBJECT_ASHRAE_UNDEFINED_START;
		stop << (OBJECT_PROPRIETARY_START-1);

		// Not sure if I should return an undefined type or just throw.. for now I'll throw.
		//return BACnetEnumObjectType::OBJECT_ASHRAE_UNDEFINED;
		oss << enumValue;

		std::string s = "Invalid Enum Value (" + oss.str() + "): BACnetObjTypeEnum::getEnumByValue(uint16_t enumValue)"
				" The Enum value (" + oss.str() + ") correlates to an ASHRAE undefined object type.\n"
						"ASHRAE has a range of undefined object types from (" + start.str() +
						" - " + stop.str() + ")\n";
		throw std::invalid_argument(s);
	}
	else if(enumValue >= OBJECT_PROPRIETARY_START && enumValue <= MAX_OBJECT_TYPE) {

		/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
		if(itr != objectMap.end()) {
			return *itr->second;
		}
		/** Object was not found in the list, so create it and insert it into the list...*/
		else {

			/** This structure hold an iterator and a bool. If the map.insert() succeeds the iterator
			 * will point to the newly inserted element and the bool will be true,
			 * otherwise the iterator will point to the element with an equivalent key in the map
			 * and bool will be false, indicating that the insert did NOT succeed.*/
			std::pair<std::map<uint16_t, BACnetObjectType const *>::iterator, bool> ret;

			ret = objectMap.insert(std::pair<uint16_t, BACnetObjectType const *>(
					enumValue, new BACnetObjectType(enumValue, "VENDOR_PROPRIETARY")));

			/** Something went wrong! If ret.second is equal to false then the insertion didn't work.*/
			if(ret.second == false) {
				oss << enumValue;
				std::string errstr = "Failure! BACnetEnumObjectType::getEnumByValue(uint16_t enumValue)"
						" failed to add BACnetObjectType(" + oss.str() + ", \"VENDOR_PROPRIETARY\") to "
								"the object map\n";
				throw std::invalid_argument(errstr);
			}
			/** The insert must have succeeded...*/
			else {
				return *ret.first->second;
			}

		}
	}

	oss << enumValue;
	std::string s = "Invalid Enum Value (" + oss.str() + "): BACnetObjTypeEnum::getEnumByValue(uint16_t enumValue)";
	throw std::invalid_argument(s);

}


std::map<uint16_t, BACnetObjectType const *> BACnetEnumObjectType::init_map() {

	std::map<uint16_t, BACnetObjectType const *> lmap;

	lmap[OBJECT_ANALOG_INPUT.getValue()] = (BACnetObjectType const *) &OBJECT_ANALOG_INPUT;
	lmap[OBJECT_ANALOG_OUTPUT.getValue()] = (BACnetObjectType const *) &OBJECT_ANALOG_OUTPUT;
	lmap[OBJECT_ANALOG_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_ANALOG_VALUE;
	lmap[OBJECT_BINARY_INPUT.getValue()] = (BACnetObjectType const *) &OBJECT_BINARY_INPUT;
	lmap[OBJECT_BINARY_OUTPUT.getValue()] = (BACnetObjectType const *) &OBJECT_BINARY_OUTPUT;
	lmap[OBJECT_BINARY_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_BINARY_VALUE;
	lmap[OBJECT_CALENDAR.getValue()] = (BACnetObjectType const *) &OBJECT_CALENDAR;
	lmap[OBJECT_COMMAND.getValue()] = (BACnetObjectType const *) &OBJECT_COMMAND;
	lmap[OBJECT_DEVICE.getValue()] = (BACnetObjectType const *) &OBJECT_DEVICE;
	lmap[OBJECT_EVENT_ENROLLMENT.getValue()] = (BACnetObjectType const *) &OBJECT_EVENT_ENROLLMENT;
	lmap[OBJECT_FILE.getValue()] = (BACnetObjectType const *) &OBJECT_FILE;
	lmap[OBJECT_GROUP.getValue()] = (BACnetObjectType const *) &OBJECT_GROUP;
	lmap[OBJECT_LOOP.getValue()] = (BACnetObjectType const *) &OBJECT_LOOP;
	lmap[OBJECT_MULTI_STATE_INPUT.getValue()] = (BACnetObjectType const *) &OBJECT_MULTI_STATE_INPUT;
	lmap[OBJECT_MULTI_STATE_OUTPUT.getValue()] = (BACnetObjectType const *) &OBJECT_MULTI_STATE_OUTPUT;
	lmap[OBJECT_NOTIFICATION_CLASS.getValue()] = (BACnetObjectType const *) &OBJECT_NOTIFICATION_CLASS;
	lmap[OBJECT_PROGRAM.getValue()] = (BACnetObjectType const *) &OBJECT_PROGRAM;
	lmap[OBJECT_SCHEDULE.getValue()] = (BACnetObjectType const *) &OBJECT_SCHEDULE;
	lmap[OBJECT_AVERAGING.getValue()] = (BACnetObjectType const *) &OBJECT_AVERAGING;
	lmap[OBJECT_MULTI_STATE_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_MULTI_STATE_VALUE;
	lmap[OBJECT_TRENDLOG.getValue()] = (BACnetObjectType const *) &OBJECT_TRENDLOG;
	lmap[OBJECT_LIFE_SAFETY_POINT.getValue()] = (BACnetObjectType const *) &OBJECT_LIFE_SAFETY_POINT;
	lmap[OBJECT_LIFE_SAFETY_ZONE.getValue()] = (BACnetObjectType const *) &OBJECT_LIFE_SAFETY_ZONE;
	lmap[OBJECT_ACCUMULATOR.getValue()] = (BACnetObjectType const *) &OBJECT_ACCUMULATOR;
	lmap[OBJECT_PULSE_CONVERTER.getValue()] = (BACnetObjectType const *) &OBJECT_PULSE_CONVERTER;
	lmap[OBJECT_EVENT_LOG.getValue()] = (BACnetObjectType const *) &OBJECT_EVENT_LOG;
	lmap[OBJECT_GLOBAL_GROUP.getValue()] = (BACnetObjectType const *) &OBJECT_GLOBAL_GROUP;
	lmap[OBJECT_TREND_LOG_MULTIPLE.getValue()] = (BACnetObjectType const *) &OBJECT_TREND_LOG_MULTIPLE;
	lmap[OBJECT_LOAD_CONTROL.getValue()] = (BACnetObjectType const *) &OBJECT_LOAD_CONTROL;
	lmap[OBJECT_STRUCTURED_VIEW.getValue()] = (BACnetObjectType const *) &OBJECT_STRUCTURED_VIEW;
	lmap[OBJECT_ACCESS_DOOR.getValue()] = (BACnetObjectType const *) &OBJECT_ACCESS_DOOR;
	lmap[OBJECT_31_UNASSIGNED.getValue()] = (BACnetObjectType const *) &OBJECT_31_UNASSIGNED;
	lmap[OBJECT_ACCESS_CREDENTIAL.getValue()] = (BACnetObjectType const *) &OBJECT_ACCESS_CREDENTIAL;
	lmap[OBJECT_ACCESS_POINT.getValue()] = (BACnetObjectType const *) &OBJECT_ACCESS_POINT;
	lmap[OBJECT_ACCESS_RIGHTS.getValue()] = (BACnetObjectType const *) &OBJECT_ACCESS_RIGHTS;
	lmap[OBJECT_ACCESS_USER.getValue()] = (BACnetObjectType const *) &OBJECT_ACCESS_USER;
	lmap[OBJECT_ACCESS_ZONE.getValue()] = (BACnetObjectType const *) &OBJECT_ACCESS_ZONE;
	lmap[OBJECT_CREDENTIAL_DATA_INPUT.getValue()] = (BACnetObjectType const *) &OBJECT_CREDENTIAL_DATA_INPUT;
	lmap[OBJECT_NETWORK_SECURITY.getValue()] = (BACnetObjectType const *) &OBJECT_NETWORK_SECURITY;
	lmap[OBJECT_BITSTRING_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_BITSTRING_VALUE;
	lmap[OBJECT_CHARACTERSTRING_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_CHARACTERSTRING_VALUE;
	lmap[OBJECT_DATE_PATTERN_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_DATE_PATTERN_VALUE;
	lmap[OBJECT_DATE_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_DATE_VALUE;
	lmap[OBJECT_DATETIME_PATTERN_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_DATETIME_PATTERN_VALUE;
	lmap[OBJECT_DATETIME_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_DATETIME_VALUE;
	lmap[OBJECT_INTEGER_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_INTEGER_VALUE;
	lmap[OBJECT_LARGE_ANALOG_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_LARGE_ANALOG_VALUE;
	lmap[OBJECT_OCTETSTRING_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_OCTETSTRING_VALUE;
	lmap[OBJECT_POSITIVE_INTEGER_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_POSITIVE_INTEGER_VALUE;
	lmap[OBJECT_TIME_PATTERN_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_TIME_PATTERN_VALUE;
	lmap[OBJECT_TIME_VALUE.getValue()] = (BACnetObjectType const *) &OBJECT_TIME_VALUE;
	lmap[OBJECT_NOTIFICATION_FORWARDER.getValue()] = (BACnetObjectType const *) &OBJECT_NOTIFICATION_FORWARDER;
	lmap[OBJECT_ALERT_ENROLLMENT.getValue()] = (BACnetObjectType const *) &OBJECT_ALERT_ENROLLMENT;
	lmap[OBJECT_CHANNEL.getValue()] = (BACnetObjectType const *) &OBJECT_CHANNEL;
	lmap[OBJECT_LIGHTING_OUTPUT.getValue()] = (BACnetObjectType const *) &OBJECT_LIGHTING_OUTPUT;
	lmap[OBJECT_ASHRAE_UNDEFINED.getValue()] = (BACnetObjectType const *) &OBJECT_ASHRAE_UNDEFINED;
	lmap[OBJECT_VENDOR_PROPRIETARY.getValue()] = (BACnetObjectType const *) &OBJECT_VENDOR_PROPRIETARY;

	return lmap;
}

