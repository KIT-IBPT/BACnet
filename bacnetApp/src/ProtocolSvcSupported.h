/*
 * ProtocolSvcSupported.h
 *
 *  Created on: Jun 14, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_PROTOCOLSVCSUPPORTED_H_
#define BACNETAPP_SRC_PROTOCOLSVCSUPPORTED_H_

#include "BACnetBitString.h"
#include "BACnetEnumSvcSupChoice.h"

class ProtocolSvcSupported : public BACnetBitString {
private:

public:
	ProtocolSvcSupported();
	virtual ~ProtocolSvcSupported();

	bool isServiceSupported(BACnetSvcSupChoice const *bacService) const;
	string toString(void) const;
	void printData(void);
};

#endif /* BACNETAPP_SRC_PROTOCOLSVCSUPPORTED_H_ */
