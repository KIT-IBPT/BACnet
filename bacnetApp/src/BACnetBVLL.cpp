/*
 * BACnetBVLL.cpp
 *
 *  Created on: Sep 22, 2016
 *      Author: 8w4
 */

#include <BACnetBVLL.h>
#include <stdexcept>
#include <sstream>
#include <iomanip>

BACnetBVLL::BACnetBVLL()
: bvlc_type(BVLL_FOR_BACNET_IP), bvlc_func(0), bvlc_len(0) {
	// TODO Auto-generated constructor stub

}

BACnetBVLL::BACnetBVLL(BACnetBvlcFunction const *bvlcFunc)
: bvlc_type(BVLL_FOR_BACNET_IP), bvlc_func(bvlcFunc), bvlc_len(0) {
	// TODO Auto-generated constructor stub

}

BACnetBVLL::~BACnetBVLL() {
	// TODO Auto-generated destructor stub
}

uint8_t BACnetBVLL::get_bvlc_type(void) const {
	return bvlc_type;
}

BACnetBvlcFunction const *BACnetBVLL::get_bvlc_function(void) const {
	return bvlc_func;
}

uint16_t BACnetBVLL::get_bvlc_length(void) const {
	return bvlc_len;
}

void BACnetBVLL::set_bvlc_type(uint8_t type) {
	bvlc_type = type;
}

void BACnetBVLL::set_bvlc_function(BACnetBvlcFunction const *bvlcFunc) {
	bvlc_func = bvlcFunc;
}

void BACnetBVLL::set_bvlc_length(uint16_t len) {
	bvlc_len = len;
}

size_t BACnetBVLL::decode(BACnetBuffer &buff) {

	/** First octet is BVLC-Type */
	this->bvlc_type = buff.get_ui8();

	if(get_bvlc_type() != BVLL_FOR_BACNET_IP) {
		stringstream ss;
		ss << "ERROR! size_t BACnetBVLL::decode(BACnetBuffer &buff)" << endl;
		ss << "-> While decoding the buffer the BVLC-TYPE octet (" << "0x" <<
				std::setfill('0') << std::setw(2) << std::hex << (unsigned int) this->bvlc_type << ") "
				"is invalid. It must be 0x81" << endl;
		throw std::invalid_argument(ss.str());
	}

	/** Second octet is BVLC-Function Code*/
	this->bvlc_func = &BACnetEnumBvlcFunction::getEnumByValue(buff.get_ui8());

	/** Third octet is Length, in octets, of the BVLL message*/
	this->bvlc_len = buff.get_ui16();

	return 4;
}



