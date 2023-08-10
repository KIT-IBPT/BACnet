/*
 * BACnetEnumMaxApduAccepted.h
 *
 *  Created on: Dec 19, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMMAXAPDUACCEPTED_H_
#define BACNETAPP_SRC_BACNETENUMMAXAPDUACCEPTED_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_APDU_LEN_ACCEPTED 0x05

class BACnetMaxApduLenAccepted : public BACnetEnumSingle {

public:
	BACnetMaxApduLenAccepted(unsigned int const enumValue, string const name);
	virtual ~BACnetMaxApduLenAccepted();
};

class BACnetEnumMaxApduAccepted {

private:
	static std::map<uint8_t, BACnetMaxApduLenAccepted const *> objectMap;

	static std::map<uint8_t, BACnetMaxApduLenAccepted const *> init_map(void);

public:

	static BACnetMaxApduLenAccepted const UP_TO_50_OCTETS;
	static BACnetMaxApduLenAccepted const UP_TO_128_OCTETS;
	static BACnetMaxApduLenAccepted const UP_TO_206_OCTETS;
	static BACnetMaxApduLenAccepted const UP_TO_480_OCTETS;
	static BACnetMaxApduLenAccepted const UP_TO_1024_OCTETS;
	static BACnetMaxApduLenAccepted const UP_TO_1476_OCTETS;

	static BACnetMaxApduLenAccepted const &getEnumByValue(uint8_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMMAXAPDUACCEPTED_H_ */
