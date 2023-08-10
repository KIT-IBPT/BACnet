/*
 * BACnetEnumTxRxEr.h
 *
 *  Created on: Sep 24, 2018
 *      Author: 8w4
 */

#ifndef BACNET2017APP_SRC_BACNETENUMTXRXER_H_
#define BACNET2017APP_SRC_BACNETENUMTXRXER_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_TxRxEr_CHOICE 0x02

class BACnetTxRxErChoice : public BACnetEnumSingle {

public:
	BACnetTxRxErChoice(uint16_t const enumValue, string const name);
	virtual ~BACnetTxRxErChoice();
};

class BACnetEnumTxRxEr {
private:
	static std::map<uint16_t, BACnetTxRxErChoice const *> objectMap;

	static std::map<uint16_t, BACnetTxRxErChoice const *> init_map(void);
public:
	static BACnetTxRxErChoice const TX;
	static BACnetTxRxErChoice const RX;
	static BACnetTxRxErChoice const ER;

	static BACnetTxRxErChoice const &getEnumByValue(uint16_t enumValue);
	static BACnetTxRxErChoice const &getEnumByName(const string &nameStr);
};

#endif /* BACNET2017APP_SRC_BACNETENUMTXRXER_H_ */
