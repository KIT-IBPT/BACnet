/*
 * BACnetBuffer.h
 *
 *  Created on: Sep 7, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETBUFFER_H_
#define BACNETAPP_SRC_BACNETBUFFER_H_

#include <stdint.h>
#include <string>
#include <cstddef>

using namespace std;

class BACnetBuffer {

#define MAX_BUFFER_LEN 1500
private:
	uint8_t buffer[MAX_BUFFER_LEN];
	uint8_t *pFill; // End of valid data. When adding data, this is incremented
	uint8_t *pRead; // Start of data to read

	size_t get_remaining();

	uint8_t const *getBeginAddr(void) const {return &buffer[0];}

public:
	BACnetBuffer();

	/** Copy constructor, for the pointers...*/
	BACnetBuffer(const BACnetBuffer &buff);

	virtual ~BACnetBuffer();

	typedef const uint8_t *iterator;
	iterator begin(void) const {return &buffer[0];}
	iterator end(void) const {return pFill;}

	size_t get_fill_size(void) const;
	size_t get_fill_length(void) const;
	int get_fill_position(void) const;

	size_t get_read_size(void) const;
	size_t get_read_length(void) const;
	int get_read_position(void) const;

	void rewind_read_pointer(void);
	void rewind_fill_pointer(void);

	void rewind_all(void);

	void clear_buffer(void);

	/** Access individual element. Pointers do not advance.*/
	uint8_t &operator[](const int index);

	/** Encode byte.*/
	void operator+=(const uint8_t val);

	/** Return the buffer as a hexadecimal string.*/
	string hex_dump(void) const;

	/** Encode byte.*/
	void encode_ui8(uint8_t const val);
	void encode_ui16(uint16_t const val);
	void encode_ui24(uint32_t const val);
	void encode_ui32(uint32_t const val);
	size_t encodeUnsignedInt(unsigned int ui);
	void encode_buffer(uint8_t const *src, size_t const src_pos, size_t const len);
	BACnetBuffer &operator=(BACnetBuffer const &source);
	void copyBuffer(BACnetBuffer const &source);

	/** Used for reading the buffer.
	 * If has_next() returns true then there is an element available to read.
	 * If has_next() returns false then the read pointer is at the end of the buffer.*/
	bool has_next(void);

	/** Decode/get byte.*/
	uint8_t get_ui8(void);
	uint16_t get_ui16(void);
	uint32_t get_ui24(void);
	uint32_t get_ui32(void);

	uint8_t peek(void) const;
	uint8_t const *getReadPointer(void) const;


	/** Return a char array as a hexadecimal string.*/
	static string hex_dump(uint8_t const *const buff, unsigned int const pos, size_t const len);

	static unsigned int decodeUnsignedInt(BACnetBuffer &buff, size_t length);

	static size_t getUintLength(uint32_t);

	static uint8_t const *get_ui8(uint8_t const *ptr, uint32_t &retVal);
	static uint8_t const *get_ui16(uint8_t const *ptr, uint32_t &retVal);
	static uint8_t const *get_ui24(uint8_t const *ptr, uint32_t &retVal);
	static uint8_t const *get_ui32(uint8_t const *ptr, uint32_t &retVal);
};

#endif /* BACNETAPP_SRC_BACNETBUFFER_H_ */
