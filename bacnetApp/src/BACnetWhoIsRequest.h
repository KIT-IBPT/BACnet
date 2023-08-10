/*
 * BACnetWhoIsRequest.h
 *
 *  Created on: Sep 7, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETWHOISREQUEST_H_
#define BACNETAPP_SRC_BACNETWHOISREQUEST_H_

#include <iostream>
#include <string>
#include <stdint.h>

#include "BACnetDefs.h"
#include "BACnetConnection.h"
#include "BACnetDeviceAddress.h"
#include "BACnetWhoIsService.h"
#include "BACnetDevice.h"
#include "BACnetWhoIsResponse.h"

using namespace std;

class BACnetWhoIsRequest {
private:


public:
	BACnetWhoIsRequest();
	virtual ~BACnetWhoIsRequest();

	int sendWhoIsReqGlobal(BACnetDevice &bacDev);

};

#endif /* BACNETAPP_SRC_BACNETWHOISREQUEST_H_ */
