/*
 * BACnetEnumErrorCode.h
 *
 *  Created on: Aug 9, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMERRORCODE_H_
#define BACNETAPP_SRC_BACNETENUMERRORCODE_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_ERROR_CODE_CHOICE 0x88 //136 in decimal

class BACnetErrCodeChoice : public BACnetEnumSingle {

public:
	BACnetErrCodeChoice(uint16_t const enumValue, string const name);
	virtual ~BACnetErrCodeChoice();
};

class BACnetEnumErrorCode {
private:
	static std::map<uint16_t, BACnetErrCodeChoice const *> objectMap;

	static std::map<uint16_t, BACnetErrCodeChoice const *> init_map(void);
public:

	/* valid for all classes */
	static BACnetErrCodeChoice const OTHER;

	/* Error Class - Device */
	static BACnetErrCodeChoice const DEVICE_BUSY;
	static BACnetErrCodeChoice const CONFIGURATION_IN_PROGRESS;
	static BACnetErrCodeChoice const OPERATIONAL_PROBLEM;

	/* Error Class - Object */
	static BACnetErrCodeChoice const DYNAMIC_CREATION_NOT_SUPPORTED;
	static BACnetErrCodeChoice const NO_OBJECTS_OF_SPECIFIED_TYPE;
	static BACnetErrCodeChoice const OBJECT_DELETION_NOT_PERMITTED;
	static BACnetErrCodeChoice const OBJECT_IDENTIFIER_ALREADY_EXISTS;
	static BACnetErrCodeChoice const READ_ACCESS_DENIED;
	static BACnetErrCodeChoice const UNKNOWN_OBJECT;
	static BACnetErrCodeChoice const UNSUPPORTED_OBJECT_TYPE;

	/* Error Class - Property */
	static BACnetErrCodeChoice const CHARACTER_SET_NOT_SUPPORTED;
	static BACnetErrCodeChoice const DATATYPE_NOT_SUPPORTED;
	static BACnetErrCodeChoice const INCONSISTENT_SELECTION_CRITERION;
	static BACnetErrCodeChoice const INVALID_ARRAY_INDEX;
	static BACnetErrCodeChoice const INVALID_DATA_TYPE;
	static BACnetErrCodeChoice const NOT_COV_PROPERTY;
	static BACnetErrCodeChoice const OPTIONAL_FUNCTIONALITY_NOT_SUPPORTED;
	static BACnetErrCodeChoice const PROPERTY_IS_NOT_AN_ARRAY;
	/* ERROR_CODE_READ_ACCESS_DENIED; */
	static BACnetErrCodeChoice const UNKNOWN_PROPERTY;
	static BACnetErrCodeChoice const VALUE_OUT_OF_RANGE;
	static BACnetErrCodeChoice const WRITE_ACCESS_DENIED;

	/* Error Class - Resources */
	static BACnetErrCodeChoice const NO_SPACE_FOR_OBJECT;
	static BACnetErrCodeChoice const NO_SPACE_TO_ADD_LIST_ELEMENT;
	static BACnetErrCodeChoice const NO_SPACE_TO_WRITE_PROPERTY;

	/* Error Class - Security */
	static BACnetErrCodeChoice const AUTHENTICATION_FAILED;
	/* ERROR_CODE_CHARACTER_SET_NOT_SUPPORTED; */
	static BACnetErrCodeChoice const INCOMPATIBLE_SECURITY_LEVELS;
	static BACnetErrCodeChoice const INVALID_OPERATOR_NAME;
	static BACnetErrCodeChoice const KEY_GENERATION_ERROR;
	static BACnetErrCodeChoice const PASSWORD_FAILURE;
	static BACnetErrCodeChoice const SECURITY_NOT_SUPPORTED;
	static BACnetErrCodeChoice const TIMEOUT;

	/* Error Class - Services */
	/* ERROR_CODE_CHARACTER_SET_NOT_SUPPORTED; */
	static BACnetErrCodeChoice const COV_SUBSCRIPTION_FAILED;
	static BACnetErrCodeChoice const DUPLICATE_NAME;
	static BACnetErrCodeChoice const DUPLICATE_OBJECT_ID;
	static BACnetErrCodeChoice const FILE_ACCESS_DENIED;
	static BACnetErrCodeChoice const INCONSISTENT_PARAMETERS;
	static BACnetErrCodeChoice const INVALID_CONFIGURATION_DATA;
	static BACnetErrCodeChoice const INVALID_FILE_ACCESS_METHOD;
	static BACnetErrCodeChoice const INVALID_FILE_START_POSITION;
	static BACnetErrCodeChoice const INVALID_PARAMETER_DATA_TYPE;
	static BACnetErrCodeChoice const INVALID_TIME_STAMP;
	static BACnetErrCodeChoice const MISSING_REQUIRED_PARAMETER;
	/* ERROR_CODE_OPTIONAL_FUNCTIONALITY_NOT_SUPPORTED; */
	static BACnetErrCodeChoice const PROPERTY_IS_NOT_A_LIST;
	static BACnetErrCodeChoice const SERVICE_REQUEST_DENIED;

	/* Error Class - VT */
	static BACnetErrCodeChoice const UNKNOWN_VT_CLASS;
	static BACnetErrCodeChoice const UNKNOWN_VT_SESSION;
	static BACnetErrCodeChoice const NO_VT_SESSIONS_AVAILABLE;
	static BACnetErrCodeChoice const VT_SESSION_ALREADY_CLOSED;
	static BACnetErrCodeChoice const VT_SESSION_TERMINATION_FAILURE;

	/* unused */
	static BACnetErrCodeChoice const RESERVED1;
	/* new error codes from new addenda */
	static BACnetErrCodeChoice const ABORT_BUFFER_OVERFLOW;
	static BACnetErrCodeChoice const ABORT_INVALID_APDU_IN_THIS_STATE;
	static BACnetErrCodeChoice const ABORT_PREEMPTED_BY_HIGHER_PRIORITY_TASK;
	static BACnetErrCodeChoice const ABORT_SEGMENTATION_NOT_SUPPORTED;
	static BACnetErrCodeChoice const ABORT_PROPRIETARY;
	static BACnetErrCodeChoice const ABORT_OTHER;
	static BACnetErrCodeChoice const INVALID_TAG;
	static BACnetErrCodeChoice const NETWORK_DOWN;
	static BACnetErrCodeChoice const REJECT_BUFFER_OVERFLOW;
	static BACnetErrCodeChoice const REJECT_INCONSISTENT_PARAMETERS;
	static BACnetErrCodeChoice const REJECT_INVALID_PARAMETER_DATA_TYPE;
	static BACnetErrCodeChoice const REJECT_INVALID_TAG;
	static BACnetErrCodeChoice const REJECT_MISSING_REQUIRED_PARAMETER;
	static BACnetErrCodeChoice const REJECT_PARAMETER_OUT_OF_RANGE;
	static BACnetErrCodeChoice const REJECT_TOO_MANY_ARGUMENTS;
	static BACnetErrCodeChoice const REJECT_UNDEFINED_ENUMERATION;
	static BACnetErrCodeChoice const REJECT_UNRECOGNIZED_SERVICE;
	static BACnetErrCodeChoice const REJECT_PROPRIETARY;
	static BACnetErrCodeChoice const REJECT_OTHER;
	static BACnetErrCodeChoice const UNKNOWN_DEVICE;
	static BACnetErrCodeChoice const UNKNOWN_ROUTE;
	static BACnetErrCodeChoice const VALUE_NOT_INITIALIZED;
	static BACnetErrCodeChoice const INVALID_EVENT_STATE;
	static BACnetErrCodeChoice const NO_ALARM_CONFIGURED;
	static BACnetErrCodeChoice const LOG_BUFFER_FULL;
	static BACnetErrCodeChoice const LOGGED_VALUE_PURGED;
	static BACnetErrCodeChoice const NO_PROPERTY_SPECIFIED;
	static BACnetErrCodeChoice const NOT_CONFIGURED_FOR_TRIGGERED_LOGGING;
	static BACnetErrCodeChoice const UNKNOWN_SUBSCRIPTION;
	static BACnetErrCodeChoice const PARAMETER_OUT_OF_RANGE;
	static BACnetErrCodeChoice const LIST_ELEMENT_NOT_FOUND;
	static BACnetErrCodeChoice const BUSY;
	static BACnetErrCodeChoice const COMMUNICATION_DISABLED;
	static BACnetErrCodeChoice const SUCCESS;
	static BACnetErrCodeChoice const ACCESS_DENIED;
	static BACnetErrCodeChoice const BAD_DESTINATION_ADDRESS;
	static BACnetErrCodeChoice const BAD_DESTINATION_DEVICE_ID;
	static BACnetErrCodeChoice const BAD_SIGNATURE;
	static BACnetErrCodeChoice const BAD_SOURCE_ADDRESS;
	static BACnetErrCodeChoice const BAD_TIMESTAMP;
	static BACnetErrCodeChoice const CANNOT_USE_KEY;
	static BACnetErrCodeChoice const CANNOT_VERIFY_MESSAGE_ID;
	static BACnetErrCodeChoice const CORRECT_KEY_REVISION;
	static BACnetErrCodeChoice const DESTINATION_DEVICE_ID_REQUIRED;
	static BACnetErrCodeChoice const DUPLICATE_MESSAGE;
	static BACnetErrCodeChoice const ENCRYPTION_NOT_CONFIGURED;
	static BACnetErrCodeChoice const ENCRYPTION_REQUIRED;
	static BACnetErrCodeChoice const INCORRECT_KEY;
	static BACnetErrCodeChoice const INVALID_KEY_DATA;
	static BACnetErrCodeChoice const KEY_UPDATE_IN_PROGRESS;
	static BACnetErrCodeChoice const MALFORMED_MESSAGE;
	static BACnetErrCodeChoice const NOT_KEY_SERVER;
	static BACnetErrCodeChoice const SECURITY_NOT_CONFIGURED;
	static BACnetErrCodeChoice const SOURCE_SECURITY_REQUIRED;
	static BACnetErrCodeChoice const TOO_MANY_KEYS;
	static BACnetErrCodeChoice const UNKNOWN_AUTHENTICATION_TYPE;
	static BACnetErrCodeChoice const UNKNOWN_KEY;
	static BACnetErrCodeChoice const UNKNOWN_KEY_REVISION;
	static BACnetErrCodeChoice const UNKNOWN_SOURCE_MESSAGE;
	static BACnetErrCodeChoice const NOT_ROUTER_TO_DNET;
	static BACnetErrCodeChoice const ROUTER_BUSY;
	static BACnetErrCodeChoice const UNKNOWN_NETWORK_MESSAGE;
	static BACnetErrCodeChoice const MESSAGE_TOO_LONG;
	static BACnetErrCodeChoice const SECURITY_ERROR;
	static BACnetErrCodeChoice const ADDRESSING_ERROR;
	static BACnetErrCodeChoice const WRITE_BDT_FAILED;
	static BACnetErrCodeChoice const READ_BDT_FAILED;
	static BACnetErrCodeChoice const REGISTER_FOREIGN_DEVICE_FAILED;
	static BACnetErrCodeChoice const READ_FDT_FAILED;
	static BACnetErrCodeChoice const DELETE_FDT_ENTRY_FAILED;
	static BACnetErrCodeChoice const DISTRIBUTE_BROADCAST_FAILED;
	static BACnetErrCodeChoice const UNKNOWN_FILE_SIZE;
	static BACnetErrCodeChoice const ABORT_APDU_TOO_LONG;
	static BACnetErrCodeChoice const ABORT_APPLICATION_EXCEEDED_REPLY_TIME;
	static BACnetErrCodeChoice const ABORT_OUT_OF_RESOURCES;
	static BACnetErrCodeChoice const ABORT_TSM_TIMEOUT;
	static BACnetErrCodeChoice const ABORT_WINDOW_SIZE_OUT_OF_RANGE;
	static BACnetErrCodeChoice const FILE_FULL;
	static BACnetErrCodeChoice const INCONSISTENT_CONFIGURATION;
	static BACnetErrCodeChoice const INCONSISTENT_OBJECT_TYPE;
	static BACnetErrCodeChoice const INTERNAL_ERROR;
	static BACnetErrCodeChoice const NOT_CONFIGURED;
	static BACnetErrCodeChoice const OUT_OF_MEMORY;
	static BACnetErrCodeChoice const VALUE_TOO_LONG;
	static BACnetErrCodeChoice const ABORT_INSUFFICIENT_SECURITY;
	static BACnetErrCodeChoice const ABORT_SECURITY_ERROR;

	//TODO: Handle these these types...
	/* Enumerated values 0-255 are reserved for definition by ASHRAE. */
	/* Enumerated values 256-65535 may be used by others subject to */
	/* the procedures and constraints described in Clause 23. */
	/* do the max range inside of enum so that
       compilers will allocate adequate sized datatype for enum
       which is used to store decoding */

	static BACnetErrCodeChoice const &getEnumByValue(uint16_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMERRORCODE_H_ */
