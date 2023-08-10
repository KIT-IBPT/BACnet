/*
 * BACnetRpmAck.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: 8w4
 */

#include "BACnetRpmAck.h"

#include <sstream>
#include <cstring>
#include <stdexcept>

#include "BACnetTag.h"
#include "BACnetDevice.h"

BACnetRpmAck::BACnetRpmAck() {
	// TODO Auto-generated constructor stub

}

BACnetRpmAck::~BACnetRpmAck() {
	// TODO Auto-generated destructor stub
}

const uint8_t *BACnetRpmAck::decodeObjectId(BACnetBuffer &buff, BACnetObjIdentifier &objId) {

	stringstream ss;

	/** Context tag [0] must be BACnet Object-Identifier */

	/** Gotta decode the tag first, so you will know what is next.*/
	BACnetTag tag;
	tag.decode(buff);

	if(tag.getTagNumber() != 0) {
		ss << "BACnetRpmAck::decodeObjectId(BACnetBuffer &buff, BACnetObjIdentifier &objId): "
				"Invalid tag number for context specific tag [0], while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected (0), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	/** We don't have to check that tag.getTagClass() isn't NULL before we use it here because it gets set in tag.decode
	 * and if there was an issue in tag.decode then it will throw and this next line doesn't matter anyway.*/
	if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		ss << "BACnetRpmAck::decodeObjectId(BACnetBuffer &buff, BACnetObjIdentifier &objId): "
				"Invalid BACnet Tag Class while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() != 4) {
		ss << "BACnetRpmAck::decodeObjectId(BACnetBuffer &buff, BACnetObjIdentifier &objId): "
				"Invalid BACnet Tag Length/Value/Type while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected (4), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	objId.decode(buff);

	return buff.getReadPointer();
}

const uint8_t *BACnetRpmAck::decodePropertyId(BACnetBuffer &buff, uint32_t &propId) {

	stringstream ss;

	/** Next: Context tag [2] Property-identifier  */

	BACnetTag tag;
	tag.decode(buff);

	if(tag.getTagNumber() != 2) {
		ss << "BACnetRpmAck::decodePropertyId(BACnetBuffer &buff, const BACnetPropertyType *propId): "
				"Invalid tag number for context specific tag [2], while "
				"decoding BACnet Property Identifier." << endl;
		ss << "Expected (2), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		ss << "BACnetRpmAck::decodePropertyId(BACnetBuffer &buff, const BACnetPropertyType *propId): "
				"Invalid BACnet Tag Class while "
				"decoding BACnet Property Identifier." << endl;
		ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() < 1 || tag.getLengthValueType() > 3) {
		ss << "BACnetRpmAck::decodePropertyId(BACnetBuffer &buff, const BACnetPropertyType *propId): "
				"Invalid BACnet Tag Length/Value/Type while "
				"decoding BACnet Property Identifier." << endl;
		ss << "Expected (Greater than 1 but less than 3), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	/** There are a lot of BACnet property values... this could be from 1 to 3 octets...
	 * the standard says 0-4194303*/
	switch (tag.getLengthValueType()) {
	case 1:
		propId = buff.get_ui8();
		break;
	case 2:
		propId = buff.get_ui16();
		break;
	case 3:
		propId = buff.get_ui24();
		break;
	default:
		/** We can never get here anyway, because we check for this up above.*/
		break;
	}

	return buff.getReadPointer();
}

const uint8_t *BACnetRpmAck::decodeArrayIndex(BACnetBuffer &buff, int &arrayIndex) {

	stringstream ss;

	/** Next: Context tag [3] Optional Array-Index  */

	BACnetTag tag;
	tag.decode(buff);

	if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		ss << "BACnetRpmAck::decodeArrayIndex(BACnetBuffer &buff, int &arrayIndex): Invalid BACnet Tag Class while "
				"decoding BACnet property array index." << endl;
		ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() < 1 || tag.getLengthValueType() > 4) {
		ss << "BACnetRpmAck::decodeArrayIndex(BACnetBuffer &buff, int &arrayIndex): Invalid BACnet Tag Length/Value/Type while "
				"decoding BACnet property array index." << endl;
		ss << "Expected (1-4), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	switch (tag.getLengthValueType()) {
	case 1:
		arrayIndex = buff.get_ui8();
		break;
	case 2:
		arrayIndex = buff.get_ui16();
		break;
	case 3:
		arrayIndex = buff.get_ui24();
		break;
	case 4:
		arrayIndex = buff.get_ui32();
		break;
	default:
		/** We can never get here anyway, because we check for this up above.*/
		break;
	}
	return buff.getReadPointer();
}

bool BACnetRpmAck::isArrayIndex(const uint8_t *ptr) {

	/**
	 * context-specific-tag [3] is the signature of an array-index present.
	 * Bit: 7       0
	 *      0011 1000
	 *
	 * */
	const uint8_t ARRAYSIG = 0x38;

	if((*ptr & ARRAYSIG) == ARRAYSIG) {
		return true;
	}
	return false;
}

const uint8_t *BACnetRpmAck::decodeReadResult(BACnetBuffer &buff, appDataList_t &ackDataLst) {

	stringstream ss;

	/** Next: Context tag [4] Opening-tag identifier [4E] */
	const uint8_t *rptr = decodeContextSpecificOpeningTag(buff, 4);


	/** Property-Value...*/

	uint8_t const CLOSING_TAGG = 0x4F;
	BACnetApplicationData ackData;

	while(*rptr != CLOSING_TAGG) {
		ackData.decode(buff);
		ackDataLst.push_back(ackData);
		rptr = buff.getReadPointer();
	}

	/** Next: Context tag [4] Closing-tag identifier [4F] */
	decodeContextSpecificClosingTag(buff, 4);

	return buff.getReadPointer();
}

const uint8_t *BACnetRpmAck::decodeContextSpecificOpeningTag(BACnetBuffer &buff, int tagNumber) {

	stringstream ss;
	BACnetTag tag;
	tag.decode(buff);

	if(tag.getTagNumber() != tagNumber) {
		ss << "BACnetRpmAck::decodeContextSpecificOpeningTag(BACnetBuffer &buff): "
				"Invalid tag number for context specific tag [" << (unsigned int) tagNumber << "], while "
				"decoding an opening-tag." << endl;
		ss << "Expected (" << (unsigned int) tagNumber << "), but decoded (" <<
				(unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		ss << "BACnetRpmAck::decodeContextSpecificOpeningTag(BACnetBuffer &buff): Invalid BACnet Tag Class while "
				"decoding an opening-tag." << endl;
		ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() != 6) {
		ss << "BACnetRpmAck::decodeContextSpecificOpeningTag(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
				"decoding an opening-tag." << endl;
		ss << "Expected (6), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	return buff.getReadPointer();
}

const uint8_t *BACnetRpmAck::decodeContextSpecificClosingTag(BACnetBuffer &buff, int tagNumber) {

	stringstream ss;
	BACnetTag tag;
	tag.decode(buff);

	if(tag.getTagNumber() != tagNumber) {
		ss << "BACnetRpmAck::decodeContextSpecificClosingTag(BACnetBuffer &buff): "
				"Invalid tag number for context specific tag [" << (unsigned int) tagNumber << "], while "
				"decoding an opening-tag." << endl;
		ss << "Expected (" << (unsigned int) tagNumber << "), but decoded (" <<
				(unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		ss << "BACnetRpmAck::decodeContextSpecificClosingTag(BACnetBuffer &buff): Invalid BACnet Tag Class while "
				"decoding an opening-tag." << endl;
		ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() != 7) {
		ss << "BACnetRpmAck::decodeContextSpecificClosingTag(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
				"decoding an opening-tag." << endl;
		ss << "Expected (6), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}
	return buff.getReadPointer();
}

const uint8_t *BACnetRpmAck::decodeListOfResults(BACnetBuffer &buff, uint32_t &pid, int &arrayIndx,
		appDataList_t &ackDataLst) {

	stringstream ss;

	/** Context tag [2] must be BACnet-Property-Identifier */
	const uint8_t *rptr = decodePropertyId(buff, pid);

	/** Next: Context tag [3] is optional but if present then must be BACnet propertyArrayIndex */

	if(isArrayIndex(rptr)) {
		rptr = decodeArrayIndex(buff, arrayIndx);
	}

	/**
	 * readResult	CHOICE {
	 * 						propertyValue		[4] ABSTRACT-SYNTAX.&Type,
	 * 						propertyAccessError	[5] Error
	 * 				}
	 *
	 * */

	/** Property-Value...*/
	/** Next: Context tag [4] Opening-tag identifier [4E] */
	rptr = decodeReadResult(buff, ackDataLst);

	return rptr;
}

const uint8_t *BACnetRpmAck::decodeListOfResults(BACnetBuffer &buff, BACnetPropRefValue &prefvalue) {

	uint32_t pid = 0;
	int arrayIndx = -1;
	appDataList_t ackDataLst;

	/** Context tag [2] must be BACnet-Property-Identifier */
	const uint8_t *rptr = decodePropertyId(buff, pid);

	/** Next: Context tag [3] is optional but if present then must be BACnet propertyArrayIndex */

	if(isArrayIndex(rptr)) {
		rptr = decodeArrayIndex(buff, arrayIndx);
	}

	/**
	 * readResult	CHOICE {
	 * 						propertyValue		[4] ABSTRACT-SYNTAX.&Type,
	 * 						propertyAccessError	[5] Error
	 * 				}
	 *
	 * */

	/** Property-Value...*/
	/** Next: Context tag [4] Opening-tag identifier [4E] */
	rptr = decodeReadResult(buff, ackDataLst);

	prefvalue.setData(pid, arrayIndx, ackDataLst);

	return buff.getReadPointer();
}

void BACnetRpmAck::decode(BACnetBuffer &buff) {

	stringstream ss;

	/**
	 * ReadAccessResult ::= SEQUENCE {
	 * 		objectIdentifier 		[0] BACnetObjectIdentifier,
	 * 		listOfResults			[1] SEQUENCE OF SEQUENCE {
	 * 			propertyIdentifier		[2] BACnetPropertyIdentifier,
	 * 			propertyArrayIndex		[3] Unsigned OPTIONAL, -- used only with array datatype
	 * 															-- if omitted with an array the entire
	 * 															-- array is referenced
	 * 			readResult		CHOICE {
	 * 								propertyValue		[4] ABSTRACT-SYNTAX.&Type,
	 * 								propertyAccessError	[5] Error
	 * 							}
	 * 			} OPTIONAL
	 * 	}
	 *
	 * */


	/** Gotta decode the tag first, so you will know what is next.*/
	BACnetTag tag;

	BACnetObjIdentifier oid;

	const uint8_t *rptr = buff.getReadPointer();
	const uint8_t OBJID_SIGNATURE = 0x0C;
	const uint8_t CLOSINGTAG = 0x1F;

	std::list<BACnetPropRefValue> pRefValLst;
	BACnetPropRefValue pRefVal;
	BACnetRpmResult rpmRslt;

	/** Outer loop is for the next object-id in a sequence, while the inner loop is for the listOfResults.*/

	while(buff.get_read_length() > 0 && *rptr == OBJID_SIGNATURE) {

		/** Context tag [0] must be BACnet Object-Identifier */
		rptr = decodeObjectId(buff, oid);

		/** Context tag [1] must be opening-tag, i.e., [0x1E] */
		rptr = decodeContextSpecificOpeningTag(buff, 1);

		while(*rptr != CLOSINGTAG) {

			/** must be listOfResults... Context-Specific Tags [2], [3], and [4] or [5]*/

			rptr = decodeListOfResults(buff, pRefVal);
			pRefValLst.push_back(pRefVal);

			/** Clear the data for the next iteration, if there is one */
			pRefVal.clearData();
		}

		/** Context tag [1] must be closing-tag, i.e., [0x1F] */
		rptr = decodeContextSpecificClosingTag(buff, 1);

		rpmRslt.setData(oid, pRefValLst);
		this->readResult.push_back(rpmRslt);

		/** Clear the data for the next iteration, if there is one. */
		rpmRslt.clearData();
		pRefValLst.clear();
	}
}

rpmResultList_t &BACnetRpmAck::getRpmResultList(void) {
	return this->readResult;
}

size_t BACnetRpmAck::getNumberOfResultItems(void) {

	size_t len = 0;
	rpmResultList_t::const_iterator itr = this->readResult.begin();

	while(itr != this->readResult.end()) {
		len += (*itr).getPropRefValListSize();
		itr++;
	}

	return len;
}

size_t BACnetRpmAck::getNumberOfObjectIds(void) const {
	return this->readResult.size();
}

rpmResultList_t::const_iterator BACnetRpmAck::getIteratorToResultBegin(void) const {
	return this->readResult.begin();
}

rpmResultList_t::const_iterator BACnetRpmAck::getIteratorToResultEnd(void) const {
	return this->readResult.end();
}



