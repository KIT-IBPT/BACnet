/*
 * BACnetTag.h
 *
 *  Created on: Dec 19, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETTAG_H_
#define BACNETAPP_SRC_BACNETTAG_H_

#include "BACnetBuffer.h"
#include "BACnetDefs.h"

using namespace std;

#define MAX_TAG_NUMBER 0xFE
#define MAX_TAG_LVT 0xFFFFFFFFU

#define EXTENDED_TAG_NUMBER 0xF0	/** 1111 0000*/
#define OPENING_TAG 0x06	/** 0000 0110*/
#define CLOSING_TAG 0x07	/** 0000 0111*/
#define CONTEXT_SPECIFIC 0x08	/** 0000 0111*/

class BACnetTag {
private:

	const BACnetTagClassChoice *tagClass;
	uint8_t tagNumber;
	uint32_t tagLvt;

	uint8_t encodeTagNumber(uint8_t tagNumb);

public:
	BACnetTag();
	BACnetTag(const BACnetTagClassChoice *tagClass, const uint8_t tagNumber, const uint32_t tagLvt);
	virtual ~BACnetTag();

	uint8_t getTagNumber(void) const;
	uint32_t getLengthValueType(void) const;
	const BACnetTagClassChoice *getTagClass(void) const;

	void encode(BACnetBuffer &buff);
	void encodeContextTag(uint8_t tagNumb, uint32_t lvt, BACnetBuffer &buff);
	void encodeApplicationTag(uint8_t tagNumb, uint32_t lvt, BACnetBuffer &buff);
	void encodeOpeningTag(uint8_t tagNumb, BACnetBuffer &buff);
	void encodeClosingTag(uint8_t tagNumb, BACnetBuffer &buff);
	void decode(BACnetBuffer &buff);
	uint8_t const *decode(uint8_t const *buff);

	friend std::ostream& operator<< (std::ostream &out, const BACnetTag &bactag);
};

#endif /* BACNETAPP_SRC_BACNETTAG_H_ */
