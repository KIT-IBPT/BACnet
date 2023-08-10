/*
 * BACnetEnumErrorCode.cpp
 *
 *  Created on: Aug 9, 2018
 *      Author: 8w4
 */

#include "BACnetEnumErrorCode.h"


#include <iostream>
#include <sstream>
#include <stdexcept>


BACnetErrCodeChoice::BACnetErrCodeChoice(uint16_t const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_ERROR_CODE_CHOICE) {
		stringstream ss;

		ss << "\tError: BACnetVarFuncChoice::BACnetVarFuncChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Error-Code Choice is 0-" << MAX_ERROR_CODE_CHOICE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetErrCodeChoice::~BACnetErrCodeChoice() {
	// TODO Auto-generated destructor stub
}

/* valid for all classes */
BACnetErrCodeChoice const BACnetEnumErrorCode::OTHER = BACnetErrCodeChoice(0, "OTHER");

/* Error Class - Device */
BACnetErrCodeChoice const BACnetEnumErrorCode::DEVICE_BUSY = BACnetErrCodeChoice(3, "DEVICE_BUSY");
BACnetErrCodeChoice const BACnetEnumErrorCode::CONFIGURATION_IN_PROGRESS = BACnetErrCodeChoice(2, "CONFIGURATION_IN_PROGRESS");
BACnetErrCodeChoice const BACnetEnumErrorCode::OPERATIONAL_PROBLEM = BACnetErrCodeChoice(25, "OPERATIONAL_PROBLEM");

/* Error Class - Object */
BACnetErrCodeChoice const BACnetEnumErrorCode::DYNAMIC_CREATION_NOT_SUPPORTED = BACnetErrCodeChoice(4, "DYNAMIC_CREATION_NOT_SUPPORTED");
BACnetErrCodeChoice const BACnetEnumErrorCode::NO_OBJECTS_OF_SPECIFIED_TYPE = BACnetErrCodeChoice(17, "NO_OBJECTS_OF_SPECIFIED_TYPE");
BACnetErrCodeChoice const BACnetEnumErrorCode::OBJECT_DELETION_NOT_PERMITTED = BACnetErrCodeChoice(23, "OBJECT_DELETION_NOT_PERMITTED");
BACnetErrCodeChoice const BACnetEnumErrorCode::OBJECT_IDENTIFIER_ALREADY_EXISTS = BACnetErrCodeChoice(24, "OBJECT_IDENTIFIER_ALREADY_EXISTS");
BACnetErrCodeChoice const BACnetEnumErrorCode::READ_ACCESS_DENIED = BACnetErrCodeChoice(27, "READ_ACCESS_DENIED");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_OBJECT = BACnetErrCodeChoice(31, "UNKNOWN_OBJECT");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNSUPPORTED_OBJECT_TYPE = BACnetErrCodeChoice(36, "UNSUPPORTED_OBJECT_TYPE");

/* Error Class - Property */
BACnetErrCodeChoice const BACnetEnumErrorCode::CHARACTER_SET_NOT_SUPPORTED = BACnetErrCodeChoice(41, "CHARACTER_SET_NOT_SUPPORTED");
BACnetErrCodeChoice const BACnetEnumErrorCode::DATATYPE_NOT_SUPPORTED = BACnetErrCodeChoice(47, "DATATYPE_NOT_SUPPORTED");
BACnetErrCodeChoice const BACnetEnumErrorCode::INCONSISTENT_SELECTION_CRITERION = BACnetErrCodeChoice(8, "INCONSISTENT_SELECTION_CRITERION");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_ARRAY_INDEX = BACnetErrCodeChoice(42, "INVALID_ARRAY_INDEX");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_DATA_TYPE = BACnetErrCodeChoice(9, "INVALID_DATA_TYPE");
BACnetErrCodeChoice const BACnetEnumErrorCode::NOT_COV_PROPERTY = BACnetErrCodeChoice(44, "NOT_COV_PROPERTY");
BACnetErrCodeChoice const BACnetEnumErrorCode::OPTIONAL_FUNCTIONALITY_NOT_SUPPORTED = BACnetErrCodeChoice(45, "OPTIONAL_FUNCTIONALITY_NOT_SUPPORTED");
BACnetErrCodeChoice const BACnetEnumErrorCode::PROPERTY_IS_NOT_AN_ARRAY = BACnetErrCodeChoice(50, "PROPERTY_IS_NOT_AN_ARRAY");
/* ERROR_CODE_READ_ACCESS_DENIED = 27, */
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_PROPERTY = BACnetErrCodeChoice(32, "UNKNOWN_PROPERTY");
BACnetErrCodeChoice const BACnetEnumErrorCode::VALUE_OUT_OF_RANGE = BACnetErrCodeChoice(37, "VALUE_OUT_OF_RANGE");
BACnetErrCodeChoice const BACnetEnumErrorCode::WRITE_ACCESS_DENIED = BACnetErrCodeChoice(40, "WRITE_ACCESS_DENIED");

/* Error Class - Resources */
BACnetErrCodeChoice const BACnetEnumErrorCode::NO_SPACE_FOR_OBJECT = BACnetErrCodeChoice(18, "NO_SPACE_FOR_OBJECT");
BACnetErrCodeChoice const BACnetEnumErrorCode::NO_SPACE_TO_ADD_LIST_ELEMENT = BACnetErrCodeChoice(19, "NO_SPACE_TO_ADD_LIST_ELEMENT");
BACnetErrCodeChoice const BACnetEnumErrorCode::NO_SPACE_TO_WRITE_PROPERTY = BACnetErrCodeChoice(20, "NO_SPACE_TO_WRITE_PROPERTY");

/* Error Class - Security */
BACnetErrCodeChoice const BACnetEnumErrorCode::AUTHENTICATION_FAILED = BACnetErrCodeChoice(1, "AUTHENTICATION_FAILED");
/* ERROR_CODE_CHARACTER_SET_NOT_SUPPORTED = 41, */
BACnetErrCodeChoice const BACnetEnumErrorCode::INCOMPATIBLE_SECURITY_LEVELS = BACnetErrCodeChoice(6, "INCOMPATIBLE_SECURITY_LEVELS");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_OPERATOR_NAME = BACnetErrCodeChoice(12, "INVALID_OPERATOR_NAME");
BACnetErrCodeChoice const BACnetEnumErrorCode::KEY_GENERATION_ERROR = BACnetErrCodeChoice(15, "KEY_GENERATION_ERROR");
BACnetErrCodeChoice const BACnetEnumErrorCode::PASSWORD_FAILURE = BACnetErrCodeChoice(26, "PASSWORD_FAILURE");
BACnetErrCodeChoice const BACnetEnumErrorCode::SECURITY_NOT_SUPPORTED = BACnetErrCodeChoice(28, "SECURITY_NOT_SUPPORTED");
BACnetErrCodeChoice const BACnetEnumErrorCode::TIMEOUT = BACnetErrCodeChoice(30, "TIMEOUT");

/* Error Class - Services */
/* ERROR_CODE_CHARACTER_SET_NOT_SUPPORTED = 41, */
BACnetErrCodeChoice const BACnetEnumErrorCode::COV_SUBSCRIPTION_FAILED = BACnetErrCodeChoice(43, "COV_SUBSCRIPTION_FAILED");
BACnetErrCodeChoice const BACnetEnumErrorCode::DUPLICATE_NAME = BACnetErrCodeChoice(48, "DUPLICATE_NAME");
BACnetErrCodeChoice const BACnetEnumErrorCode::DUPLICATE_OBJECT_ID = BACnetErrCodeChoice(49, "DUPLICATE_OBJECT_ID");
BACnetErrCodeChoice const BACnetEnumErrorCode::FILE_ACCESS_DENIED = BACnetErrCodeChoice(5, "FILE_ACCESS_DENIED");
BACnetErrCodeChoice const BACnetEnumErrorCode::INCONSISTENT_PARAMETERS = BACnetErrCodeChoice(7, "INCONSISTENT_PARAMETERS");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_CONFIGURATION_DATA = BACnetErrCodeChoice(46, "INVALID_CONFIGURATION_DATA");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_FILE_ACCESS_METHOD = BACnetErrCodeChoice(10, "INVALID_FILE_ACCESS_METHOD");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_FILE_START_POSITION = BACnetErrCodeChoice(11, "INVALID_FILE_START_POSITION");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_PARAMETER_DATA_TYPE = BACnetErrCodeChoice(13, "INVALID_PARAMETER_DATA_TYPE");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_TIME_STAMP = BACnetErrCodeChoice(14, "INVALID_TIME_STAMP");
BACnetErrCodeChoice const BACnetEnumErrorCode::MISSING_REQUIRED_PARAMETER = BACnetErrCodeChoice(16, "MISSING_REQUIRED_PARAMETER");
/* ERROR_CODE_OPTIONAL_FUNCTIONALITY_NOT_SUPPORTED = 45, */
BACnetErrCodeChoice const BACnetEnumErrorCode::PROPERTY_IS_NOT_A_LIST = BACnetErrCodeChoice(22, "PROPERTY_IS_NOT_A_LIST");
BACnetErrCodeChoice const BACnetEnumErrorCode::SERVICE_REQUEST_DENIED = BACnetErrCodeChoice(29, "SERVICE_REQUEST_DENIED");

/* Error Class - VT */
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_VT_CLASS = BACnetErrCodeChoice(34, "UNKNOWN_VT_CLASS");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_VT_SESSION = BACnetErrCodeChoice(35, "UNKNOWN_VT_SESSION");
BACnetErrCodeChoice const BACnetEnumErrorCode::NO_VT_SESSIONS_AVAILABLE = BACnetErrCodeChoice(21, "NO_VT_SESSIONS_AVAILABLE");
BACnetErrCodeChoice const BACnetEnumErrorCode::VT_SESSION_ALREADY_CLOSED = BACnetErrCodeChoice(38, "VT_SESSION_ALREADY_CLOSED");
BACnetErrCodeChoice const BACnetEnumErrorCode::VT_SESSION_TERMINATION_FAILURE = BACnetErrCodeChoice(39, "VT_SESSION_TERMINATION_FAILURE");

/* unused */
BACnetErrCodeChoice const BACnetEnumErrorCode::RESERVED1 = BACnetErrCodeChoice(33, "RESERVED1");
/* new error codes from new addenda */
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_BUFFER_OVERFLOW = BACnetErrCodeChoice(51, "ABORT_BUFFER_OVERFLOW");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_INVALID_APDU_IN_THIS_STATE = BACnetErrCodeChoice(52, "ABORT_INVALID_APDU_IN_THIS_STATE");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_PREEMPTED_BY_HIGHER_PRIORITY_TASK = BACnetErrCodeChoice(53, "ABORT_PREEMPTED_BY_HIGHER_PRIORITY_TASK");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_SEGMENTATION_NOT_SUPPORTED = BACnetErrCodeChoice(54, "ABORT_SEGMENTATION_NOT_SUPPORTED");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_PROPRIETARY = BACnetErrCodeChoice(55, "ABORT_PROPRIETARY");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_OTHER = BACnetErrCodeChoice(56, "ABORT_OTHER");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_TAG = BACnetErrCodeChoice(57, "INVALID_TAG");
BACnetErrCodeChoice const BACnetEnumErrorCode::NETWORK_DOWN = BACnetErrCodeChoice(58, "NETWORK_DOWN");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_BUFFER_OVERFLOW = BACnetErrCodeChoice(59, "REJECT_BUFFER_OVERFLOW");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_INCONSISTENT_PARAMETERS = BACnetErrCodeChoice(60, "REJECT_INCONSISTENT_PARAMETERS");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_INVALID_PARAMETER_DATA_TYPE = BACnetErrCodeChoice(61, "REJECT_INVALID_PARAMETER_DATA_TYPE");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_INVALID_TAG = BACnetErrCodeChoice(62, "REJECT_INVALID_TAG");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_MISSING_REQUIRED_PARAMETER = BACnetErrCodeChoice(63, "REJECT_MISSING_REQUIRED_PARAMETER");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_PARAMETER_OUT_OF_RANGE = BACnetErrCodeChoice(64, "REJECT_PARAMETER_OUT_OF_RANGE");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_TOO_MANY_ARGUMENTS = BACnetErrCodeChoice(65, "REJECT_TOO_MANY_ARGUMENTS");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_UNDEFINED_ENUMERATION = BACnetErrCodeChoice(66, "REJECT_UNDEFINED_ENUMERATION");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_UNRECOGNIZED_SERVICE = BACnetErrCodeChoice(67, "REJECT_UNRECOGNIZED_SERVICE");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_PROPRIETARY = BACnetErrCodeChoice(68, "REJECT_PROPRIETARY");
BACnetErrCodeChoice const BACnetEnumErrorCode::REJECT_OTHER = BACnetErrCodeChoice(69, "REJECT_OTHER");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_DEVICE = BACnetErrCodeChoice(70, "UNKNOWN_DEVICE");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_ROUTE = BACnetErrCodeChoice(71, "UNKNOWN_ROUTE");
BACnetErrCodeChoice const BACnetEnumErrorCode::VALUE_NOT_INITIALIZED = BACnetErrCodeChoice(72, "VALUE_NOT_INITIALIZED");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_EVENT_STATE = BACnetErrCodeChoice(73, "INVALID_EVENT_STATE");
BACnetErrCodeChoice const BACnetEnumErrorCode::NO_ALARM_CONFIGURED = BACnetErrCodeChoice(74, "NO_ALARM_CONFIGURED");
BACnetErrCodeChoice const BACnetEnumErrorCode::LOG_BUFFER_FULL = BACnetErrCodeChoice(75, "LOG_BUFFER_FULL");
BACnetErrCodeChoice const BACnetEnumErrorCode::LOGGED_VALUE_PURGED = BACnetErrCodeChoice(76, "LOGGED_VALUE_PURGED");
BACnetErrCodeChoice const BACnetEnumErrorCode::NO_PROPERTY_SPECIFIED = BACnetErrCodeChoice(77, "NO_PROPERTY_SPECIFIED");
BACnetErrCodeChoice const BACnetEnumErrorCode::NOT_CONFIGURED_FOR_TRIGGERED_LOGGING = BACnetErrCodeChoice(78, "NOT_CONFIGURED_FOR_TRIGGERED_LOGGING");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_SUBSCRIPTION = BACnetErrCodeChoice(79, "UNKNOWN_SUBSCRIPTION");
BACnetErrCodeChoice const BACnetEnumErrorCode::PARAMETER_OUT_OF_RANGE = BACnetErrCodeChoice(80, "PARAMETER_OUT_OF_RANGE");
BACnetErrCodeChoice const BACnetEnumErrorCode::LIST_ELEMENT_NOT_FOUND = BACnetErrCodeChoice(81, "LIST_ELEMENT_NOT_FOUND");
BACnetErrCodeChoice const BACnetEnumErrorCode::BUSY = BACnetErrCodeChoice(82, "BUSY");
BACnetErrCodeChoice const BACnetEnumErrorCode::COMMUNICATION_DISABLED = BACnetErrCodeChoice(83, "COMMUNICATION_DISABLED");
BACnetErrCodeChoice const BACnetEnumErrorCode::SUCCESS = BACnetErrCodeChoice(84, "SUCCESS");
BACnetErrCodeChoice const BACnetEnumErrorCode::ACCESS_DENIED = BACnetErrCodeChoice(85, "ACCESS_DENIED");
BACnetErrCodeChoice const BACnetEnumErrorCode::BAD_DESTINATION_ADDRESS = BACnetErrCodeChoice(86, "BAD_DESTINATION_ADDRESS");
BACnetErrCodeChoice const BACnetEnumErrorCode::BAD_DESTINATION_DEVICE_ID = BACnetErrCodeChoice(87, "BAD_DESTINATION_DEVICE_ID");
BACnetErrCodeChoice const BACnetEnumErrorCode::BAD_SIGNATURE = BACnetErrCodeChoice(88, "BAD_SIGNATURE");
BACnetErrCodeChoice const BACnetEnumErrorCode::BAD_SOURCE_ADDRESS = BACnetErrCodeChoice(89, "BAD_SOURCE_ADDRESS");
BACnetErrCodeChoice const BACnetEnumErrorCode::BAD_TIMESTAMP = BACnetErrCodeChoice(90, "BAD_TIMESTAMP");
BACnetErrCodeChoice const BACnetEnumErrorCode::CANNOT_USE_KEY = BACnetErrCodeChoice(91, "CANNOT_USE_KEY");
BACnetErrCodeChoice const BACnetEnumErrorCode::CANNOT_VERIFY_MESSAGE_ID = BACnetErrCodeChoice(92, "CANNOT_VERIFY_MESSAGE_ID");
BACnetErrCodeChoice const BACnetEnumErrorCode::CORRECT_KEY_REVISION = BACnetErrCodeChoice(93, "CORRECT_KEY_REVISION");
BACnetErrCodeChoice const BACnetEnumErrorCode::DESTINATION_DEVICE_ID_REQUIRED = BACnetErrCodeChoice(94, "DESTINATION_DEVICE_ID_REQUIRED");
BACnetErrCodeChoice const BACnetEnumErrorCode::DUPLICATE_MESSAGE = BACnetErrCodeChoice(95, "DUPLICATE_MESSAGE");
BACnetErrCodeChoice const BACnetEnumErrorCode::ENCRYPTION_NOT_CONFIGURED = BACnetErrCodeChoice(96, "ENCRYPTION_NOT_CONFIGURED");
BACnetErrCodeChoice const BACnetEnumErrorCode::ENCRYPTION_REQUIRED = BACnetErrCodeChoice(97, "ENCRYPTION_REQUIRED");
BACnetErrCodeChoice const BACnetEnumErrorCode::INCORRECT_KEY = BACnetErrCodeChoice(98, "INCORRECT_KEY");
BACnetErrCodeChoice const BACnetEnumErrorCode::INVALID_KEY_DATA = BACnetErrCodeChoice(99, "INVALID_KEY_DATA");
BACnetErrCodeChoice const BACnetEnumErrorCode::KEY_UPDATE_IN_PROGRESS = BACnetErrCodeChoice(100, "KEY_UPDATE_IN_PROGRESS");
BACnetErrCodeChoice const BACnetEnumErrorCode::MALFORMED_MESSAGE = BACnetErrCodeChoice(101, "MALFORMED_MESSAGE");
BACnetErrCodeChoice const BACnetEnumErrorCode::NOT_KEY_SERVER = BACnetErrCodeChoice(102, "NOT_KEY_SERVER");
BACnetErrCodeChoice const BACnetEnumErrorCode::SECURITY_NOT_CONFIGURED = BACnetErrCodeChoice(103, "SECURITY_NOT_CONFIGURED");
BACnetErrCodeChoice const BACnetEnumErrorCode::SOURCE_SECURITY_REQUIRED = BACnetErrCodeChoice(104, "SOURCE_SECURITY_REQUIRED");
BACnetErrCodeChoice const BACnetEnumErrorCode::TOO_MANY_KEYS = BACnetErrCodeChoice(105, "TOO_MANY_KEYS");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_AUTHENTICATION_TYPE = BACnetErrCodeChoice(106, "UNKNOWN_AUTHENTICATION_TYPE");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_KEY = BACnetErrCodeChoice(107, "UNKNOWN_KEY");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_KEY_REVISION = BACnetErrCodeChoice(108, "UNKNOWN_KEY_REVISION");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_SOURCE_MESSAGE = BACnetErrCodeChoice(109, "UNKNOWN_SOURCE_MESSAGE");
BACnetErrCodeChoice const BACnetEnumErrorCode::NOT_ROUTER_TO_DNET = BACnetErrCodeChoice(110, "NOT_ROUTER_TO_DNET");
BACnetErrCodeChoice const BACnetEnumErrorCode::ROUTER_BUSY = BACnetErrCodeChoice(111, "ROUTER_BUSY");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_NETWORK_MESSAGE = BACnetErrCodeChoice(112, "UNKNOWN_NETWORK_MESSAGE");
BACnetErrCodeChoice const BACnetEnumErrorCode::MESSAGE_TOO_LONG = BACnetErrCodeChoice(113, "MESSAGE_TOO_LONG");
BACnetErrCodeChoice const BACnetEnumErrorCode::SECURITY_ERROR = BACnetErrCodeChoice(114, "SECURITY_ERROR");
BACnetErrCodeChoice const BACnetEnumErrorCode::ADDRESSING_ERROR = BACnetErrCodeChoice(115, "ADDRESSING_ERROR");
BACnetErrCodeChoice const BACnetEnumErrorCode::WRITE_BDT_FAILED = BACnetErrCodeChoice(116, "WRITE_BDT_FAILED");
BACnetErrCodeChoice const BACnetEnumErrorCode::READ_BDT_FAILED = BACnetErrCodeChoice(117, "READ_BDT_FAILED");
BACnetErrCodeChoice const BACnetEnumErrorCode::REGISTER_FOREIGN_DEVICE_FAILED = BACnetErrCodeChoice(118, "REGISTER_FOREIGN_DEVICE_FAILED");
BACnetErrCodeChoice const BACnetEnumErrorCode::READ_FDT_FAILED = BACnetErrCodeChoice(119, "READ_FDT_FAILED");
BACnetErrCodeChoice const BACnetEnumErrorCode::DELETE_FDT_ENTRY_FAILED = BACnetErrCodeChoice(120, "DELETE_FDT_ENTRY_FAILED");
BACnetErrCodeChoice const BACnetEnumErrorCode::DISTRIBUTE_BROADCAST_FAILED = BACnetErrCodeChoice(121, "DISTRIBUTE_BROADCAST_FAILED");
BACnetErrCodeChoice const BACnetEnumErrorCode::UNKNOWN_FILE_SIZE = BACnetErrCodeChoice(122, "UNKNOWN_FILE_SIZE");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_APDU_TOO_LONG = BACnetErrCodeChoice(123, "ABORT_APDU_TOO_LONG");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_APPLICATION_EXCEEDED_REPLY_TIME = BACnetErrCodeChoice(124, "ABORT_APPLICATION_EXCEEDED_REPLY_TIME");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_OUT_OF_RESOURCES = BACnetErrCodeChoice(125, "ABORT_OUT_OF_RESOURCES");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_TSM_TIMEOUT = BACnetErrCodeChoice(126, "ABORT_TSM_TIMEOUT");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_WINDOW_SIZE_OUT_OF_RANGE = BACnetErrCodeChoice(127, "ABORT_WINDOW_SIZE_OUT_OF_RANGE");
BACnetErrCodeChoice const BACnetEnumErrorCode::FILE_FULL = BACnetErrCodeChoice(128, "FILE_FULL");
BACnetErrCodeChoice const BACnetEnumErrorCode::INCONSISTENT_CONFIGURATION = BACnetErrCodeChoice(129, "INCONSISTENT_CONFIGURATION");
BACnetErrCodeChoice const BACnetEnumErrorCode::INCONSISTENT_OBJECT_TYPE = BACnetErrCodeChoice(130, "INCONSISTENT_OBJECT_TYPE");
BACnetErrCodeChoice const BACnetEnumErrorCode::INTERNAL_ERROR = BACnetErrCodeChoice(131, "INTERNAL_ERROR");
BACnetErrCodeChoice const BACnetEnumErrorCode::NOT_CONFIGURED = BACnetErrCodeChoice(132, "NOT_CONFIGURED");
BACnetErrCodeChoice const BACnetEnumErrorCode::OUT_OF_MEMORY = BACnetErrCodeChoice(133, "OUT_OF_MEMORY");
BACnetErrCodeChoice const BACnetEnumErrorCode::VALUE_TOO_LONG = BACnetErrCodeChoice(134, "VALUE_TOO_LONG");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_INSUFFICIENT_SECURITY = BACnetErrCodeChoice(135, "ABORT_INSUFFICIENT_SECURITY");
BACnetErrCodeChoice const BACnetEnumErrorCode::ABORT_SECURITY_ERROR = BACnetErrCodeChoice(136, "ABORT_SECURITY_ERROR");

    /* Enumerated values 0-255 are reserved for definition by ASHRAE. */
    /* Enumerated values 256-65535 may be used by others subject to */
    /* the procedures and constraints described in Clause 23. */
/* do the max range inside of enum so that
   compilers will allocate adequate sized datatype for enum
   which is used to store decoding */



std::map<uint16_t, BACnetErrCodeChoice const *> BACnetEnumErrorCode::objectMap = BACnetEnumErrorCode::init_map();


std::map<uint16_t, BACnetErrCodeChoice const *> BACnetEnumErrorCode::init_map() {

	std::map<uint16_t, BACnetErrCodeChoice const *> lmap;

	/* valid for all classes */
	lmap[OTHER.getValue()] = (BACnetErrCodeChoice const *) &OTHER;

	/* Error Class - Device */
	lmap[DEVICE_BUSY.getValue()] = (BACnetErrCodeChoice const *) &DEVICE_BUSY;
	lmap[CONFIGURATION_IN_PROGRESS.getValue()] = (BACnetErrCodeChoice const *) &CONFIGURATION_IN_PROGRESS;
	lmap[OPERATIONAL_PROBLEM.getValue()] = (BACnetErrCodeChoice const *) &OPERATIONAL_PROBLEM;

	/* Error Class - Object */
	lmap[DYNAMIC_CREATION_NOT_SUPPORTED.getValue()] = (BACnetErrCodeChoice const *) &DYNAMIC_CREATION_NOT_SUPPORTED;
	lmap[NO_OBJECTS_OF_SPECIFIED_TYPE.getValue()] = (BACnetErrCodeChoice const *) &NO_OBJECTS_OF_SPECIFIED_TYPE;
	lmap[OBJECT_DELETION_NOT_PERMITTED.getValue()] = (BACnetErrCodeChoice const *) &OBJECT_DELETION_NOT_PERMITTED;
	lmap[OBJECT_IDENTIFIER_ALREADY_EXISTS.getValue()] = (BACnetErrCodeChoice const *) &OBJECT_IDENTIFIER_ALREADY_EXISTS;
	lmap[READ_ACCESS_DENIED.getValue()] = (BACnetErrCodeChoice const *) &READ_ACCESS_DENIED;
	lmap[UNKNOWN_OBJECT.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_OBJECT;
	lmap[UNSUPPORTED_OBJECT_TYPE.getValue()] = (BACnetErrCodeChoice const *) &UNSUPPORTED_OBJECT_TYPE;

	/* Error Class - Property */
	lmap[CHARACTER_SET_NOT_SUPPORTED.getValue()] = (BACnetErrCodeChoice const *) &CHARACTER_SET_NOT_SUPPORTED;
	lmap[DATATYPE_NOT_SUPPORTED.getValue()] = (BACnetErrCodeChoice const *) &DATATYPE_NOT_SUPPORTED;
	lmap[INCONSISTENT_SELECTION_CRITERION.getValue()] = (BACnetErrCodeChoice const *) &INCONSISTENT_SELECTION_CRITERION;
	lmap[INVALID_ARRAY_INDEX.getValue()] = (BACnetErrCodeChoice const *) &INVALID_ARRAY_INDEX;
	lmap[INVALID_DATA_TYPE.getValue()] = (BACnetErrCodeChoice const *) &INVALID_DATA_TYPE;
	lmap[NOT_COV_PROPERTY.getValue()] = (BACnetErrCodeChoice const *) &NOT_COV_PROPERTY;
	lmap[OPTIONAL_FUNCTIONALITY_NOT_SUPPORTED.getValue()] = (BACnetErrCodeChoice const *) &OPTIONAL_FUNCTIONALITY_NOT_SUPPORTED;
	lmap[PROPERTY_IS_NOT_AN_ARRAY.getValue()] = (BACnetErrCodeChoice const *) &PROPERTY_IS_NOT_AN_ARRAY;
	/* ERROR_CODE_READ_ACCESS_DENIED = 27, */
	lmap[UNKNOWN_PROPERTY.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_PROPERTY;
	lmap[VALUE_OUT_OF_RANGE.getValue()] = (BACnetErrCodeChoice const *) &VALUE_OUT_OF_RANGE;
	lmap[WRITE_ACCESS_DENIED.getValue()] = (BACnetErrCodeChoice const *) &WRITE_ACCESS_DENIED;

	/* Error Class - Resources */
	lmap[NO_SPACE_FOR_OBJECT.getValue()] = (BACnetErrCodeChoice const *) &NO_SPACE_FOR_OBJECT;
	lmap[NO_SPACE_TO_ADD_LIST_ELEMENT.getValue()] = (BACnetErrCodeChoice const *) &NO_SPACE_TO_ADD_LIST_ELEMENT;
	lmap[NO_SPACE_TO_WRITE_PROPERTY.getValue()] = (BACnetErrCodeChoice const *) &NO_SPACE_TO_WRITE_PROPERTY;

	/* Error Class - Security */
	lmap[AUTHENTICATION_FAILED.getValue()] = (BACnetErrCodeChoice const *) &AUTHENTICATION_FAILED;
	/* ERROR_CODE_CHARACTER_SET_NOT_SUPPORTED = 41, */
	lmap[INCOMPATIBLE_SECURITY_LEVELS.getValue()] = (BACnetErrCodeChoice const *) &INCOMPATIBLE_SECURITY_LEVELS;
	lmap[INVALID_OPERATOR_NAME.getValue()] = (BACnetErrCodeChoice const *) &INVALID_OPERATOR_NAME;
	lmap[KEY_GENERATION_ERROR.getValue()] = (BACnetErrCodeChoice const *) &KEY_GENERATION_ERROR;
	lmap[PASSWORD_FAILURE.getValue()] = (BACnetErrCodeChoice const *) &PASSWORD_FAILURE;
	lmap[SECURITY_NOT_SUPPORTED.getValue()] = (BACnetErrCodeChoice const *) &SECURITY_NOT_SUPPORTED;
	lmap[TIMEOUT.getValue()] = (BACnetErrCodeChoice const *) &TIMEOUT;

	/* Error Class - Services */
	/* ERROR_CODE_CHARACTER_SET_NOT_SUPPORTED = 41, */
	lmap[COV_SUBSCRIPTION_FAILED.getValue()] = (BACnetErrCodeChoice const *) &COV_SUBSCRIPTION_FAILED;
	lmap[DUPLICATE_NAME.getValue()] = (BACnetErrCodeChoice const *) &DUPLICATE_NAME;
	lmap[DUPLICATE_OBJECT_ID.getValue()] = (BACnetErrCodeChoice const *) &DUPLICATE_OBJECT_ID;
	lmap[FILE_ACCESS_DENIED.getValue()] = (BACnetErrCodeChoice const *) &FILE_ACCESS_DENIED;
	lmap[INCONSISTENT_PARAMETERS.getValue()] = (BACnetErrCodeChoice const *) &INCONSISTENT_PARAMETERS;
	lmap[INVALID_CONFIGURATION_DATA.getValue()] = (BACnetErrCodeChoice const *) &INVALID_CONFIGURATION_DATA;
	lmap[INVALID_FILE_ACCESS_METHOD.getValue()] = (BACnetErrCodeChoice const *) &INVALID_FILE_ACCESS_METHOD;
	lmap[INVALID_FILE_START_POSITION.getValue()] = (BACnetErrCodeChoice const *) &INVALID_FILE_START_POSITION;
	lmap[INVALID_PARAMETER_DATA_TYPE.getValue()] = (BACnetErrCodeChoice const *) &INVALID_PARAMETER_DATA_TYPE;
	lmap[INVALID_TIME_STAMP.getValue()] = (BACnetErrCodeChoice const *) &INVALID_TIME_STAMP;
	lmap[MISSING_REQUIRED_PARAMETER.getValue()] = (BACnetErrCodeChoice const *) &MISSING_REQUIRED_PARAMETER;
	/* ERROR_CODE_OPTIONAL_FUNCTIONALITY_NOT_SUPPORTED = 45, */
	lmap[PROPERTY_IS_NOT_A_LIST.getValue()] = (BACnetErrCodeChoice const *) &PROPERTY_IS_NOT_A_LIST;
	lmap[SERVICE_REQUEST_DENIED.getValue()] = (BACnetErrCodeChoice const *) &SERVICE_REQUEST_DENIED;

	/* Error Class - VT */
	lmap[UNKNOWN_VT_CLASS.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_VT_CLASS;
	lmap[UNKNOWN_VT_SESSION.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_VT_SESSION;
	lmap[NO_VT_SESSIONS_AVAILABLE.getValue()] = (BACnetErrCodeChoice const *) &NO_VT_SESSIONS_AVAILABLE;
	lmap[VT_SESSION_ALREADY_CLOSED.getValue()] = (BACnetErrCodeChoice const *) &VT_SESSION_ALREADY_CLOSED;
	lmap[VT_SESSION_TERMINATION_FAILURE.getValue()] = (BACnetErrCodeChoice const *) &VT_SESSION_TERMINATION_FAILURE;

	/* unused */
	lmap[RESERVED1.getValue()] = (BACnetErrCodeChoice const *) &RESERVED1;
	/* new error codes from new addenda */
	lmap[ABORT_BUFFER_OVERFLOW.getValue()] = (BACnetErrCodeChoice const *) &ABORT_BUFFER_OVERFLOW;
	lmap[ABORT_INVALID_APDU_IN_THIS_STATE.getValue()] = (BACnetErrCodeChoice const *) &ABORT_INVALID_APDU_IN_THIS_STATE;
	lmap[ABORT_PREEMPTED_BY_HIGHER_PRIORITY_TASK.getValue()] = (BACnetErrCodeChoice const *) &ABORT_PREEMPTED_BY_HIGHER_PRIORITY_TASK;
	lmap[ABORT_SEGMENTATION_NOT_SUPPORTED.getValue()] = (BACnetErrCodeChoice const *) &ABORT_SEGMENTATION_NOT_SUPPORTED;
	lmap[ABORT_PROPRIETARY.getValue()] = (BACnetErrCodeChoice const *) &ABORT_PROPRIETARY;
	lmap[ABORT_OTHER.getValue()] = (BACnetErrCodeChoice const *) &ABORT_OTHER;
	lmap[INVALID_TAG.getValue()] = (BACnetErrCodeChoice const *) &INVALID_TAG;
	lmap[NETWORK_DOWN.getValue()] = (BACnetErrCodeChoice const *) &NETWORK_DOWN;
	lmap[REJECT_BUFFER_OVERFLOW.getValue()] = (BACnetErrCodeChoice const *) &REJECT_BUFFER_OVERFLOW;
	lmap[REJECT_INCONSISTENT_PARAMETERS.getValue()] = (BACnetErrCodeChoice const *) &REJECT_INCONSISTENT_PARAMETERS;
	lmap[REJECT_INVALID_PARAMETER_DATA_TYPE.getValue()] = (BACnetErrCodeChoice const *) &REJECT_INVALID_PARAMETER_DATA_TYPE;
	lmap[REJECT_INVALID_TAG.getValue()] = (BACnetErrCodeChoice const *) &REJECT_INVALID_TAG;
	lmap[REJECT_MISSING_REQUIRED_PARAMETER.getValue()] = (BACnetErrCodeChoice const *) &REJECT_MISSING_REQUIRED_PARAMETER;
	lmap[REJECT_PARAMETER_OUT_OF_RANGE.getValue()] = (BACnetErrCodeChoice const *) &REJECT_PARAMETER_OUT_OF_RANGE;
	lmap[REJECT_TOO_MANY_ARGUMENTS.getValue()] = (BACnetErrCodeChoice const *) &REJECT_TOO_MANY_ARGUMENTS;
	lmap[REJECT_UNDEFINED_ENUMERATION.getValue()] = (BACnetErrCodeChoice const *) &REJECT_UNDEFINED_ENUMERATION;
	lmap[REJECT_UNRECOGNIZED_SERVICE.getValue()] = (BACnetErrCodeChoice const *) &REJECT_UNRECOGNIZED_SERVICE;
	lmap[REJECT_PROPRIETARY.getValue()] = (BACnetErrCodeChoice const *) &REJECT_PROPRIETARY;
	lmap[REJECT_OTHER.getValue()] = (BACnetErrCodeChoice const *) &REJECT_OTHER;
	lmap[UNKNOWN_DEVICE.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_DEVICE;
	lmap[UNKNOWN_ROUTE.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_ROUTE;
	lmap[VALUE_NOT_INITIALIZED.getValue()] = (BACnetErrCodeChoice const *) &VALUE_NOT_INITIALIZED;
	lmap[INVALID_EVENT_STATE.getValue()] = (BACnetErrCodeChoice const *) &INVALID_EVENT_STATE;
	lmap[NO_ALARM_CONFIGURED.getValue()] = (BACnetErrCodeChoice const *) &NO_ALARM_CONFIGURED;
	lmap[LOG_BUFFER_FULL.getValue()] = (BACnetErrCodeChoice const *) &LOG_BUFFER_FULL;
	lmap[LOGGED_VALUE_PURGED.getValue()] = (BACnetErrCodeChoice const *) &LOGGED_VALUE_PURGED;
	lmap[NO_PROPERTY_SPECIFIED.getValue()] = (BACnetErrCodeChoice const *) &NO_PROPERTY_SPECIFIED;
	lmap[NOT_CONFIGURED_FOR_TRIGGERED_LOGGING.getValue()] = (BACnetErrCodeChoice const *) &NOT_CONFIGURED_FOR_TRIGGERED_LOGGING;
	lmap[UNKNOWN_SUBSCRIPTION.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_SUBSCRIPTION;
	lmap[PARAMETER_OUT_OF_RANGE.getValue()] = (BACnetErrCodeChoice const *) &PARAMETER_OUT_OF_RANGE;
	lmap[LIST_ELEMENT_NOT_FOUND.getValue()] = (BACnetErrCodeChoice const *) &LIST_ELEMENT_NOT_FOUND;
	lmap[BUSY.getValue()] = (BACnetErrCodeChoice const *) &BUSY;
	lmap[COMMUNICATION_DISABLED.getValue()] = (BACnetErrCodeChoice const *) &COMMUNICATION_DISABLED;
	lmap[SUCCESS.getValue()] = (BACnetErrCodeChoice const *) &SUCCESS;
	lmap[ACCESS_DENIED.getValue()] = (BACnetErrCodeChoice const *) &ACCESS_DENIED;
	lmap[BAD_DESTINATION_ADDRESS.getValue()] = (BACnetErrCodeChoice const *) &BAD_DESTINATION_ADDRESS;
	lmap[BAD_DESTINATION_DEVICE_ID.getValue()] = (BACnetErrCodeChoice const *) &BAD_DESTINATION_DEVICE_ID;
	lmap[BAD_SIGNATURE.getValue()] = (BACnetErrCodeChoice const *) &BAD_SIGNATURE;
	lmap[BAD_SOURCE_ADDRESS.getValue()] = (BACnetErrCodeChoice const *) &BAD_SOURCE_ADDRESS;
	lmap[BAD_TIMESTAMP.getValue()] = (BACnetErrCodeChoice const *) &BAD_TIMESTAMP;
	lmap[CANNOT_USE_KEY.getValue()] = (BACnetErrCodeChoice const *) &CANNOT_USE_KEY;
	lmap[CANNOT_VERIFY_MESSAGE_ID.getValue()] = (BACnetErrCodeChoice const *) &CANNOT_VERIFY_MESSAGE_ID;
	lmap[CORRECT_KEY_REVISION.getValue()] = (BACnetErrCodeChoice const *) &CORRECT_KEY_REVISION;
	lmap[DESTINATION_DEVICE_ID_REQUIRED.getValue()] = (BACnetErrCodeChoice const *) &DESTINATION_DEVICE_ID_REQUIRED;
	lmap[DUPLICATE_MESSAGE.getValue()] = (BACnetErrCodeChoice const *) &DUPLICATE_MESSAGE;
	lmap[ENCRYPTION_NOT_CONFIGURED.getValue()] = (BACnetErrCodeChoice const *) &ENCRYPTION_NOT_CONFIGURED;
	lmap[ENCRYPTION_REQUIRED.getValue()] = (BACnetErrCodeChoice const *) &ENCRYPTION_REQUIRED;
	lmap[INCORRECT_KEY.getValue()] = (BACnetErrCodeChoice const *) &INCORRECT_KEY;
	lmap[INVALID_KEY_DATA.getValue()] = (BACnetErrCodeChoice const *) &INVALID_KEY_DATA;
	lmap[KEY_UPDATE_IN_PROGRESS.getValue()] = (BACnetErrCodeChoice const *) &KEY_UPDATE_IN_PROGRESS;
	lmap[MALFORMED_MESSAGE.getValue()] = (BACnetErrCodeChoice const *) &MALFORMED_MESSAGE;
	lmap[NOT_KEY_SERVER.getValue()] = (BACnetErrCodeChoice const *) &NOT_KEY_SERVER;
	lmap[SECURITY_NOT_CONFIGURED.getValue()] = (BACnetErrCodeChoice const *) &SECURITY_NOT_CONFIGURED;
	lmap[SOURCE_SECURITY_REQUIRED.getValue()] = (BACnetErrCodeChoice const *) &SOURCE_SECURITY_REQUIRED;
	lmap[TOO_MANY_KEYS.getValue()] = (BACnetErrCodeChoice const *) &TOO_MANY_KEYS;
	lmap[UNKNOWN_AUTHENTICATION_TYPE.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_AUTHENTICATION_TYPE;
	lmap[UNKNOWN_KEY.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_KEY;
	lmap[UNKNOWN_KEY_REVISION.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_KEY_REVISION;
	lmap[UNKNOWN_SOURCE_MESSAGE.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_SOURCE_MESSAGE;
	lmap[NOT_ROUTER_TO_DNET.getValue()] = (BACnetErrCodeChoice const *) &NOT_ROUTER_TO_DNET;
	lmap[ROUTER_BUSY.getValue()] = (BACnetErrCodeChoice const *) &ROUTER_BUSY;
	lmap[UNKNOWN_NETWORK_MESSAGE.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_NETWORK_MESSAGE;
	lmap[MESSAGE_TOO_LONG.getValue()] = (BACnetErrCodeChoice const *) &MESSAGE_TOO_LONG;
	lmap[SECURITY_ERROR.getValue()] = (BACnetErrCodeChoice const *) &SECURITY_ERROR;
	lmap[ADDRESSING_ERROR.getValue()] = (BACnetErrCodeChoice const *) &ADDRESSING_ERROR;
	lmap[WRITE_BDT_FAILED.getValue()] = (BACnetErrCodeChoice const *) &WRITE_BDT_FAILED;
	lmap[READ_BDT_FAILED.getValue()] = (BACnetErrCodeChoice const *) &READ_BDT_FAILED;
	lmap[REGISTER_FOREIGN_DEVICE_FAILED.getValue()] = (BACnetErrCodeChoice const *) &REGISTER_FOREIGN_DEVICE_FAILED;
	lmap[READ_FDT_FAILED.getValue()] = (BACnetErrCodeChoice const *) &READ_FDT_FAILED;
	lmap[DELETE_FDT_ENTRY_FAILED.getValue()] = (BACnetErrCodeChoice const *) &DELETE_FDT_ENTRY_FAILED;
	lmap[DISTRIBUTE_BROADCAST_FAILED.getValue()] = (BACnetErrCodeChoice const *) &DISTRIBUTE_BROADCAST_FAILED;
	lmap[UNKNOWN_FILE_SIZE.getValue()] = (BACnetErrCodeChoice const *) &UNKNOWN_FILE_SIZE;
	lmap[ABORT_APDU_TOO_LONG.getValue()] = (BACnetErrCodeChoice const *) &ABORT_APDU_TOO_LONG;
	lmap[ABORT_APPLICATION_EXCEEDED_REPLY_TIME.getValue()] = (BACnetErrCodeChoice const *) &ABORT_APPLICATION_EXCEEDED_REPLY_TIME;
	lmap[ABORT_OUT_OF_RESOURCES.getValue()] = (BACnetErrCodeChoice const *) &ABORT_OUT_OF_RESOURCES;
	lmap[ABORT_TSM_TIMEOUT.getValue()] = (BACnetErrCodeChoice const *) &ABORT_TSM_TIMEOUT;
	lmap[ABORT_WINDOW_SIZE_OUT_OF_RANGE.getValue()] = (BACnetErrCodeChoice const *) &ABORT_WINDOW_SIZE_OUT_OF_RANGE;
	lmap[FILE_FULL.getValue()] = (BACnetErrCodeChoice const *) &FILE_FULL;
	lmap[INCONSISTENT_CONFIGURATION.getValue()] = (BACnetErrCodeChoice const *) &INCONSISTENT_CONFIGURATION;
	lmap[INCONSISTENT_OBJECT_TYPE.getValue()] = (BACnetErrCodeChoice const *) &INCONSISTENT_OBJECT_TYPE;
	lmap[INTERNAL_ERROR.getValue()] = (BACnetErrCodeChoice const *) &INTERNAL_ERROR;
	lmap[NOT_CONFIGURED.getValue()] = (BACnetErrCodeChoice const *) &NOT_CONFIGURED;
	lmap[OUT_OF_MEMORY.getValue()] = (BACnetErrCodeChoice const *) &OUT_OF_MEMORY;
	lmap[VALUE_TOO_LONG.getValue()] = (BACnetErrCodeChoice const *) &VALUE_TOO_LONG;
	lmap[ABORT_INSUFFICIENT_SECURITY.getValue()] = (BACnetErrCodeChoice const *) &ABORT_INSUFFICIENT_SECURITY;
	lmap[ABORT_SECURITY_ERROR.getValue()] = (BACnetErrCodeChoice const *) &ABORT_SECURITY_ERROR;


	return lmap;
}

BACnetErrCodeChoice const &BACnetEnumErrorCode::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetErrCodeChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumErrorCode::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}



