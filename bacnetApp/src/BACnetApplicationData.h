/*
 * BACnetApplicationData.h
 *
 *  Created on: Jun 13, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETAPPLICATIONDATA_H_
#define BACNETAPP_SRC_BACNETAPPLICATIONDATA_H_

#include <stdint.h>
#include <string>

#include "BACnetDefs.h"
#include "BACnetBuffer.h"

using namespace std;

#define MAX_APP_DATA_LEN 255

class BACnetApplicationData {

protected:
	BACnetApplicationDataTypeChoice const *type;
	uint32_t dataLength;
	uint8_t data[MAX_APP_DATA_LEN];

public:
	BACnetApplicationData();
	virtual ~BACnetApplicationData();

	void decode(BACnetBuffer &buff);

	BACnetApplicationDataTypeChoice const *getAppDataType(void) const;
	uint32_t getDataLength(void) const;
	uint8_t const *getData(void) const;
	void clearData(void);
};

#endif /* BACNETAPP_SRC_BACNETAPPLICATIONDATA_H_ */
