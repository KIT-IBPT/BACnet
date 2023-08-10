/*
 * BACnetEnumSegmentation.h
 *
 *  Created on: Jun 2, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMSEGMENTATION_H_
#define BACNETAPP_SRC_BACNETENUMSEGMENTATION_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_SEGMENTATION 0x03

class BACnetSegmentation : public BACnetEnumSingle {

public:
	BACnetSegmentation(unsigned int const enumValue, string const name);
	virtual ~BACnetSegmentation();
};

class BACnetEnumSegmentation {
private:
	static std::map<uint16_t, BACnetSegmentation const *> objectMap;

	static std::map<uint16_t, BACnetSegmentation const *> init_map(void);

public:

	static BACnetSegmentation const SEGMENTED_BOTH;
	static BACnetSegmentation const SEGMENTED_TRANSMIT;
	static BACnetSegmentation const SEGMENTED_RECEIVE;
	static BACnetSegmentation const NO_SEGMENTATION;

	static BACnetSegmentation const &getEnumByValue(uint16_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMSEGMENTATION_H_ */
