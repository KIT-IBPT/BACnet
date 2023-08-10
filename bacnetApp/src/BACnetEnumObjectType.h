/*
 * BACnetEnumObjectType.h
 *
 *  Created on: Mar 16, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMOBJECTTYPE_H_
#define BACNETAPP_SRC_BACNETENUMOBJECTTYPE_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

// Enumerated values 0-127 are reserved for definition by ASHRAE.
// Enumerated values -- 128-1023 may be used by others subject to
// the procedures and constraints described -- in Clause 23.
#define OBJECT_ASHRAE_UNDEFINED_START 55
#define OBJECT_PROPRIETARY_START 128

#define MAX_OBJECT_TYPE 0x3FF

class BACnetObjectType : public BACnetEnumSingle {

public:

	BACnetObjectType(unsigned int enumValue, string const obj_name);
	virtual ~BACnetObjectType();
};

class BACnetEnumObjectType {

private:
	static std::map<uint16_t, BACnetObjectType const *> objectMap;

	static std::map<uint16_t, BACnetObjectType const *> init_map(void);

public:

	static BACnetObjectType const OBJECT_ANALOG_INPUT;
	static BACnetObjectType const OBJECT_ANALOG_OUTPUT;
	static BACnetObjectType const OBJECT_ANALOG_VALUE;
	static BACnetObjectType const OBJECT_BINARY_INPUT;
	static BACnetObjectType const OBJECT_BINARY_OUTPUT;
	static BACnetObjectType const OBJECT_BINARY_VALUE;
	static BACnetObjectType const OBJECT_CALENDAR;
	static BACnetObjectType const OBJECT_COMMAND;
	static BACnetObjectType const OBJECT_DEVICE;
	static BACnetObjectType const OBJECT_EVENT_ENROLLMENT;
	static BACnetObjectType const OBJECT_FILE;
	static BACnetObjectType const OBJECT_GROUP;
	static BACnetObjectType const OBJECT_LOOP;
	static BACnetObjectType const OBJECT_MULTI_STATE_INPUT;
	static BACnetObjectType const OBJECT_MULTI_STATE_OUTPUT;
	static BACnetObjectType const OBJECT_NOTIFICATION_CLASS;
	static BACnetObjectType const OBJECT_PROGRAM;
	static BACnetObjectType const OBJECT_SCHEDULE;
	static BACnetObjectType const OBJECT_AVERAGING;
	static BACnetObjectType const OBJECT_MULTI_STATE_VALUE;
	static BACnetObjectType const OBJECT_TRENDLOG;
	static BACnetObjectType const OBJECT_LIFE_SAFETY_POINT;
	static BACnetObjectType const OBJECT_LIFE_SAFETY_ZONE;
	static BACnetObjectType const OBJECT_ACCUMULATOR;
	static BACnetObjectType const OBJECT_PULSE_CONVERTER;
	static BACnetObjectType const OBJECT_EVENT_LOG;
	static BACnetObjectType const OBJECT_GLOBAL_GROUP;
	static BACnetObjectType const OBJECT_TREND_LOG_MULTIPLE;
	static BACnetObjectType const OBJECT_LOAD_CONTROL;
	static BACnetObjectType const OBJECT_STRUCTURED_VIEW;
	static BACnetObjectType const OBJECT_ACCESS_DOOR;
	static BACnetObjectType const OBJECT_31_UNASSIGNED;
	static BACnetObjectType const OBJECT_ACCESS_CREDENTIAL;
	static BACnetObjectType const OBJECT_ACCESS_POINT;
	static BACnetObjectType const OBJECT_ACCESS_RIGHTS;
	static BACnetObjectType const OBJECT_ACCESS_USER;
	static BACnetObjectType const OBJECT_ACCESS_ZONE;
	static BACnetObjectType const OBJECT_CREDENTIAL_DATA_INPUT;
	static BACnetObjectType const OBJECT_NETWORK_SECURITY;
	static BACnetObjectType const OBJECT_BITSTRING_VALUE;
	static BACnetObjectType const OBJECT_CHARACTERSTRING_VALUE;
	static BACnetObjectType const OBJECT_DATE_PATTERN_VALUE;
	static BACnetObjectType const OBJECT_DATE_VALUE;
	static BACnetObjectType const OBJECT_DATETIME_PATTERN_VALUE;
	static BACnetObjectType const OBJECT_DATETIME_VALUE;
	static BACnetObjectType const OBJECT_INTEGER_VALUE;
	static BACnetObjectType const OBJECT_LARGE_ANALOG_VALUE;
	static BACnetObjectType const OBJECT_OCTETSTRING_VALUE;
	static BACnetObjectType const OBJECT_POSITIVE_INTEGER_VALUE;
	static BACnetObjectType const OBJECT_TIME_PATTERN_VALUE;
	static BACnetObjectType const OBJECT_TIME_VALUE;
	static BACnetObjectType const OBJECT_NOTIFICATION_FORWARDER;
	static BACnetObjectType const OBJECT_ALERT_ENROLLMENT;
	static BACnetObjectType const OBJECT_CHANNEL;
	static BACnetObjectType const OBJECT_LIGHTING_OUTPUT;
	static BACnetObjectType const OBJECT_ASHRAE_UNDEFINED;
	static BACnetObjectType const OBJECT_VENDOR_PROPRIETARY;

	static BACnetObjectType const &getEnumByValue(uint16_t enumValue);

};

#endif /* BACNETAPP_SRC_BACNETENUMOBJECTTYPE_H_ */
