/*
 * BACnetBitString.h
 *
 *  Created on: Jun 13, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETBITSTRING_H_
#define BACNETAPP_SRC_BACNETBITSTRING_H_

#include <stdint.h>
#include <string>
#include <bitset>

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

#define MAX_BITSTRING_BYTES 8	//TODO: Find max byte-length. I have no idea...

class BACnetBitString : public BACnetAppDataType {
private:
	uint32_t bitsUsed;
	uint8_t value[MAX_BITSTRING_BYTES];

	uint8_t reverseBits(uint8_t byteIn);

	size_t getByteLength(void) const;

public:
	BACnetBitString();
	virtual ~BACnetBitString();

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	string toString(void) const;
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	bool checkBit(uint8_t bit) const;
	uint32_t getBytesAsUint32t() const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);

};

#endif /* BACNETAPP_SRC_BACNETBITSTRING_H_ */
