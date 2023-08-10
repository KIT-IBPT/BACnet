/*
 * BACnetEnumVarFunc.h
 *
 *  Created on: Jun 28, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMVARFUNC_H_
#define BACNETAPP_SRC_BACNETENUMVARFUNC_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_VARFUNC_CHOICE 0x01

class BACnetVarFuncChoice : public BACnetEnumSingle {

public:
	BACnetVarFuncChoice(uint16_t const enumValue, string const name);
	virtual ~BACnetVarFuncChoice();
};

class BACnetEnumVarFunc {
private:
	static std::map<uint16_t, BACnetVarFuncChoice const *> objectMap;

	static std::map<uint16_t, BACnetVarFuncChoice const *> init_map(void);
public:
	static BACnetVarFuncChoice const READ;
	static BACnetVarFuncChoice const WRITE;


	static BACnetVarFuncChoice const &getEnumByValue(uint16_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMVARFUNC_H_ */
