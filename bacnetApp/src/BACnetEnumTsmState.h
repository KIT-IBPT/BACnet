/*
 * BACnetEnumTsmState.h
 *
 *  Created on: May 24, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMTSMSTATE_H_
#define BACNETAPP_SRC_BACNETENUMTSMSTATE_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_TSM_STATE 0x05

class BACnetTsmState : public BACnetEnumSingle {
public:
	BACnetTsmState(unsigned int const enumValue, string const name);
	virtual ~BACnetTsmState();
};

class BACnetEnumTsmState {
private:
	static std::map<uint8_t, BACnetTsmState const *> objectMap;

	static std::map<uint8_t, BACnetTsmState const *> init_map(void);

public:

	static BACnetTsmState const IDLE;
	static BACnetTsmState const AWAIT_CONFIRMATION;
	static BACnetTsmState const AWAIT_RESPONSE;
	static BACnetTsmState const SEGMENTED_REQUEST;
	static BACnetTsmState const SEGMENTED_CONFIRMATION;
	static BACnetTsmState const AWAIT_IAM;

	static BACnetTsmState const &getEnumByValue(uint8_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMTSMSTATE_H_ */
