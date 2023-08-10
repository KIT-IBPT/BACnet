/*
 * BACnetEnumConfSvc.h
 *
 *  Created on: Dec 20, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMCONFSVC_H_
#define BACNETAPP_SRC_BACNETENUMCONFSVC_H_

#include <string>
#include <list>
#include <map>

#include "BACnetConfSvcChoice.h"

using namespace std;

class BACnetEnumConfSvc {
private:

	static std::map<uint16_t, BACnetConfSvcChoice const *> objectMap;

	static std::map<uint16_t, BACnetConfSvcChoice const *> init_map(void);

public:

	static BACnetConfSvcChoice const ACKNOWLEDGE_ALARM;				// (0)
	static BACnetConfSvcChoice const COV_NOTIFICATION;				// (1)
	static BACnetConfSvcChoice const EVENT_NOTIFICATION;			// (2)
	static BACnetConfSvcChoice const GET_ALARM_SUMMARY;				// (3)
	static BACnetConfSvcChoice const GET_ENROLLMENT_SUMMARY;		// (4)
	static BACnetConfSvcChoice const SUBSCRIBE_COV;					// (5)
	static BACnetConfSvcChoice const ATOMIC_READ_FILE;				// (6)
	static BACnetConfSvcChoice const ATOMIC_WRITE_FILE;				// (7)
	static BACnetConfSvcChoice const ADD_LIST_ELEMENT;				// (8)
	static BACnetConfSvcChoice const REMOVE_LIST_ELEMENT;			// (9)
	static BACnetConfSvcChoice const CREATE_OBJECT;					// (10)
	static BACnetConfSvcChoice const DELETE_OBJECT;					// (11)
	static BACnetConfSvcChoice const READ_PROPERTY;					// (12)
	static BACnetConfSvcChoice const READ_PROP_CONDITIONAL;			// (13)
	static BACnetConfSvcChoice const READ_PROP_MULTIPLE;			// (14)
	static BACnetConfSvcChoice const WRITE_PROPERTY;				// (15)
	static BACnetConfSvcChoice const WRITE_PROP_MULTIPLE;			// (16)
	static BACnetConfSvcChoice const DEVICE_COMMUNICATION_CONTROL;	// (17)
	static BACnetConfSvcChoice const PRIVATE_TRANSFER;				// (18)
	static BACnetConfSvcChoice const TEXT_MESSAGE;					// (19)
	static BACnetConfSvcChoice const REINITIALIZE_DEVICE;			// (20)
	static BACnetConfSvcChoice const VT_OPEN;						// (21)
	static BACnetConfSvcChoice const VT_CLOSE;						// (22)
	static BACnetConfSvcChoice const VT_DATA;						// (23)
	static BACnetConfSvcChoice const AUTHENTICATE;					// (24)
	static BACnetConfSvcChoice const REQUEST_KEY;					// (25)
	static BACnetConfSvcChoice const READ_RANGE;					// (26)
	static BACnetConfSvcChoice const LIFE_SAFETY_OPERATION;			// (27)
	static BACnetConfSvcChoice const SUBSCRIBE_COV_PROPERTY;		// (28)
	static BACnetConfSvcChoice const GET_EVENT_INFORMATION;			// (29)

	static BACnetConfSvcChoice const &getEnumByValue(uint16_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMCONFSVC_H_ */
