/*
 * BACnetBuffer.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: 8w4
 */

#include "BACnetBuffer.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <iomanip>

BACnetBuffer::BACnetBuffer() {
	/** Zero it out.*/
	clear_buffer();
}

BACnetBuffer::BACnetBuffer(const BACnetBuffer &buff) {
	/** Zero it out.*/
	clear_buffer();
	encode_buffer(buff.getBeginAddr(), 0, buff.get_fill_length());
	pFill = &buffer[0] + buff.get_fill_position();
	pRead = &buffer[0] + buff.get_read_position();
}

BACnetBuffer::~BACnetBuffer() {
	// TODO Auto-generated destructor stub
}

size_t BACnetBuffer::get_remaining() {
		return (&buffer[MAX_BUFFER_LEN] - pFill);
}

/** throws std::invalid_argument if index is out of bounds...
 * If inserting a new value the end pointer is not moved. There
 * is no way to distinguish between a read and a write to set the
 * end pointer.*/
uint8_t &BACnetBuffer::operator[](const int index) {

	stringstream ss;

	if(index < 0 || index > (MAX_BUFFER_LEN-1)) {
		ss << "BACnetBuffer::operator[](const int index):\n"
				"\tArray index (" << index << ") out of bounds" << endl;
		throw std::invalid_argument(ss.str());
	}

	return buffer[index];
}

/** Fill Size*/
size_t BACnetBuffer::get_fill_size(void) const {
	return get_fill_length();
}

size_t BACnetBuffer::get_fill_length(void) const {
	return (pFill - &buffer[0]);
}

int BACnetBuffer::get_fill_position(void) const {
	return (pFill - &buffer[0]);
}

/** Read Size*/
size_t BACnetBuffer::get_read_size(void) const {
	return get_read_length();
}

size_t BACnetBuffer::get_read_length(void) const {
	return (pFill - pRead);
}

int BACnetBuffer::get_read_position(void) const {
	return (pRead - &buffer[0]);
}

void BACnetBuffer::rewind_read_pointer(void) {

	pRead = &buffer[0];
}

void BACnetBuffer::rewind_fill_pointer(void) {

	pFill = &buffer[0];
}

void BACnetBuffer::rewind_all(void) {
	/** Align pointers...*/
	pFill = &buffer[0];
	pRead = &buffer[0];
}

void BACnetBuffer::clear_buffer(void) {
	/** Zero it out.*/
	memset(buffer, 0, MAX_BUFFER_LEN);

	/** Align pointers...*/
	pFill = &buffer[0];
	pRead = &buffer[0];
}

/** Throws std::invalid_argument */
void BACnetBuffer::operator +=(const uint8_t val) {

	stringstream ss;

	if(get_remaining() < 1) {
		ss << "BACnetBuffer::operator +=(const uint8_t val):\n"
				"\tBuffer is full. Buffer end pointer (" << (void *) pFill <<
				") and &buffer[MAX_BUFFER_LEN] (" << (void *)&buffer[MAX_BUFFER_LEN] << ")" << endl;
		throw std::invalid_argument(ss.str());
	}
	*(pFill++) = val;
}

string BACnetBuffer::hex_dump(void) const {

	stringstream ss;

	BACnetBuffer::iterator it;

	/** Initial line is zero*/
	ss << "0000: ";

	/** Use iterator to loop through the buffer.*/
	//TODO check against last element?
	for(it = begin(); it < end(); it++) {

		/** Format it and print it in Hex.*/
		ss << "0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) *it;

		/** Every 16th element needs to be on a new line.*/
		if((it + 1) != end()) {
			if(((it-begin())+1) % 16 == 0) {
				ss << "\n" << std::setfill('0') << std::setw(4) << std::hex << ((it-begin())+1) << ": ";
			}
			/** Every 8th element needs a double space.*/
			else if(((it-begin())+1) % 8 == 0) {
				ss << "  ";
			}
			/** Put space between each element.*/
			else {
				ss << " ";
			}
		}
		else
			ss << endl;
	}

	return ss.str();
}

string BACnetBuffer::hex_dump(uint8_t const * const buff, unsigned int const pos, size_t const len) {

	stringstream ss;

	/** Initial line is zero*/
	ss << "0000: ";

	/** loop through the buffer.*/
	for(size_t i = 0; i < len; i++) {
		/** Format it and print it in Hex.*/
		ss << "0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) buff[(i+pos)];

		/** Every 16th element needs to be on a new line.*/
		if((i + 1) < len) {
			if((i+1) % 16 == 0) {
				ss << "\n" << std::setfill('0') << std::setw(4) << std::hex << (i+1) << ": ";
			}
			/** Every 8th element needs a double space.*/
			else if((i+1) % 8 == 0) {
				ss << "  ";
			}
			/** Put space between each element.*/
			else {
				ss << " ";
			}
		}
		else
			ss << endl;
	}

	return ss.str();
}

void BACnetBuffer::encode_ui8(uint8_t const val) {

	/** Check for out of bounds...*/
	if(get_remaining() < 1) {
		stringstream ss;
		ss << "BACnetBuffer::encode_ui8(uint8_t const val):\n"
				"\tCould not encode buffer. Insufficient space remaining ("
				<< get_remaining() << ")" << endl;
		throw std::invalid_argument(ss.str());
	}

	*(pFill++) = (uint8_t) (val & 0xff);
}

void BACnetBuffer::encode_ui16(uint16_t const val) {

	/** Check for out of bounds...*/
	if(get_remaining() < 2) {
		stringstream ss;
		ss << "BACnetBuffer::encode_ui16(uint16_t const val):\n"
				"\tCould not encode buffer. Insufficient space remaining ("
				<< get_remaining() << ")" << endl;
		throw std::invalid_argument(ss.str());
	}


	*(pFill++) = (uint8_t) ((val & 0xff00) >> 8);
	*(pFill++) = (uint8_t) (val & 0x00ff);
}

void BACnetBuffer::encode_ui24(uint32_t const val) {

	/** Check for out of bounds...*/
	if(get_remaining() < 3) {
		stringstream ss;
		ss << "BACnetBuffer::encode_ui24(uint32_t const val):\n"
				"\tCould not encode buffer. Insufficient space remaining ("
				<< get_remaining() << ")" << endl;
		throw std::invalid_argument(ss.str());
	}


	*(pFill++) = (uint8_t) ((val & 0x00ff0000) >> 16);
	*(pFill++) = (uint8_t) ((val & 0x0000ff00) >> 8);
	*(pFill++) = (uint8_t) (val & 0x000000ff);
}

void BACnetBuffer::encode_ui32(uint32_t const val) {

	/** Check for out of bounds...*/
	if(get_remaining() < 4) {
		stringstream ss;
		ss << "BACnetBuffer::encode_ui32(uint32_t val):\n"
				"\tCould not encode buffer. Insufficient space remaining ("
				<< get_remaining() << ")" << endl;
		throw std::invalid_argument(ss.str());
	}

	*(pFill++) = (uint8_t) ((val & 0xff000000) >> 24);
	*(pFill++) = (uint8_t) ((val & 0x00ff0000) >> 16);
	*(pFill++) = (uint8_t) ((val & 0x0000ff00) >> 8);
	*(pFill++) = (uint8_t) (val & 0x000000ff);
}

size_t BACnetBuffer::encodeUnsignedInt(unsigned int ui) {

	size_t len = getUintLength(ui);

	switch (len) {
		case 1:
			this->encode_ui8(ui);
			break;
		case 2:
			this->encode_ui16(ui);
			break;
		case 3:
			this->encode_ui24(ui);
			break;
		case 4:
			this->encode_ui32(ui);
			break;
		default:
			len = 0;
			break;
	}

	return len;
}

/** Throws std::invalid_argument*/
void BACnetBuffer::encode_buffer(uint8_t const *src, size_t const src_pos, size_t const len) {

	/** Check for out of bounds...*/
	if(len > get_remaining()) {
		stringstream ss;
		ss << "BACnetBuffer::encode_buffer(uint8_t *src, size_t pos, size_t len):\n"
				"\tSource length (" << len << ") is greater than space remaining in buffer ("
				<< get_remaining() << ")" << endl;
		throw std::invalid_argument(ss.str());
	}

	/** We have room, copy it!*/
	memcpy(pFill, &src[src_pos], len);
	pFill += len;
}

BACnetBuffer &BACnetBuffer::operator=(BACnetBuffer const &source) {

	/** Zero it out.*/
	clear_buffer();
	encode_buffer(source.getBeginAddr(), 0, source.get_fill_length());
	pFill = &buffer[0] + source.get_fill_position();
	pRead = &buffer[0] + source.get_read_position();
	return *this;
}

void BACnetBuffer::copyBuffer(BACnetBuffer const &source) {
	clear_buffer();
	encode_buffer(source.getBeginAddr(), 0, source.get_fill_length());
	pFill = &buffer[0] + source.get_fill_position();
	pRead = &buffer[0] + source.get_read_position();
}

bool BACnetBuffer::has_next(void) {
	return get_read_size() > 0;
	return 0;
}

uint8_t BACnetBuffer::get_ui8(void) {

	return *(pRead++);
}

uint16_t BACnetBuffer::get_ui16(void) {

	uint16_t ui16 = 0;

	ui16 = *(pRead++) << 8;
	ui16 |= *(pRead++);

	return ui16;
}

uint32_t BACnetBuffer::get_ui24(void) {

	uint32_t ui32 = 0;

	ui32 = *(pRead++) << 16;
	ui32 |= *(pRead++) << 8;
	ui32 |= *(pRead++);

	return ui32;
}

uint32_t BACnetBuffer::get_ui32(void) {

	uint32_t ui32 = 0;

	ui32 = *(pRead++) << 24;
	ui32 |= *(pRead++) << 16;
	ui32 |= *(pRead++) << 8;
	ui32 |= *(pRead++);

	return ui32;
}

uint8_t BACnetBuffer::peek(void) const {

	return *(pRead);
}

uint8_t const *BACnetBuffer::getReadPointer(void) const {
	return pRead;
}

unsigned int BACnetBuffer::decodeUnsignedInt(BACnetBuffer &buff, size_t length) {

	if(length < 0 || length > 4) {
		stringstream ss;
		ss << "BACnetBuffer::decodeUnsignedInt(BACnetBuffer &buff, size_t length):\n"
				"\tLength parameter (" << length << ") is greater than 4 bytes" << endl;
		throw std::invalid_argument(ss.str());
	}

	if(length == 4) {
		return buff.get_ui32();
	}
	else if(length == 3) {
		return buff.get_ui24();
	}
	else if(length == 2) {
		return buff.get_ui16();
	}
	else if(length == 1) {
		return buff.get_ui8();
	}

	return 0;
}

size_t BACnetBuffer::getUintLength(uint32_t uint32) {

	size_t len = 0;

	if(uint32 < 0x100) {
		len = 1;
	}
	else if(uint32 < 0x10000) {
		len = 2;
	}
	else if(uint32 < 0x1000000) {
		len = 3;
	}
	else {
		len = 4;	/** Only gonna handle 4-byte ints for now*/
	}
	return len;
}

uint8_t const *BACnetBuffer::get_ui8(uint8_t const *ptr, uint32_t &retVal) {

	if(ptr == NULL) {
		return ptr;
	}

	retVal = (*ptr++);

	return ptr;
}

uint8_t const *BACnetBuffer::get_ui16(uint8_t const *ptr, uint32_t &retVal) {

	if(ptr == NULL) {
		return ptr;
	}
	uint16_t ui16 = 0;

	ui16 = (*ptr++) << 8;
	ui16 |= (*ptr++);

	retVal = ui16;

	return ptr;
}

uint8_t const *BACnetBuffer::get_ui24(uint8_t const *ptr, uint32_t &retVal) {

	if(ptr == NULL) {
		return ptr;
	}
	uint32_t ui32 = 0;

	ui32 = (*ptr++) << 16;
	ui32 |= (*ptr++) << 8;
	ui32 |= (*ptr++);

	retVal = ui32;

	return ptr;
}

uint8_t const *BACnetBuffer::get_ui32(uint8_t const *ptr, uint32_t &retVal) {

	if(ptr == NULL) {
		return ptr;
	}
	uint32_t ui32 = 0;

	ui32 = (*ptr++) << 24;
	ui32 |= (*ptr++) << 16;
	ui32 |= (*ptr++) << 8;
	ui32 |= (*ptr++);

	return ptr;
}



