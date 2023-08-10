/*
 * BACnetIamService.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: 8w4
 */

#include "BACnetIamService.h"
#include "BACnetTag.h"

#include <sstream>
#include <cstring>
#include <stdexcept>

BACnetIamService::BACnetIamService()
:objectId(), maxApduLengthAccepted(0), segmentationSupported(&BACnetEnumSegmentation::NO_SEGMENTATION), vendorId(0)
{
	// TODO Auto-generated constructor stub

}

BACnetIamService::~BACnetIamService() {
	// TODO Auto-generated destructor stub
}

BACnetObjIdentifier const *BACnetIamService::getObjectId(void) const {
	return &this->objectId;
}

uint32_t BACnetIamService::getObjectIstance(void) const {
	return this->objectId.getObjectInstanceAsUint32_t();
}

uint32_t BACnetIamService::getMaxApduAccepted(void) const {
	return this->maxApduLengthAccepted;
}

BACnetSegmentation const *BACnetIamService::getSegmentationSupported(void) const {
	return this->segmentationSupported;
}

uint16_t BACnetIamService::getVendorId(void) const {
	return this->vendorId;
}

void BACnetIamService::decode(BACnetBuffer &buff) {

	stringstream ss;

	uint8_t oct = buff.get_ui8();

	BACnetEnumSingle const *eNum = &BACnetEnumPDUChoice::getEnumByValue((oct >> 4));

	if(*eNum != BACnetEnumPDUChoice::UNCONFIRMED_REQUEST) {
		ss << "BACnetIamService::decode: PDU-TYPE (" <<  eNum->getValue() <<
				") does NOT equal BACnetEnumPDUChoice::UNCONFIRMED_REQUEST" << endl;
		throw std::invalid_argument(ss.str());
	}

	oct = buff.get_ui8();

	eNum = &BACnetEnumUnconfirmedService::getEnumByValue(oct);

	if(*eNum != BACnetEnumUnconfirmedService::I_AM) {
		ss << "BACnetIamService::decode: Unconfirmed Service Choice (" <<  eNum->getValue() <<
				") does NOT equal BACnetEnumUnconfirmedService::I_AM" << endl;
		throw std::invalid_argument(ss.str());
	}

	/** BACnet Object-Identifier */

	/** Gotta decode the tag first, so you will know what is next.*/
	BACnetTag tag = BACnetTag();
	tag.decode(buff);

	if(tag.getTagNumber() != BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER.getValue()) {
		ss << "BACnetIamService::decode: Invalid enumeration for BACnet Application Data Type while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected (12), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::APPLICATION_TAG) {
		ss << "BACnetIamService::decode: Invalid BACnet Tag Class while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected \"APPLICATION_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() != 4) {
		ss << "BACnetIamService::decode: Invalid BACnet Tag Length/Value/Type while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected (4), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	this->objectId.decode(buff);

	/** Maximum APDU Length Accepted (Unsigned) */

	tag.decode(buff);

	if(tag.getTagNumber() != BACnetEnumApplicationDataType::UNSIGNED_INTEGER.getValue()) {
		ss << "BACnetIamService::decode: Invalid enumeration for BACnet Application Data Type while "
				"decoding Maximum APDU Length Accepted." << endl;
		ss << "Expected (2), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::APPLICATION_TAG) {
		ss << "BACnetIamService::decode: Invalid BACnet Tag Class while "
				"decoding Maximum APDU Length Accepted." << endl;
		ss << "Expected \"APPLICATION_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() < 1 || tag.getLengthValueType() > 4) {
		ss << "BACnetIamService::decode: Invalid BACnet Tag Length/Value/Type while "
				"decoding Maximum APDU Length Accepted." << endl;
		ss << "Expected ( 1 thru 4), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	this->maxApduLengthAccepted = BACnetBuffer::decodeUnsignedInt(buff, tag.getLengthValueType());

	/** Segmentation Supported */

	tag.decode(buff);

	if(tag.getTagNumber() != BACnetEnumApplicationDataType::ENUMERATED.getValue()) {
		ss << "BACnetIamService::decode: Invalid enumeration for BACnet Application Data Type while "
				"decoding Segmentation Supported." << endl;
		ss << "Expected (9), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::APPLICATION_TAG) {
		ss << "BACnetIamService::decode: Invalid BACnet Tag Class while "
				"decoding Segmentation Supported." << endl;
		ss << "Expected \"APPLICATION_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() != 1) {
		ss << "BACnetIamService::decode: Invalid BACnet Tag Length/Value/Type while "
				"decoding Segmentation Supported." << endl;
		ss << "Expected (1), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	uint32_t enun = BACnetBuffer::decodeUnsignedInt(buff, tag.getLengthValueType());

	this->segmentationSupported = &BACnetEnumSegmentation::getEnumByValue(enun);

	/** Vendor ID*/

	tag.decode(buff);

	if(tag.getTagNumber() != BACnetEnumApplicationDataType::UNSIGNED_INTEGER.getValue()) {
		ss << "BACnetIamService::decode: Invalid enumeration for BACnet Application Data Type while "
				"decoding Vendor ID." << endl;
		ss << "Expected (2), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::APPLICATION_TAG) {
		ss << "BACnetIamService::decode: Invalid BACnet Tag Class while "
				"decoding Vendor ID." << endl;
		ss << "Expected \"APPLICATION_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() < 1 || tag.getLengthValueType() > 2) {
		ss << "BACnetIamService::decode: Invalid BACnet Tag Length/Value/Type while "
				"decoding Vendor ID." << endl;
		ss << "Expected (1 thru 2), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	this->vendorId = BACnetBuffer::decodeUnsignedInt(buff, tag.getLengthValueType());

}

std::ostream& operator<< (std::ostream &out, const BACnetIamService &bacIam)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.

    out << "BACnetIamService {" << endl;
    out << "\tObject-Id: " << bacIam.getObjectId()->getObjectType()->getName() << ":" <<
    		bacIam.getObjectId()->getObjectInstance().get_instance() << endl;
    out << "\tMax APDU Length Accepted: " << bacIam.getMaxApduAccepted() << endl;
    out << "\tSegmentation Supported: " << bacIam.getSegmentationSupported()->getName() << endl;
    out << "\tVendor-Id: " << bacIam.getVendorId() << endl;
    out << "} BACnetIamService" << endl;

    return out;
}

