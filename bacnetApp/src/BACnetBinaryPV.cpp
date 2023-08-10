/*
 * BACnetBinaryPV.cpp
 *
 *  Created on: Jul 2, 2018
 *      Author: 8w4
 */

#include "BACnetBinaryPV.h"
#include <sstream>

BACnetBinaryPV::BACnetBinaryPV() {
	// TODO Auto-generated constructor stub

}

BACnetBinaryPV::~BACnetBinaryPV() {
	// TODO Auto-generated destructor stub
}

bool BACnetBinaryPV::getValue(void) {
	return this->BACnetEnumerated::getValue() ? 1:0;
}

string BACnetBinaryPV::toString(void) const {

	stringstream ss;

	ss << "BACnetBinaryPV: Value = ";
	if(this->isNull()) {
		ss << "\"NULL\"";
	}
	else {
		if(this->BACnetEnumerated::getValue() > 0) {
			ss << BACnetEnumBinary::ACTIVE.getName() << " (" << this->BACnetEnumerated::getValue() << ")";
		}
		else {
			ss << BACnetEnumBinary::INACTIVE.getName() << " (" << this->BACnetEnumerated::getValue() << ")";
		}
	}
	ss << endl;

	return ss.str();
}

void BACnetBinaryPV::printData(void) {
	cout << this->toString() << endl;
}

size_t BACnetBinaryPV::getLength(void) {
	return 1;
}

