/*
 * BACnetEnumSvcSupChoice.h
 *
 *  Created on: Jun 15, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMSVCSUPCHOICE_H_
#define BACNETAPP_SRC_BACNETENUMSVCSUPCHOICE_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_PROTO_SVC_SUP_CHOICE 0x28

class BACnetSvcSupChoice : public BACnetEnumSingle {
public:
	BACnetSvcSupChoice(unsigned int const enumValue, string const name);
	virtual ~BACnetSvcSupChoice();
};

class BACnetEnumSvcSupChoice {

private:
	static std::map<uint16_t, BACnetSvcSupChoice const *> objectMap;

	static std::map<uint16_t, BACnetSvcSupChoice const *> init_map(void);

public:

	static BACnetSvcSupChoice const SERVICE_SUPPORTED_ACKNOWLEDGE_ALARM;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_CONFIRMED_COV_NOTIFICATION;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_CONFIRMED_EVENT_NOTIFICATION;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_GET_ALARM_SUMMARY;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_GET_ENROLLMENT_SUMMARY;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_GET_EVENT_INFORMATION;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_SUBSCRIBE_COV;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_SUBSCRIBE_COV_PROPERTY;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_LIFE_SAFETY_OPERATION;
    /* File Access Services */
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_ATOMIC_READ_FILE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_ATOMIC_WRITE_FILE;
    /* Object Access Services */
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_ADD_LIST_ELEMENT;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_REMOVE_LIST_ELEMENT;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_CREATE_OBJECT;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_DELETE_OBJECT;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_READ_PROPERTY;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_READ_PROP_CONDITIONAL;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_READ_PROP_MULTIPLE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_READ_RANGE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_WRITE_PROPERTY;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_WRITE_PROP_MULTIPLE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_WRITE_GROUP;
    /* Remote Device Management Services */
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_DEVICE_COMMUNICATION_CONTROL;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_PRIVATE_TRANSFER;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_TEXT_MESSAGE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_REINITIALIZE_DEVICE;
    /* Virtual Terminal Services */
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_VT_OPEN;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_VT_CLOSE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_VT_DATA;
    /* Security Services */
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_AUTHENTICATE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_REQUEST_KEY;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_I_AM;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_I_HAVE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_UNCONFIRMED_COV_NOTIFICATION;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_UNCONFIRMED_EVENT_NOTIFICATION;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_UNCONFIRMED_PRIVATE_TRANSFER;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_UNCONFIRMED_TEXT_MESSAGE;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_TIME_SYNCHRONIZATION;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_UTC_TIME_SYNCHRONIZATION;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_WHO_HAS;
	static BACnetSvcSupChoice const SERVICE_SUPPORTED_WHO_IS;
        /* Other services to be added as they are defined. */
        /* All values in this production are reserved */
        /* for definition by ASHRAE. */

	static BACnetSvcSupChoice const &getEnumByValue(uint16_t enumValue);

	typedef std::map<uint16_t, BACnetSvcSupChoice const *>::const_iterator iterator;
	static iterator getBegin(void);
	static iterator getEnd(void);
};

#endif /* BACNETAPP_SRC_BACNETENUMSVCSUPCHOICE_H_ */
