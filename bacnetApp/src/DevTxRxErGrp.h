/*
 * DevTxRxErGrp.h
 *
 *  Created on: Sep 26, 2018
 *      Author: 8w4
 */

#ifndef BACNET2017APP_SRC_DEVTXRXERGRP_H_
#define BACNET2017APP_SRC_DEVTXRXERGRP_H_

#include "BACnetDevice.h"
#include "BACnetEnumTxRxEr.h"

using namespace std;

class DevTxRxErGrp {
private:
	const BACnetDevice &dev;
	const BACnetTxRxErChoice &txrxer;

public:
	DevTxRxErGrp(const BACnetDevice &bacDev, const BACnetTxRxErChoice &txRxEr);
	virtual ~DevTxRxErGrp();

	const BACnetDevice &getDevice(void);
	const BACnetTxRxErChoice &getTxRxErChoice(void);

};

#endif /* BACNET2017APP_SRC_DEVTXRXERGRP_H_ */
