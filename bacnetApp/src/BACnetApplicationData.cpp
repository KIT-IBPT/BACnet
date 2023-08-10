/*
 * BACnetApplicationData.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: 8w4
 */

#include "BACnetApplicationData.h"
#include "BACnetTag.h"
#include "BACnetBitString.h"
#include "BACnetDevice.h"

#include <stdint.h>
#include <string>
#include <cstring>
#include <sstream>
#include <stdexcept>


BACnetApplicationData::BACnetApplicationData()
:type(NULL), dataLength(0)
{
	/** Zero it out.*/
	clearData();
}

BACnetApplicationData::~BACnetApplicationData() {
	// TODO Auto-generated destructor stub
}

void BACnetApplicationData::clearData(void) {
	/** Zero it out.*/
	this->type = NULL;
	this->dataLength = 0;
	memset(data, 0, MAX_APP_DATA_LEN);
}

void BACnetApplicationData::decode(BACnetBuffer &buff) {

	if(BACnet_verbosity > 1) {
		cout << "BACnetApplicationData::decode!" << endl;
	}

	stringstream ss;
	BACnetTag tag;

	tag.decode(buff);

	if(*tag.getTagClass() != BACnetEnumTagChoice::APPLICATION_TAG) {
		ss << "BACnetApplicationData::decode(BACnetBuffer &buff): Invalid BACnet Tag Class while "
				"decoding application data for BACnet." << endl;
		ss << "Expected \"APPLICATION_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}


	/** Ok, it is an application tag now what kind of application data-type is it?*/
	BACnetApplicationDataTypeChoice const &DATA_TYPE_CHOICE = BACnetEnumApplicationDataType::getEnumByValue(tag.getTagNumber());

	if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::NNULL) {
		this->type = &BACnetEnumApplicationDataType::NNULL;
		this->dataLength = tag.getLengthValueType();
		this->data[0] = tag.getLengthValueType();

		if(BACnet_verbosity > 1) {
			cout << "This is a NULL value!" << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}
	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::BOOLEAN) {
		this->type = &BACnetEnumApplicationDataType::BOOLEAN;
		this->dataLength = tag.getLengthValueType();
		this->data[0] = tag.getLengthValueType();

		if(BACnet_verbosity > 1) {
			cout << "This is a BOOLEAN value!" << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}
	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::UNSIGNED_INTEGER) {

		this->type = &BACnetEnumApplicationDataType::UNSIGNED_INTEGER;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {
			cout << "This is an UNSIGNED_INTEGER value!" << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}

	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::SIGNED_INTEGER) {

		this->type = &BACnetEnumApplicationDataType::SIGNED_INTEGER;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {
			cout << "This is an SIGNED_INTEGER value!" << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}

	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::REAL) {

		this->type = &BACnetEnumApplicationDataType::REAL;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {
			cout << "This is a REAL value!" << endl;

			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}


	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::DOUBLE) {
		ss << "BACnetApplicationData::decode(BACnetBuffer &buff): Data-type-choice decoded is equal to DOUBLE, "
				"and I do not support type DOUBLE yet." << endl;
		throw std::invalid_argument(ss.str());
	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::OCTET_STRING) {
		ss << "BACnetApplicationData::decode(BACnetBuffer &buff): Data-type-choice decoded is equal to OCTET_STRING, "
				"and I do not support type OCTET_STRING yet." << endl;
		throw std::invalid_argument(ss.str());
	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::CHARACTER_STRING) {

		this->type = &BACnetEnumApplicationDataType::CHARACTER_STRING;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {
			cout << "This is a CHARACTER_STRING value!" << endl;
			cout << "The length of this bit string is: " << tag.getLengthValueType() << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}

	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::BIT_STRING) {

		this->type = &BACnetEnumApplicationDataType::BIT_STRING;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {

			cout << "This is a bit string value!" << endl;
			cout << "The length of this bit string is: " << tag.getLengthValueType() << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}


	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::ENUMERATED) {

		this->type = &BACnetEnumApplicationDataType::ENUMERATED;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {

			cout << "This is an ENUMERATED value!" << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}


	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::DATE) {

		this->type = &BACnetEnumApplicationDataType::DATE;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {

			cout << "This is an DATE value!" << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}

	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::TIME) {

		this->type = &BACnetEnumApplicationDataType::TIME;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {

			cout << "This is an TIME value!" << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}

	}
	else if(DATA_TYPE_CHOICE == BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER) {

		this->type = &BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER;
		this->dataLength = tag.getLengthValueType();

		for(uint8_t i=0; i<this->dataLength; i++) {
			this->data[i] = buff.get_ui8();
		}

		if(BACnet_verbosity > 1) {

			cout << "This is a BACNET_OBJECT_IDENTIFIER value!" << endl;
			cout << "Type: " << this->type->getName() << ", Len: " << this->dataLength << endl;
			cout << "Data: " << buff.hex_dump(this->data, 0, this->dataLength) << endl;
		}
	}
	else {
		ss << "BACnetApplicationData::decode(BACnetBuffer &buff): Data-type-choice decoded is not defined." << endl;
		throw std::invalid_argument(ss.str());
	}
}

BACnetApplicationDataTypeChoice const *BACnetApplicationData::getAppDataType(void) const {
	return this->type;
}

uint32_t BACnetApplicationData::getDataLength(void) const {
	return this->dataLength;
}

uint8_t const *BACnetApplicationData::getData(void) const {
	return this->data;
}



