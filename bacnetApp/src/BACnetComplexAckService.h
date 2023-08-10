/*
 * BACnetComplexAckService.h
 *
 *  Created on: Dec 20, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETCOMPLEXACKSERVICE_H_
#define BACNETAPP_SRC_BACNETCOMPLEXACKSERVICE_H_

#include <iostream>
#include <stdint.h>

#include "BACnetBuffer.h"
#include "BACnetObjIdentifier.h"
#include "BACnetDefs.h"

using namespace std;

class BACnetComplexAckService {

private:


public:
	BACnetComplexAckService();
	virtual ~BACnetComplexAckService();
};

#endif /* BACNETAPP_SRC_BACNETCOMPLEXACKSERVICE_H_ */
