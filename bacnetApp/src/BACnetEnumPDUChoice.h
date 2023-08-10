/*
 * BACnetEnumPDUChoice.h
 *
 *  Created on: Aug 8, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMPDUCHOICE_H_
#define BACNETAPP_SRC_BACNETENUMPDUCHOICE_H_

#include <string>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_PDU_CHOICE 0x07

class BACnetPDUChoice : public BACnetEnumSingle {

public:
	BACnetPDUChoice(unsigned int const enumValue, string const name);
	virtual ~BACnetPDUChoice();
};

class BACnetEnumPDUChoice {
private:
	static std::map<uint8_t, BACnetPDUChoice const *> objectMap;

	static std::map<uint8_t, BACnetPDUChoice const *> init_map(void);

public:

	static BACnetPDUChoice const CONFIRMED_REQUEST;
	static BACnetPDUChoice const UNCONFIRMED_REQUEST;
	static BACnetPDUChoice const SIMPLE_ACK;
	static BACnetPDUChoice const COMPLEX_ACK;
	static BACnetPDUChoice const SEGMENT_ACK;
	static BACnetPDUChoice const ERROR;
	static BACnetPDUChoice const REJECT;
	static BACnetPDUChoice const ABORT;

	static BACnetPDUChoice const &getEnumByValue(uint8_t enumValue);
};

#endif /* BACNETAPP_SRC_BACNETENUMPDUCHOICE_H_ */
