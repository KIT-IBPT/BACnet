/*
 * BACnetTag.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: 8w4
 */

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <BACnetTag.h>

BACnetTag::BACnetTag()
:tagClass(0), tagNumber(0), tagLvt(0)
{

}

BACnetTag::BACnetTag(const BACnetTagClassChoice *tagClass, const uint8_t tagNumber, const uint32_t tagLvt) {

	if(tagNumber > MAX_TAG_NUMBER) {
		stringstream ss;
		ss << "\nError! BACnet Tag-Number (" << (unsigned int) tagNumber << ") is out of range. 0-" << MAX_TAG_NUMBER << endl;
		throw std::invalid_argument(ss.str());
	}
	this->tagClass = tagClass;
	this->tagNumber = tagNumber;
	this->tagLvt = tagLvt;
}

BACnetTag::~BACnetTag() {
	// TODO Auto-generated destructor stub
}

uint8_t BACnetTag::getTagNumber(void) const {
	return this->tagNumber;
}

uint32_t BACnetTag::getLengthValueType(void) const {
	return this->tagLvt;
}

const BACnetTagClassChoice *BACnetTag::getTagClass(void) const {
	return this->tagClass;
}

void BACnetTag::encode(BACnetBuffer &buff) {
	/**
	 *    7     6     5     4     3     2     1     0
	 * |-----|-----|-----|-----|-----|-----|-----|-----|
	 * |        Tag Number     |Class|Length/Value/Type|
	 * |-----|-----|-----|-----|-----|-----|-----|-----|
	 *
	 * */


	const int BIT3 = 0x08;

	/** For extended encodings with Tag-Number and Tag-Length/Value/Type*/
	uint8_t extendedData[10] = {};
	uint8_t *pExtData = &extendedData[0];

	/** ---- TAG NUMBER ---- */
	/**
	 * 20.2.1.2 Tag Number
	 *
	 * Tag numbers ranging from zero to 14 (inclusive) shall be encoded in the Tag Number field of
	 * the initial octet as a four bit binary integer with bit 7 the most significant bit.
	 *
	 * Tag numbers ranging from 15 to 254 (inclusive) shall be encoded by setting the Tag Number
	 * field of the initial octet to B'1111' and following the initial tag octet by an octet
	 * containing the tag number represented as an eight-bit binary integer with bit 7 the most
	 * significant bit.
	 *
	 * The encoding does not allow, nor does BACnet require, tag numbers larger than 254.
	 * The value B'11111111' of the subsequent octet is reserved by ASHRAE.
	 *
	 * */

	uint8_t initialOctet = encodeTagNumber(tagNumber);

	/** If tag number has been extended then the tag number follows the initial octet */
	if((initialOctet & EXTENDED_TAG_NUMBER) == EXTENDED_TAG_NUMBER) {
		*(pExtData++) = tagNumber;
	}

	/** ---- TAG CLASS ---- */
	/** TAG CLASS: The Class bit shall be zero for application tags. The Class bit shall be one for
	 * context specific tags.*/

	if(tagClass == NULL) {
		stringstream ss;
		ss << "ERROR! BACnetTag::encode Tag-class member is NULL or not set" << endl;
		throw std::invalid_argument(ss.str());
	}

	if(*tagClass == BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG) {
		initialOctet |= BIT3;
	}


	/** ---- TAG Length/Value/Type ----*/
	/**
	 *
	 * 20.2.1.3 Length/Value/Type
	 * The content of the length/value/type field of the initial octet distinguishes between primitive
	 * and constructed encodings and specifies the length or value of primitive data. A primitive encoding
	 * is one in which the data do not contain other tagged encodings. A constructed encoding is one in
	 * which the data do contain other tagged encodings.
	 *
	 * */

	/** Data length in octets ranging from zero to four (inclusive) shall be encoded in the length/value/type
	 * field of the initial octet as a three-bit binary integer with bit 2 the most significant bit.*/
	if(tagLvt >= 0x00 && tagLvt <= 0x04) {
		initialOctet |= tagLvt;
	}
	/**
	 * Data length in octets ranging from 5 to 253 (inclusive) shall be encoded by setting the length/value/type
	 * field of the initial octet to B'101' and following the initial tag octet or, if the Tag Number has been
	 * extended, following the Tag Number extension octet by an octet containing the data length represented as
	 * an eight-bit binary integer with bit 7 the most significant bit.
	 * */
	else if(tagLvt >= 0x05 && tagLvt <= 0xFD) {
		initialOctet |= 0x05;		/** B'101' */
		*(pExtData++) = tagLvt;
	}
	/**
	 * Data length in octets ranging from 254 to 65535 (inclusive) shall be encoded by setting the length/value/type
	 * field of the initial octet to B'101' and following the initial tag octet or, if the Tag Number has been
	 * extended, following the Tag Number extension octet by an octet containing D'254' and two additional octets
	 * whose value contains the data length represented as a 16-bit binary integer with the most significant octet
	 * first.
	 * */
	else if(tagLvt >= 0xfe && tagLvt <= 0xffff) {
		initialOctet |= 0x05;		/** B'101' */
		*(pExtData++) = 0xfe;		/** D'254'*/

		*(pExtData++) = (tagLvt & 0xff00) >> 8;
		*(pExtData++) = (tagLvt & 0x00ff);

	}
	/**
	 * Data length in octets ranging from 65536 to 2^32-1 (inclusive) shall be encoded by setting the
	 * length/value/type field of the initial octet to B'101' and following the initial tag octet or, if the Tag
	 * Number has been extended, following the Tag Number extension octet by an octet containing D'255' and four
	 * additional octets whose value contains the data length represented as a 32-bit binary integer with the most
	 * significant octet first.
	 * */
	else if(tagLvt >= 0x10000 && tagLvt <= 0xffffffffL) {
		initialOctet |= 0x05;		/** B'101' */
		*(pExtData++) = 0xfe;		/** D'255'*/

		*(pExtData++) = (tagLvt & 0xff000000) >> 24;
		*(pExtData++) = (tagLvt & 0x00ff0000) >> 16;
		*(pExtData++) = (tagLvt & 0x0000ff00) >> 8;
		*(pExtData++) = (tagLvt & 0x000000ff);

	}

	buff.encode_ui8(initialOctet);

	/** Did we have any extended data? */

	size_t exLen = pExtData - &extendedData[0];

	if(exLen) {
		buff.encode_buffer(&extendedData[0], 0, exLen);
	}

}

void BACnetTag::encodeContextTag(uint8_t tagNumb, uint32_t lvt, BACnetBuffer &buff) {

	this->tagNumber = tagNumb;
	this->tagClass = &BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG;
	this->tagLvt = lvt;

	encode(buff);
}

void BACnetTag::encodeApplicationTag(uint8_t tagNumb, uint32_t lvt, BACnetBuffer &buff) {

	this->tagNumber = tagNumb;
	this->tagClass = &BACnetEnumTagChoice::APPLICATION_TAG;
	this->tagLvt = lvt;

	encode(buff);
}

uint8_t BACnetTag::encodeTagNumber(uint8_t tagNumb) {

	uint8_t initialOctet = 0;

	/**
	 * 20.2.1.2 Tag Number
	 *
	 * Tag numbers ranging from zero to 14 (inclusive) shall be encoded in the Tag Number field of
	 * the initial octet as a four bit binary integer with bit 7 the most significant bit.
	 *
	 * Tag numbers ranging from 15 to 254 (inclusive) shall be encoded by setting the Tag Number
	 * field of the initial octet to B'1111' and following the initial tag octet by an octet
	 * containing the tag number represented as an eight-bit binary integer with bit 7 the most
	 * significant bit.
	 *
	 * The encoding does not allow, nor does BACnet require, tag numbers larger than 254.
	 * The value B'11111111' of the subsequent octet is reserved by ASHRAE.
	 *
	 * */

	if(tagNumb > MAX_TAG_NUMBER) {
		stringstream ss;
		ss << "ERROR! BACnetTag::encodeTagNumber: BACnet Tag-Number (" << (unsigned int) tagNumb << ") is out of range. 0-" << MAX_TAG_NUMBER << endl;
		throw std::invalid_argument(ss.str());
	}

	this->tagNumber = tagNumb;

	if(tagNumber < 15) {
		initialOctet = (tagNumber << 4);
	}
	else if(tagNumber < 255) {
		/** Holdup! We have an extended tag number*/
		initialOctet = EXTENDED_TAG_NUMBER;		/** 1111 0000*/
	}

	return initialOctet;
}

void BACnetTag::encodeOpeningTag(uint8_t tagNumb, BACnetBuffer &buff) {

	uint8_t initialOct = encodeTagNumber(tagNumb);

	/** 20.2.1.3.2 Constructed Data
	 * (a) an "opening" tag whose Tag Number field shall contain the value of the tag number,
	 * whose Class field shall indicate "context specific," and whose length/value/type field
	 * shall have the value B'110';
	 * */
	this->tagClass = &BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG;
	initialOct |= CONTEXT_SPECIFIC;

	this->tagLvt = OPENING_TAG;
	initialOct |= OPENING_TAG;

	buff.encode_ui8(initialOct);

	/** If tag number has been extended then the tag number follows the initial octet */
	if((initialOct & EXTENDED_TAG_NUMBER) == EXTENDED_TAG_NUMBER) {
		buff.encode_ui8(tagNumber);
	}

}

void BACnetTag::encodeClosingTag(uint8_t tagNumb, BACnetBuffer &buff) {

	uint8_t initialOct = encodeTagNumber(tagNumb);

	/** 20.2.1.3.2 Constructed Data
	 * (a) an "opening" tag whose Tag Number field shall contain the value of the tag number,
	 * whose Class field shall indicate "context specific," and whose length/value/type field
	 * shall have the value B'110';
	 * */
	this->tagClass = &BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG;
	initialOct |= CONTEXT_SPECIFIC;

	this->tagLvt = CLOSING_TAG;
	initialOct |= CLOSING_TAG;

	buff.encode_ui8(initialOct);

	/** If tag number has been extended then the tag number follows the initial octet */
	if((initialOct & EXTENDED_TAG_NUMBER) == EXTENDED_TAG_NUMBER) {
		buff.encode_ui8(tagNumber);
	}

}

void BACnetTag::decode(BACnetBuffer &buff) {
	/**
	 *    7     6     5     4     3     2     1     0
	 * |-----|-----|-----|-----|-----|-----|-----|-----|
	 * |        Tag Number     |Class|Length/Value/Type|
	 * |-----|-----|-----|-----|-----|-----|-----|-----|
	 *
	 * */

	stringstream ss;

	const int BIT3 = 0x08;

	const uint8_t INITIAL_OCT = buff.get_ui8();

	const uint8_t TNUM = (INITIAL_OCT & 0xF0) >> 4;

	const uint8_t LVT = (INITIAL_OCT & 0x07);

	this->tagClass = (INITIAL_OCT & BIT3) ? &BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG : &BACnetEnumTagChoice::APPLICATION_TAG;

	/** Is this BACnet Application Tag? */
	if(*this->tagClass == BACnetEnumTagChoice::APPLICATION_TAG) {

		/** 20.2.1.4 Application Tags
		    0 = NULL
		  	1 = Boolean
			2 = Unsigned Integer
			3 = Signed Integer (2's complement notation)
			4 = Real (ANSI/IEEE-754 floating point)
			5 = Double (ANSI/IEEE-754 double precision floating point)
			6 = Octet String
			7 = Character String
			8 = Bit String
			9 = Enumerated
			10 = Date
			11 = Time
			12 = BACnetObjectIdentifier
			13, 14, 15 = Reserved for ASHRAE
			*/

		/** BACnet Application Tags' tag numbers must be within range.*/
		if(TNUM > 12) {
			ss << "BACnetTag::decode: While decoding the tag number portion of a BACnet Application Class Tag"
					" the tag number (" << (unsigned int) TNUM << ") is out of range (0-12)" << endl;
			throw std::invalid_argument(ss.str());
		}

		this->tagNumber = TNUM;

	}
	else {
		/** 20.2.1.2 Tag Number
		 *
		 * Tag numbers ranging from zero to 14 (inclusive) shall be encoded in
		 * the Tag Number field of the initial octet as a four bit binary integer with bit 7 the most
		 * significant bit.
		 *
		 * Tag numbers ranging from 15 to 254 (inclusive) shall be encoded by setting the Tag Number
		 * field of the initial octet to B'1111' and following the initial tag octet by an octet
		 * containing the tag number represented as an eight-bit binary integer with bit 7 the most
		 * significant bit.
		 *
		 * The encoding does not allow, nor does BACnet require, tag numbers larger than 254.
		 * The value B'11111111' of the subsequent octet is reserved by ASHRAE.
		 * */

		/** Has tag number been extended? */
		if(TNUM == 0x0F) {
			uint8_t extdnum = buff.get_ui8();

			/** Check for validity: 15-254*/
			if(extdnum >= 0x0F && extdnum <= 0xFE) {
				this->tagNumber = extdnum;
			}
			else {
				ss << "BACnetTag::decode: While decoding the tag number portion of a BACnet Context Specific Class Tag"
						" the Extended tag number (" << (unsigned int) extdnum << ") is out of range (15-254)" << endl;
				throw std::invalid_argument(ss.str());
			}
		} else if(TNUM < 0x0F) {
			this->tagNumber = TNUM;
		}
		else {
			ss << "BACnetTag::decode: While decoding the tag number portion of a BACnet Context Specific Class Tag"
					" the tag number (" << (unsigned int) TNUM << ") is out of range (0-14)" << endl;
			throw std::invalid_argument(ss.str());
		}

	}

	/** ---- TAG Length/Value/Type ----*/

	/**
	 *
	 * 20.2.1.3 Length/Value/Type
	 * The content of the length/value/type field of the initial octet distinguishes between primitive
	 * and constructed encodings and specifies the length or value of primitive data. A primitive encoding
	 * is one in which the data do not contain other tagged encodings. A constructed encoding is one in
	 * which the data do contain other tagged encodings.
	 *
	 * */

	/** Data length in octets ranging from zero to four (inclusive) shall be encoded in the length/value/type
	 * field of the initial octet as a three-bit binary integer with bit 2 the most significant bit.*/

	if(LVT < 0x05) {
		this->tagLvt = LVT;
	}
	/**
	 * Length/Value/Type field has been extended.
	 * */
	else if(LVT == 0x05) {

		const uint8_t extdlvt = buff.get_ui8();

		/**
		 * Data length in octets ranging from 5 to 253 (inclusive) shall be encoded by setting the length/value/type
		 * field of the initial octet to B'101' and following the initial tag octet or, if the Tag Number has been
		 * extended, following the Tag Number extension octet by an octet containing the data length represented as
		 * an eight-bit binary integer with bit 7 the most significant bit.
		 * */
		if(extdlvt < 0xFE) {
			this->tagLvt = extdlvt;
		}
		/**
		 * Data length in octets ranging from 254 to 65535 (inclusive) shall be encoded by setting the length/value/type
		 * field of the initial octet to B'101' and following the initial tag octet or, if the Tag Number has been
		 * extended, following the Tag Number extension octet by an octet containing D'254' and two additional octets
		 * whose value contains the data length represented as a 16-bit binary integer with the most significant octet
		 * first.
		 * */
		else if(extdlvt == 0xFE) {
			this->tagLvt = buff.get_ui16();
		}
		/**
		 * Data length in octets ranging from 65536 to 2^32-1 (inclusive) shall be encoded by setting the
		 * length/value/type field of the initial octet to B'101' and following the initial tag octet or, if the Tag
		 * Number has been extended, following the Tag Number extension octet by an octet containing D'255' and four
		 * additional octets whose value contains the data length represented as a 32-bit binary integer with the most
		 * significant octet first.
		 * */
		else if(extdlvt == 0xFF) {
			this->tagLvt = buff.get_ui32();
		}
		else {
			ss << "BACnetTag::decode: While decoding the Length/Value/Type portion of a BACnet Tag"
					" the Extended L/V/T value (" << (unsigned int) extdlvt << ") is out of range (0-255)" << endl;
			throw std::invalid_argument(ss.str());
		}

	}
	/** 0x06 signifies Constructed data and is referred to as an opening tag*/
	else if(LVT == 0x06) {
		this->tagLvt = LVT;
	}
	/** 0x07 signifies Constructed data and is referred to as a closing tag*/
	else if(LVT == 0x07) {
		this->tagLvt = LVT;
	}
	else {
		ss << "BACnetTag::decode: While decoding the Length/Value/Type portion of a BACnet Tag"
				" L/V/T value (" << (unsigned int) LVT << ") is out of range (0-5)" << endl;
		throw std::invalid_argument(ss.str());
	}

}

uint8_t const *BACnetTag::decode(uint8_t const *buff) {
	/**
	 *    7     6     5     4     3     2     1     0
	 * |-----|-----|-----|-----|-----|-----|-----|-----|
	 * |        Tag Number     |Class|Length/Value/Type|
	 * |-----|-----|-----|-----|-----|-----|-----|-----|
	 *
	 * */

	if(buff == NULL) {
		return buff;
	}

	stringstream ss;

	const int BIT3 = 0x08;

	const uint8_t INITIAL_OCT = (*buff++);

	const uint8_t TNUM = (INITIAL_OCT & 0xF0) >> 4;

	const uint8_t LVT = (INITIAL_OCT & 0x07);

	this->tagClass = (INITIAL_OCT & BIT3) ? &BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG : &BACnetEnumTagChoice::APPLICATION_TAG;

	/** Is this BACnet Application Tag? */
	if(*this->tagClass == BACnetEnumTagChoice::APPLICATION_TAG) {

		/** 20.2.1.4 Application Tags
		    0 = NULL
		  	1 = Boolean
			2 = Unsigned Integer
			3 = Signed Integer (2's complement notation)
			4 = Real (ANSI/IEEE-754 floating point)
			5 = Double (ANSI/IEEE-754 double precision floating point)
			6 = Octet String
			7 = Character String
			8 = Bit String
			9 = Enumerated
			10 = Date
			11 = Time
			12 = BACnetObjectIdentifier
			13, 14, 15 = Reserved for ASHRAE
		 */

		/** BACnet Application Tags' tag numbers must be within range.*/
		if(TNUM > 12) {
			ss << "BACnetTag::decode: While decoding the tag number portion of a BACnet Application Class Tag"
					" the tag number (" << (unsigned int) TNUM << ") is out of range (0-12)" << endl;
			throw std::invalid_argument(ss.str());
		}

		this->tagNumber = TNUM;

	}
	else {
		/** 20.2.1.2 Tag Number
		 *
		 * Tag numbers ranging from zero to 14 (inclusive) shall be encoded in
		 * the Tag Number field of the initial octet as a four bit binary integer with bit 7 the most
		 * significant bit.
		 *
		 * Tag numbers ranging from 15 to 254 (inclusive) shall be encoded by setting the Tag Number
		 * field of the initial octet to B'1111' and following the initial tag octet by an octet
		 * containing the tag number represented as an eight-bit binary integer with bit 7 the most
		 * significant bit.
		 *
		 * The encoding does not allow, nor does BACnet require, tag numbers larger than 254.
		 * The value B'11111111' of the subsequent octet is reserved by ASHRAE.
		 * */

		/** Has tag number been extended? */
		if(TNUM == 0x0F) {
			uint8_t extdnum = (*buff++);

			/** Check for validity: 15-254*/
			if(extdnum >= 0x0F && extdnum <= 0xFE) {
				this->tagNumber = extdnum;
			}
			else {
				ss << "BACnetTag::decode: While decoding the tag number portion of a BACnet Context Specific Class Tag"
						" the Extended tag number (" << (unsigned int) extdnum << ") is out of range (15-254)" << endl;
				throw std::invalid_argument(ss.str());
			}
		} else if(TNUM < 0x0F) {
			this->tagNumber = TNUM;
		}
		else {
			ss << "BACnetTag::decode: While decoding the tag number portion of a BACnet Context Specific Class Tag"
					" the tag number (" << (unsigned int) TNUM << ") is out of range (0-14)" << endl;
			throw std::invalid_argument(ss.str());
		}

	}

	/** ---- TAG Length/Value/Type ----*/

	/**
	 *
	 * 20.2.1.3 Length/Value/Type
	 * The content of the length/value/type field of the initial octet distinguishes between primitive
	 * and constructed encodings and specifies the length or value of primitive data. A primitive encoding
	 * is one in which the data do not contain other tagged encodings. A constructed encoding is one in
	 * which the data do contain other tagged encodings.
	 *
	 * */

	/** Data length in octets ranging from zero to four (inclusive) shall be encoded in the length/value/type
	 * field of the initial octet as a three-bit binary integer with bit 2 the most significant bit.*/

	if(LVT < 0x05) {
		this->tagLvt = LVT;
	}
	/**
	 * Length/Value/Type field has been extended.
	 * */
	else if(LVT == 0x05) {

		const uint8_t extdlvt = (*buff++);

		/**
		 * Data length in octets ranging from 5 to 253 (inclusive) shall be encoded by setting the length/value/type
		 * field of the initial octet to B'101' and following the initial tag octet or, if the Tag Number has been
		 * extended, following the Tag Number extension octet by an octet containing the data length represented as
		 * an eight-bit binary integer with bit 7 the most significant bit.
		 * */
		if(extdlvt < 0xFE) {
			this->tagLvt = extdlvt;
		}
		/**
		 * Data length in octets ranging from 254 to 65535 (inclusive) shall be encoded by setting the length/value/type
		 * field of the initial octet to B'101' and following the initial tag octet or, if the Tag Number has been
		 * extended, following the Tag Number extension octet by an octet containing D'254' and two additional octets
		 * whose value contains the data length represented as a 16-bit binary integer with the most significant octet
		 * first.
		 * */
		else if(extdlvt == 0xFE) {
			buff = BACnetBuffer::get_ui16(buff, this->tagLvt);
		}
		/**
		 * Data length in octets ranging from 65536 to 2^32-1 (inclusive) shall be encoded by setting the
		 * length/value/type field of the initial octet to B'101' and following the initial tag octet or, if the Tag
		 * Number has been extended, following the Tag Number extension octet by an octet containing D'255' and four
		 * additional octets whose value contains the data length represented as a 32-bit binary integer with the most
		 * significant octet first.
		 * */
		else if(extdlvt == 0xFF) {
			buff = BACnetBuffer::get_ui32(buff, this->tagLvt);
		}
		/** 0x06 signifies Constructed data and is referred to as an opening tag*/
		else if(LVT == 0x06) {
			this->tagLvt = LVT;
		}
		/** 0x07 signifies Constructed data and is referred to as a closing tag*/
		else if(LVT == 0x07) {
			this->tagLvt = LVT;
		}
		else {
			ss << "BACnetTag::decode: While decoding the Length/Value/Type portion of a BACnet Tag"
					" the Extended L/V/T value (" << (unsigned int) extdlvt << ") is out of range (0-255)" << endl;
			throw std::invalid_argument(ss.str());
		}

	}
	else {
		ss << "BACnetTag::decode: While decoding the Length/Value/Type portion of a BACnet Tag"
				" L/V/T value (" << (unsigned int) LVT << ") is out of range (0-5)" << endl;
		throw std::invalid_argument(ss.str());
	}
	return buff;
}

std::ostream& operator<< (std::ostream &out, const BACnetTag &bactag)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.

    out << "BACnetTag {" << endl;
    if(bactag.getTagClass() && bactag.getTagClass() == &BACnetEnumTagChoice::APPLICATION_TAG) {
    	BACnetApplicationDataTypeChoice const *appT = &BACnetEnumApplicationDataType::getEnumByValue(bactag.getTagNumber());
    	out << "\tApplication Tag Type: " << appT->getName() << ":" << (unsigned int) bactag.getTagNumber() << endl;
    }
    else
    	out << "\tTag Number: " << (unsigned int) bactag.getTagNumber() << endl;
    out << "\tTag Class: " << bactag.getTagClass()->getName() << endl;
    out << "\tTag Length/Value/Type: " << bactag.getLengthValueType() << endl;
    out << "\t} BACnetTag" << endl;

    return out;
}

