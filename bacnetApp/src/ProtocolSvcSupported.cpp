/*
 * ProtocolSvcSupported.cpp
 *
 *  Created on: Jun 14, 2018
 *      Author: 8w4
 */

#include "ProtocolSvcSupported.h"
#include <sstream>

ProtocolSvcSupported::ProtocolSvcSupported() {
	// TODO Auto-generated constructor stub

}

ProtocolSvcSupported::~ProtocolSvcSupported() {
	// TODO Auto-generated destructor stub
}

bool ProtocolSvcSupported::isServiceSupported(BACnetSvcSupChoice const *bacService) const {

	if(bacService) {
		return this->checkBit( (uint8_t) bacService->getValue());
	}
	return false;
}

string ProtocolSvcSupported::toString(void) const {

	stringstream ss;

	BACnetEnumSvcSupChoice::iterator itr = BACnetEnumSvcSupChoice::getBegin();
	BACnetEnumSvcSupChoice::iterator endIt = BACnetEnumSvcSupChoice::getEnd();

	ss << this->BACnetBitString::toString() << endl;

	if(!this->isNull()) {
		while(itr != endIt) {
			ss << itr->second->getName() << " (";
			ss << (this->isServiceSupported(itr->second) ? "Yes)" : "No)") << endl;
			itr++;
		}
	}

	return ss.str();
}

void ProtocolSvcSupported::printData(void) {
	cout << this->toString() << endl;
}

