/*
 * BACnetWritePropService.cpp
 *
 *  Created on: Jul 31, 2018
 *      Author: 8w4
 */

#include "BACnetWritePropService.h"
#include <sstream>
#include <cstring>
#include <stdexcept>

#include "BACnetTag.h"

BACnetWritePropService::BACnetWritePropService()
: BACnetApdu(&BACnetEnumPDUChoice::CONFIRMED_REQUEST, &BACnetEnumConfSvc::WRITE_PROPERTY),
  objId(), propId(NULL), arrayIndex(-1), writePriority(-1), appData(NULL)
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

BACnetWritePropService::~BACnetWritePropService() {
	// TODO Auto-generated destructor stub
}

/** Get the length of encoding */
size_t BACnetWritePropService::get_length(void) const {

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

	/** Service-choice (i.e., Write-Property:(15)) is one octet.*/
	len += 1;

	/** The rest is the length of the service request*/

	/**
	 * WriteProperty-Request ::= SEQUENCE {
	 * objectIdentifier				[0] BACnetObjectIdentifier,
	 * propertyIdentifier			[1] BACnetPropertyIdentifier,
	 * propertyArrayIndex			[2] Unsigned OPTIONAL, --used only with array datatypes
	 * 														-- if omitted with an array the entire
	 * 														-- array is referenced
	 * propertyValue				[3] ABSTRACT-SYNTAX.&Type,
	 * priority						[4] Unsigned (1..16) OPTIONAL --used only when property is commandable
	 * }
	 * */

	/** [0] Object-Id: Clause 20.2.14 states that an BACnet Object-Id is 4-bytes long. Plus one octet for the preceding
	 * tag encoding describing the following octets*/
	len += (4 + 1);

	/** [1] Property-Id, Plus a single octet for the tag*/
	len += this->propId->getLength() + 1;

	/** [2] Optional Array-Index, Plus a single octet for the tag*/
	if(this->arrayIndex > (-1)) {
		len += (BACnetBuffer::getUintLength(this->arrayIndex) + 1);
	}

	/** [3] Opening tag 0x3E is one octet*/
	len += 1;

	/** [3] Get the length of the abstract data-type. Plus one for the tag octet*/
	if(this->appData != NULL) {
		len += this->appData->getLength() + 1;
	}

	/** [3] Closing tag 0x3F is one octet*/
	len += 1;

	/** [4] Priority (1-16) is one octet plus another octet for the tag*/
	len += (1+1);

	return len;
}

/** Encode this Write-Property service into a buffer */
int BACnetWritePropService::encode(BACnetBuffer &buff) {

	const uint8_t BIT1 = 0x02;
	const uint8_t BIT2 = 0x04;
	const uint8_t BIT3 = 0x08;

//	const uint8_t OPENING_TAG = 0x06;
//	const uint8_t CLOSING_TAG = 0x07;

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

	buff += BACnetEnumConfSvc::WRITE_PROPERTY.getValue();

	/**
	 * WriteProperty-Request ::= SEQUENCE {
	 * objectIdentifier				[0] BACnetObjectIdentifier,
	 * propertyIdentifier			[1] BACnetPropertyIdentifier,
	 * propertyArrayIndex			[2] Unsigned OPTIONAL, --used only with array datatypes
	 * 														-- if omitted with an array the entire
	 * 														-- array is referenced
	 * propertyValue				[3] ABSTRACT-SYNTAX.&Type,
	 * priority						[4] Unsigned (1..16) OPTIONAL --used only when property is commandable
	 * }
	 * */

	BACnetTag tag;

	/** [0] */
	tag.encodeContextTag(0, 4, buff);
	this->objId.encode(buff);

	/** [1] */
	tag.encodeContextTag(1, this->propId->getLength(), buff);
	buff.encodeUnsignedInt(this->propId->getValue());

	/** [2] */
	if(this->arrayIndex > (-1)) {
		tag.encodeContextTag(2, BACnetBuffer::getUintLength(this->arrayIndex), buff);
		buff.encodeUnsignedInt(this->arrayIndex);
	}

	/** [3] Opening Tag 0x3E*/
	tag.encodeOpeningTag(3, buff);

	/** [3] Property Value: ABSTRACT-SYNTAX.&Type,*/
	if(this->appData != NULL) {
		this->appData->encode(buff);
	}

	/** [3] Closing Tag 0x3F*/
	tag.encodeClosingTag(3, buff);


	/** [4] Priority */
	tag.encodeContextTag(4, 1, buff);

	/** A valid write priority range is from 1 to 16, so we better check this before we encode it,
	 * since we use (-1) as a sentinel value.*/
	if(this->writePriority < 1 || this->writePriority > 16) {
		cout << "ERROR! BACnetWritePropService::encode: the write-priority value (" << this->writePriority
				<< ") must be between 1 and 16. I am going to assume 16 by default" << endl;

		buff.encode_ui8(this->writePriority);
	}
	else {
		buff.encode_ui8(this->writePriority);
	}

	return len;
}

void BACnetWritePropService::makeUnsegmentedRequest(uint8_t invokeId, BACnetObjPropRef const &objProp,
		BACnetAppDataType *appData)
{

	this->objId = objProp.getObjectId();
	this->propId = objProp.getPropertyId();
	this->arrayIndex = objProp.getArrayIndex();
	this->writePriority = objProp.getWritePriority();
	this->appData = appData;

	pci.segmentedMessage = false;
	pci.moreFollows = false;
	pci.segmetedResponseAccepted = false;
	pci.maxSegments = &BACnetEnumMaxSegAccepted::UNSPECIFIED;
	pci.maxApduLen = &BACnetEnumMaxApduAccepted::UP_TO_1476_OCTETS;
	pci.invokeId = invokeId;
	pci.sequenceNum = 0;
	pci.windowSize = 0;
}





