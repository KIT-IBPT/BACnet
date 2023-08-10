/*
 * BACnetRpmReq.h
 *
 *  Created on: Aug 15, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETRPMREQ_H_
#define BACNETAPP_SRC_BACNETRPMREQ_H_

#include "BACnetBuffer.h"
#include "BACnetApdu.h"
#include "BACnetObjIdentifier.h"
#include "BACnetDefs.h"
#include "BACnetObjPropRef.h"
#include "BACnetVariable.h"

using namespace std;

class BACnetRpmReq : public BACnetApdu {

private:
	Confirmed_Req_PCI pci;
	std::list<BACnetVariable *> rpmList;

public:
	BACnetRpmReq();
	virtual ~BACnetRpmReq();

	/** Get the length of encoding */
	size_t get_length(void) const;

	/** Encode this whoIs service into a buffer */
	int encode(BACnetBuffer &buff);

	void makeUnsegmentedRequest(uint8_t invokeId, const std::list<BACnetVariable *> &rpmLst);

};

#endif /* BACNETAPP_SRC_BACNETRPMREQ_H_ */
