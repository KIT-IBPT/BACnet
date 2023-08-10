/*
 * BACnetCharacterString.h
 *
 *  Created on: Jul 3, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETCHARACTERSTRING_H_
#define BACNETAPP_SRC_BACNETCHARACTERSTRING_H_

#include <stdint.h>
#include <string>
#include <bitset>

#include "BACnetDefs.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"
#include "BACnetEnumCharSet.h"

using namespace std;

#define MAX_CHAR_STRING_BYTES ((1476-6)-1)	//TODO: Find max byte-length. I have no idea...

class BACnetCharacterString : public BACnetAppDataType {
private:
	BACnetCharChoice const *encoding;
	size_t length;
	char Value[MAX_CHAR_STRING_BYTES];

public:
	BACnetCharacterString();
	virtual ~BACnetCharacterString();

	uint32_t getBytesAsUint32t(void) const;

	void decode(BACnetApplicationData const &appType);
	void encode(BACnetBuffer &buff);
	string toString(void) const;
	size_t toCString(char *toStr, size_t maxSizeOfToStr) const;
	void printData(void);
	size_t getLength(void);
	string getValAsStr(void);

};

#endif /* BACNETAPP_SRC_BACNETCHARACTERSTRING_H_ */
