/*
 * BACnetRpmReq.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: 8w4
 */

#include "BACnetRpmReq.h"
#include "BACnetTag.h"

BACnetRpmReq::BACnetRpmReq()
: BACnetApdu(&BACnetEnumPDUChoice::CONFIRMED_REQUEST, &BACnetEnumConfSvc::READ_PROP_MULTIPLE)
{
	// TODO Auto-generated constructor stub

}

BACnetRpmReq::~BACnetRpmReq() {
	// TODO Auto-generated destructor stub
}

/** Get the length of encoding */
size_t BACnetRpmReq::get_length(void) const {

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

	/** Service-choice (i.e., READ_PROP_MULTIPLE:(14)) is one octet.*/
	len += 1;

	/** The rest is the length of the service request*/

	/** The structure...
	 *
	 * ReadPropertyMultiple-Request ::= SEQUENCE {
	 * listOfReadAccessSpecs	SEQUENCE OF ReadAccessSpecification
	 * }
	 *
	 * ReadAccessSpecification ::= SEQUENCE {
	 * objectIdentifier 		[0] BACnetObjectIdentifier,
	 * listOfPropertyReferences	[1] SEQUENCE OF BACnetPropertyReference
	 * }
	 *
	 * BACnetPropertyReference ::= SEQUENCE {
	 * propertyIdentifier			[0] BACnetPropertyIdentifier,
	 * propertyArrayIndex			[1]UnsignedOPTIONAL --used only with array datatype
	 * 									-- if omitted with an array the entire array is referenced
	 * }
	 *
	 * */

	std::list<BACnetVariable *>::const_iterator itr = this->rpmList.begin();

	const BACnetObjIdentifier *objid = NULL;

	while(itr != this->rpmList.end()) {

		objid = &(*itr)->getObjectIdentifier();

		/** Begin ---- ReadAccessSpecification ::= SEQUENCE { ---- */

		/** Context-Tag [0] Must be the object-identifier */
		/** Object-Id: Clause 20.2.14 states that an BACnet Object-Id is 4-bytes long. Plus one octet for the preceding
		 * tag encoding describing the following octets*/
		len += (4 + 1);

		/** Context-Tag [1] SEQUENCE OF BACnetPropertyReference */
		len += 1; // Opening-Tag [1E]

		/** Begin ---- BACnetPropertyReference ::= SEQUENCE ----*/
		/** Sub-Context-Tag[0] must be Property-Id, Plus a single octet for the tag*/
		len += (*itr)->getObjectProperty().getLength() + 1;

		/** Sub-Context-Tag[1] Optional but if present must be array-index, Plus a single octet for the tag*/
		if((*itr)->hasArrayIndex()) {
			len += (BACnetBuffer::getUintLength((*itr)->getArrayIndex()) + 1);
		}

		itr++;

		/** Are there more objects and properties? */
		if(itr != this->rpmList.end()) {

			/** Are there more properties associated with this SAME object? If so, then loop
			 * thru all of the properties that belong to this object. */
			while((*itr)->getObjectIdentifier() == *objid) {
				/** Begin ---- BACnetPropertyReference ::= SEQUENCE ----*/
				/** Sub-Context-Tag[0] must be Property-Id, Plus a single octet for the tag*/
				len += (*itr)->getObjectProperty().getLength() + 1;

				/** Sub-Context-Tag[1] Optional but if present must be array-index, Plus a single octet for the tag*/
				if((*itr)->hasArrayIndex()) {
					len += (BACnetBuffer::getUintLength((*itr)->getArrayIndex()) + 1);
				}
				itr++;
				if(itr == this->rpmList.end()) {
					break;
				}
			}
		}

		/** Context-Tag [1] SEQUENCE OF BACnetPropertyReference */
		len += 1; // Closing-Tag [1F]

	}

	return len;
}

/** Encode this read-property-multiple service into a buffer */
int BACnetRpmReq::encode(BACnetBuffer &buff) {

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

	buff += BACnetEnumConfSvc::READ_PROP_MULTIPLE.getValue();

	/** Now encode the list of ReadAccessSpecification parameters.
	 *
	 * ReadPropertyMultiple-Request ::= SEQUENCE {
	 * listOfReadAccessSpecs	SEQUENCE OF ReadAccessSpecification
	 * }
	 *
	 * ReadAccessSpecification ::= SEQUENCE {
	 * objectIdentifier 		[0] BACnetObjectIdentifier,
	 * listOfPropertyReferences	[1] SEQUENCE OF BACnetPropertyReference
	 * }
	 *
	 * BACnetPropertyReference ::= SEQUENCE {
	 * propertyIdentifier			[0] BACnetPropertyIdentifier,
	 * propertyArrayIndex			[1]UnsignedOPTIONAL --used only with array datatype
	 * 									-- if omitted with an array the entire array is referenced
	 * }
	 *
	 * */

	std::list<BACnetVariable *>::const_iterator itr = this->rpmList.begin();

	const BACnetObjPropRef *objPropRef = NULL;
	const BACnetObjIdentifier *objid = NULL;

	while(itr != this->rpmList.end()) {

		objid = &(*itr)->getObjectIdentifier();

		/** Begin ---- ReadAccessSpecification ::= SEQUENCE { ---- */

		/** Context-Tag [0] Must be the object-identifier */
		/** Object-Id: Clause 20.2.14 states that an BACnet Object-Id is 4-bytes long. Plus one octet for the preceding
		 * tag encoding describing the following octets*/
		BACnetTag tag;// = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 0, 4);
		tag.encodeContextTag(0, 4, buff);
		objid->encode(buff);

		/** Context-Tag [1] SEQUENCE OF BACnetPropertyReference */
		tag.encodeOpeningTag(1, buff); // Opening-Tag [1E]

		/** Begin ---- BACnetPropertyReference ::= SEQUENCE ----*/
		/** Sub-Context-Tag[0] must be Property-Id, Plus a single octet for the tag*/
		tag.encodeContextTag(0, (*itr)->getObjectProperty().getLength(), buff);
		buff.encodeUnsignedInt((*itr)->getObjectProperty().getValue());

		/** Sub-Context-Tag[1] Optional but if present must be array-index, Plus a single octet for the tag*/
		if((*itr)->hasArrayIndex()) {
			tag.encodeContextTag(1, buff.getUintLength((*itr)->getArrayIndex()), buff);
			buff.encodeUnsignedInt((*itr)->getArrayIndex());
		}

		itr++;

		/** Are there more objects and properties? */
		if(itr != this->rpmList.end()) {

			/** Are there more properties associated with this SAME object? If so, then loop
			 * thru all of the properties that belong to this object. */
			while((*itr)->getObjectIdentifier() == *objid) {
				/** Begin ---- BACnetPropertyReference ::= SEQUENCE ----*/
				/** Sub-Context-Tag[0] must be Property-Id, Plus a single octet for the tag*/
				tag.encodeContextTag(0, (*itr)->getObjectProperty().getLength(), buff);
				buff.encodeUnsignedInt((*itr)->getObjectProperty().getValue());

				/** Sub-Context-Tag[1] Optional but if present must be array-index, Plus a single octet for the tag*/
				if((*itr)->hasArrayIndex()) {
					tag.encodeContextTag(1, buff.getUintLength((*itr)->getArrayIndex()), buff);
					buff.encodeUnsignedInt((*itr)->getArrayIndex());
				}
				itr++;
				if(itr == this->rpmList.end()) {
					break;
				}
			}
		}

		/** Context-Tag [1] SEQUENCE OF BACnetPropertyReference */
		tag.encodeClosingTag(1, buff); // Closing-Tag [1F]

	}

	//	BACnetTag tag = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 0, 4);
	//	tag.encode(buff);
	//	this->objId.encode(buff);
	//
	//	tag = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 1, this->propId->getLength());
	//	tag.encode(buff);
	//	buff.encodeUnsignedInt(this->propId->getValue());
	//
	//	if(this->arrayIndex > (-1)) {
	//		tag = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 2, BACnetBuffer::getUintLength(this->arrayIndex));
	//		tag.encode(buff);
	//		buff.encodeUnsignedInt(this->arrayIndex);
	//	}

	return len;
}

void BACnetRpmReq::makeUnsegmentedRequest(uint8_t invokeId, const std::list<BACnetVariable *> &rpmLst) {

	pci.segmentedMessage = false;
	pci.moreFollows = false;
	pci.segmetedResponseAccepted = false;
	pci.maxSegments = &BACnetEnumMaxSegAccepted::UNSPECIFIED;
	pci.maxApduLen = &BACnetEnumMaxApduAccepted::UP_TO_1476_OCTETS;
	pci.invokeId = invokeId;
	pci.sequenceNum = 0;
	pci.windowSize = 0;

	this->rpmList = rpmLst;

}

