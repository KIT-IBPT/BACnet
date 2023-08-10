/*
 * BACnetBvllForwardedNpdu.h
 *
 *  Created on: Sep 27, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETBVLLFORWARDEDNPDU_H_
#define BACNETAPP_SRC_BACNETBVLLFORWARDEDNPDU_H_

#include "BACnetBVLL.h"
#include "BACnetNpdu.h"
#include "BACnetDeviceAddress.h"

class BACnetBvllForwardedNpdu : public BACnetBVLL {
private:
	BACnetNpdu *npdu;
	uint8_t bipOrigin[6];

protected:
	virtual void print(ostream& o) const;

public:
	BACnetBvllForwardedNpdu();
	virtual ~BACnetBvllForwardedNpdu();

	size_t get_length(void) const;
	void encode(BACnetBuffer &buff);
	size_t decode(BACnetBuffer &buff);

	void getBipOrigin(BACnetDeviceAddress &bipOrigin) const;
};

#endif /* BACNETAPP_SRC_BACNETBVLLFORWARDEDNPDU_H_ */
