/*
 * BACnetOctetString.h
 *
 *  Created on: Jun 13, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETOCTETSTRING_H_
#define BACNETAPP_SRC_BACNETOCTETSTRING_H_

#include <stdint.h>
#include <string>
#include <bitset>

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

#define MAX_OCTET_STRING_BYTES ((1476-6)-1)	//TODO: Find max byte-length. I have no idea...

class BACnetOctetString : public BACnetAppDataType {
private:

	uint8_t value[MAX_OCTET_STRING_BYTES];
	size_t length;

public:
	BACnetOctetString();
	virtual ~BACnetOctetString();

	uint32_t getBytesAsUint32t(void) const;

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	string toString(void) const;
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);

};

#endif /* BACNETAPP_SRC_BACNETOCTETSTRING_H_ */
