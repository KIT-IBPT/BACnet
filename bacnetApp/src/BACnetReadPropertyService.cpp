/*
 * BACnetReadPropertyService.cpp
 *
 *  Created on: Dec 19, 2017
 *      Author: 8w4
 */

#include "BACnetReadPropertyService.h"

#include <sstream>
#include <cstring>
#include <stdexcept>

#include "BACnetTag.h"

BACnetReadPropertyService::BACnetReadPropertyService()
: BACnetApdu(&BACnetEnumPDUChoice::CONFIRMED_REQUEST, &BACnetEnumConfSvc::READ_PROPERTY),
  objId(), propId(NULL), arrayIndex(-1)
{

	/** Initialize to default of unsegmented message*/
	pci.segmentedMessage = false;
	pci.moreFollows = false;
	pci.segmetedResponseAccepted = false;
	pci.maxSegments = &BACnetEnumMaxSegAccepted::UNSPECIFIED;
	pci.maxApduLen = &BACnetEnumMaxApduAccepted::UP_TO_1476_OCTETS;
	pci.invokeId = 0;
	pci.sequenceNum = 0;
	pci.windowSize = 0;

}

BACnetReadPropertyService::~BACnetReadPropertyService() {
	// TODO Auto-generated destructor stub
}


/** Get the length of encoding */
size_t BACnetReadPropertyService::get_length(void) const {

	size_t len = 0;

	/** PDU-Type and segmentation flags are one octet.*/
	len += 1;

	/** Max segments and max response are one octet.*/
	len += 1;

	/** Invoke-Id is one octet.*/
	len += 1;

	if(this->pci.segmentedMessage) {

		/** Sequence number is one octet.*/
		len += 1;

		/** Proposed window size is one octet.*/
		len += 1;
	}

	/** Service-choice (i.e., Read-Property:(12)) is one octet.*/
	len += 1;

	/** The rest is the length of the service request*/

	/** Object-Id: Clause 20.2.14 states that an BACnet Object-Id is 4-bytes long. Plus one octet for the preceding
	 * tag encoding describing the following octets*/
	len += (4 + 1);

	/** Property-Id, Plus a single octet for the tag*/
	len += this->propId->getLength() + 1;

	/** Optional Array-Index, Plus a single octet for the tag*/
	if(this->arrayIndex > (-1)) {
		len += (BACnetBuffer::getUintLength(this->arrayIndex) + 1);
	}

	return len;
}

/** Encode this whoIs service into a buffer */
int BACnetReadPropertyService::encode(BACnetBuffer &buff) {

	const uint8_t BIT1 = 0x02;
	const uint8_t BIT2 = 0x04;
	const uint8_t BIT3 = 0x08;

	size_t len = 0;

	uint8_t ui8 = (BACnetEnumPDUChoice::CONFIRMED_REQUEST.getValue() << 4);
	ui8 |= this->pci.segmentedMessage ? BIT3 : 0x00;
	ui8 |= this->pci.moreFollows ? BIT2 : 0x00;
	ui8 |= this->pci.segmetedResponseAccepted ? BIT1 : 0x00;

	buff += ui8;

	ui8 = 0;
	ui8 = (pci.maxSegments->getValue() << 4);
	ui8 |= pci.maxApduLen->getValue();

	buff += ui8;

	buff += pci.invokeId & 0xFF;

	if(this->pci.segmentedMessage) {
		buff += pci.sequenceNum;
		buff += pci.windowSize;
	}

	buff += BACnetEnumConfSvc::READ_PROPERTY.getValue();

	BACnetTag tag = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 0, 4);
	tag.encode(buff);
	this->objId.encode(buff);

	tag = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 1, this->propId->getLength());
	tag.encode(buff);
	buff.encodeUnsignedInt(this->propId->getValue());

	if(this->arrayIndex > (-1)) {
		tag = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 2, BACnetBuffer::getUintLength(this->arrayIndex));
		tag.encode(buff);
		buff.encodeUnsignedInt(this->arrayIndex);
	}

	return len;
}

void BACnetReadPropertyService::makeUnsegmentedRequest(uint8_t invokeId, BACnetObjPropRef const &objProp) {

	this->objId = objProp.getObjectId();
	this->propId = objProp.getPropertyId();
	this->arrayIndex = objProp.getArrayIndex();

	pci.segmentedMessage = false;
	pci.moreFollows = false;
	pci.segmetedResponseAccepted = false;
	pci.maxSegments = &BACnetEnumMaxSegAccepted::UNSPECIFIED;
	pci.maxApduLen = &BACnetEnumMaxApduAccepted::UP_TO_1476_OCTETS;
	pci.invokeId = invokeId;
	pci.sequenceNum = 0;
	pci.windowSize = 0;
}




