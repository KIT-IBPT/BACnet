/*
 * BACnetPropertyIdentifier.cpp
 *
 *  Created on: Mar 20, 2017
 *      Author: 8w4
 */


#include <stdexcept>
#include <iostream>
#include <sstream>

#include "BACnetEnumPropertyIdentifier.h"

BACnetPropertyType::BACnetPropertyType(unsigned int const enumValue, string const prop_name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, prop_name)
{

	if(enumValue > MAX_PROPERTY_TYPE) {
		stringstream ss;

		ss << "\tError: BACnetPropertyType::BACnetPropertyType(uint32_t const enumValue, string const prop_name):"
				" The valid range for a BACnet Property Type is 0-" << MAX_PROPERTY_TYPE << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetPropertyType::~BACnetPropertyType() {
	// TODO Auto-generated destructor stub
}

BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACKED_TRANSITIONS = BACnetPropertyType(0,"PROP_ACKED_TRANSITIONS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACK_REQUIRED = BACnetPropertyType(1,"PROP_ACK_REQUIRED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACTION = BACnetPropertyType(2,"PROP_ACTION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACTION_TEXT = BACnetPropertyType(3,"PROP_ACTION_TEXT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACTIVE_TEXT = BACnetPropertyType(4,"PROP_ACTIVE_TEXT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACTIVE_VT_SESSIONS = BACnetPropertyType(5,"PROP_ACTIVE_VT_SESSIONS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ALARM_VALUE = BACnetPropertyType(6,"PROP_ALARM_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ALARM_VALUES = BACnetPropertyType(7,"PROP_ALARM_VALUES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ALL = BACnetPropertyType(8,"PROP_ALL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ALL_WRITES_SUCCESSFUL = BACnetPropertyType(9,"PROP_ALL_WRITES_SUCCESSFUL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_APDU_SEGMENT_TIMEOUT = BACnetPropertyType(10,"PROP_APDU_SEGMENT_TIMEOUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_APDU_TIMEOUT = BACnetPropertyType(11,"PROP_APDU_TIMEOUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_APPLICATION_SOFTWARE_VERSION = BACnetPropertyType(12,"PROP_APPLICATION_SOFTWARE_VERSION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ARCHIVE = BACnetPropertyType(13,"PROP_ARCHIVE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BIAS = BACnetPropertyType(14,"PROP_BIAS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CHANGE_OF_STATE_COUNT = BACnetPropertyType(15,"PROP_CHANGE_OF_STATE_COUNT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CHANGE_OF_STATE_TIME = BACnetPropertyType(16,"PROP_CHANGE_OF_STATE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NOTIFICATION_CLASS = BACnetPropertyType(17,"PROP_NOTIFICATION_CLASS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BLANK_1 = BACnetPropertyType(18,"PROP_BLANK_1");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CONTROLLED_VARIABLE_REFERENCE = BACnetPropertyType(19,"PROP_CONTROLLED_VARIABLE_REFERENCE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CONTROLLED_VARIABLE_UNITS = BACnetPropertyType(20,"PROP_CONTROLLED_VARIABLE_UNITS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CONTROLLED_VARIABLE_VALUE = BACnetPropertyType(21,"PROP_CONTROLLED_VARIABLE_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_COV_INCREMENT = BACnetPropertyType(22,"PROP_COV_INCREMENT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DATE_LIST = BACnetPropertyType(23,"PROP_DATE_LIST");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DAYLIGHT_SAVINGS_STATUS = BACnetPropertyType(24,"PROP_DAYLIGHT_SAVINGS_STATUS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DEADBAND = BACnetPropertyType(25,"PROP_DEADBAND");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DERIVATIVE_CONSTANT = BACnetPropertyType(26,"PROP_DERIVATIVE_CONSTANT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DERIVATIVE_CONSTANT_UNITS = BACnetPropertyType(27,"PROP_DERIVATIVE_CONSTANT_UNITS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DESCRIPTION = BACnetPropertyType(28,"PROP_DESCRIPTION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DESCRIPTION_OF_HALT = BACnetPropertyType(29,"PROP_DESCRIPTION_OF_HALT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DEVICE_ADDRESS_BINDING = BACnetPropertyType(30,"PROP_DEVICE_ADDRESS_BINDING");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DEVICE_TYPE = BACnetPropertyType(31,"PROP_DEVICE_TYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EFFECTIVE_PERIOD = BACnetPropertyType(32,"PROP_EFFECTIVE_PERIOD");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ELAPSED_ACTIVE_TIME = BACnetPropertyType(33,"PROP_ELAPSED_ACTIVE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ERROR_LIMIT = BACnetPropertyType(34,"PROP_ERROR_LIMIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_ENABLE = BACnetPropertyType(35,"PROP_EVENT_ENABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_STATE = BACnetPropertyType(36,"PROP_EVENT_STATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_TYPE = BACnetPropertyType(37,"PROP_EVENT_TYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EXCEPTION_SCHEDULE = BACnetPropertyType(38,"PROP_EXCEPTION_SCHEDULE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FAULT_VALUES = BACnetPropertyType(39,"PROP_FAULT_VALUES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FEEDBACK_VALUE = BACnetPropertyType(40,"PROP_FEEDBACK_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FILE_ACCESS_METHOD = BACnetPropertyType(41,"PROP_FILE_ACCESS_METHOD");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FILE_SIZE = BACnetPropertyType(42,"PROP_FILE_SIZE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FILE_TYPE = BACnetPropertyType(43,"PROP_FILE_TYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FIRMWARE_REVISION = BACnetPropertyType(44,"PROP_FIRMWARE_REVISION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_HIGH_LIMIT = BACnetPropertyType(45,"PROP_HIGH_LIMIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_INACTIVE_TEXT = BACnetPropertyType(46,"PROP_INACTIVE_TEXT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_IN_PROCESS = BACnetPropertyType(47,"PROP_IN_PROCESS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_INSTANCE_OF = BACnetPropertyType(48,"PROP_INSTANCE_OF");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_INTEGRAL_CONSTANT = BACnetPropertyType(49,"PROP_INTEGRAL_CONSTANT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_INTEGRAL_CONSTANT_UNITS = BACnetPropertyType(50,"PROP_INTEGRAL_CONSTANT_UNITS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ISSUE_CONFIRMED_NOTIFICATIONS = BACnetPropertyType(51,"PROP_ISSUE_CONFIRMED_NOTIFICATIONS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LIMIT_ENABLE = BACnetPropertyType(52,"PROP_LIMIT_ENABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LIST_OF_GROUP_MEMBERS = BACnetPropertyType(53,"PROP_LIST_OF_GROUP_MEMBERS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LIST_OF_OBJECT_PROPERTY_REFERENCES = BACnetPropertyType(54,"PROP_LIST_OF_OBJECT_PROPERTY_REFERENCES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LIST_OF_SESSION_KEYS = BACnetPropertyType(55,"PROP_LIST_OF_SESSION_KEYS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOCAL_DATE = BACnetPropertyType(56,"PROP_LOCAL_DATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOCAL_TIME = BACnetPropertyType(57,"PROP_LOCAL_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOCATION = BACnetPropertyType(58,"PROP_LOCATION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOW_LIMIT = BACnetPropertyType(59,"PROP_LOW_LIMIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MANIPULATED_VARIABLE_REFERENCE = BACnetPropertyType(60,"PROP_MANIPULATED_VARIABLE_REFERENCE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAXIMUM_OUTPUT = BACnetPropertyType(61,"PROP_MAXIMUM_OUTPUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAX_APDU_LENGTH_ACCEPTED = BACnetPropertyType(62,"PROP_MAX_APDU_LENGTH_ACCEPTED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAX_INFO_FRAMES = BACnetPropertyType(63,"PROP_MAX_INFO_FRAMES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAX_MASTER = BACnetPropertyType(64,"PROP_MAX_MASTER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAX_PRES_VALUE = BACnetPropertyType(65,"PROP_MAX_PRES_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MINIMUM_OFF_TIME = BACnetPropertyType(66,"PROP_MINIMUM_OFF_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MINIMUM_ON_TIME = BACnetPropertyType(67,"PROP_MINIMUM_ON_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MINIMUM_OUTPUT = BACnetPropertyType(68,"PROP_MINIMUM_OUTPUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MIN_PRES_VALUE = BACnetPropertyType(69,"PROP_MIN_PRES_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MODEL_NAME = BACnetPropertyType(70,"PROP_MODEL_NAME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MODIFICATION_DATE = BACnetPropertyType(71,"PROP_MODIFICATION_DATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NOTIFY_TYPE = BACnetPropertyType(72,"PROP_NOTIFY_TYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NUMBER_OF_APDU_RETRIES = BACnetPropertyType(73,"PROP_NUMBER_OF_APDU_RETRIES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NUMBER_OF_STATES = BACnetPropertyType(74,"PROP_NUMBER_OF_STATES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER = BACnetPropertyType(75,"PROP_OBJECT_IDENTIFIER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OBJECT_LIST = BACnetPropertyType(76,"PROP_OBJECT_LIST");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME = BACnetPropertyType(77,"PROP_OBJECT_NAME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OBJECT_PROPERTY_REFERENCE = BACnetPropertyType(78,"PROP_OBJECT_PROPERTY_REFERENCE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE = BACnetPropertyType(79,"PROP_OBJECT_TYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OPTIONAL = BACnetPropertyType(80,"PROP_OPTIONAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OUT_OF_SERVICE = BACnetPropertyType(81,"PROP_OUT_OF_SERVICE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OUTPUT_UNITS = BACnetPropertyType(82,"PROP_OUTPUT_UNITS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_PARAMETERS = BACnetPropertyType(83,"PROP_EVENT_PARAMETERS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_POLARITY = BACnetPropertyType(84,"PROP_POLARITY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE = BACnetPropertyType(85,"PROP_PRESENT_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PRIORITY = BACnetPropertyType(86,"PROP_PRIORITY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PRIORITY_ARRAY = BACnetPropertyType(87,"PROP_PRIORITY_ARRAY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PRIORITY_FOR_WRITING = BACnetPropertyType(88,"PROP_PRIORITY_FOR_WRITING");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROCESS_IDENTIFIER = BACnetPropertyType(89,"PROP_PROCESS_IDENTIFIER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROGRAM_CHANGE = BACnetPropertyType(90,"PROP_PROGRAM_CHANGE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROGRAM_LOCATION = BACnetPropertyType(91,"PROP_PROGRAM_LOCATION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROGRAM_STATE = BACnetPropertyType(92,"PROP_PROGRAM_STATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROPORTIONAL_CONSTANT = BACnetPropertyType(93,"PROP_PROPORTIONAL_CONSTANT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROPORTIONAL_CONSTANT_UNITS = BACnetPropertyType(94,"PROP_PROPORTIONAL_CONSTANT_UNITS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROTOCOL_CONFORMANCE_CLASS = BACnetPropertyType(95,"PROP_PROTOCOL_CONFORMANCE_CLASS");       /* deleted in version 1 revision 2 */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROTOCOL_OBJECT_TYPES_SUPPORTED = BACnetPropertyType(96,"PROP_PROTOCOL_OBJECT_TYPES_SUPPORTED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROTOCOL_SERVICES_SUPPORTED = BACnetPropertyType(97,"PROP_PROTOCOL_SERVICES_SUPPORTED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROTOCOL_VERSION = BACnetPropertyType(98,"PROP_PROTOCOL_VERSION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_READ_ONLY = BACnetPropertyType(99,"PROP_READ_ONLY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_REASON_FOR_HALT = BACnetPropertyType(100,"PROP_REASON_FOR_HALT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RECIPIENT = BACnetPropertyType(101,"PROP_RECIPIENT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RECIPIENT_LIST = BACnetPropertyType(102,"PROP_RECIPIENT_LIST");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RELIABILITY = BACnetPropertyType(103,"PROP_RELIABILITY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RELINQUISH_DEFAULT = BACnetPropertyType(104,"PROP_RELINQUISH_DEFAULT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_REQUIRED = BACnetPropertyType(105,"PROP_REQUIRED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RESOLUTION = BACnetPropertyType(106,"PROP_RESOLUTION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SEGMENTATION_SUPPORTED = BACnetPropertyType(107,"PROP_SEGMENTATION_SUPPORTED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SETPOINT = BACnetPropertyType(108,"PROP_SETPOINT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SETPOINT_REFERENCE = BACnetPropertyType(109,"PROP_SETPOINT_REFERENCE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_STATE_TEXT = BACnetPropertyType(110,"PROP_STATE_TEXT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_STATUS_FLAGS = BACnetPropertyType(111,"PROP_STATUS_FLAGS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SYSTEM_STATUS = BACnetPropertyType(112,"PROP_SYSTEM_STATUS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TIME_DELAY = BACnetPropertyType(113,"PROP_TIME_DELAY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TIME_OF_ACTIVE_TIME_RESET = BACnetPropertyType(114,"PROP_TIME_OF_ACTIVE_TIME_RESET");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TIME_OF_STATE_COUNT_RESET = BACnetPropertyType(115,"PROP_TIME_OF_STATE_COUNT_RESET");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TIME_SYNCHRONIZATION_RECIPIENTS = BACnetPropertyType(116,"PROP_TIME_SYNCHRONIZATION_RECIPIENTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_UNITS = BACnetPropertyType(117,"PROP_UNITS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_UPDATE_INTERVAL = BACnetPropertyType(118,"PROP_UPDATE_INTERVAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_UTC_OFFSET = BACnetPropertyType(119,"PROP_UTC_OFFSET");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VENDOR_IDENTIFIER = BACnetPropertyType(120,"PROP_VENDOR_IDENTIFIER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VENDOR_NAME = BACnetPropertyType(121,"PROP_VENDOR_NAME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VT_CLASSES_SUPPORTED = BACnetPropertyType(122,"PROP_VT_CLASSES_SUPPORTED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_WEEKLY_SCHEDULE = BACnetPropertyType(123,"PROP_WEEKLY_SCHEDULE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ATTEMPTED_SAMPLES = BACnetPropertyType(124,"PROP_ATTEMPTED_SAMPLES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_AVERAGE_VALUE = BACnetPropertyType(125,"PROP_AVERAGE_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BUFFER_SIZE = BACnetPropertyType(126,"PROP_BUFFER_SIZE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CLIENT_COV_INCREMENT = BACnetPropertyType(127,"PROP_CLIENT_COV_INCREMENT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_COV_RESUBSCRIPTION_INTERVAL = BACnetPropertyType(128,"PROP_COV_RESUBSCRIPTION_INTERVAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CURRENT_NOTIFY_TIME = BACnetPropertyType(129,"PROP_CURRENT_NOTIFY_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_TIME_STAMPS = BACnetPropertyType(130,"PROP_EVENT_TIME_STAMPS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOG_BUFFER = BACnetPropertyType(131,"PROP_LOG_BUFFER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOG_DEVICE_OBJECT_PROPERTY = BACnetPropertyType(132,"PROP_LOG_DEVICE_OBJECT_PROPERTY");
    /* The enable property is renamed from log-enable in
       Addendum b to ANSI/ASHRAE 135-2004(135b-2) */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ENABLE = BACnetPropertyType(133,"PROP_ENABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOG_INTERVAL = BACnetPropertyType(134,"PROP_LOG_INTERVAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAXIMUM_VALUE = BACnetPropertyType(135,"PROP_MAXIMUM_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MINIMUM_VALUE = BACnetPropertyType(136,"PROP_MINIMUM_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NOTIFICATION_THRESHOLD = BACnetPropertyType(137,"PROP_NOTIFICATION_THRESHOLD");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PREVIOUS_NOTIFY_TIME = BACnetPropertyType(138,"PROP_PREVIOUS_NOTIFY_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROTOCOL_REVISION = BACnetPropertyType(139,"PROP_PROTOCOL_REVISION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RECORDS_SINCE_NOTIFICATION = BACnetPropertyType(140,"PROP_RECORDS_SINCE_NOTIFICATION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RECORD_COUNT = BACnetPropertyType(141,"PROP_RECORD_COUNT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_START_TIME = BACnetPropertyType(142,"PROP_START_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_STOP_TIME = BACnetPropertyType(143,"PROP_STOP_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_STOP_WHEN_FULL = BACnetPropertyType(144,"PROP_STOP_WHEN_FULL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TOTAL_RECORD_COUNT = BACnetPropertyType(145,"PROP_TOTAL_RECORD_COUNT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VALID_SAMPLES = BACnetPropertyType(146,"PROP_VALID_SAMPLES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_WINDOW_INTERVAL = BACnetPropertyType(147,"PROP_WINDOW_INTERVAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_WINDOW_SAMPLES = BACnetPropertyType(148,"PROP_WINDOW_SAMPLES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAXIMUM_VALUE_TIMESTAMP = BACnetPropertyType(149,"PROP_MAXIMUM_VALUE_TIMESTAMP");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MINIMUM_VALUE_TIMESTAMP = BACnetPropertyType(150,"PROP_MINIMUM_VALUE_TIMESTAMP");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VARIANCE_VALUE = BACnetPropertyType(151,"PROP_VARIANCE_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACTIVE_COV_SUBSCRIPTIONS = BACnetPropertyType(152,"PROP_ACTIVE_COV_SUBSCRIPTIONS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BACKUP_FAILURE_TIMEOUT = BACnetPropertyType(153,"PROP_BACKUP_FAILURE_TIMEOUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CONFIGURATION_FILES = BACnetPropertyType(154,"PROP_CONFIGURATION_FILES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DATABASE_REVISION = BACnetPropertyType(155,"PROP_DATABASE_REVISION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DIRECT_READING = BACnetPropertyType(156,"PROP_DIRECT_READING");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_RESTORE_TIME = BACnetPropertyType(157,"PROP_LAST_RESTORE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAINTENANCE_REQUIRED = BACnetPropertyType(158,"PROP_MAINTENANCE_REQUIRED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MEMBER_OF = BACnetPropertyType(159,"PROP_MEMBER_OF");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MODE = BACnetPropertyType(160,"PROP_MODE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OPERATION_EXPECTED = BACnetPropertyType(161,"PROP_OPERATION_EXPECTED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SETTING = BACnetPropertyType(162,"PROP_SETTING");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SILENCED = BACnetPropertyType(163,"PROP_SILENCED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TRACKING_VALUE = BACnetPropertyType(164,"PROP_TRACKING_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ZONE_MEMBERS = BACnetPropertyType(165,"PROP_ZONE_MEMBERS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LIFE_SAFETY_ALARM_VALUES = BACnetPropertyType(166,"PROP_LIFE_SAFETY_ALARM_VALUES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAX_SEGMENTS_ACCEPTED = BACnetPropertyType(167,"PROP_MAX_SEGMENTS_ACCEPTED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROFILE_NAME = BACnetPropertyType(168,"PROP_PROFILE_NAME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_AUTO_SLAVE_DISCOVERY = BACnetPropertyType(169,"PROP_AUTO_SLAVE_DISCOVERY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MANUAL_SLAVE_ADDRESS_BINDING = BACnetPropertyType(170,"PROP_MANUAL_SLAVE_ADDRESS_BINDING");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SLAVE_ADDRESS_BINDING = BACnetPropertyType(171,"PROP_SLAVE_ADDRESS_BINDING");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SLAVE_PROXY_ENABLE = BACnetPropertyType(172,"PROP_SLAVE_PROXY_ENABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_NOTIFY_RECORD = BACnetPropertyType(173,"PROP_LAST_NOTIFY_RECORD");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SCHEDULE_DEFAULT = BACnetPropertyType(174,"PROP_SCHEDULE_DEFAULT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCEPTED_MODES = BACnetPropertyType(175,"PROP_ACCEPTED_MODES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ADJUST_VALUE = BACnetPropertyType(176,"PROP_ADJUST_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_COUNT = BACnetPropertyType(177,"PROP_COUNT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_COUNT_BEFORE_CHANGE = BACnetPropertyType(178,"PROP_COUNT_BEFORE_CHANGE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_COUNT_CHANGE_TIME = BACnetPropertyType(179,"PROP_COUNT_CHANGE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_COV_PERIOD = BACnetPropertyType(180,"PROP_COV_PERIOD");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_INPUT_REFERENCE = BACnetPropertyType(181,"PROP_INPUT_REFERENCE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LIMIT_MONITORING_INTERVAL = BACnetPropertyType(182,"PROP_LIMIT_MONITORING_INTERVAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOGGING_OBJECT = BACnetPropertyType(183,"PROP_LOGGING_OBJECT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOGGING_RECORD = BACnetPropertyType(184,"PROP_LOGGING_RECORD");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PRESCALE = BACnetPropertyType(185,"PROP_PRESCALE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PULSE_RATE = BACnetPropertyType(186,"PROP_PULSE_RATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SCALE = BACnetPropertyType(187,"PROP_SCALE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SCALE_FACTOR = BACnetPropertyType(188,"PROP_SCALE_FACTOR");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_UPDATE_TIME = BACnetPropertyType(189,"PROP_UPDATE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VALUE_BEFORE_CHANGE = BACnetPropertyType(190,"PROP_VALUE_BEFORE_CHANGE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VALUE_SET = BACnetPropertyType(191,"PROP_VALUE_SET");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VALUE_CHANGE_TIME = BACnetPropertyType(192,"PROP_VALUE_CHANGE_TIME");
    /* enumerations 193-206 are new */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ALIGN_INTERVALS = BACnetPropertyType(193,"PROP_ALIGN_INTERVALS");
    /* enumeration 194 is unassigned */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_INTERVAL_OFFSET = BACnetPropertyType(195,"PROP_INTERVAL_OFFSET");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_RESTART_REASON = BACnetPropertyType(196,"PROP_LAST_RESTART_REASON");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOGGING_TYPE = BACnetPropertyType(197,"PROP_LOGGING_TYPE");
    /* enumeration 198-201 is unassigned */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RESTART_NOTIFICATION_RECIPIENTS = BACnetPropertyType(202,"PROP_RESTART_NOTIFICATION_RECIPIENTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TIME_OF_DEVICE_RESTART = BACnetPropertyType(203,"PROP_TIME_OF_DEVICE_RESTART");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TIME_SYNCHRONIZATION_INTERVAL = BACnetPropertyType(204,"PROP_TIME_SYNCHRONIZATION_INTERVAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TRIGGER = BACnetPropertyType(205,"PROP_TRIGGER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_UTC_TIME_SYNCHRONIZATION_RECIPIENTS = BACnetPropertyType(206,"PROP_UTC_TIME_SYNCHRONIZATION_RECIPIENTS");
    /* enumerations 207-211 are used in Addendum d to ANSI/ASHRAE 135-2004 */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NODE_SUBTYPE = BACnetPropertyType(207,"PROP_NODE_SUBTYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NODE_TYPE = BACnetPropertyType(208,"PROP_NODE_TYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_STRUCTURED_OBJECT_LIST = BACnetPropertyType(209,"PROP_STRUCTURED_OBJECT_LIST");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SUBORDINATE_ANNOTATIONS = BACnetPropertyType(210,"PROP_SUBORDINATE_ANNOTATIONS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SUBORDINATE_LIST = BACnetPropertyType(211,"PROP_SUBORDINATE_LIST");
    /* enumerations 212-225 are used in Addendum e to ANSI/ASHRAE 135-2004 */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACTUAL_SHED_LEVEL = BACnetPropertyType(212,"PROP_ACTUAL_SHED_LEVEL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DUTY_WINDOW = BACnetPropertyType(213,"PROP_DUTY_WINDOW");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EXPECTED_SHED_LEVEL = BACnetPropertyType(214,"PROP_EXPECTED_SHED_LEVEL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FULL_DUTY_BASELINE = BACnetPropertyType(215,"PROP_FULL_DUTY_BASELINE");
    /* enumerations 216-217 are unassigned */
    /* enumerations 212-225 are used in Addendum e to ANSI/ASHRAE 135-2004 */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_REQUESTED_SHED_LEVEL = BACnetPropertyType(218,"PROP_REQUESTED_SHED_LEVEL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SHED_DURATION = BACnetPropertyType(219,"PROP_SHED_DURATION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SHED_LEVEL_DESCRIPTIONS = BACnetPropertyType(220,"PROP_SHED_LEVEL_DESCRIPTIONS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SHED_LEVELS = BACnetPropertyType(221,"PROP_SHED_LEVELS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_STATE_DESCRIPTION = BACnetPropertyType(222,"PROP_STATE_DESCRIPTION");
    /* enumerations 223-225 are unassigned  */
    /* enumerations 226-235 are used in Addendum f to ANSI/ASHRAE 135-2004 */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DOOR_ALARM_STATE = BACnetPropertyType(226,"PROP_DOOR_ALARM_STATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DOOR_EXTENDED_PULSE_TIME = BACnetPropertyType(227,"PROP_DOOR_EXTENDED_PULSE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DOOR_MEMBERS = BACnetPropertyType(228,"PROP_DOOR_MEMBERS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DOOR_OPEN_TOO_LONG_TIME = BACnetPropertyType(229,"PROP_DOOR_OPEN_TOO_LONG_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DOOR_PULSE_TIME = BACnetPropertyType(230,"PROP_DOOR_PULSE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DOOR_STATUS = BACnetPropertyType(231,"PROP_DOOR_STATUS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DOOR_UNLOCK_DELAY_TIME = BACnetPropertyType(232,"PROP_DOOR_UNLOCK_DELAY_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOCK_STATUS = BACnetPropertyType(233,"PROP_LOCK_STATUS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MASKED_ALARM_VALUES = BACnetPropertyType(234,"PROP_MASKED_ALARM_VALUES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SECURED_STATUS = BACnetPropertyType(235,"PROP_SECURED_STATUS");
    /* enumerations 236-243 are unassigned  */
    /* enumerations 244-311 are used in Addendum j to ANSI/ASHRAE 135-2004 */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ABSENTEE_LIMIT = BACnetPropertyType(244,"PROP_ABSENTEE_LIMIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCESS_ALARM_EVENTS = BACnetPropertyType(245,"PROP_ACCESS_ALARM_EVENTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCESS_DOORS = BACnetPropertyType(246,"PROP_ACCESS_DOORS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCESS_EVENT = BACnetPropertyType(247,"PROP_ACCESS_EVENT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCESS_EVENT_AUTHENTICATION_FACTOR = BACnetPropertyType(248,"PROP_ACCESS_EVENT_AUTHENTICATION_FACTOR");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCESS_EVENT_CREDENTIAL = BACnetPropertyType(249,"PROP_ACCESS_EVENT_CREDENTIAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCESS_EVENT_TIME = BACnetPropertyType(250,"PROP_ACCESS_EVENT_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCESS_TRANSACTION_EVENTS = BACnetPropertyType(251,"PROP_ACCESS_TRANSACTION_EVENTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCOMPANIMENT = BACnetPropertyType(252,"PROP_ACCOMPANIMENT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCOMPANIMENT_TIME = BACnetPropertyType(253,"PROP_ACCOMPANIMENT_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACTIVATION_TIME = BACnetPropertyType(254,"PROP_ACTIVATION_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACTIVE_AUTHENTICATION_POLICY = BACnetPropertyType(255,"PROP_ACTIVE_AUTHENTICATION_POLICY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ASSIGNED_ACCESS_RIGHTS = BACnetPropertyType(256,"PROP_ASSIGNED_ACCESS_RIGHTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_AUTHENTICATION_FACTORS = BACnetPropertyType(257,"PROP_AUTHENTICATION_FACTORS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_AUTHENTICATION_POLICY_LIST = BACnetPropertyType(258,"PROP_AUTHENTICATION_POLICY_LIST");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_AUTHENTICATION_POLICY_NAMES = BACnetPropertyType(259,"PROP_AUTHENTICATION_POLICY_NAMES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_AUTHORIZATION_STATUS = BACnetPropertyType(260,"PROP_AUTHORIZATION_STATUS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_AUTHORIZATION_MODE = BACnetPropertyType(261,"PROP_AUTHORIZATION_MODE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BELONGS_TO = BACnetPropertyType(262,"PROP_BELONGS_TO");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CREDENTIAL_DISABLE = BACnetPropertyType(263,"PROP_CREDENTIAL_DISABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CREDENTIAL_STATUS = BACnetPropertyType(264,"PROP_CREDENTIAL_STATUS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CREDENTIALS = BACnetPropertyType(265,"PROP_CREDENTIALS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CREDENTIALS_IN_ZONE = BACnetPropertyType(266,"PROP_CREDENTIALS_IN_ZONE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DAYS_REMAINING = BACnetPropertyType(267,"PROP_DAYS_REMAINING");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ENTRY_POINTS = BACnetPropertyType(268,"PROP_ENTRY_POINTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EXIT_POINTS = BACnetPropertyType(269,"PROP_EXIT_POINTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EXPIRY_TIME = BACnetPropertyType(270,"PROP_EXPIRY_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EXTENDED_TIME_ENABLE = BACnetPropertyType(271,"PROP_EXTENDED_TIME_ENABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FAILED_ATTEMPT_EVENTS = BACnetPropertyType(272,"PROP_FAILED_ATTEMPT_EVENTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FAILED_ATTEMPTS = BACnetPropertyType(273,"PROP_FAILED_ATTEMPTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FAILED_ATTEMPTS_TIME = BACnetPropertyType(274,"PROP_FAILED_ATTEMPTS_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_ACCESS_EVENT = BACnetPropertyType(275,"PROP_LAST_ACCESS_EVENT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_ACCESS_POINT = BACnetPropertyType(276,"PROP_LAST_ACCESS_POINT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_CREDENTIAL_ADDED = BACnetPropertyType(277,"PROP_LAST_CREDENTIAL_ADDED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_CREDENTIAL_ADDED_TIME = BACnetPropertyType(278,"PROP_LAST_CREDENTIAL_ADDED_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_CREDENTIAL_REMOVED = BACnetPropertyType(279,"PROP_LAST_CREDENTIAL_REMOVED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_CREDENTIAL_REMOVED_TIME = BACnetPropertyType(280,"PROP_LAST_CREDENTIAL_REMOVED_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_USE_TIME = BACnetPropertyType(281,"PROP_LAST_USE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOCKOUT = BACnetPropertyType(282,"PROP_LOCKOUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOCKOUT_RELINQUISH_TIME = BACnetPropertyType(283,"PROP_LOCKOUT_RELINQUISH_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MASTER_EXEMPTION = BACnetPropertyType(284,"PROP_MASTER_EXEMPTION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAX_FAILED_ATTEMPTS = BACnetPropertyType(285,"PROP_MAX_FAILED_ATTEMPTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MEMBERS = BACnetPropertyType(286,"PROP_MEMBERS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MUSTER_POINT = BACnetPropertyType(287,"PROP_MUSTER_POINT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NEGATIVE_ACCESS_RULES = BACnetPropertyType(288,"PROP_NEGATIVE_ACCESS_RULES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NUMBER_OF_AUTHENTICATION_POLICIES = BACnetPropertyType(289,"PROP_NUMBER_OF_AUTHENTICATION_POLICIES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_COUNT = BACnetPropertyType(290,"PROP_OCCUPANCY_COUNT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_COUNT_ADJUST = BACnetPropertyType(291,"PROP_OCCUPANCY_COUNT_ADJUST");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_COUNT_ENABLE = BACnetPropertyType(292,"PROP_OCCUPANCY_COUNT_ENABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_EXEMPTION = BACnetPropertyType(293,"PROP_OCCUPANCY_EXEMPTION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_LOWER_LIMIT = BACnetPropertyType(294,"PROP_OCCUPANCY_LOWER_LIMIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_LOWER_LIMIT_ENFORCED = BACnetPropertyType(295,"PROP_OCCUPANCY_LOWER_LIMIT_ENFORCED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_STATE = BACnetPropertyType(296,"PROP_OCCUPANCY_STATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_UPPER_LIMIT = BACnetPropertyType(297,"PROP_OCCUPANCY_UPPER_LIMIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_OCCUPANCY_UPPER_LIMIT_ENFORCED = BACnetPropertyType(298,"PROP_OCCUPANCY_UPPER_LIMIT_ENFORCED");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PASSBACK_EXEMPTION = BACnetPropertyType(299,"PROP_PASSBACK_EXEMPTION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PASSBACK_MODE = BACnetPropertyType(300,"PROP_PASSBACK_MODE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PASSBACK_TIMEOUT = BACnetPropertyType(301,"PROP_PASSBACK_TIMEOUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_POSITIVE_ACCESS_RULES = BACnetPropertyType(302,"PROP_POSITIVE_ACCESS_RULES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_REASON_FOR_DISABLE = BACnetPropertyType(303,"PROP_REASON_FOR_DISABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SUPPORTED_FORMATS = BACnetPropertyType(304,"PROP_SUPPORTED_FORMATS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SUPPORTED_FORMAT_CLASSES = BACnetPropertyType(305,"PROP_SUPPORTED_FORMAT_CLASSES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_THREAT_AUTHORITY = BACnetPropertyType(306,"PROP_THREAT_AUTHORITY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_THREAT_LEVEL = BACnetPropertyType(307,"PROP_THREAT_LEVEL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TRACE_FLAG = BACnetPropertyType(308,"PROP_TRACE_FLAG");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TRANSACTION_NOTIFICATION_CLASS = BACnetPropertyType(309,"PROP_TRANSACTION_NOTIFICATION_CLASS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_USER_EXTERNAL_IDENTIFIER = BACnetPropertyType(310,"PROP_USER_EXTERNAL_IDENTIFIER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_USER_INFORMATION_REFERENCE = BACnetPropertyType(311,"PROP_USER_INFORMATION_REFERENCE");
    /* enumerations 312-316 are unassigned */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_USER_NAME = BACnetPropertyType(317,"PROP_USER_NAME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_USER_TYPE = BACnetPropertyType(318,"PROP_USER_TYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_USES_REMAINING = BACnetPropertyType(319,"PROP_USES_REMAINING");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ZONE_FROM = BACnetPropertyType(320,"PROP_ZONE_FROM");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ZONE_TO = BACnetPropertyType(321,"PROP_ZONE_TO");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ACCESS_EVENT_TAG = BACnetPropertyType(322,"PROP_ACCESS_EVENT_TAG");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_GLOBAL_IDENTIFIER = BACnetPropertyType(323,"PROP_GLOBAL_IDENTIFIER");
    /* enumerations 324-325 are unassigned */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_VERIFICATION_TIME = BACnetPropertyType(326,"PROP_VERIFICATION_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BASE_DEVICE_SECURITY_POLICY = BACnetPropertyType(327,"PROP_BASE_DEVICE_SECURITY_POLICY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DISTRIBUTION_KEY_REVISION = BACnetPropertyType(328,"PROP_DISTRIBUTION_KEY_REVISION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DO_NOT_HIDE = BACnetPropertyType(329,"PROP_DO_NOT_HIDE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_KEY_SETS = BACnetPropertyType(330,"PROP_KEY_SETS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_KEY_SERVER = BACnetPropertyType(331,"PROP_LAST_KEY_SERVER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_NETWORK_ACCESS_SECURITY_POLICIES = BACnetPropertyType(332,"PROP_NETWORK_ACCESS_SECURITY_POLICIES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PACKET_REORDER_TIME = BACnetPropertyType(333,"PROP_PACKET_REORDER_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SECURITY_PDU_TIMEOUT = BACnetPropertyType(334,"PROP_SECURITY_PDU_TIMEOUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SECURITY_TIME_WINDOW = BACnetPropertyType(335,"PROP_SECURITY_TIME_WINDOW");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SUPPORTED_SECURITY_ALGORITHM = BACnetPropertyType(336,"PROP_SUPPORTED_SECURITY_ALGORITHM");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_UPDATE_KEY_SET_TIMEOUT = BACnetPropertyType(337,"PROP_UPDATE_KEY_SET_TIMEOUT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BACKUP_AND_RESTORE_STATE = BACnetPropertyType(338,"PROP_BACKUP_AND_RESTORE_STATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BACKUP_PREPARATION_TIME = BACnetPropertyType(339,"PROP_BACKUP_PREPARATION_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RESTORE_COMPLETION_TIME = BACnetPropertyType(340,"PROP_RESTORE_COMPLETION_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RESTORE_PREPARATION_TIME = BACnetPropertyType(341,"PROP_RESTORE_PREPARATION_TIME");
    /* enumerations 342-344 are defined in Addendum 2008-w */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BIT_MASK = BACnetPropertyType(342,"PROP_BIT_MASK");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BIT_TEXT = BACnetPropertyType(343,"PROP_BIT_TEXT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_IS_UTC = BACnetPropertyType(344,"PROP_IS_UTC");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_GROUP_MEMBERS = BACnetPropertyType(345,"PROP_GROUP_MEMBERS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_GROUP_MEMBER_NAMES = BACnetPropertyType(346,"PROP_GROUP_MEMBER_NAMES");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MEMBER_STATUS_FLAGS = BACnetPropertyType(347,"PROP_MEMBER_STATUS_FLAGS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_REQUESTED_UPDATE_INTERVAL = BACnetPropertyType(348,"PROP_REQUESTED_UPDATE_INTERVAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_COVU_PERIOD = BACnetPropertyType(349,"PROP_COVU_PERIOD");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_COVU_RECIPIENTS = BACnetPropertyType(350,"PROP_COVU_RECIPIENTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_MESSAGE_TEXTS = BACnetPropertyType(351,"PROP_EVENT_MESSAGE_TEXTS");
    /* enumerations 352-363 are defined in Addendum 2010-af */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_MESSAGE_TEXTS_CONFIG = BACnetPropertyType(352,"PROP_EVENT_MESSAGE_TEXTS_CONFIG");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_DETECTION_ENABLE = BACnetPropertyType(353,"PROP_EVENT_DETECTION_ENABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_ALGORITHM_INHIBIT = BACnetPropertyType(354,"PROP_EVENT_ALGORITHM_INHIBIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EVENT_ALGORITHM_INHIBIT_REF = BACnetPropertyType(355,"PROP_EVENT_ALGORITHM_INHIBIT_REF");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TIME_DELAY_NORMAL = BACnetPropertyType(356,"PROP_TIME_DELAY_NORMAL");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_RELIABILITY_EVALUATION_INHIBIT = BACnetPropertyType(357,"PROP_RELIABILITY_EVALUATION_INHIBIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FAULT_PARAMETERS = BACnetPropertyType(358,"PROP_FAULT_PARAMETERS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_FAULT_TYPE = BACnetPropertyType(359,"PROP_FAULT_TYPE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LOCAL_FORWARDING_ONLY = BACnetPropertyType(360,"PROP_LOCAL_FORWARDING_ONLY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROCESS_IDENTIFIER_FILTER = BACnetPropertyType(361,"PROP_PROCESS_IDENTIFIER_FILTER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SUBSCRIBED_RECIPIENTS = BACnetPropertyType(362,"PROP_SUBSCRIBED_RECIPIENTS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PORT_FILTER = BACnetPropertyType(363,"PROP_PORT_FILTER");
    /* enumeration 364 is defined in Addendum 2010-ae */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_AUTHORIZATION_EXEMPTIONS = BACnetPropertyType(364,"PROP_AUTHORIZATION_EXEMPTIONS");
    /* enumerations 365-370 are defined in Addendum 2010-aa */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_ALLOW_GROUP_DELAY_INHIBIT = BACnetPropertyType(365,"PROP_ALLOW_GROUP_DELAY_INHIBIT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CHANNEL_NUMBER = BACnetPropertyType(366,"PROP_CHANNEL_NUMBER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_CONTROL_GROUPS = BACnetPropertyType(367,"PROP_CONTROL_GROUPS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EXECUTION_DELAY = BACnetPropertyType(368,"PROP_EXECUTION_DELAY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LAST_PRIORITY = BACnetPropertyType(369,"PROP_LAST_PRIORITY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_WRITE_STATUS = BACnetPropertyType(370,"PROP_WRITE_STATUS");
    /* enumeration 371 is defined in Addendum 2010-ao */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_PROPERTY_LIST = BACnetPropertyType(371,"PROP_PROPERTY_LIST");
    /* enumeration 372 is defined in Addendum 2010-ak */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_SERIAL_NUMBER = BACnetPropertyType(372,"PROP_SERIAL_NUMBER");
    /* enumerations 373-386 are defined in Addendum 2010-i */
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_BLINK_WARN_ENABLE = BACnetPropertyType(373,"PROP_BLINK_WARN_ENABLE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DEFAULT_FADE_TIME = BACnetPropertyType(374,"PROP_DEFAULT_FADE_TIME");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DEFAULT_RAMP_RATE = BACnetPropertyType(375,"PROP_DEFAULT_RAMP_RATE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_DEFAULT_STEP_INCREMENT = BACnetPropertyType(376,"PROP_DEFAULT_STEP_INCREMENT");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EGRESS_TIMER = BACnetPropertyType(377,"PROP_EGRESS_TIMER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_IN_PROGRESS = BACnetPropertyType(378,"PROP_IN_PROGRESS");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_INSTANTANEOUS_POWER = BACnetPropertyType(379,"PROP_INSTANTANEOUS_POWER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LIGHTING_COMMAND = BACnetPropertyType(380,"PROP_LIGHTING_COMMAND");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_LIGHTING_COMMAND_DEFAULT_PRIORITY = BACnetPropertyType(381,"PROP_LIGHTING_COMMAND_DEFAULT_PRIORITY");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MAX_ACTUAL_VALUE = BACnetPropertyType(382,"PROP_MAX_ACTUAL_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_MIN_ACTUAL_VALUE = BACnetPropertyType(383,"PROP_MIN_ACTUAL_VALUE");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_POWER = BACnetPropertyType(384,"PROP_POWER");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_TRANSITION = BACnetPropertyType(385,"PROP_TRANSITION");
BACnetPropertyType const BACnetEnumPropertyIdentifier::PROP_EGRESS_ACTIVE = BACnetPropertyType(386,"PROP_EGRESS_ACTIVE");
/* The special property identifiers all, optional, and required  */
/* are reserved for use in the ReadPropertyConditional and */
/* ReadPropertyMultiple services or services not defined in this standard. */
/* Enumerated values 0-511 are reserved for definition by ASHRAE.  */
/* Enumerated values 512-4194303 may be used by others subject to the  */
/* procedures and constraints described in Clause 23.  */
/* do the max range inside of enum so that
       compilers will allocate adequate sized datatype for enum
       which is used to store decoding */
//MAX_BACNET_PROPERTY_ID = 4194303


std::map<uint32_t, BACnetPropertyType const *> BACnetEnumPropertyIdentifier::objectMap = BACnetEnumPropertyIdentifier::init_map();

std::map<uint32_t, BACnetPropertyType const *> BACnetEnumPropertyIdentifier::init_map() {

	std::map<uint32_t, BACnetPropertyType const *> lmap;

	lmap[PROP_ACKED_TRANSITIONS.getValue()] = (BACnetPropertyType const *) &PROP_ACKED_TRANSITIONS;
	lmap[PROP_ACK_REQUIRED.getValue()] = (BACnetPropertyType const *) &PROP_ACK_REQUIRED;
	lmap[PROP_ACTION.getValue()] = (BACnetPropertyType const *) &PROP_ACTION;
	lmap[PROP_ACTION_TEXT.getValue()] = (BACnetPropertyType const *) &PROP_ACTION_TEXT;
	lmap[PROP_ACTIVE_TEXT.getValue()] = (BACnetPropertyType const *) &PROP_ACTIVE_TEXT;
	lmap[PROP_ACTIVE_VT_SESSIONS.getValue()] = (BACnetPropertyType const *) &PROP_ACTIVE_VT_SESSIONS;
	lmap[PROP_ALARM_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_ALARM_VALUE;
	lmap[PROP_ALARM_VALUES.getValue()] = (BACnetPropertyType const *) &PROP_ALARM_VALUES;
	lmap[PROP_ALL.getValue()] = (BACnetPropertyType const *) &PROP_ALL;
	lmap[PROP_ALL_WRITES_SUCCESSFUL.getValue()] = (BACnetPropertyType const *) &PROP_ALL_WRITES_SUCCESSFUL;
	lmap[PROP_APDU_SEGMENT_TIMEOUT.getValue()] = (BACnetPropertyType const *) &PROP_APDU_SEGMENT_TIMEOUT;
	lmap[PROP_APDU_TIMEOUT.getValue()] = (BACnetPropertyType const *) &PROP_APDU_TIMEOUT;
	lmap[PROP_APPLICATION_SOFTWARE_VERSION.getValue()] = (BACnetPropertyType const *) &PROP_APPLICATION_SOFTWARE_VERSION;
	lmap[PROP_ARCHIVE.getValue()] = (BACnetPropertyType const *) &PROP_ARCHIVE;
	lmap[PROP_BIAS.getValue()] = (BACnetPropertyType const *) &PROP_BIAS;
	lmap[PROP_CHANGE_OF_STATE_COUNT.getValue()] = (BACnetPropertyType const *) &PROP_CHANGE_OF_STATE_COUNT;
	lmap[PROP_CHANGE_OF_STATE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_CHANGE_OF_STATE_TIME;
	lmap[PROP_NOTIFICATION_CLASS.getValue()] = (BACnetPropertyType const *) &PROP_NOTIFICATION_CLASS;
	lmap[PROP_BLANK_1.getValue()] = (BACnetPropertyType const *) &PROP_BLANK_1;
	lmap[PROP_CONTROLLED_VARIABLE_REFERENCE.getValue()] = (BACnetPropertyType const *) &PROP_CONTROLLED_VARIABLE_REFERENCE;
	lmap[PROP_CONTROLLED_VARIABLE_UNITS.getValue()] = (BACnetPropertyType const *) &PROP_CONTROLLED_VARIABLE_UNITS;
	lmap[PROP_CONTROLLED_VARIABLE_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_CONTROLLED_VARIABLE_VALUE;
	lmap[PROP_COV_INCREMENT.getValue()] = (BACnetPropertyType const *) &PROP_COV_INCREMENT;
	lmap[PROP_DATE_LIST.getValue()] = (BACnetPropertyType const *) &PROP_DATE_LIST;
	lmap[PROP_DAYLIGHT_SAVINGS_STATUS.getValue()] = (BACnetPropertyType const *) &PROP_DAYLIGHT_SAVINGS_STATUS;
	lmap[PROP_DEADBAND.getValue()] = (BACnetPropertyType const *) &PROP_DEADBAND;
	lmap[PROP_DERIVATIVE_CONSTANT.getValue()] = (BACnetPropertyType const *) &PROP_DERIVATIVE_CONSTANT;
	lmap[PROP_DERIVATIVE_CONSTANT_UNITS.getValue()] = (BACnetPropertyType const *) &PROP_DERIVATIVE_CONSTANT_UNITS;
	lmap[PROP_DESCRIPTION.getValue()] = (BACnetPropertyType const *) &PROP_DESCRIPTION;
	lmap[PROP_DESCRIPTION_OF_HALT.getValue()] = (BACnetPropertyType const *) &PROP_DESCRIPTION_OF_HALT;
	lmap[PROP_DEVICE_ADDRESS_BINDING.getValue()] = (BACnetPropertyType const *) &PROP_DEVICE_ADDRESS_BINDING;
	lmap[PROP_DEVICE_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_DEVICE_TYPE;
	lmap[PROP_EFFECTIVE_PERIOD.getValue()] = (BACnetPropertyType const *) &PROP_EFFECTIVE_PERIOD;
	lmap[PROP_ELAPSED_ACTIVE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_ELAPSED_ACTIVE_TIME;
	lmap[PROP_ERROR_LIMIT.getValue()] = (BACnetPropertyType const *) &PROP_ERROR_LIMIT;
	lmap[PROP_EVENT_ENABLE.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_ENABLE;
	lmap[PROP_EVENT_STATE.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_STATE;
	lmap[PROP_EVENT_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_TYPE;
	lmap[PROP_EXCEPTION_SCHEDULE.getValue()] = (BACnetPropertyType const *) &PROP_EXCEPTION_SCHEDULE;
	lmap[PROP_FAULT_VALUES.getValue()] = (BACnetPropertyType const *) &PROP_FAULT_VALUES;
	lmap[PROP_FEEDBACK_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_FEEDBACK_VALUE;
	lmap[PROP_FILE_ACCESS_METHOD.getValue()] = (BACnetPropertyType const *) &PROP_FILE_ACCESS_METHOD;
	lmap[PROP_FILE_SIZE.getValue()] = (BACnetPropertyType const *) &PROP_FILE_SIZE;
	lmap[PROP_FILE_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_FILE_TYPE;
	lmap[PROP_FIRMWARE_REVISION.getValue()] = (BACnetPropertyType const *) &PROP_FIRMWARE_REVISION;
	lmap[PROP_HIGH_LIMIT.getValue()] = (BACnetPropertyType const *) &PROP_HIGH_LIMIT;
	lmap[PROP_INACTIVE_TEXT.getValue()] = (BACnetPropertyType const *) &PROP_INACTIVE_TEXT;
	lmap[PROP_IN_PROCESS.getValue()] = (BACnetPropertyType const *) &PROP_IN_PROCESS;
	lmap[PROP_INSTANCE_OF.getValue()] = (BACnetPropertyType const *) &PROP_INSTANCE_OF;
	lmap[PROP_INTEGRAL_CONSTANT.getValue()] = (BACnetPropertyType const *) &PROP_INTEGRAL_CONSTANT;
	lmap[PROP_INTEGRAL_CONSTANT_UNITS.getValue()] = (BACnetPropertyType const *) &PROP_INTEGRAL_CONSTANT_UNITS;
	lmap[PROP_ISSUE_CONFIRMED_NOTIFICATIONS.getValue()] = (BACnetPropertyType const *) &PROP_ISSUE_CONFIRMED_NOTIFICATIONS;
	lmap[PROP_LIMIT_ENABLE.getValue()] = (BACnetPropertyType const *) &PROP_LIMIT_ENABLE;
	lmap[PROP_LIST_OF_GROUP_MEMBERS.getValue()] = (BACnetPropertyType const *) &PROP_LIST_OF_GROUP_MEMBERS;
	lmap[PROP_LIST_OF_OBJECT_PROPERTY_REFERENCES.getValue()] = (BACnetPropertyType const *) &PROP_LIST_OF_OBJECT_PROPERTY_REFERENCES;
	lmap[PROP_LIST_OF_SESSION_KEYS.getValue()] = (BACnetPropertyType const *) &PROP_LIST_OF_SESSION_KEYS;
	lmap[PROP_LOCAL_DATE.getValue()] = (BACnetPropertyType const *) &PROP_LOCAL_DATE;
	lmap[PROP_LOCAL_TIME.getValue()] = (BACnetPropertyType const *) &PROP_LOCAL_TIME;
	lmap[PROP_LOCATION.getValue()] = (BACnetPropertyType const *) &PROP_LOCATION;
	lmap[PROP_LOW_LIMIT.getValue()] = (BACnetPropertyType const *) &PROP_LOW_LIMIT;
	lmap[PROP_MANIPULATED_VARIABLE_REFERENCE.getValue()] = (BACnetPropertyType const *) &PROP_MANIPULATED_VARIABLE_REFERENCE;
	lmap[PROP_MAXIMUM_OUTPUT.getValue()] = (BACnetPropertyType const *) &PROP_MAXIMUM_OUTPUT;
	lmap[PROP_MAX_APDU_LENGTH_ACCEPTED.getValue()] = (BACnetPropertyType const *) &PROP_MAX_APDU_LENGTH_ACCEPTED;
	lmap[PROP_MAX_INFO_FRAMES.getValue()] = (BACnetPropertyType const *) &PROP_MAX_INFO_FRAMES;
	lmap[PROP_MAX_MASTER.getValue()] = (BACnetPropertyType const *) &PROP_MAX_MASTER;
	lmap[PROP_MAX_PRES_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_MAX_PRES_VALUE;
	lmap[PROP_MINIMUM_OFF_TIME.getValue()] = (BACnetPropertyType const *) &PROP_MINIMUM_OFF_TIME;
	lmap[PROP_MINIMUM_ON_TIME.getValue()] = (BACnetPropertyType const *) &PROP_MINIMUM_ON_TIME;
	lmap[PROP_MINIMUM_OUTPUT.getValue()] = (BACnetPropertyType const *) &PROP_MINIMUM_OUTPUT;
	lmap[PROP_MIN_PRES_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_MIN_PRES_VALUE;
	lmap[PROP_MODEL_NAME.getValue()] = (BACnetPropertyType const *) &PROP_MODEL_NAME;
	lmap[PROP_MODIFICATION_DATE.getValue()] = (BACnetPropertyType const *) &PROP_MODIFICATION_DATE;
	lmap[PROP_NOTIFY_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_NOTIFY_TYPE;
	lmap[PROP_NUMBER_OF_APDU_RETRIES.getValue()] = (BACnetPropertyType const *) &PROP_NUMBER_OF_APDU_RETRIES;
	lmap[PROP_NUMBER_OF_STATES.getValue()] = (BACnetPropertyType const *) &PROP_NUMBER_OF_STATES;
	lmap[PROP_OBJECT_IDENTIFIER.getValue()] = (BACnetPropertyType const *) &PROP_OBJECT_IDENTIFIER;
	lmap[PROP_OBJECT_LIST.getValue()] = (BACnetPropertyType const *) &PROP_OBJECT_LIST;
	lmap[PROP_OBJECT_NAME.getValue()] = (BACnetPropertyType const *) &PROP_OBJECT_NAME;
	lmap[PROP_OBJECT_PROPERTY_REFERENCE.getValue()] = (BACnetPropertyType const *) &PROP_OBJECT_PROPERTY_REFERENCE;
	lmap[PROP_OBJECT_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_OBJECT_TYPE;
	lmap[PROP_OPTIONAL.getValue()] = (BACnetPropertyType const *) &PROP_OPTIONAL;
	lmap[PROP_OUT_OF_SERVICE.getValue()] = (BACnetPropertyType const *) &PROP_OUT_OF_SERVICE;
	lmap[PROP_OUTPUT_UNITS.getValue()] = (BACnetPropertyType const *) &PROP_OUTPUT_UNITS;
	lmap[PROP_EVENT_PARAMETERS.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_PARAMETERS;
	lmap[PROP_POLARITY.getValue()] = (BACnetPropertyType const *) &PROP_POLARITY;
	lmap[PROP_PRESENT_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_PRESENT_VALUE;
	lmap[PROP_PRIORITY.getValue()] = (BACnetPropertyType const *) &PROP_PRIORITY;
	lmap[PROP_PRIORITY_ARRAY.getValue()] = (BACnetPropertyType const *) &PROP_PRIORITY_ARRAY;
	lmap[PROP_PRIORITY_FOR_WRITING.getValue()] = (BACnetPropertyType const *) &PROP_PRIORITY_FOR_WRITING;
	lmap[PROP_PROCESS_IDENTIFIER.getValue()] = (BACnetPropertyType const *) &PROP_PROCESS_IDENTIFIER;
	lmap[PROP_PROGRAM_CHANGE.getValue()] = (BACnetPropertyType const *) &PROP_PROGRAM_CHANGE;
	lmap[PROP_PROGRAM_LOCATION.getValue()] = (BACnetPropertyType const *) &PROP_PROGRAM_LOCATION;
	lmap[PROP_PROGRAM_STATE.getValue()] = (BACnetPropertyType const *) &PROP_PROGRAM_STATE;
	lmap[PROP_PROPORTIONAL_CONSTANT.getValue()] = (BACnetPropertyType const *) &PROP_PROPORTIONAL_CONSTANT;
	lmap[PROP_PROPORTIONAL_CONSTANT_UNITS.getValue()] = (BACnetPropertyType const *) &PROP_PROPORTIONAL_CONSTANT_UNITS;
	lmap[PROP_PROTOCOL_CONFORMANCE_CLASS.getValue()] = (BACnetPropertyType const *) &PROP_PROTOCOL_CONFORMANCE_CLASS;       /* deleted in version 1 revision 2 */
	lmap[PROP_PROTOCOL_OBJECT_TYPES_SUPPORTED.getValue()] = (BACnetPropertyType const *) &PROP_PROTOCOL_OBJECT_TYPES_SUPPORTED;
	lmap[PROP_PROTOCOL_SERVICES_SUPPORTED.getValue()] = (BACnetPropertyType const *) &PROP_PROTOCOL_SERVICES_SUPPORTED;
	lmap[PROP_PROTOCOL_VERSION.getValue()] = (BACnetPropertyType const *) &PROP_PROTOCOL_VERSION;
	lmap[PROP_READ_ONLY.getValue()] = (BACnetPropertyType const *) &PROP_READ_ONLY;
	lmap[PROP_REASON_FOR_HALT.getValue()] = (BACnetPropertyType const *) &PROP_REASON_FOR_HALT;
	lmap[PROP_RECIPIENT.getValue()] = (BACnetPropertyType const *) &PROP_RECIPIENT;
	lmap[PROP_RECIPIENT_LIST.getValue()] = (BACnetPropertyType const *) &PROP_RECIPIENT_LIST;
	lmap[PROP_RELIABILITY.getValue()] = (BACnetPropertyType const *) &PROP_RELIABILITY;
	lmap[PROP_RELINQUISH_DEFAULT.getValue()] = (BACnetPropertyType const *) &PROP_RELINQUISH_DEFAULT;
	lmap[PROP_REQUIRED.getValue()] = (BACnetPropertyType const *) &PROP_REQUIRED;
	lmap[PROP_RESOLUTION.getValue()] = (BACnetPropertyType const *) &PROP_RESOLUTION;
	lmap[PROP_SEGMENTATION_SUPPORTED.getValue()] = (BACnetPropertyType const *) &PROP_SEGMENTATION_SUPPORTED;
	lmap[PROP_SETPOINT.getValue()] = (BACnetPropertyType const *) &PROP_SETPOINT;
	lmap[PROP_SETPOINT_REFERENCE.getValue()] = (BACnetPropertyType const *) &PROP_SETPOINT_REFERENCE;
	lmap[PROP_STATE_TEXT.getValue()] = (BACnetPropertyType const *) &PROP_STATE_TEXT;
	lmap[PROP_STATUS_FLAGS.getValue()] = (BACnetPropertyType const *) &PROP_STATUS_FLAGS;
	lmap[PROP_SYSTEM_STATUS.getValue()] = (BACnetPropertyType const *) &PROP_SYSTEM_STATUS;
	lmap[PROP_TIME_DELAY.getValue()] = (BACnetPropertyType const *) &PROP_TIME_DELAY;
	lmap[PROP_TIME_OF_ACTIVE_TIME_RESET.getValue()] = (BACnetPropertyType const *) &PROP_TIME_OF_ACTIVE_TIME_RESET;
	lmap[PROP_TIME_OF_STATE_COUNT_RESET.getValue()] = (BACnetPropertyType const *) &PROP_TIME_OF_STATE_COUNT_RESET;
	lmap[PROP_TIME_SYNCHRONIZATION_RECIPIENTS.getValue()] = (BACnetPropertyType const *) &PROP_TIME_SYNCHRONIZATION_RECIPIENTS;
	lmap[PROP_UNITS.getValue()] = (BACnetPropertyType const *) &PROP_UNITS;
	lmap[PROP_UPDATE_INTERVAL.getValue()] = (BACnetPropertyType const *) &PROP_UPDATE_INTERVAL;
	lmap[PROP_UTC_OFFSET.getValue()] = (BACnetPropertyType const *) &PROP_UTC_OFFSET;
	lmap[PROP_VENDOR_IDENTIFIER.getValue()] = (BACnetPropertyType const *) &PROP_VENDOR_IDENTIFIER;
	lmap[PROP_VENDOR_NAME.getValue()] = (BACnetPropertyType const *) &PROP_VENDOR_NAME;
	lmap[PROP_VT_CLASSES_SUPPORTED.getValue()] = (BACnetPropertyType const *) &PROP_VT_CLASSES_SUPPORTED;
	lmap[PROP_WEEKLY_SCHEDULE.getValue()] = (BACnetPropertyType const *) &PROP_WEEKLY_SCHEDULE;
	lmap[PROP_ATTEMPTED_SAMPLES.getValue()] = (BACnetPropertyType const *) &PROP_ATTEMPTED_SAMPLES;
	lmap[PROP_AVERAGE_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_AVERAGE_VALUE;
	lmap[PROP_BUFFER_SIZE.getValue()] = (BACnetPropertyType const *) &PROP_BUFFER_SIZE;
	lmap[PROP_CLIENT_COV_INCREMENT.getValue()] = (BACnetPropertyType const *) &PROP_CLIENT_COV_INCREMENT;
	lmap[PROP_COV_RESUBSCRIPTION_INTERVAL.getValue()] = (BACnetPropertyType const *) &PROP_COV_RESUBSCRIPTION_INTERVAL;
	lmap[PROP_CURRENT_NOTIFY_TIME.getValue()] = (BACnetPropertyType const *) &PROP_CURRENT_NOTIFY_TIME;
	lmap[PROP_EVENT_TIME_STAMPS.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_TIME_STAMPS;
	lmap[PROP_LOG_BUFFER.getValue()] = (BACnetPropertyType const *) &PROP_LOG_BUFFER;
	lmap[PROP_LOG_DEVICE_OBJECT_PROPERTY.getValue()] = (BACnetPropertyType const *) &PROP_LOG_DEVICE_OBJECT_PROPERTY;
	lmap[PROP_ENABLE.getValue()] = (BACnetPropertyType const *) &PROP_ENABLE;
	lmap[PROP_LOG_INTERVAL.getValue()] = (BACnetPropertyType const *) &PROP_LOG_INTERVAL;
	lmap[PROP_MAXIMUM_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_MAXIMUM_VALUE;
	lmap[PROP_MINIMUM_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_MINIMUM_VALUE;
	lmap[PROP_NOTIFICATION_THRESHOLD.getValue()] = (BACnetPropertyType const *) &PROP_NOTIFICATION_THRESHOLD;
	lmap[PROP_PREVIOUS_NOTIFY_TIME.getValue()] = (BACnetPropertyType const *) &PROP_PREVIOUS_NOTIFY_TIME;
	lmap[PROP_PROTOCOL_REVISION.getValue()] = (BACnetPropertyType const *) &PROP_PROTOCOL_REVISION;
	lmap[PROP_RECORDS_SINCE_NOTIFICATION.getValue()] = (BACnetPropertyType const *) &PROP_RECORDS_SINCE_NOTIFICATION;
	lmap[PROP_RECORD_COUNT.getValue()] = (BACnetPropertyType const *) &PROP_RECORD_COUNT;
	lmap[PROP_START_TIME.getValue()] = (BACnetPropertyType const *) &PROP_START_TIME;
	lmap[PROP_STOP_TIME.getValue()] = (BACnetPropertyType const *) &PROP_STOP_TIME;
	lmap[PROP_STOP_WHEN_FULL.getValue()] = (BACnetPropertyType const *) &PROP_STOP_WHEN_FULL;
	lmap[PROP_TOTAL_RECORD_COUNT.getValue()] = (BACnetPropertyType const *) &PROP_TOTAL_RECORD_COUNT;
	lmap[PROP_VALID_SAMPLES.getValue()] = (BACnetPropertyType const *) &PROP_VALID_SAMPLES;
	lmap[PROP_WINDOW_INTERVAL.getValue()] = (BACnetPropertyType const *) &PROP_WINDOW_INTERVAL;
	lmap[PROP_WINDOW_SAMPLES.getValue()] = (BACnetPropertyType const *) &PROP_WINDOW_SAMPLES;
	lmap[PROP_MAXIMUM_VALUE_TIMESTAMP.getValue()] = (BACnetPropertyType const *) &PROP_MAXIMUM_VALUE_TIMESTAMP;
	lmap[PROP_MINIMUM_VALUE_TIMESTAMP.getValue()] = (BACnetPropertyType const *) &PROP_MINIMUM_VALUE_TIMESTAMP;
	lmap[PROP_VARIANCE_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_VARIANCE_VALUE;
	lmap[PROP_ACTIVE_COV_SUBSCRIPTIONS.getValue()] = (BACnetPropertyType const *) &PROP_ACTIVE_COV_SUBSCRIPTIONS;
	lmap[PROP_BACKUP_FAILURE_TIMEOUT.getValue()] = (BACnetPropertyType const *) &PROP_BACKUP_FAILURE_TIMEOUT;
	lmap[PROP_CONFIGURATION_FILES.getValue()] = (BACnetPropertyType const *) &PROP_CONFIGURATION_FILES;
	lmap[PROP_DATABASE_REVISION.getValue()] = (BACnetPropertyType const *) &PROP_DATABASE_REVISION;
	lmap[PROP_DIRECT_READING.getValue()] = (BACnetPropertyType const *) &PROP_DIRECT_READING;
	lmap[PROP_LAST_RESTORE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_LAST_RESTORE_TIME;
	lmap[PROP_MAINTENANCE_REQUIRED.getValue()] = (BACnetPropertyType const *) &PROP_MAINTENANCE_REQUIRED;
	lmap[PROP_MEMBER_OF.getValue()] = (BACnetPropertyType const *) &PROP_MEMBER_OF;
	lmap[PROP_MODE.getValue()] = (BACnetPropertyType const *) &PROP_MODE;
	lmap[PROP_OPERATION_EXPECTED.getValue()] = (BACnetPropertyType const *) &PROP_OPERATION_EXPECTED;
	lmap[PROP_SETTING.getValue()] = (BACnetPropertyType const *) &PROP_SETTING;
	lmap[PROP_SILENCED.getValue()] = (BACnetPropertyType const *) &PROP_SILENCED;
	lmap[PROP_TRACKING_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_TRACKING_VALUE;
	lmap[PROP_ZONE_MEMBERS.getValue()] = (BACnetPropertyType const *) &PROP_ZONE_MEMBERS;
	lmap[PROP_LIFE_SAFETY_ALARM_VALUES.getValue()] = (BACnetPropertyType const *) &PROP_LIFE_SAFETY_ALARM_VALUES;
	lmap[PROP_MAX_SEGMENTS_ACCEPTED.getValue()] = (BACnetPropertyType const *) &PROP_MAX_SEGMENTS_ACCEPTED;
	lmap[PROP_PROFILE_NAME.getValue()] = (BACnetPropertyType const *) &PROP_PROFILE_NAME;
	lmap[PROP_AUTO_SLAVE_DISCOVERY.getValue()] = (BACnetPropertyType const *) &PROP_AUTO_SLAVE_DISCOVERY;
	lmap[PROP_MANUAL_SLAVE_ADDRESS_BINDING.getValue()] = (BACnetPropertyType const *) &PROP_MANUAL_SLAVE_ADDRESS_BINDING;
	lmap[PROP_SLAVE_ADDRESS_BINDING.getValue()] = (BACnetPropertyType const *) &PROP_SLAVE_ADDRESS_BINDING;
	lmap[PROP_SLAVE_PROXY_ENABLE.getValue()] = (BACnetPropertyType const *) &PROP_SLAVE_PROXY_ENABLE;
	lmap[PROP_LAST_NOTIFY_RECORD.getValue()] = (BACnetPropertyType const *) &PROP_LAST_NOTIFY_RECORD;
	lmap[PROP_SCHEDULE_DEFAULT.getValue()] = (BACnetPropertyType const *) &PROP_SCHEDULE_DEFAULT;
	lmap[PROP_ACCEPTED_MODES.getValue()] = (BACnetPropertyType const *) &PROP_ACCEPTED_MODES;
	lmap[PROP_ADJUST_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_ADJUST_VALUE;
	lmap[PROP_COUNT.getValue()] = (BACnetPropertyType const *) &PROP_COUNT;
	lmap[PROP_COUNT_BEFORE_CHANGE.getValue()] = (BACnetPropertyType const *) &PROP_COUNT_BEFORE_CHANGE;
	lmap[PROP_COUNT_CHANGE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_COUNT_CHANGE_TIME;
	lmap[PROP_COV_PERIOD.getValue()] = (BACnetPropertyType const *) &PROP_COV_PERIOD;
	lmap[PROP_INPUT_REFERENCE.getValue()] = (BACnetPropertyType const *) &PROP_INPUT_REFERENCE;
	lmap[PROP_LIMIT_MONITORING_INTERVAL.getValue()] = (BACnetPropertyType const *) &PROP_LIMIT_MONITORING_INTERVAL;
	lmap[PROP_LOGGING_OBJECT.getValue()] = (BACnetPropertyType const *) &PROP_LOGGING_OBJECT;
	lmap[PROP_LOGGING_RECORD.getValue()] = (BACnetPropertyType const *) &PROP_LOGGING_RECORD;
	lmap[PROP_PRESCALE.getValue()] = (BACnetPropertyType const *) &PROP_PRESCALE;
	lmap[PROP_PULSE_RATE.getValue()] = (BACnetPropertyType const *) &PROP_PULSE_RATE;
	lmap[PROP_SCALE.getValue()] = (BACnetPropertyType const *) &PROP_SCALE;
	lmap[PROP_SCALE_FACTOR.getValue()] = (BACnetPropertyType const *) &PROP_SCALE_FACTOR;
	lmap[PROP_UPDATE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_UPDATE_TIME;
	lmap[PROP_VALUE_BEFORE_CHANGE.getValue()] = (BACnetPropertyType const *) &PROP_VALUE_BEFORE_CHANGE;
	lmap[PROP_VALUE_SET.getValue()] = (BACnetPropertyType const *) &PROP_VALUE_SET;
	lmap[PROP_VALUE_CHANGE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_VALUE_CHANGE_TIME;
	lmap[PROP_ALIGN_INTERVALS.getValue()] = (BACnetPropertyType const *) &PROP_ALIGN_INTERVALS;
	lmap[PROP_INTERVAL_OFFSET.getValue()] = (BACnetPropertyType const *) &PROP_INTERVAL_OFFSET;
	lmap[PROP_LAST_RESTART_REASON.getValue()] = (BACnetPropertyType const *) &PROP_LAST_RESTART_REASON;
	lmap[PROP_LOGGING_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_LOGGING_TYPE;
	lmap[PROP_RESTART_NOTIFICATION_RECIPIENTS.getValue()] = (BACnetPropertyType const *) &PROP_RESTART_NOTIFICATION_RECIPIENTS;
	lmap[PROP_TIME_OF_DEVICE_RESTART.getValue()] = (BACnetPropertyType const *) &PROP_TIME_OF_DEVICE_RESTART;
	lmap[PROP_TIME_SYNCHRONIZATION_INTERVAL.getValue()] = (BACnetPropertyType const *) &PROP_TIME_SYNCHRONIZATION_INTERVAL;
	lmap[PROP_TRIGGER.getValue()] = (BACnetPropertyType const *) &PROP_TRIGGER;
	lmap[PROP_UTC_TIME_SYNCHRONIZATION_RECIPIENTS.getValue()] = (BACnetPropertyType const *) &PROP_UTC_TIME_SYNCHRONIZATION_RECIPIENTS;
	lmap[PROP_NODE_SUBTYPE.getValue()] = (BACnetPropertyType const *) &PROP_NODE_SUBTYPE;
	lmap[PROP_NODE_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_NODE_TYPE;
	lmap[PROP_STRUCTURED_OBJECT_LIST.getValue()] = (BACnetPropertyType const *) &PROP_STRUCTURED_OBJECT_LIST;
	lmap[PROP_SUBORDINATE_ANNOTATIONS.getValue()] = (BACnetPropertyType const *) &PROP_SUBORDINATE_ANNOTATIONS;
	lmap[PROP_SUBORDINATE_LIST.getValue()] = (BACnetPropertyType const *) &PROP_SUBORDINATE_LIST;
	lmap[PROP_ACTUAL_SHED_LEVEL.getValue()] = (BACnetPropertyType const *) &PROP_ACTUAL_SHED_LEVEL;
	lmap[PROP_DUTY_WINDOW.getValue()] = (BACnetPropertyType const *) &PROP_DUTY_WINDOW;
	lmap[PROP_EXPECTED_SHED_LEVEL.getValue()] = (BACnetPropertyType const *) &PROP_EXPECTED_SHED_LEVEL;
	lmap[PROP_FULL_DUTY_BASELINE.getValue()] = (BACnetPropertyType const *) &PROP_FULL_DUTY_BASELINE;
	lmap[PROP_REQUESTED_SHED_LEVEL.getValue()] = (BACnetPropertyType const *) &PROP_REQUESTED_SHED_LEVEL;
	lmap[PROP_SHED_DURATION.getValue()] = (BACnetPropertyType const *) &PROP_SHED_DURATION;
	lmap[PROP_SHED_LEVEL_DESCRIPTIONS.getValue()] = (BACnetPropertyType const *) &PROP_SHED_LEVEL_DESCRIPTIONS;
	lmap[PROP_SHED_LEVELS.getValue()] = (BACnetPropertyType const *) &PROP_SHED_LEVELS;
	lmap[PROP_STATE_DESCRIPTION.getValue()] = (BACnetPropertyType const *) &PROP_STATE_DESCRIPTION;
	lmap[PROP_DOOR_ALARM_STATE.getValue()] = (BACnetPropertyType const *) &PROP_DOOR_ALARM_STATE;
	lmap[PROP_DOOR_EXTENDED_PULSE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_DOOR_EXTENDED_PULSE_TIME;
	lmap[PROP_DOOR_MEMBERS.getValue()] = (BACnetPropertyType const *) &PROP_DOOR_MEMBERS;
	lmap[PROP_DOOR_OPEN_TOO_LONG_TIME.getValue()] = (BACnetPropertyType const *) &PROP_DOOR_OPEN_TOO_LONG_TIME;
	lmap[PROP_DOOR_PULSE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_DOOR_PULSE_TIME;
	lmap[PROP_DOOR_STATUS.getValue()] = (BACnetPropertyType const *) &PROP_DOOR_STATUS;
	lmap[PROP_DOOR_UNLOCK_DELAY_TIME.getValue()] = (BACnetPropertyType const *) &PROP_DOOR_UNLOCK_DELAY_TIME;
	lmap[PROP_LOCK_STATUS.getValue()] = (BACnetPropertyType const *) &PROP_LOCK_STATUS;
	lmap[PROP_MASKED_ALARM_VALUES.getValue()] = (BACnetPropertyType const *) &PROP_MASKED_ALARM_VALUES;
	lmap[PROP_SECURED_STATUS.getValue()] = (BACnetPropertyType const *) &PROP_SECURED_STATUS;
	lmap[PROP_ABSENTEE_LIMIT.getValue()] = (BACnetPropertyType const *) &PROP_ABSENTEE_LIMIT;
	lmap[PROP_ACCESS_ALARM_EVENTS.getValue()] = (BACnetPropertyType const *) &PROP_ACCESS_ALARM_EVENTS;
	lmap[PROP_ACCESS_DOORS.getValue()] = (BACnetPropertyType const *) &PROP_ACCESS_DOORS;
	lmap[PROP_ACCESS_EVENT.getValue()] = (BACnetPropertyType const *) &PROP_ACCESS_EVENT;
	lmap[PROP_ACCESS_EVENT_AUTHENTICATION_FACTOR.getValue()] = (BACnetPropertyType const *) &PROP_ACCESS_EVENT_AUTHENTICATION_FACTOR;
	lmap[PROP_ACCESS_EVENT_CREDENTIAL.getValue()] = (BACnetPropertyType const *) &PROP_ACCESS_EVENT_CREDENTIAL;
	lmap[PROP_ACCESS_EVENT_TIME.getValue()] = (BACnetPropertyType const *) &PROP_ACCESS_EVENT_TIME;
	lmap[PROP_ACCESS_TRANSACTION_EVENTS.getValue()] = (BACnetPropertyType const *) &PROP_ACCESS_TRANSACTION_EVENTS;
	lmap[PROP_ACCOMPANIMENT.getValue()] = (BACnetPropertyType const *) &PROP_ACCOMPANIMENT;
	lmap[PROP_ACCOMPANIMENT_TIME.getValue()] = (BACnetPropertyType const *) &PROP_ACCOMPANIMENT_TIME;
	lmap[PROP_ACTIVATION_TIME.getValue()] = (BACnetPropertyType const *) &PROP_ACTIVATION_TIME;
	lmap[PROP_ACTIVE_AUTHENTICATION_POLICY.getValue()] = (BACnetPropertyType const *) &PROP_ACTIVE_AUTHENTICATION_POLICY;
	lmap[PROP_ASSIGNED_ACCESS_RIGHTS.getValue()] = (BACnetPropertyType const *) &PROP_ASSIGNED_ACCESS_RIGHTS;
	lmap[PROP_AUTHENTICATION_FACTORS.getValue()] = (BACnetPropertyType const *) &PROP_AUTHENTICATION_FACTORS;
	lmap[PROP_AUTHENTICATION_POLICY_LIST.getValue()] = (BACnetPropertyType const *) &PROP_AUTHENTICATION_POLICY_LIST;
	lmap[PROP_AUTHENTICATION_POLICY_NAMES.getValue()] = (BACnetPropertyType const *) &PROP_AUTHENTICATION_POLICY_NAMES;
	lmap[PROP_AUTHORIZATION_STATUS.getValue()] = (BACnetPropertyType const *) &PROP_AUTHORIZATION_STATUS;
	lmap[PROP_AUTHORIZATION_MODE.getValue()] = (BACnetPropertyType const *) &PROP_AUTHORIZATION_MODE;
	lmap[PROP_BELONGS_TO.getValue()] = (BACnetPropertyType const *) &PROP_BELONGS_TO;
	lmap[PROP_CREDENTIAL_DISABLE.getValue()] = (BACnetPropertyType const *) &PROP_CREDENTIAL_DISABLE;
	lmap[PROP_CREDENTIAL_STATUS.getValue()] = (BACnetPropertyType const *) &PROP_CREDENTIAL_STATUS;
	lmap[PROP_CREDENTIALS.getValue()] = (BACnetPropertyType const *) &PROP_CREDENTIALS;
	lmap[PROP_CREDENTIALS_IN_ZONE.getValue()] = (BACnetPropertyType const *) &PROP_CREDENTIALS_IN_ZONE;
	lmap[PROP_DAYS_REMAINING.getValue()] = (BACnetPropertyType const *) &PROP_DAYS_REMAINING;
	lmap[PROP_ENTRY_POINTS.getValue()] = (BACnetPropertyType const *) &PROP_ENTRY_POINTS;
	lmap[PROP_EXIT_POINTS.getValue()] = (BACnetPropertyType const *) &PROP_EXIT_POINTS;
	lmap[PROP_EXPIRY_TIME.getValue()] = (BACnetPropertyType const *) &PROP_EXPIRY_TIME;
	lmap[PROP_EXTENDED_TIME_ENABLE.getValue()] = (BACnetPropertyType const *) &PROP_EXTENDED_TIME_ENABLE;
	lmap[PROP_FAILED_ATTEMPT_EVENTS.getValue()] = (BACnetPropertyType const *) &PROP_FAILED_ATTEMPT_EVENTS;
	lmap[PROP_FAILED_ATTEMPTS.getValue()] = (BACnetPropertyType const *) &PROP_FAILED_ATTEMPTS;
	lmap[PROP_FAILED_ATTEMPTS_TIME.getValue()] = (BACnetPropertyType const *) &PROP_FAILED_ATTEMPTS_TIME;
	lmap[PROP_LAST_ACCESS_EVENT.getValue()] = (BACnetPropertyType const *) &PROP_LAST_ACCESS_EVENT;
	lmap[PROP_LAST_ACCESS_POINT.getValue()] = (BACnetPropertyType const *) &PROP_LAST_ACCESS_POINT;
	lmap[PROP_LAST_CREDENTIAL_ADDED.getValue()] = (BACnetPropertyType const *) &PROP_LAST_CREDENTIAL_ADDED;
	lmap[PROP_LAST_CREDENTIAL_ADDED_TIME.getValue()] = (BACnetPropertyType const *) &PROP_LAST_CREDENTIAL_ADDED_TIME;
	lmap[PROP_LAST_CREDENTIAL_REMOVED.getValue()] = (BACnetPropertyType const *) &PROP_LAST_CREDENTIAL_REMOVED;
	lmap[PROP_LAST_CREDENTIAL_REMOVED_TIME.getValue()] = (BACnetPropertyType const *) &PROP_LAST_CREDENTIAL_REMOVED_TIME;
	lmap[PROP_LAST_USE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_LAST_USE_TIME;
	lmap[PROP_LOCKOUT.getValue()] = (BACnetPropertyType const *) &PROP_LOCKOUT;
	lmap[PROP_LOCKOUT_RELINQUISH_TIME.getValue()] = (BACnetPropertyType const *) &PROP_LOCKOUT_RELINQUISH_TIME;
	lmap[PROP_MASTER_EXEMPTION.getValue()] = (BACnetPropertyType const *) &PROP_MASTER_EXEMPTION;
	lmap[PROP_MAX_FAILED_ATTEMPTS.getValue()] = (BACnetPropertyType const *) &PROP_MAX_FAILED_ATTEMPTS;
	lmap[PROP_MEMBERS.getValue()] = (BACnetPropertyType const *) &PROP_MEMBERS;
	lmap[PROP_MUSTER_POINT.getValue()] = (BACnetPropertyType const *) &PROP_MUSTER_POINT;
	lmap[PROP_NEGATIVE_ACCESS_RULES.getValue()] = (BACnetPropertyType const *) &PROP_NEGATIVE_ACCESS_RULES;
	lmap[PROP_NUMBER_OF_AUTHENTICATION_POLICIES.getValue()] = (BACnetPropertyType const *) &PROP_NUMBER_OF_AUTHENTICATION_POLICIES;
	lmap[PROP_OCCUPANCY_COUNT.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_COUNT;
	lmap[PROP_OCCUPANCY_COUNT_ADJUST.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_COUNT_ADJUST;
	lmap[PROP_OCCUPANCY_COUNT_ENABLE.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_COUNT_ENABLE;
	lmap[PROP_OCCUPANCY_EXEMPTION.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_EXEMPTION;
	lmap[PROP_OCCUPANCY_LOWER_LIMIT.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_LOWER_LIMIT;
	lmap[PROP_OCCUPANCY_LOWER_LIMIT_ENFORCED.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_LOWER_LIMIT_ENFORCED;
	lmap[PROP_OCCUPANCY_STATE.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_STATE;
	lmap[PROP_OCCUPANCY_UPPER_LIMIT.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_UPPER_LIMIT;
	lmap[PROP_OCCUPANCY_UPPER_LIMIT_ENFORCED.getValue()] = (BACnetPropertyType const *) &PROP_OCCUPANCY_UPPER_LIMIT_ENFORCED;
	lmap[PROP_PASSBACK_EXEMPTION.getValue()] = (BACnetPropertyType const *) &PROP_PASSBACK_EXEMPTION;
	lmap[PROP_PASSBACK_MODE.getValue()] = (BACnetPropertyType const *) &PROP_PASSBACK_MODE;
	lmap[PROP_PASSBACK_TIMEOUT.getValue()] = (BACnetPropertyType const *) &PROP_PASSBACK_TIMEOUT;
	lmap[PROP_POSITIVE_ACCESS_RULES.getValue()] = (BACnetPropertyType const *) &PROP_POSITIVE_ACCESS_RULES;
	lmap[PROP_REASON_FOR_DISABLE.getValue()] = (BACnetPropertyType const *) &PROP_REASON_FOR_DISABLE;
	lmap[PROP_SUPPORTED_FORMATS.getValue()] = (BACnetPropertyType const *) &PROP_SUPPORTED_FORMATS;
	lmap[PROP_SUPPORTED_FORMAT_CLASSES.getValue()] = (BACnetPropertyType const *) &PROP_SUPPORTED_FORMAT_CLASSES;
	lmap[PROP_THREAT_AUTHORITY.getValue()] = (BACnetPropertyType const *) &PROP_THREAT_AUTHORITY;
	lmap[PROP_THREAT_LEVEL.getValue()] = (BACnetPropertyType const *) &PROP_THREAT_LEVEL;
	lmap[PROP_TRACE_FLAG.getValue()] = (BACnetPropertyType const *) &PROP_TRACE_FLAG;
	lmap[PROP_TRANSACTION_NOTIFICATION_CLASS.getValue()] = (BACnetPropertyType const *) &PROP_TRANSACTION_NOTIFICATION_CLASS;
	lmap[PROP_USER_EXTERNAL_IDENTIFIER.getValue()] = (BACnetPropertyType const *) &PROP_USER_EXTERNAL_IDENTIFIER;
	lmap[PROP_USER_INFORMATION_REFERENCE.getValue()] = (BACnetPropertyType const *) &PROP_USER_INFORMATION_REFERENCE;
	lmap[PROP_USER_NAME.getValue()] = (BACnetPropertyType const *) &PROP_USER_NAME;
	lmap[PROP_USER_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_USER_TYPE;
	lmap[PROP_USES_REMAINING.getValue()] = (BACnetPropertyType const *) &PROP_USES_REMAINING;
	lmap[PROP_ZONE_FROM.getValue()] = (BACnetPropertyType const *) &PROP_ZONE_FROM;
	lmap[PROP_ZONE_TO.getValue()] = (BACnetPropertyType const *) &PROP_ZONE_TO;
	lmap[PROP_ACCESS_EVENT_TAG.getValue()] = (BACnetPropertyType const *) &PROP_ACCESS_EVENT_TAG;
	lmap[PROP_GLOBAL_IDENTIFIER.getValue()] = (BACnetPropertyType const *) &PROP_GLOBAL_IDENTIFIER;
	lmap[PROP_VERIFICATION_TIME.getValue()] = (BACnetPropertyType const *) &PROP_VERIFICATION_TIME;
	lmap[PROP_BASE_DEVICE_SECURITY_POLICY.getValue()] = (BACnetPropertyType const *) &PROP_BASE_DEVICE_SECURITY_POLICY;
	lmap[PROP_DISTRIBUTION_KEY_REVISION.getValue()] = (BACnetPropertyType const *) &PROP_DISTRIBUTION_KEY_REVISION;
	lmap[PROP_DO_NOT_HIDE.getValue()] = (BACnetPropertyType const *) &PROP_DO_NOT_HIDE;
	lmap[PROP_KEY_SETS.getValue()] = (BACnetPropertyType const *) &PROP_KEY_SETS;
	lmap[PROP_LAST_KEY_SERVER.getValue()] = (BACnetPropertyType const *) &PROP_LAST_KEY_SERVER;
	lmap[PROP_NETWORK_ACCESS_SECURITY_POLICIES.getValue()] = (BACnetPropertyType const *) &PROP_NETWORK_ACCESS_SECURITY_POLICIES;
	lmap[PROP_PACKET_REORDER_TIME.getValue()] = (BACnetPropertyType const *) &PROP_PACKET_REORDER_TIME;
	lmap[PROP_SECURITY_PDU_TIMEOUT.getValue()] = (BACnetPropertyType const *) &PROP_SECURITY_PDU_TIMEOUT;
	lmap[PROP_SECURITY_TIME_WINDOW.getValue()] = (BACnetPropertyType const *) &PROP_SECURITY_TIME_WINDOW;
	lmap[PROP_SUPPORTED_SECURITY_ALGORITHM.getValue()] = (BACnetPropertyType const *) &PROP_SUPPORTED_SECURITY_ALGORITHM;
	lmap[PROP_UPDATE_KEY_SET_TIMEOUT.getValue()] = (BACnetPropertyType const *) &PROP_UPDATE_KEY_SET_TIMEOUT;
	lmap[PROP_BACKUP_AND_RESTORE_STATE.getValue()] = (BACnetPropertyType const *) &PROP_BACKUP_AND_RESTORE_STATE;
	lmap[PROP_BACKUP_PREPARATION_TIME.getValue()] = (BACnetPropertyType const *) &PROP_BACKUP_PREPARATION_TIME;
	lmap[PROP_RESTORE_COMPLETION_TIME.getValue()] = (BACnetPropertyType const *) &PROP_RESTORE_COMPLETION_TIME;
	lmap[PROP_RESTORE_PREPARATION_TIME.getValue()] = (BACnetPropertyType const *) &PROP_RESTORE_PREPARATION_TIME;
	lmap[PROP_BIT_MASK.getValue()] = (BACnetPropertyType const *) &PROP_BIT_MASK;
	lmap[PROP_BIT_TEXT.getValue()] = (BACnetPropertyType const *) &PROP_BIT_TEXT;
	lmap[PROP_IS_UTC.getValue()] = (BACnetPropertyType const *) &PROP_IS_UTC;
	lmap[PROP_GROUP_MEMBERS.getValue()] = (BACnetPropertyType const *) &PROP_GROUP_MEMBERS;
	lmap[PROP_GROUP_MEMBER_NAMES.getValue()] = (BACnetPropertyType const *) &PROP_GROUP_MEMBER_NAMES;
	lmap[PROP_MEMBER_STATUS_FLAGS.getValue()] = (BACnetPropertyType const *) &PROP_MEMBER_STATUS_FLAGS;
	lmap[PROP_REQUESTED_UPDATE_INTERVAL.getValue()] = (BACnetPropertyType const *) &PROP_REQUESTED_UPDATE_INTERVAL;
	lmap[PROP_COVU_PERIOD.getValue()] = (BACnetPropertyType const *) &PROP_COVU_PERIOD;
	lmap[PROP_COVU_RECIPIENTS.getValue()] = (BACnetPropertyType const *) &PROP_COVU_RECIPIENTS;
	lmap[PROP_EVENT_MESSAGE_TEXTS.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_MESSAGE_TEXTS;
	lmap[PROP_EVENT_MESSAGE_TEXTS_CONFIG.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_MESSAGE_TEXTS_CONFIG;
	lmap[PROP_EVENT_DETECTION_ENABLE.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_DETECTION_ENABLE;
	lmap[PROP_EVENT_ALGORITHM_INHIBIT.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_ALGORITHM_INHIBIT;
	lmap[PROP_EVENT_ALGORITHM_INHIBIT_REF.getValue()] = (BACnetPropertyType const *) &PROP_EVENT_ALGORITHM_INHIBIT_REF;
	lmap[PROP_TIME_DELAY_NORMAL.getValue()] = (BACnetPropertyType const *) &PROP_TIME_DELAY_NORMAL;
	lmap[PROP_RELIABILITY_EVALUATION_INHIBIT.getValue()] = (BACnetPropertyType const *) &PROP_RELIABILITY_EVALUATION_INHIBIT;
	lmap[PROP_FAULT_PARAMETERS.getValue()] = (BACnetPropertyType const *) &PROP_FAULT_PARAMETERS;
	lmap[PROP_FAULT_TYPE.getValue()] = (BACnetPropertyType const *) &PROP_FAULT_TYPE;
	lmap[PROP_LOCAL_FORWARDING_ONLY.getValue()] = (BACnetPropertyType const *) &PROP_LOCAL_FORWARDING_ONLY;
	lmap[PROP_PROCESS_IDENTIFIER_FILTER.getValue()] = (BACnetPropertyType const *) &PROP_PROCESS_IDENTIFIER_FILTER;
	lmap[PROP_SUBSCRIBED_RECIPIENTS.getValue()] = (BACnetPropertyType const *) &PROP_SUBSCRIBED_RECIPIENTS;
	lmap[PROP_PORT_FILTER.getValue()] = (BACnetPropertyType const *) &PROP_PORT_FILTER;
	lmap[PROP_AUTHORIZATION_EXEMPTIONS.getValue()] = (BACnetPropertyType const *) &PROP_AUTHORIZATION_EXEMPTIONS;
	lmap[PROP_ALLOW_GROUP_DELAY_INHIBIT.getValue()] = (BACnetPropertyType const *) &PROP_ALLOW_GROUP_DELAY_INHIBIT;
	lmap[PROP_CHANNEL_NUMBER.getValue()] = (BACnetPropertyType const *) &PROP_CHANNEL_NUMBER;
	lmap[PROP_CONTROL_GROUPS.getValue()] = (BACnetPropertyType const *) &PROP_CONTROL_GROUPS;
	lmap[PROP_EXECUTION_DELAY.getValue()] = (BACnetPropertyType const *) &PROP_EXECUTION_DELAY;
	lmap[PROP_LAST_PRIORITY.getValue()] = (BACnetPropertyType const *) &PROP_LAST_PRIORITY;
	lmap[PROP_WRITE_STATUS.getValue()] = (BACnetPropertyType const *) &PROP_WRITE_STATUS;
	lmap[PROP_PROPERTY_LIST.getValue()] = (BACnetPropertyType const *) &PROP_PROPERTY_LIST;
	lmap[PROP_SERIAL_NUMBER.getValue()] = (BACnetPropertyType const *) &PROP_SERIAL_NUMBER;
	lmap[PROP_BLINK_WARN_ENABLE.getValue()] = (BACnetPropertyType const *) &PROP_BLINK_WARN_ENABLE;
	lmap[PROP_DEFAULT_FADE_TIME.getValue()] = (BACnetPropertyType const *) &PROP_DEFAULT_FADE_TIME;
	lmap[PROP_DEFAULT_RAMP_RATE.getValue()] = (BACnetPropertyType const *) &PROP_DEFAULT_RAMP_RATE;
	lmap[PROP_DEFAULT_STEP_INCREMENT.getValue()] = (BACnetPropertyType const *) &PROP_DEFAULT_STEP_INCREMENT;
	lmap[PROP_EGRESS_TIMER.getValue()] = (BACnetPropertyType const *) &PROP_EGRESS_TIMER;
	lmap[PROP_IN_PROGRESS.getValue()] = (BACnetPropertyType const *) &PROP_IN_PROGRESS;
	lmap[PROP_INSTANTANEOUS_POWER.getValue()] = (BACnetPropertyType const *) &PROP_INSTANTANEOUS_POWER;
	lmap[PROP_LIGHTING_COMMAND.getValue()] = (BACnetPropertyType const *) &PROP_LIGHTING_COMMAND;
	lmap[PROP_LIGHTING_COMMAND_DEFAULT_PRIORITY.getValue()] = (BACnetPropertyType const *) &PROP_LIGHTING_COMMAND_DEFAULT_PRIORITY;
	lmap[PROP_MAX_ACTUAL_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_MAX_ACTUAL_VALUE;
	lmap[PROP_MIN_ACTUAL_VALUE.getValue()] = (BACnetPropertyType const *) &PROP_MIN_ACTUAL_VALUE;
	lmap[PROP_POWER.getValue()] = (BACnetPropertyType const *) &PROP_POWER;
	lmap[PROP_TRANSITION.getValue()] = (BACnetPropertyType const *) &PROP_TRANSITION;
	lmap[PROP_EGRESS_ACTIVE.getValue()] = (BACnetPropertyType const *) &PROP_EGRESS_ACTIVE;

	/* The special property identifiers all, optional, and required  */
	/* are reserved for use in the ReadPropertyConditional and */
	/* ReadPropertyMultiple services or services not defined in this standard. */
	/* Enumerated values 0-511 are reserved for definition by ASHRAE.  */
	/* Enumerated values 512-4194303 may be used by others subject to the  */
	/* procedures and constraints described in Clause 23.  */
	/* do the max range inside of enum so that
       compilers will allocate adequate sized datatype for enum
       which is used to store decoding */
	//static BACnetPropertyType const PROP_MAX_BACNET_PROPERTY_ID = 4194303;

	return lmap;
}

BACnetPropertyType const &BACnetEnumPropertyIdentifier::getEnumByValue(uint32_t enumValue) {

	std::map<uint32_t, BACnetPropertyType const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): "
				"BACnetEnumPropertyIdentifier::getEnumByValue(uint32_t enumValue) Property does not exist.\n";
		throw std::invalid_argument(s);
	}
}


