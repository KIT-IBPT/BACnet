/*
 * BACnetReadPropAck.cpp
 *
 *  Created on: Aug 2, 2018
 *      Author: 8w4
 */

#include "BACnetReadPropAck.h"

#include <sstream>
#include <cstring>
#include <stdexcept>

#include "BACnetTag.h"
#include "BACnetDevice.h"

BACnetReadPropAck::BACnetReadPropAck()
:objId(), propId(NULL), arrayIndex(-1), appdata()
{
	// TODO Auto-generated constructor stub

}

BACnetReadPropAck::~BACnetReadPropAck() {
	// TODO Auto-generated destructor stub
}

void BACnetReadPropAck::decode(BACnetBuffer &buff) {

	stringstream ss;
	const uint8_t BIT3 = 0x08;

	/**
	 * Read-Property-Ack: Are all context specific tags...
	 *
	 * ReadProperty-ACK ::= SEQUENCE {
	 * objectIdentifier				[0] BACnetObjectIdentifier,
	 * propertyIdentifier			[1] BACnetPropertyIdentifier,
	 * propertyArrayIndex			[2] Unsigned OPTIONAL,--used only with array datatype
	 * 									-- if omitted with an array the entire array is referenced
	 * propertyValue				[3] ABSTRACT-SYNTAX.&Type
	 * }
	 *
	 * */

	/** Context tag [0] must be BACnet Object-Identifier */

	/** Gotta decode the tag first, so you will know what is next.*/
	BACnetTag tag = BACnetTag();
	tag.decode(buff);

	if(tag.getTagNumber() != 0) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid tag number for context specific tag [0], while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected (0), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	/** We don't have to check that tag.getTagClass() isn't NULL before we use it here because it gets set in tag.decode
	 * and if there was an issue in tag.decode then it will throw and this next line doesn't matter anyway.*/
	if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Class while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() != 4) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
				"decoding BACnet Object Identifier." << endl;
		ss << "Expected (4), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	this->objId.decode(buff);

	/** Next: Context tag [1] must be BACnet BACnetPropertyIdentifier */

	/** get the next tag/octet*/
	tag.decode(buff);

	if(tag.getTagNumber() != 1) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid tag number for context specific tag [1], while "
				"decoding BACnet Property Identifier." << endl;
		ss << "Expected (1), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Class while "
				"decoding BACnet Property Identifier." << endl;
		ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() < 1 || tag.getLengthValueType() > 3) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
				"decoding BACnet Property Identifier." << endl;
		ss << "Expected (Greater than 1 but less than 3), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	/** There are a lot of BACnet property values... this could be from 1 to 3 octets...
	 * the standard says 0-4194303*/
	switch (tag.getLengthValueType()) {
	case 1:
		this->propId = &BACnetEnumPropertyIdentifier::getEnumByValue(buff.get_ui8());
		break;
	case 2:
		this->propId = &BACnetEnumPropertyIdentifier::getEnumByValue(buff.get_ui16());
		break;
	case 3:
		this->propId = &BACnetEnumPropertyIdentifier::getEnumByValue(buff.get_ui24());
		break;
	default:
		/** Oh, No! This is bad. How could we end up here after we already check for this
		 * condition above? Throw again, geez...*/
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
		"decoding BACnet Property Identifier." << endl;
		ss << "Expected (Greater than 1 and less than 3), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
		break;
	}

	if(BACnet_verbosity > 1) {
		cout << "tag.getLengthValueType(): " << tag.getLengthValueType() << "this->propId->getName(): " << this->propId->getName() << endl;
	}

	/** get the next tag/octet*/
	tag.decode(buff);

	/** The next tag number must be a 2 or a 3*/
	if(tag.getTagNumber() < 2 || tag.getTagNumber() > 3) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid tag number while "
				"decoding BACnet context specific tag." << endl;
		ss << "Expected (2) or (3), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	/** Next: Context tag [2] is optional but if present then must be BACnet propertyArrayIndex */

	/** If tag number is equal to 2 then the optional array index is being used and we have to decode it...*/
	if(tag.getTagNumber() == 2) {

		if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
			ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Class while "
					"decoding BACnet property array index." << endl;
			ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
			ss << tag << endl;
			throw std::invalid_argument(ss.str());
		}

		if(tag.getLengthValueType() < 1 || tag.getLengthValueType() > 4) {
			ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
					"decoding BACnet property array index." << endl;
			ss << "Expected (1-4), but decoded (" << tag.getLengthValueType() << ")." << endl;
			ss << tag << endl;
			throw std::invalid_argument(ss.str());
		}

		switch (tag.getLengthValueType()) {
		case 1:
			this->arrayIndex = buff.get_ui8();
			break;
		case 2:
			this->arrayIndex = buff.get_ui16();
			break;
		case 3:
			this->arrayIndex = buff.get_ui24();
			break;
		case 4:
			this->arrayIndex = buff.get_ui32();
			break;
		default:
			/** Oh, No! This is bad. How could we end up here after we already check for this
			 * condition above? Throw again, geez...*/
			ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
			"decoding array index." << endl;
			ss << "Expected 1-4, but decoded (" << tag.getLengthValueType() << ")." << endl;
			ss << tag << endl;
			throw std::invalid_argument(ss.str());
			break;
		}

		/** get the next tag/octet*/
		tag.decode(buff);
	}

	/** Next: Context tag [3] (The opening tag with a signature of 0x3E) must be a
	 * BACnet propertyValue (ABSTRACT-SYNTAX.&Type)
	 * */

	if(tag.getTagNumber() != 3) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid tag number for context specific tag [3], while "
				"decoding opening tag for BACnet propertyValue." << endl;
		ss << "Expected (3), but decoded (" << (unsigned int) tag.getTagNumber() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tag.getTagClass() != BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Class while "
				"decoding opening tag for BACnet propertyValue." << endl;
		ss << "Expected \"CONTEXT_SPECIFIC_TAG\", but decoded \"" << tag.getTagClass()->getName() << "\"." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(tag.getLengthValueType() != 6) {
		ss << "BACnetReadPropAck::decode(BACnetBuffer &buff): Invalid BACnet Tag Length/Value/Type while "
				"decoding opening tag for BACnet propertyValue." << endl;
		ss << "Expected (6), but decoded (" << tag.getLengthValueType() << ")." << endl;
		ss << tag << endl;
		throw std::invalid_argument(ss.str());
	}

	if(BACnet_verbosity > 1) {
		cout << "Decoded tag all the way down to abstract type! " << (unsigned int) buff.peek() << endl;
	}

	/** Now let's get to the value...*/

	/** get the next tag/octet*/
	uint8_t oct = buff.peek();
	BACnetTagClassChoice const &TAG_CHOICE = (oct & BIT3) ? BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG : BACnetEnumTagChoice::APPLICATION_TAG;

	if(TAG_CHOICE == BACnetEnumTagChoice::APPLICATION_TAG) {

		BACnetApplicationData ackData;
		uint8_t const CLOSING_TAGG = 0x3F;
		/** Could be a list of items so loop until the magic flag (0x3F) is found*/
		while(oct != CLOSING_TAGG) {
			ackData.decode(buff);
			//dataList.push_back(ackData);
			this->appdata.push_back(ackData);
			oct = buff.peek();
		}
	}

	/** Is there any more data? Peek at the next octet. If it is 0x3F then that signifies a closing tag
	 * and we are done. If next octet is not equal to 0x3F then there is more data and you need to figure
	 * out how to handle that...*/

}

BACnetObjIdentifier const &BACnetReadPropAck::getObjectId(void) const {
	return this->objId;
}

BACnetPropertyType const *BACnetReadPropAck::getPropertyId(void) const {
	return this->propId;
}

int BACnetReadPropAck::getArrayIndex(void) const {
	return this->arrayIndex;
}

appDataList_t &BACnetReadPropAck::getAppDataList(void) {
	return this->appdata;
}





