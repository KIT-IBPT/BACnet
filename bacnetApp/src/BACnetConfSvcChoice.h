/*
 * BACnetConfSvcChoice.h
 *
 *  Created on: Dec 20, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETCONFSVCCHOICE_H_
#define BACNETAPP_SRC_BACNETCONFSVCCHOICE_H_

#include <stdint.h>
#include <string>
#include <iostream>

#include "BACnetEnumSingle.h"

using namespace std;

#define MAX_CONFIRMED_SERVICE 0x1D

class BACnetConfSvcChoice : public BACnetEnumSingle {

public:
	BACnetConfSvcChoice(unsigned int const enumValue, string const name);
	virtual ~BACnetConfSvcChoice();
};

#endif /* BACNETAPP_SRC_BACNETCONFSVCCHOICE_H_ */
