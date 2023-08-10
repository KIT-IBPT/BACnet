/*
 * BACnetErrorPdu.cpp
 *
 *  Created on: Aug 9, 2018
 *      Author: 8w4
 */

#include "BACnetErrorPdu.h"
#include "BACnetEnumPDUChoice.h"
#include "BACnetTag.h"

#include <sstream>
#include <cstring>
#include <stdexcept>

BACnetErrorPdu::BACnetErrorPdu()
:invokeId(0), errChoice(NULL), errClass(NULL), errCode(NULL)
{
	// TODO Auto-generated constructor stub

}

BACnetErrorPdu::BACnetErrorPdu(const BACnetErrorPdu &rhs) {
	this->invokeId = rhs.invokeId;
	this->errChoice = rhs.errChoice;
	this->errClass = rhs.errClass;
	this->errCode = rhs.errCode;
}

BACnetErrorPdu::~BACnetErrorPdu() {
	// TODO Auto-generated destructor stub
}

BACnetErrorPdu &BACnetErrorPdu::operator = (const BACnetErrorPdu &rhs) {
	if(this != &rhs) {
		this->invokeId = rhs.invokeId;
		this->errChoice = rhs.errChoice;
		this->errClass = rhs.errClass;
		this->errCode = rhs.errCode;
	}
	return *this;
}

void BACnetErrorPdu::clearData(void) {
	this->invokeId = 0;
	errChoice = NULL;
	errClass = NULL;
	errCode = NULL;
}

void BACnetErrorPdu::decode(BACnetBuffer &buff) {

	/**
	 * BACnet-Error-PDU ::= SEQUENCE {
			pdu-type				[0] Unsigned (0..15), -- 5 for this PDU type
			reserved				[1] Unsigned (0..15), -- must be set to zero
			original-invokeID		[2] Unsigned (0..255),
			error-choice			[3] BACnetConfirmedServiceChoice,
			error					[4] BACnet-Error
			-- Context specific tags 0..4 are NOT used in header encoding
		}
	 * */
	stringstream ss;

	/** Get the PDU-Type. It must be a ERROR*/
	uint8_t oct = buff.get_ui8();

	BACnetPDUChoice const &PDU_TYPE = BACnetEnumPDUChoice::getEnumByValue((oct >> 4));

	if(PDU_TYPE != BACnetEnumPDUChoice::ERROR) {
		ss << "ERROR! BACnetErrorPdu::decode(BACnetBuffer &buff): PDU-TYPE (" <<  PDU_TYPE.getValue() <<
				") does NOT equal BACnetEnumPDUChoice::ERROR" << endl;
		throw std::invalid_argument(ss.str());
	}

	this->invokeId = buff.get_ui8();

	this->errChoice = &BACnetEnumConfSvc::getEnumByValue(buff.get_ui8());

	/** The remaining elements are tagged elements*/
	BACnetTag tag;
	tag.decode(buff);

	/** We don't have to check that tag.getTagClass() isn't NULL before we use it here because it gets set in tag.decode
	 * and if there was an issue in tag.decode then it will throw and this next line doesn't matter anyway.*/
	if(*tag.getTagClass() != BACnetEnumTagChoice::APPLICATION_TAG) {
		ss << "BACnetErrorPdu::decode(BACnetBuffer &buff): Invalid BACnet Tag Class while "
				"decoding BACnet-Error-Class." << endl;
		ss << "Expected \"APPLICATION_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getTagNumber() != BACnetEnumApplicationDataType::ENUMERATED.getValue()) {
		ss << "BACnetErrorPdu::decode(BACnetBuffer &buff): Invalid tag number while "
				"decoding BACnet-Error-Class." << endl;
		ss << "Expected (9), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() < 1 || tag.getLengthValueType() > 3) {
		ss << "BACnetErrorPdu::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
				"decoding BACnet-Error-Class." << endl;
		ss << "Expected (Greater than 1 but less than 3), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	/**
	 *
	 * */
	switch (tag.getLengthValueType()) {
	case 1:
		this->errClass = &BACnetEnumErrorClass::getEnumByValue(buff.get_ui8());
		break;
	case 2:
		this->errClass = &BACnetEnumErrorClass::getEnumByValue(buff.get_ui16());
		break;
	case 3:
		this->errClass = &BACnetEnumErrorClass::getEnumByValue(buff.get_ui24());
		break;
	default:
		/** Oh, No! This is bad. How could we end up here after we already check for this
		 * condition above? Throw again, geez...*/
		ss << "BACnetErrorPdu::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
		"decoding BACnet-Error-Class." << endl;
		ss << "Expected (Greater than 1 and less than 3), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
		break;
	}

	tag.decode(buff);

	/** We don't have to check that tag.getTagClass() isn't NULL before we use it here because it gets set in tag.decode
	 * and if there was an issue in tag.decode then it will throw and this next line doesn't matter anyway.*/
	if(*tag.getTagClass() != BACnetEnumTagChoice::APPLICATION_TAG) {
		ss << "BACnetErrorPdu::decode(BACnetBuffer &buff): Invalid BACnet Tag Class while "
				"decoding BACnet-Error-Code." << endl;
		ss << "Expected \"APPLICATION_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getTagNumber() != BACnetEnumApplicationDataType::ENUMERATED.getValue()) {
		ss << "BACnetErrorPdu::decode(BACnetBuffer &buff): Invalid tag number while "
				"decoding BACnet-Error-Code." << endl;
		ss << "Expected (9), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() < 1 || tag.getLengthValueType() > 3) {
		ss << "BACnetErrorPdu::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
				"decoding BACnet-Error-Code." << endl;
		ss << "Expected (Greater than 1 but less than 3), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	/**
	 *
	 * */
	switch (tag.getLengthValueType()) {
	case 1:
		this->errCode = &BACnetEnumErrorCode::getEnumByValue(buff.get_ui8());
		break;
	case 2:
		this->errCode = &BACnetEnumErrorCode::getEnumByValue(buff.get_ui16());
		break;
	case 3:
		this->errCode = &BACnetEnumErrorCode::getEnumByValue(buff.get_ui24());
		break;
	default:
		/** Oh, No! This is bad. How could we end up here after we already check for this
		 * condition above? Throw again, geez...*/
		ss << "BACnetErrorPdu::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
		"decoding BACnet-Error-Code." << endl;
		ss << "Expected (Greater than 1 and less than 3), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
		break;
	}

}

uint8_t BACnetErrorPdu::getInvokeId(void) const {
	return this->invokeId;
}

BACnetConfSvcChoice const *BACnetErrorPdu::getErrorChoice(void) const {
	return this->errChoice;
}

BACnetErrClassChoice const *BACnetErrorPdu::getErrorClass(void) const {
	return this->errClass;
}

BACnetErrCodeChoice const *BACnetErrorPdu::getErrorCode(void) const {
	return this->errCode;
}

string BACnetErrorPdu::toString(void) const {

	stringstream ss;

	ss << "BACnet-Error {" << endl;

	ss << "Error-Invoke-Id: \"" << (unsigned int) this->invokeId << "\"" << endl;

	ss << "Error-Choice: ";
	if(this->errChoice) {
		ss << "\"" << this->errChoice->getName() << "\"" << endl;
	}
	else
		ss << "isNull" << endl;

	ss << "Error-Class: ";
	if(this->errClass) {
		ss << "\"" << this->errClass->getName() << "\"" << endl;
	}
	else
		ss << "isNull" << endl;

	ss << "Error-Code: ";
	if(this->errCode) {
		ss << "\"" << this->errCode->getName() << "\"" << endl;
	}
	else
		ss << "isNull" << endl;

	ss << "} BACnet-Error" << endl;

	return ss.str();
}

