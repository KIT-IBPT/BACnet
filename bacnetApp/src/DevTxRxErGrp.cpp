/*
 * DevCommGrp.cpp
 *
 *  Created on: Sep 26, 2018
 *      Author: 8w4
 */

#include <DevTxRxErGrp.h>

DevTxRxErGrp::DevTxRxErGrp(const BACnetDevice &bacDev, const BACnetTxRxErChoice &txRxEr)
:dev(bacDev), txrxer(txRxEr)
{
	// TODO Auto-generated constructor stub

}

DevTxRxErGrp::~DevTxRxErGrp() {
	// TODO Auto-generated destructor stub
}

const BACnetDevice &DevTxRxErGrp::getDevice(void) {
	return this->dev;
}

const BACnetTxRxErChoice &DevTxRxErGrp::getTxRxErChoice(void) {
	return this->txrxer;
}



