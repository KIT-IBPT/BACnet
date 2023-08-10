/*
 * BnetReadAccessSpec.cpp
 *
 *  Created on: Aug 14, 2018
 *      Author: 8w4
 */

#include "BnetReadAccessSpec.h"

BnetReadAccessSpec::BnetReadAccessSpec(const BACnetVariable &var) {
	// TODO Auto-generated constructor stub
	this->objId = var.getObjectPropertyReference().getObjectId();

}

BnetReadAccessSpec::~BnetReadAccessSpec() {
	// TODO Auto-generated destructor stub
}

