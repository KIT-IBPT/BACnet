/*
 * BACnetEnumBvlcFunction.h
 *
 *  Created on: Sep 7, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMBVLCFUNCTION_H_
#define BACNETAPP_SRC_BACNETENUMBVLCFUNCTION_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_BVLC_FUNCTION 0x0B

class BACnetBvlcFunction : public BACnetEnumSingle {

public:
	BACnetBvlcFunction(unsigned int const enumValue, string const name);
	virtual ~BACnetBvlcFunction();
};

class BACnetEnumBvlcFunction {
private:
	static std::map<uint8_t, BACnetBvlcFunction const *> objectMap;

	static std::map<uint8_t, BACnetBvlcFunction const *> init_map(void);

public:

	static BACnetBvlcFunction const RESULT;
	static BACnetBvlcFunction const WRITE_BROADCAST_DISTRIBUTION_TABLE;
	static BACnetBvlcFunction const READ_BROADCAST_DIST_TABLE;
	static BACnetBvlcFunction const READ_BROADCAST_DIST_TABLE_ACK;
	static BACnetBvlcFunction const FORWARDED_NPDU;
	static BACnetBvlcFunction const REGISTER_FOREIGN_DEVICE;
	static BACnetBvlcFunction const READ_FOREIGN_DEVICE_TABLE;
	static BACnetBvlcFunction const READ_FOREIGN_DEVICE_TABLE_ACK;
	static BACnetBvlcFunction const DELETE_FOREIGN_DEVICE_TABLE_ENTRY;
	static BACnetBvlcFunction const DISTRIBUTE_BROADCAST_TO_NETWORK;
	static BACnetBvlcFunction const ORIGINAL_UNICAST_NPDU;
	static BACnetBvlcFunction const ORIGINAL_BROADCAST_NPDU;

	static BACnetBvlcFunction const &getEnumByValue(uint8_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMBVLCFUNCTION_H_ */
