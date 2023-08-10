/*
 * BACnetEnumPropertyIdentifier.h
 *
 *  Created on: Mar 20, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMPROPERTYIDENTIFIER_H_
#define BACNETAPP_SRC_BACNETENUMPROPERTYIDENTIFIER_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_PROPERTY_TYPE 0x3FFFFF

class BACnetPropertyType : public BACnetEnumSingle {

public:
	BACnetPropertyType(unsigned int const enumValue, string const prop_name);
	virtual ~BACnetPropertyType();
};

class BACnetEnumPropertyIdentifier {

private:
	static std::map<uint32_t, BACnetPropertyType const *> objectMap;

	static std::map<uint32_t, BACnetPropertyType const *> init_map(void);

public:
	static BACnetPropertyType const PROP_ACKED_TRANSITIONS;
	static BACnetPropertyType const PROP_ACK_REQUIRED;
	static BACnetPropertyType const PROP_ACTION;
	static BACnetPropertyType const PROP_ACTION_TEXT;
	static BACnetPropertyType const PROP_ACTIVE_TEXT;
	static BACnetPropertyType const PROP_ACTIVE_VT_SESSIONS;
	static BACnetPropertyType const PROP_ALARM_VALUE;
	static BACnetPropertyType const PROP_ALARM_VALUES;
	static BACnetPropertyType const PROP_ALL;
	static BACnetPropertyType const PROP_ALL_WRITES_SUCCESSFUL;
	static BACnetPropertyType const PROP_APDU_SEGMENT_TIMEOUT;
	static BACnetPropertyType const PROP_APDU_TIMEOUT;
	static BACnetPropertyType const PROP_APPLICATION_SOFTWARE_VERSION;
	static BACnetPropertyType const PROP_ARCHIVE;
	static BACnetPropertyType const PROP_BIAS;
	static BACnetPropertyType const PROP_CHANGE_OF_STATE_COUNT;
	static BACnetPropertyType const PROP_CHANGE_OF_STATE_TIME;
	static BACnetPropertyType const PROP_NOTIFICATION_CLASS;
	static BACnetPropertyType const PROP_BLANK_1;
	static BACnetPropertyType const PROP_CONTROLLED_VARIABLE_REFERENCE;
	static BACnetPropertyType const PROP_CONTROLLED_VARIABLE_UNITS;
	static BACnetPropertyType const PROP_CONTROLLED_VARIABLE_VALUE;
	static BACnetPropertyType const PROP_COV_INCREMENT;
	static BACnetPropertyType const PROP_DATE_LIST;
	static BACnetPropertyType const PROP_DAYLIGHT_SAVINGS_STATUS;
	static BACnetPropertyType const PROP_DEADBAND;
	static BACnetPropertyType const PROP_DERIVATIVE_CONSTANT;
	static BACnetPropertyType const PROP_DERIVATIVE_CONSTANT_UNITS;
	static BACnetPropertyType const PROP_DESCRIPTION;
	static BACnetPropertyType const PROP_DESCRIPTION_OF_HALT;
	static BACnetPropertyType const PROP_DEVICE_ADDRESS_BINDING;
	static BACnetPropertyType const PROP_DEVICE_TYPE;
	static BACnetPropertyType const PROP_EFFECTIVE_PERIOD;
	static BACnetPropertyType const PROP_ELAPSED_ACTIVE_TIME;
	static BACnetPropertyType const PROP_ERROR_LIMIT;
	static BACnetPropertyType const PROP_EVENT_ENABLE;
	static BACnetPropertyType const PROP_EVENT_STATE;
	static BACnetPropertyType const PROP_EVENT_TYPE;
	static BACnetPropertyType const PROP_EXCEPTION_SCHEDULE;
	static BACnetPropertyType const PROP_FAULT_VALUES;
	static BACnetPropertyType const PROP_FEEDBACK_VALUE;
	static BACnetPropertyType const PROP_FILE_ACCESS_METHOD;
	static BACnetPropertyType const PROP_FILE_SIZE;
	static BACnetPropertyType const PROP_FILE_TYPE;
	static BACnetPropertyType const PROP_FIRMWARE_REVISION;
	static BACnetPropertyType const PROP_HIGH_LIMIT;
	static BACnetPropertyType const PROP_INACTIVE_TEXT;
	static BACnetPropertyType const PROP_IN_PROCESS;
	static BACnetPropertyType const PROP_INSTANCE_OF;
	static BACnetPropertyType const PROP_INTEGRAL_CONSTANT;
	static BACnetPropertyType const PROP_INTEGRAL_CONSTANT_UNITS;
	static BACnetPropertyType const PROP_ISSUE_CONFIRMED_NOTIFICATIONS;
	static BACnetPropertyType const PROP_LIMIT_ENABLE;
	static BACnetPropertyType const PROP_LIST_OF_GROUP_MEMBERS;
	static BACnetPropertyType const PROP_LIST_OF_OBJECT_PROPERTY_REFERENCES;
	static BACnetPropertyType const PROP_LIST_OF_SESSION_KEYS;
	static BACnetPropertyType const PROP_LOCAL_DATE;
	static BACnetPropertyType const PROP_LOCAL_TIME;
	static BACnetPropertyType const PROP_LOCATION;
	static BACnetPropertyType const PROP_LOW_LIMIT;
	static BACnetPropertyType const PROP_MANIPULATED_VARIABLE_REFERENCE;
	static BACnetPropertyType const PROP_MAXIMUM_OUTPUT;
	static BACnetPropertyType const PROP_MAX_APDU_LENGTH_ACCEPTED;
	static BACnetPropertyType const PROP_MAX_INFO_FRAMES;
	static BACnetPropertyType const PROP_MAX_MASTER;
	static BACnetPropertyType const PROP_MAX_PRES_VALUE;
	static BACnetPropertyType const PROP_MINIMUM_OFF_TIME;
	static BACnetPropertyType const PROP_MINIMUM_ON_TIME;
	static BACnetPropertyType const PROP_MINIMUM_OUTPUT;
	static BACnetPropertyType const PROP_MIN_PRES_VALUE;
	static BACnetPropertyType const PROP_MODEL_NAME;
	static BACnetPropertyType const PROP_MODIFICATION_DATE;
	static BACnetPropertyType const PROP_NOTIFY_TYPE;
	static BACnetPropertyType const PROP_NUMBER_OF_APDU_RETRIES;
	static BACnetPropertyType const PROP_NUMBER_OF_STATES;
	static BACnetPropertyType const PROP_OBJECT_IDENTIFIER;
	static BACnetPropertyType const PROP_OBJECT_LIST;
	static BACnetPropertyType const PROP_OBJECT_NAME;
	static BACnetPropertyType const PROP_OBJECT_PROPERTY_REFERENCE;
	static BACnetPropertyType const PROP_OBJECT_TYPE;
	static BACnetPropertyType const PROP_OPTIONAL;
	static BACnetPropertyType const PROP_OUT_OF_SERVICE;
	static BACnetPropertyType const PROP_OUTPUT_UNITS;
	static BACnetPropertyType const PROP_EVENT_PARAMETERS;
	static BACnetPropertyType const PROP_POLARITY;
	static BACnetPropertyType const PROP_PRESENT_VALUE;
	static BACnetPropertyType const PROP_PRIORITY;
	static BACnetPropertyType const PROP_PRIORITY_ARRAY;
	static BACnetPropertyType const PROP_PRIORITY_FOR_WRITING;
	static BACnetPropertyType const PROP_PROCESS_IDENTIFIER;
	static BACnetPropertyType const PROP_PROGRAM_CHANGE;
	static BACnetPropertyType const PROP_PROGRAM_LOCATION;
	static BACnetPropertyType const PROP_PROGRAM_STATE;
	static BACnetPropertyType const PROP_PROPORTIONAL_CONSTANT;
	static BACnetPropertyType const PROP_PROPORTIONAL_CONSTANT_UNITS;
	static BACnetPropertyType const PROP_PROTOCOL_CONFORMANCE_CLASS;       /* deleted in version 1 revision 2 */
	static BACnetPropertyType const PROP_PROTOCOL_OBJECT_TYPES_SUPPORTED;
	static BACnetPropertyType const PROP_PROTOCOL_SERVICES_SUPPORTED;
	static BACnetPropertyType const PROP_PROTOCOL_VERSION;
	static BACnetPropertyType const PROP_READ_ONLY;
	static BACnetPropertyType const PROP_REASON_FOR_HALT;
	static BACnetPropertyType const PROP_RECIPIENT;
	static BACnetPropertyType const PROP_RECIPIENT_LIST;
	static BACnetPropertyType const PROP_RELIABILITY;
	static BACnetPropertyType const PROP_RELINQUISH_DEFAULT;
	static BACnetPropertyType const PROP_REQUIRED;
	static BACnetPropertyType const PROP_RESOLUTION;
	static BACnetPropertyType const PROP_SEGMENTATION_SUPPORTED;
	static BACnetPropertyType const PROP_SETPOINT;
	static BACnetPropertyType const PROP_SETPOINT_REFERENCE;
	static BACnetPropertyType const PROP_STATE_TEXT;
	static BACnetPropertyType const PROP_STATUS_FLAGS;
	static BACnetPropertyType const PROP_SYSTEM_STATUS;
	static BACnetPropertyType const PROP_TIME_DELAY;
	static BACnetPropertyType const PROP_TIME_OF_ACTIVE_TIME_RESET;
	static BACnetPropertyType const PROP_TIME_OF_STATE_COUNT_RESET;
	static BACnetPropertyType const PROP_TIME_SYNCHRONIZATION_RECIPIENTS;
	static BACnetPropertyType const PROP_UNITS;
	static BACnetPropertyType const PROP_UPDATE_INTERVAL;
	static BACnetPropertyType const PROP_UTC_OFFSET;
	static BACnetPropertyType const PROP_VENDOR_IDENTIFIER;
	static BACnetPropertyType const PROP_VENDOR_NAME;
	static BACnetPropertyType const PROP_VT_CLASSES_SUPPORTED;
	static BACnetPropertyType const PROP_WEEKLY_SCHEDULE;
	static BACnetPropertyType const PROP_ATTEMPTED_SAMPLES;
	static BACnetPropertyType const PROP_AVERAGE_VALUE;
	static BACnetPropertyType const PROP_BUFFER_SIZE;
	static BACnetPropertyType const PROP_CLIENT_COV_INCREMENT;
	static BACnetPropertyType const PROP_COV_RESUBSCRIPTION_INTERVAL;
	static BACnetPropertyType const PROP_CURRENT_NOTIFY_TIME;
	static BACnetPropertyType const PROP_EVENT_TIME_STAMPS;
	static BACnetPropertyType const PROP_LOG_BUFFER;
	static BACnetPropertyType const PROP_LOG_DEVICE_OBJECT_PROPERTY;
    /* The enable property is renamed from log-enable in
       Addendum b to ANSI/ASHRAE 135-2004(135b-2) */
	static BACnetPropertyType const PROP_ENABLE;
	static BACnetPropertyType const PROP_LOG_INTERVAL;
	static BACnetPropertyType const PROP_MAXIMUM_VALUE;
	static BACnetPropertyType const PROP_MINIMUM_VALUE;
	static BACnetPropertyType const PROP_NOTIFICATION_THRESHOLD;
	static BACnetPropertyType const PROP_PREVIOUS_NOTIFY_TIME;
	static BACnetPropertyType const PROP_PROTOCOL_REVISION;
	static BACnetPropertyType const PROP_RECORDS_SINCE_NOTIFICATION;
	static BACnetPropertyType const PROP_RECORD_COUNT;
	static BACnetPropertyType const PROP_START_TIME;
	static BACnetPropertyType const PROP_STOP_TIME;
	static BACnetPropertyType const PROP_STOP_WHEN_FULL;
	static BACnetPropertyType const PROP_TOTAL_RECORD_COUNT;
	static BACnetPropertyType const PROP_VALID_SAMPLES;
	static BACnetPropertyType const PROP_WINDOW_INTERVAL;
	static BACnetPropertyType const PROP_WINDOW_SAMPLES;
	static BACnetPropertyType const PROP_MAXIMUM_VALUE_TIMESTAMP;
	static BACnetPropertyType const PROP_MINIMUM_VALUE_TIMESTAMP;
	static BACnetPropertyType const PROP_VARIANCE_VALUE;
	static BACnetPropertyType const PROP_ACTIVE_COV_SUBSCRIPTIONS;
	static BACnetPropertyType const PROP_BACKUP_FAILURE_TIMEOUT;
	static BACnetPropertyType const PROP_CONFIGURATION_FILES;
	static BACnetPropertyType const PROP_DATABASE_REVISION;
	static BACnetPropertyType const PROP_DIRECT_READING;
	static BACnetPropertyType const PROP_LAST_RESTORE_TIME;
	static BACnetPropertyType const PROP_MAINTENANCE_REQUIRED;
	static BACnetPropertyType const PROP_MEMBER_OF;
	static BACnetPropertyType const PROP_MODE;
	static BACnetPropertyType const PROP_OPERATION_EXPECTED;
	static BACnetPropertyType const PROP_SETTING;
	static BACnetPropertyType const PROP_SILENCED;
	static BACnetPropertyType const PROP_TRACKING_VALUE;
	static BACnetPropertyType const PROP_ZONE_MEMBERS;
	static BACnetPropertyType const PROP_LIFE_SAFETY_ALARM_VALUES;
	static BACnetPropertyType const PROP_MAX_SEGMENTS_ACCEPTED;
	static BACnetPropertyType const PROP_PROFILE_NAME;
	static BACnetPropertyType const PROP_AUTO_SLAVE_DISCOVERY;
	static BACnetPropertyType const PROP_MANUAL_SLAVE_ADDRESS_BINDING;
	static BACnetPropertyType const PROP_SLAVE_ADDRESS_BINDING;
	static BACnetPropertyType const PROP_SLAVE_PROXY_ENABLE;
	static BACnetPropertyType const PROP_LAST_NOTIFY_RECORD;
	static BACnetPropertyType const PROP_SCHEDULE_DEFAULT;
	static BACnetPropertyType const PROP_ACCEPTED_MODES;
	static BACnetPropertyType const PROP_ADJUST_VALUE;
	static BACnetPropertyType const PROP_COUNT;
	static BACnetPropertyType const PROP_COUNT_BEFORE_CHANGE;
	static BACnetPropertyType const PROP_COUNT_CHANGE_TIME;
	static BACnetPropertyType const PROP_COV_PERIOD;
	static BACnetPropertyType const PROP_INPUT_REFERENCE;
	static BACnetPropertyType const PROP_LIMIT_MONITORING_INTERVAL;
	static BACnetPropertyType const PROP_LOGGING_OBJECT;
	static BACnetPropertyType const PROP_LOGGING_RECORD;
	static BACnetPropertyType const PROP_PRESCALE;
	static BACnetPropertyType const PROP_PULSE_RATE;
	static BACnetPropertyType const PROP_SCALE;
	static BACnetPropertyType const PROP_SCALE_FACTOR;
	static BACnetPropertyType const PROP_UPDATE_TIME;
	static BACnetPropertyType const PROP_VALUE_BEFORE_CHANGE;
	static BACnetPropertyType const PROP_VALUE_SET;
	static BACnetPropertyType const PROP_VALUE_CHANGE_TIME;
    /* enumerations 193-206 are new */
	static BACnetPropertyType const PROP_ALIGN_INTERVALS;
    /* enumeration 194 is unassigned */
	static BACnetPropertyType const PROP_INTERVAL_OFFSET;
	static BACnetPropertyType const PROP_LAST_RESTART_REASON;
	static BACnetPropertyType const PROP_LOGGING_TYPE;
    /* enumeration 198-201 is unassigned */
	static BACnetPropertyType const PROP_RESTART_NOTIFICATION_RECIPIENTS;
	static BACnetPropertyType const PROP_TIME_OF_DEVICE_RESTART;
	static BACnetPropertyType const PROP_TIME_SYNCHRONIZATION_INTERVAL;
	static BACnetPropertyType const PROP_TRIGGER;
	static BACnetPropertyType const PROP_UTC_TIME_SYNCHRONIZATION_RECIPIENTS;
    /* enumerations 207-211 are used in Addendum d to ANSI/ASHRAE 135-2004 */
	static BACnetPropertyType const PROP_NODE_SUBTYPE;
	static BACnetPropertyType const PROP_NODE_TYPE;
	static BACnetPropertyType const PROP_STRUCTURED_OBJECT_LIST;
	static BACnetPropertyType const PROP_SUBORDINATE_ANNOTATIONS;
	static BACnetPropertyType const PROP_SUBORDINATE_LIST;
    /* enumerations 212-225 are used in Addendum e to ANSI/ASHRAE 135-2004 */
	static BACnetPropertyType const PROP_ACTUAL_SHED_LEVEL;
	static BACnetPropertyType const PROP_DUTY_WINDOW;
	static BACnetPropertyType const PROP_EXPECTED_SHED_LEVEL;
	static BACnetPropertyType const PROP_FULL_DUTY_BASELINE;
    /* enumerations 216-217 are unassigned */
    /* enumerations 212-225 are used in Addendum e to ANSI/ASHRAE 135-2004 */
	static BACnetPropertyType const PROP_REQUESTED_SHED_LEVEL;
	static BACnetPropertyType const PROP_SHED_DURATION;
	static BACnetPropertyType const PROP_SHED_LEVEL_DESCRIPTIONS;
	static BACnetPropertyType const PROP_SHED_LEVELS;
	static BACnetPropertyType const PROP_STATE_DESCRIPTION;
    /* enumerations 223-225 are unassigned  */
    /* enumerations 226-235 are used in Addendum f to ANSI/ASHRAE 135-2004 */
	static BACnetPropertyType const PROP_DOOR_ALARM_STATE;
	static BACnetPropertyType const PROP_DOOR_EXTENDED_PULSE_TIME;
	static BACnetPropertyType const PROP_DOOR_MEMBERS;
	static BACnetPropertyType const PROP_DOOR_OPEN_TOO_LONG_TIME;
	static BACnetPropertyType const PROP_DOOR_PULSE_TIME;
	static BACnetPropertyType const PROP_DOOR_STATUS;
	static BACnetPropertyType const PROP_DOOR_UNLOCK_DELAY_TIME;
	static BACnetPropertyType const PROP_LOCK_STATUS;
	static BACnetPropertyType const PROP_MASKED_ALARM_VALUES;
	static BACnetPropertyType const PROP_SECURED_STATUS;
    /* enumerations 236-243 are unassigned  */
    /* enumerations 244-311 are used in Addendum j to ANSI/ASHRAE 135-2004 */
	static BACnetPropertyType const PROP_ABSENTEE_LIMIT;
	static BACnetPropertyType const PROP_ACCESS_ALARM_EVENTS;
	static BACnetPropertyType const PROP_ACCESS_DOORS;
	static BACnetPropertyType const PROP_ACCESS_EVENT;
	static BACnetPropertyType const PROP_ACCESS_EVENT_AUTHENTICATION_FACTOR;
	static BACnetPropertyType const PROP_ACCESS_EVENT_CREDENTIAL;
	static BACnetPropertyType const PROP_ACCESS_EVENT_TIME;
	static BACnetPropertyType const PROP_ACCESS_TRANSACTION_EVENTS;
	static BACnetPropertyType const PROP_ACCOMPANIMENT;
	static BACnetPropertyType const PROP_ACCOMPANIMENT_TIME;
	static BACnetPropertyType const PROP_ACTIVATION_TIME;
	static BACnetPropertyType const PROP_ACTIVE_AUTHENTICATION_POLICY;
	static BACnetPropertyType const PROP_ASSIGNED_ACCESS_RIGHTS;
	static BACnetPropertyType const PROP_AUTHENTICATION_FACTORS;
	static BACnetPropertyType const PROP_AUTHENTICATION_POLICY_LIST;
	static BACnetPropertyType const PROP_AUTHENTICATION_POLICY_NAMES;
	static BACnetPropertyType const PROP_AUTHORIZATION_STATUS;
	static BACnetPropertyType const PROP_AUTHORIZATION_MODE;
	static BACnetPropertyType const PROP_BELONGS_TO;
	static BACnetPropertyType const PROP_CREDENTIAL_DISABLE;
	static BACnetPropertyType const PROP_CREDENTIAL_STATUS;
	static BACnetPropertyType const PROP_CREDENTIALS;
	static BACnetPropertyType const PROP_CREDENTIALS_IN_ZONE;
	static BACnetPropertyType const PROP_DAYS_REMAINING;
	static BACnetPropertyType const PROP_ENTRY_POINTS;
	static BACnetPropertyType const PROP_EXIT_POINTS;
	static BACnetPropertyType const PROP_EXPIRY_TIME;
	static BACnetPropertyType const PROP_EXTENDED_TIME_ENABLE;
	static BACnetPropertyType const PROP_FAILED_ATTEMPT_EVENTS;
	static BACnetPropertyType const PROP_FAILED_ATTEMPTS;
	static BACnetPropertyType const PROP_FAILED_ATTEMPTS_TIME;
	static BACnetPropertyType const PROP_LAST_ACCESS_EVENT;
	static BACnetPropertyType const PROP_LAST_ACCESS_POINT;
	static BACnetPropertyType const PROP_LAST_CREDENTIAL_ADDED;
	static BACnetPropertyType const PROP_LAST_CREDENTIAL_ADDED_TIME;
	static BACnetPropertyType const PROP_LAST_CREDENTIAL_REMOVED;
	static BACnetPropertyType const PROP_LAST_CREDENTIAL_REMOVED_TIME;
	static BACnetPropertyType const PROP_LAST_USE_TIME;
	static BACnetPropertyType const PROP_LOCKOUT;
	static BACnetPropertyType const PROP_LOCKOUT_RELINQUISH_TIME;
	static BACnetPropertyType const PROP_MASTER_EXEMPTION;
	static BACnetPropertyType const PROP_MAX_FAILED_ATTEMPTS;
	static BACnetPropertyType const PROP_MEMBERS;
	static BACnetPropertyType const PROP_MUSTER_POINT;
	static BACnetPropertyType const PROP_NEGATIVE_ACCESS_RULES;
	static BACnetPropertyType const PROP_NUMBER_OF_AUTHENTICATION_POLICIES;
	static BACnetPropertyType const PROP_OCCUPANCY_COUNT;
	static BACnetPropertyType const PROP_OCCUPANCY_COUNT_ADJUST;
	static BACnetPropertyType const PROP_OCCUPANCY_COUNT_ENABLE;
	static BACnetPropertyType const PROP_OCCUPANCY_EXEMPTION;
	static BACnetPropertyType const PROP_OCCUPANCY_LOWER_LIMIT;
	static BACnetPropertyType const PROP_OCCUPANCY_LOWER_LIMIT_ENFORCED;
	static BACnetPropertyType const PROP_OCCUPANCY_STATE;
	static BACnetPropertyType const PROP_OCCUPANCY_UPPER_LIMIT;
	static BACnetPropertyType const PROP_OCCUPANCY_UPPER_LIMIT_ENFORCED;
	static BACnetPropertyType const PROP_PASSBACK_EXEMPTION;
	static BACnetPropertyType const PROP_PASSBACK_MODE;
	static BACnetPropertyType const PROP_PASSBACK_TIMEOUT;
	static BACnetPropertyType const PROP_POSITIVE_ACCESS_RULES;
	static BACnetPropertyType const PROP_REASON_FOR_DISABLE;
	static BACnetPropertyType const PROP_SUPPORTED_FORMATS;
	static BACnetPropertyType const PROP_SUPPORTED_FORMAT_CLASSES;
	static BACnetPropertyType const PROP_THREAT_AUTHORITY;
	static BACnetPropertyType const PROP_THREAT_LEVEL;
	static BACnetPropertyType const PROP_TRACE_FLAG;
	static BACnetPropertyType const PROP_TRANSACTION_NOTIFICATION_CLASS;
	static BACnetPropertyType const PROP_USER_EXTERNAL_IDENTIFIER;
	static BACnetPropertyType const PROP_USER_INFORMATION_REFERENCE;
    /* enumerations 312-316 are unassigned */
	static BACnetPropertyType const PROP_USER_NAME;
	static BACnetPropertyType const PROP_USER_TYPE;
	static BACnetPropertyType const PROP_USES_REMAINING;
	static BACnetPropertyType const PROP_ZONE_FROM;
	static BACnetPropertyType const PROP_ZONE_TO;
	static BACnetPropertyType const PROP_ACCESS_EVENT_TAG;
	static BACnetPropertyType const PROP_GLOBAL_IDENTIFIER;
    /* enumerations 324-325 are unassigned */
	static BACnetPropertyType const PROP_VERIFICATION_TIME;
	static BACnetPropertyType const PROP_BASE_DEVICE_SECURITY_POLICY;
	static BACnetPropertyType const PROP_DISTRIBUTION_KEY_REVISION;
	static BACnetPropertyType const PROP_DO_NOT_HIDE;
	static BACnetPropertyType const PROP_KEY_SETS;
	static BACnetPropertyType const PROP_LAST_KEY_SERVER;
	static BACnetPropertyType const PROP_NETWORK_ACCESS_SECURITY_POLICIES;
	static BACnetPropertyType const PROP_PACKET_REORDER_TIME;
	static BACnetPropertyType const PROP_SECURITY_PDU_TIMEOUT;
	static BACnetPropertyType const PROP_SECURITY_TIME_WINDOW;
	static BACnetPropertyType const PROP_SUPPORTED_SECURITY_ALGORITHM;
	static BACnetPropertyType const PROP_UPDATE_KEY_SET_TIMEOUT;
	static BACnetPropertyType const PROP_BACKUP_AND_RESTORE_STATE;
	static BACnetPropertyType const PROP_BACKUP_PREPARATION_TIME;
	static BACnetPropertyType const PROP_RESTORE_COMPLETION_TIME;
	static BACnetPropertyType const PROP_RESTORE_PREPARATION_TIME;
    /* enumerations 342-344 are defined in Addendum 2008-w */
	static BACnetPropertyType const PROP_BIT_MASK;
	static BACnetPropertyType const PROP_BIT_TEXT;
	static BACnetPropertyType const PROP_IS_UTC;
	static BACnetPropertyType const PROP_GROUP_MEMBERS;
	static BACnetPropertyType const PROP_GROUP_MEMBER_NAMES;
	static BACnetPropertyType const PROP_MEMBER_STATUS_FLAGS;
	static BACnetPropertyType const PROP_REQUESTED_UPDATE_INTERVAL;
	static BACnetPropertyType const PROP_COVU_PERIOD;
	static BACnetPropertyType const PROP_COVU_RECIPIENTS;
	static BACnetPropertyType const PROP_EVENT_MESSAGE_TEXTS;
    /* enumerations 352-363 are defined in Addendum 2010-af */
	static BACnetPropertyType const PROP_EVENT_MESSAGE_TEXTS_CONFIG;
	static BACnetPropertyType const PROP_EVENT_DETECTION_ENABLE;
	static BACnetPropertyType const PROP_EVENT_ALGORITHM_INHIBIT;
	static BACnetPropertyType const PROP_EVENT_ALGORITHM_INHIBIT_REF;
	static BACnetPropertyType const PROP_TIME_DELAY_NORMAL;
	static BACnetPropertyType const PROP_RELIABILITY_EVALUATION_INHIBIT;
	static BACnetPropertyType const PROP_FAULT_PARAMETERS;
	static BACnetPropertyType const PROP_FAULT_TYPE;
	static BACnetPropertyType const PROP_LOCAL_FORWARDING_ONLY;
	static BACnetPropertyType const PROP_PROCESS_IDENTIFIER_FILTER;
	static BACnetPropertyType const PROP_SUBSCRIBED_RECIPIENTS;
	static BACnetPropertyType const PROP_PORT_FILTER;
    /* enumeration 364 is defined in Addendum 2010-ae */
	static BACnetPropertyType const PROP_AUTHORIZATION_EXEMPTIONS;
    /* enumerations 365-370 are defined in Addendum 2010-aa */
	static BACnetPropertyType const PROP_ALLOW_GROUP_DELAY_INHIBIT;
	static BACnetPropertyType const PROP_CHANNEL_NUMBER;
	static BACnetPropertyType const PROP_CONTROL_GROUPS;
	static BACnetPropertyType const PROP_EXECUTION_DELAY;
	static BACnetPropertyType const PROP_LAST_PRIORITY;
	static BACnetPropertyType const PROP_WRITE_STATUS;
    /* enumeration 371 is defined in Addendum 2010-ao */
	static BACnetPropertyType const PROP_PROPERTY_LIST;
    /* enumeration 372 is defined in Addendum 2010-ak */
	static BACnetPropertyType const PROP_SERIAL_NUMBER;
    /* enumerations 373-386 are defined in Addendum 2010-i */
	static BACnetPropertyType const PROP_BLINK_WARN_ENABLE;
	static BACnetPropertyType const PROP_DEFAULT_FADE_TIME;
	static BACnetPropertyType const PROP_DEFAULT_RAMP_RATE;
	static BACnetPropertyType const PROP_DEFAULT_STEP_INCREMENT;
	static BACnetPropertyType const PROP_EGRESS_TIMER;
	static BACnetPropertyType const PROP_IN_PROGRESS;
	static BACnetPropertyType const PROP_INSTANTANEOUS_POWER;
	static BACnetPropertyType const PROP_LIGHTING_COMMAND;
	static BACnetPropertyType const PROP_LIGHTING_COMMAND_DEFAULT_PRIORITY;
	static BACnetPropertyType const PROP_MAX_ACTUAL_VALUE;
	static BACnetPropertyType const PROP_MIN_ACTUAL_VALUE;
	static BACnetPropertyType const PROP_POWER;
	static BACnetPropertyType const PROP_TRANSITION;
	static BACnetPropertyType const PROP_EGRESS_ACTIVE;
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

	static BACnetPropertyType const &getEnumByValue(uint32_t enumValue);
};


#endif /* BACNETAPP_SRC_BACNETENUMPROPERTYIDENTIFIER_H_ */
