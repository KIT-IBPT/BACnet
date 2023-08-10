/*
 * BACnetEnumErrorClass.h
 *
 *  Created on: Aug 9, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMERRORCLASS_H_
#define BACNETAPP_SRC_BACNETENUMERRORCLASS_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_ERROR_CLASS_CHOICE 0x07

class BACnetErrClassChoice : public BACnetEnumSingle {

public:
	BACnetErrClassChoice(uint16_t const enumValue, string const name);
	virtual ~BACnetErrClassChoice();
};

class BACnetEnumErrorClass {
private:
	static std::map<uint16_t, BACnetErrClassChoice const *> objectMap;

	static std::map<uint16_t, BACnetErrClassChoice const *> init_map(void);
public:

	static BACnetErrClassChoice const DEVICE;
	static BACnetErrClassChoice const OBJECT;
	static BACnetErrClassChoice const PROPERTY;
	static BACnetErrClassChoice const RESOURCES;
	static BACnetErrClassChoice const SECURITY;
	static BACnetErrClassChoice const SERVICES;
	static BACnetErrClassChoice const VT;
	static BACnetErrClassChoice const COMMUNICATION;

	static BACnetErrClassChoice const &getEnumByValue(uint16_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMERRORCLASS_H_ */
