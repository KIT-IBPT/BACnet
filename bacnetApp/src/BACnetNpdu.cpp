/*
 * BACnetNpdu.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: 8w4
 */

#include "BACnetNpdu.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>

BACnetNpdu::BACnetNpdu()
:srcAddr(), destAddr(), apdu(0), messagePriority(0), dataExpectingReply(false)
{
	// TODO Auto-generated constructor stub

}

BACnetNpdu::BACnetNpdu(BACnetDeviceAddress &srcAddr, BACnetDeviceAddress &destAddr, BACnetApdu *apdu,
		BACnetMessagePriority const *networkPriority, bool expectingReply)
:srcAddr(srcAddr), destAddr(destAddr), apdu(apdu), messagePriority(networkPriority), dataExpectingReply(expectingReply)
{
	// TODO Auto-generated constructor stub

}

BACnetNpdu::~BACnetNpdu() {
	// TODO Auto-generated destructor stub
}

/** Get the length of encoding */
size_t BACnetNpdu::get_length(void) const {
	size_t len = 0;

	/** Minimum length is 2 octets: One octet for the protocol version, and one octet for the control octet*/

	len = 2;

	/** The remaining octets may vary.*/
	if(this->destAddr.getRemoteNetwork() > 0) {

		/** 2-Octets for network number*/
		len += 2;

		/** 1-Octet for DLEN*/
		len += 1;

		if(this->destAddr.getRemoteNetworkAddressLength() > 0) {
			/** DADR*/
			len += this->destAddr.getRemoteNetworkAddressLength();
		}
	}

	if(this->srcAddr.getRemoteNetwork() > 0 &&
			this->srcAddr.getRemoteNetworkAddressLength() > 0) {

		/** 2-Octets for network number*/
		len += 2;

		/** 1-Octet for SLEN*/
		len += 1;

		/** SADR*/
		len += this->srcAddr.getRemoteNetworkAddressLength();
	}

	/** Hop count present?*/
	if(this->destAddr.getRemoteNetwork() > 0) {
		/** If there is a remote network then there shall be a hop count.*/
		len += 1;
	}

	//TODO
	/** Add support for message type and vendor ID. See section 6.2.2 of the Standard.*/

	if(apdu) {
		len += apdu->get_length();
	}

	return len;
}

/** Encode this into a buffer */
int BACnetNpdu::encode(BACnetBuffer &buff) {

	uint8_t const BIT5 = 0x20;
	uint8_t const BIT3 = 0x08;
	uint8_t const BIT2 = 0x04;
	uint8_t const BITS_0_1 = 0x03;


	/** The second octet is the control octet, let't do it first.*/
	/** Zero out the control octet.*/
	uint8_t cntrl = 0;

	/** BIT7: Network Layer message (1) or BACnet APDU (0)?
	 * Since I am not supporting network layer messages yet
	 * let's leave BIT7 at (0)*/

	/** BIT6: Is reserved and must be (0), so skip BIT6.*/

	/** BIT5: Destination Specifier...*/
	if(this->destAddr.getRemoteNetwork() > 0) {
		cntrl |= BIT5;
	}

	/** BIT4: Is reserved and must be (0), so skip BIT4.*/

	/** BIT3: Source Specifier...*/
	if(this->srcAddr.getRemoteNetwork() > 0 && this->srcAddr.getRemoteNetworkAddressLength() > 0) {
		cntrl |= BIT3;
	}

	/** BIT2: Expecting reply?*/
	if(dataExpectingReply) {
		cntrl |= BIT2;
	}

	/** BIT1 & BIT0: Network Priority?*/
	cntrl |= (messagePriority->getValue() & BITS_0_1);

	size_t len = 0;

	/** Minimum length is 2 octets.*/

	/** The first octet is the protocol version.*/
	buff += BACNET_PROTOCOL_VERSION;

	/** Add control octet*/
	buff += cntrl;

	/** Length: Minimum length at this point is 2*/
	len += 2;

	/** DNET: If there is one... encode it...*/
	if((cntrl & BIT5)) {

		buff.encode_ui16(this->destAddr.getRemoteNetwork());
		len += 2;

		/** DLEN: 0 denotes broadcast MAC DADR and DADR field is absent.
		 * DLEN > 0 specifies length of DADR field*/

		uint8_t remAddrLen = this->destAddr.getRemoteNetworkAddressLength();

		buff.encode_ui8(remAddrLen);
		len += 1;

		/** DADR: If DLEN is greater than 0, then encode the destination address.*/
		if(remAddrLen > 0) {
			buff.encode_buffer(this->destAddr.getRemoteNetowrkAddress(), 0, remAddrLen);
			len += remAddrLen;
		}
	}

	if((cntrl & BIT3)) {

		/** SNET*/
		buff.encode_ui16(this->srcAddr.getRemoteNetwork());
		len += 2;

		/** SLEN*/
		uint8_t remAddrLen = this->srcAddr.getRemoteNetworkAddressLength();

		buff.encode_ui8(remAddrLen);
		len += 1;

		/** SADR*/
		buff.encode_buffer(this->srcAddr.getRemoteNetowrkAddress(), 0, remAddrLen);
		len += remAddrLen;
	}

	/** HOP COUNT: if there is a remote network then there must be a HOP COUNT.*/
	if((cntrl & BIT5)) {
		buff.encode_ui8(BACNET_DEFAULT_HOP_COUNT);
		len += 1;
	}

	/** TODO: Sometime figure out how to support Network Layer messages.*/

	/** Encode the APDU */
	if(apdu) {
		apdu->encode(buff);
	}

	return 0;
}

int BACnetNpdu::decode(BACnetBuffer &buff) {

	uint8_t const BIT7 = 0x80;
	uint8_t const BIT6 = 0x40;
	uint8_t const BIT5 = 0x20;
	uint8_t const BIT4 = 0x10;
	uint8_t const BIT3 = 0x08;
	uint8_t const BIT2 = 0x04;
	uint8_t const BITS_0_1 = 0x03;

	stringstream ss;

	uint8_t oct = buff.get_ui8();

	/** Check the first octet for the valid Protocol version.*/
	if(oct != BACNET_PROTOCOL_VERSION) {

		ss << "ERROR! int BACnetNpdu::decode(BACnetBuffer &buff)" << endl;
		ss << "-> While decoding the buffer the BACNET_PROTOCOL_VERSION octet (" << "0x" <<
				std::setfill('0') << std::setw(2) << std::hex << (unsigned int) oct << ") "
				"is invalid. It must be 0x" << std::setfill('0') << std::setw(2) << std::hex <<
				(unsigned int) BACNET_PROTOCOL_VERSION << endl;
		throw std::invalid_argument(ss.str());
	}

	/** Must be a valid NPDU...*/
	uint8_t const cntrl = buff.get_ui8();

	/** BIT7: Network layer message or APDU?*/
	if((cntrl & BIT7)) {
		/** Abort! Network layer message is present. We don't know how to handle those yet.*/
		ss << "FYI! int BACnetNpdu::decode(BACnetBuffer &buff)" << endl;
		ss << "-> While decoding the buffer bit-7 of the NPDU-control octet is set, indicating"
				" that this is a network layer message, instead of a BACnet-APDU. I only know"
				" how to handle APDU-messages..." << endl;
		throw std::invalid_argument(ss.str());
	}

	/** BIT6: Reserved and shall be zero.*/
	(void) BIT6;

	/** BIT5: DNET Specifier:
	 * BIT5 = 0: DNET, DLEN, DADR, and Hop Count absent.
	 * BIT5 = 1: DNET, DLEN, and Hop Count present.
	 * DLEN = 0 denotes broadcast MAC DADR and DADR field is absent.
	 * DLEN > 0 specifies length of DADR field*/
	if((cntrl & BIT5)) {
		uint16_t dnet = buff.get_ui16();
		this->destAddr.setRemoteNetwork(dnet);

		uint8_t dlen = buff.get_ui8();

		if(dlen > 0 && dlen <= MAX_MAC_LENGTH) {
			uint8_t dadr[dlen];
			for(int i = 0; i < dlen; i++) {
				dadr[i] = buff.get_ui8();
			}
			this->destAddr.setRemoteNetworkAddress(&dadr[0], dlen);
		}
	}

	/** BIT4: Reserved and shall be zero.*/
	(void) BIT4;

	/** BIT3: SNET Specifier:
	 * BIT5 = 0: SNET, SLEN and SADR absent.
	 * BIT5 = 1: SNET, SLEN and SADR present.
	 * SLEN = 0 is invalid.
	 * SLEN > 0 specifies length of SADR field*/
	if((cntrl & BIT3)) {

		uint16_t snet = buff.get_ui16();
		this->srcAddr.setRemoteNetwork(snet);

		uint8_t slen = buff.get_ui8();

		if(slen > 0 && slen <= MAX_MAC_LENGTH) {
			uint8_t sadr[slen];
			for(int i = 0; i < slen; i++) {
				sadr[i] = buff.get_ui8();
			}
			this->srcAddr.setRemoteNetworkAddress(&sadr[0], slen);
		}
	}

	/** Hop Count TODO: Do something with this sometime... Supposed to decrement but we are not routers so... */
	if((cntrl & BIT5)) {
		buff.get_ui8();
	}

	/** BIT2: Data Expecting Reply*/
	if((cntrl & BIT2)) {
		this->dataExpectingReply = true;
	}

	/** BIT*/
	/** BIT1 & BIT0: Network Priority?*/
	this->dataExpectingReply = &BACnetEnumMessagePriority::getEnumByValue((cntrl & BITS_0_1));

	return 0;
}

bool BACnetNpdu::hasSourceSpecifier(void) const {
	return (this->srcAddr.getRemoteNetwork() > 0);
}

int BACnetNpdu::getSourceAddress(BACnetDeviceAddress &addr) const {

		addr.setRemoteNetwork(this->srcAddr.getRemoteNetwork());
		addr.setRemoteNetworkAddress(this->srcAddr.getRemoteNetowrkAddress(), this->srcAddr.getRemoteNetworkAddressLength());
	return 0;
}



