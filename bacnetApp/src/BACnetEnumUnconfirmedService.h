/*
 * BACnetEnumUnconfirmedService.h
 *
 *  Created on: Aug 8, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMUNCONFIRMEDSERVICE_H_
#define BACNETAPP_SRC_BACNETENUMUNCONFIRMEDSERVICE_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_UNCONFIRMED_SERVICE 0x0A

class BACnetUnconfirmedServiceChoice : public BACnetEnumSingle {

public:
	BACnetUnconfirmedServiceChoice(unsigned int const enumValue, string const name);
	virtual ~BACnetUnconfirmedServiceChoice();
};

class BACnetEnumUnconfirmedService {
private:

	static std::map<uint8_t, BACnetUnconfirmedServiceChoice const *> objectMap;

	static std::map<uint8_t, BACnetUnconfirmedServiceChoice const *> init_map(void);

public:

	static BACnetUnconfirmedServiceChoice const I_AM;
	static BACnetUnconfirmedServiceChoice const I_HAVE;
	static BACnetUnconfirmedServiceChoice const COV_NOTIFICATION;
	static BACnetUnconfirmedServiceChoice const EVENT_NOTIFICATION;
	static BACnetUnconfirmedServiceChoice const PRIVATE_TRANSFER;
	static BACnetUnconfirmedServiceChoice const TEXT_MESSAGE;
	static BACnetUnconfirmedServiceChoice const TIME_SYNCHRONIZATION;
	static BACnetUnconfirmedServiceChoice const WHO_HAS;
	static BACnetUnconfirmedServiceChoice const WHO_IS;
	static BACnetUnconfirmedServiceChoice const UTC_TIME_SYNCHRONIZATION;
	static BACnetUnconfirmedServiceChoice const WRITE_GROUP;

	static BACnetUnconfirmedServiceChoice const &getEnumByValue(uint8_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMUNCONFIRMEDSERVICE_H_ */
