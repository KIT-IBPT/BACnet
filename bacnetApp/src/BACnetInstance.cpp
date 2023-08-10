/*
 * BACnetInstance.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: 8w4
 */

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "BACnetInstance.h"

BACnetInstance::BACnetInstance() {
	instance = NULL_BACNET_INSTANCE;
}

BACnetInstance::BACnetInstance(const BACnetInstance &inst)
:instance(inst.instance)
{

}

BACnetInstance::BACnetInstance(uint32_t inst) {
	setInstance(inst);
}

BACnetInstance::~BACnetInstance() {
	// TODO Auto-generated destructor stub
}

void BACnetInstance::setInstance(uint32_t newInstance) {

	if(newInstance > MAX_BACNET_INSTANCE) {

		stringstream ss;

		ss << "\nERROR: Invalid BACnet Instance: (" << newInstance << "). The valid instance range is 0-"
				<< MAX_BACNET_INSTANCE << "." << endl;

		throw std::invalid_argument(ss.str());
	}

	this->instance = newInstance;
}

void BACnetInstance::setToNullInstance(void) {
	this->instance = NULL_BACNET_INSTANCE;
}

uint32_t BACnetInstance::get_instance(void) const {
	return instance;
}

size_t BACnetInstance::get_length(void) const {

	size_t len = 0;


	/** Special value NULL_BACNET_INSTANCE*/
	if(instance == NULL_BACNET_INSTANCE) {
		return 0;
	}else if (instance < 0x100) {
		len = 1;
	} else if (instance < 0x10000) {
		len = 2;
		/** Note! Since MAX_BACNET_INSTANCE is 0x3FFFFFU we cannot ever be greater than 3-bytes! */
	} else {
		len = 3;
	}
	return len;
}


int BACnetInstance::encode(BACnetBuffer &buff) {

	size_t len = this->get_length();

	if(len > 2) {
		buff.encode_ui8((instance & 0xff0000) >> 16);
	}
	if(len > 1) {
		buff.encode_ui8((instance & 0x00ff00) >> 8);
	}
	if(len > 0) {
		buff.encode_ui8((instance & 0x0000ff));
	}
	return len;
}


/** Return (0) if equal. Return (-1) if left is less than right. Return (1) if left is greater than right.*/
int BACnetInstance::compare(const BACnetInstance &left, const BACnetInstance &right) const {
	/** See if they have the same address in memory...*/
	if(&left == &right) {
		return 0;
	}
	else if(left.instance == right.instance) {
		return 0;
	}
	else if(left.instance < right.instance) {
		return -1;
	}
	else
		return 1;
}

bool BACnetInstance::operator == (const BACnetInstance &right) const {

	if(compare(*this, right) == 0) {
		return true;
	}
	else
		return false;
}

bool BACnetInstance::operator != (const BACnetInstance &right) const {
	if(compare(*this, right) != 0) {
		return true;
	}
	else
		return false;
}

bool BACnetInstance::operator < (const BACnetInstance &right) const {
	if(compare(*this, right) == -1) {
		return true;
	}
	else
		return false;
}

bool BACnetInstance::operator > (const BACnetInstance &right) const {
	if(compare(*this, right) == 1) {
		return true;
	}
	else
		return false;
}
