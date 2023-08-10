/*
 * BnetReadAccessSpec.h
 *
 *  Created on: Aug 14, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BNETREADACCESSSPEC_H_
#define BACNETAPP_SRC_BNETREADACCESSSPEC_H_

#include "BACnetObjIdentifier.h"
#include "BACnetPropertyRef.h"
#include "BACnetVariable.h"

using namespace std;

class BnetReadAccessSpec {
private:
	BACnetObjIdentifier objId;
	std::list<BACnetPropertyRef> propRef;

public:
	BnetReadAccessSpec(const BACnetVariable &var);
	virtual ~BnetReadAccessSpec();
};

#endif /* BACNETAPP_SRC_BNETREADACCESSSPEC_H_ */
