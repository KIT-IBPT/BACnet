/*
 * BACnetBVLLOrigBcastNPDU.cpp
 *
 *  Created on: Sep 22, 2016
 *      Author: 8w4
 */

#include <iomanip>

#include "BACnetBVLLOrigBcastNPDU.h"

BACnetBVLLOrigBcastNPDU::BACnetBVLLOrigBcastNPDU()
:BACnetBVLL(&BACnetEnumBvlcFunction::ORIGINAL_BROADCAST_NPDU), npdu(0)
{


}

BACnetBVLLOrigBcastNPDU::BACnetBVLLOrigBcastNPDU(BACnetNpdu *bac_npdu)
:BACnetBVLL(&BACnetEnumBvlcFunction::ORIGINAL_BROADCAST_NPDU), npdu(bac_npdu)
{

}

BACnetNpdu const *BACnetBVLLOrigBcastNPDU::get_npdu(void) const {
	return npdu;
}

void BACnetBVLLOrigBcastNPDU::set_npdu(BACnetNpdu *bac_npdu) {
	npdu = bac_npdu;
}

BACnetBVLLOrigBcastNPDU::~BACnetBVLLOrigBcastNPDU() {
	// TODO Auto-generated destructor stub
}

size_t BACnetBVLLOrigBcastNPDU::get_length(void) const {
	return get_bvlc_length();
}

void BACnetBVLLOrigBcastNPDU::encode(BACnetBuffer &buff) {

	/** J.2.12.1 Original-Broadcast-NPDU: Format
	 * The Original-Broadcast-NPDU message consists of four fields:
	 * BVLC Type:		1-octet X'81' 					BVLL for BACnet/IP
	 * BVLC Function:	1-octet X'0B' 					Original-Broadcast-NPDU
	 * BVLC Length:		2-octets L						Length L, in octets, of the BVLL message
	 * BACnet NPDU:		Variable length
	 * */

	buff += get_bvlc_type();

	buff += BACnetEnumBvlcFunction::ORIGINAL_BROADCAST_NPDU.getValue();

	/** Now encode the length...*/
	set_bvlc_length(4 + npdu->get_length());

	buff.encode_ui16(get_bvlc_length());

	/** Now encode the NPDU...*/
	npdu->encode(buff);
	//((BACnetNpdu *)npdu)->encode(buff);

}

size_t BACnetBVLLOrigBcastNPDU::decode(BACnetBuffer &buff) {

	size_t len = this->BACnetBVLL::decode(buff);

	if(npdu) {
		//npdu->decode(src_addr, buff);
	}

	return len;
}

void BACnetBVLLOrigBcastNPDU::print(ostream& out) const {

    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "BACnet BVLL {" << endl;
    out << "\tBVLC Type: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) get_bvlc_type() << endl;
    out << "\tBVLC Function: " << std::dec << get_bvlc_function()->getName() << "(" << (unsigned int) get_bvlc_function()->getValue() << ")" << endl;
    out << "\tBVLC Length: " << get_bvlc_length() << endl;
    out << "\tNPDU: ";
    if(npdu) {
    	//out << *npdu;
    }
    else {
    	out << "\tNPDU: Does not exist" << endl;
    }

    out << "} BACnet BVLL" << endl;
}
