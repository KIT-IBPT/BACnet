/*
 * BACnetEnumTagChoice.h
 *
 *  Created on: Dec 19, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMTAGCHOICE_H_
#define BACNETAPP_SRC_BACNETENUMTAGCHOICE_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_TAG_CHOICE 0x01

class BACnetTagClassChoice : public BACnetEnumSingle {

public:
	BACnetTagClassChoice(unsigned int const enumValue, string const name);
	virtual ~BACnetTagClassChoice();
};

class BACnetEnumTagChoice {

private:
	static std::map<uint16_t, BACnetTagClassChoice const *> objectMap;

	static std::map<uint16_t, BACnetTagClassChoice const *> init_map(void);

public:

	static BACnetTagClassChoice const APPLICATION_TAG;
	static BACnetTagClassChoice const CONTEXT_SPECIFIC_TAG;

	static BACnetTagClassChoice const &getEnumByValue(uint16_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMTAGCHOICE_H_ */
