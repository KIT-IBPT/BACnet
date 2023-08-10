/*
 * BACnetEnumMessagePriority.h
 *
 *  Created on: Aug 10, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMMESSAGEPRIORITY_H_
#define BACNETAPP_SRC_BACNETENUMMESSAGEPRIORITY_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_MESSAGE_PRIORITY 0x03

class BACnetMessagePriority : public BACnetEnumSingle {

public:

	BACnetMessagePriority(unsigned int const enumValue, string const name);
	virtual ~BACnetMessagePriority();
};

class BACnetEnumMessagePriority {
private:
	static std::map<uint8_t, BACnetMessagePriority const *> objectMap;

	static std::map<uint8_t, BACnetMessagePriority const *> init_map(void);

public:

	static BACnetMessagePriority const NORMAL;
	static BACnetMessagePriority const URGENT;
	static BACnetMessagePriority const CRITICAL_EQUIPMENT;
	static BACnetMessagePriority const LIFE_SAFETY;

	static BACnetMessagePriority const &getEnumByValue(uint8_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMMESSAGEPRIORITY_H_ */
