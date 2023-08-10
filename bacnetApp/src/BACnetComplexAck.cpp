/*
 * BACnetComplexAck.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: 8w4
 */

#include "BACnetComplexAck.h"

#include <sstream>
#include <cstring>
#include <stdexcept>

#include "BACnetTag.h"
#include "BACnetBitString.h"
#include "BACnetDevice.h"

BACnetComplexAck::BACnetComplexAck()
: BACnetApdu(&BACnetEnumPDUChoice::COMPLEX_ACK, NULL), cSvcChoice(NULL)
{
	// TODO Auto-generated constructor stub

}

BACnetComplexAck::~BACnetComplexAck() {
	// TODO Auto-generated destructor stub
}

/** Get the length of encoding
 * TODO: Fix me */
size_t BACnetComplexAck::get_length(void) const {
	return 0;
}

uint8_t BACnetComplexAck::getInvokeId(void) const {
	return this->pci.invokeId;
}

BACnetConfSvcChoice const *BACnetComplexAck::getServiceChoice(void) const {
	return this->cSvcChoice;
}

/** Encode this whoIs service into a buffer
 * TODO: Fix me */
int BACnetComplexAck::encode(BACnetBuffer &buff) {
	return 0;
}

void BACnetComplexAck::decode(BACnetBuffer &buff) {

	stringstream ss;
	const uint8_t BIT2 = 0x04;
	const uint8_t BIT3 = 0x08;

	/** Get the PDU-Type. It must be a COMPLEX_ACK*/
	uint8_t oct = buff.get_ui8();

	BACnetPDUChoice const &PDU_TYPE = BACnetEnumPDUChoice::getEnumByValue((oct >> 4));

	if(PDU_TYPE != BACnetEnumPDUChoice::COMPLEX_ACK) {
		ss << "ERROR! BACnetComplexAck::decode(BACnetBuffer &buff): PDU-TYPE (" <<  PDU_TYPE.getValue() <<
				") does NOT equal BACnetEnumPDUChoice::COMPLEX_ACK" << endl;
		throw std::invalid_argument(ss.str());
	}

	/** All the PDU-Flag business is all about segmented messages. But since we do not support segmented
	 * messages at the moment the I am just going to leave them right here. What we really are after is
	 * the invoke-id of the message. It was what we will use to match it up with our request that
	 * precipitated this message.*/

	/** Get the PDU-Flags*/
	uint8_t PDU_FLAGS = oct & 0xF;

	/** Next must be invoke-id */
	this->pci.invokeId = buff.get_ui8();

	/** Is this a segmented message?*/
	this->pci.segmentedMessage = (PDU_FLAGS & BIT3) ? true : false;

	if(this->pci.segmentedMessage) {
		this->pci.moreFollows = (PDU_FLAGS & BIT2) ? true : false;
		this->pci.sequenceNum = buff.get_ui8();
		this->pci.windowSize = buff.get_ui8();
	}

	/** Get the service-type: Read-property... write-property... etc*/
	this->cSvcChoice = &BACnetEnumConfSvc::getEnumByValue(buff.get_ui8());
}

BACnetObjIdentifier const &BACnetComplexAck::getObjectId(void) const {
	return this->objId;
}

BACnetPropertyType const *BACnetComplexAck::getPropertyId(void) const {
	return this->propId;
}


