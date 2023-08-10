/*
 * BACnetEnumMaxSegAccepted.h
 *
 *  Created on: Dec 19, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMMAXSEGACCEPTED_H_
#define BACNETAPP_SRC_BACNETENUMMAXSEGACCEPTED_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_SEGMENT_ACCEPTED 0x07

class BACnetMaxSegmentsAccepted : public BACnetEnumSingle {

public:
	BACnetMaxSegmentsAccepted(unsigned int const enumValue, string const name);
	virtual ~BACnetMaxSegmentsAccepted();
};

class BACnetEnumMaxSegAccepted {
private:
	static std::map<uint8_t, BACnetMaxSegmentsAccepted const *> objectMap;

	static std::map<uint8_t, BACnetMaxSegmentsAccepted const *> init_map(void);

public:

	static BACnetMaxSegmentsAccepted const UNSPECIFIED;
	static BACnetMaxSegmentsAccepted const TWO;
	static BACnetMaxSegmentsAccepted const FOUR;
	static BACnetMaxSegmentsAccepted const EIGHT;
	static BACnetMaxSegmentsAccepted const SIXTEEN;
	static BACnetMaxSegmentsAccepted const THIRTY_TWO;
	static BACnetMaxSegmentsAccepted const SIXTY_FOUR;
	static BACnetMaxSegmentsAccepted const GREATER_THAN_64;

	static BACnetMaxSegmentsAccepted const &getEnumByValue(uint8_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMMAXSEGACCEPTED_H_ */
