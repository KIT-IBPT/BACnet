/*
 * BACnetBvllForwardedNpdu.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: 8w4
 */

#include "BACnetBvllForwardedNpdu.h"

#include <iomanip>
#include <cstring>

BACnetBvllForwardedNpdu::BACnetBvllForwardedNpdu()
:BACnetBVLL(&BACnetEnumBvlcFunction::FORWARDED_NPDU), npdu(0)
{
	// TODO Auto-generated constructor stub

}

BACnetBvllForwardedNpdu::~BACnetBvllForwardedNpdu() {
	// TODO Auto-generated destructor stub
}

size_t BACnetBvllForwardedNpdu::get_length(void) const {
	return get_bvlc_length();
}

void BACnetBvllForwardedNpdu::encode(BACnetBuffer &buff) {

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

size_t BACnetBvllForwardedNpdu::decode(BACnetBuffer &buff) {

	size_t len = this->BACnetBVLL::decode(buff);

	this->bipOrigin[0] = buff.get_ui8();
	this->bipOrigin[1] = buff.get_ui8();
	this->bipOrigin[2] = buff.get_ui8();
	this->bipOrigin[3] = buff.get_ui8();
	this->bipOrigin[4] = buff.get_ui8();
	this->bipOrigin[5] = buff.get_ui8();

	if(npdu) {
		//npdu->decode(src_addr, buff);
	}

	return len;
}

void BACnetBvllForwardedNpdu::print(ostream& out) const {

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

void BACnetBvllForwardedNpdu::getBipOrigin(BACnetDeviceAddress &bipOrigin) const {
	struct in_addr ipv4_addr;
	memcpy(&ipv4_addr, &this->bipOrigin[0], 4);
	bipOrigin.setIpAddress(&ipv4_addr);

	uint16_t port;
	memcpy(&port, &this->bipOrigin[4], 2);
	bipOrigin.setIpPortAs_ntohs(port);

}


