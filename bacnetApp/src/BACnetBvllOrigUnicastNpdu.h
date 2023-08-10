/*
 * BACnetBvllOrigUnicastNpdu.h
 *
 *  Created on: Dec 19, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETBVLLORIGUNICASTNPDU_H_
#define BACNETAPP_SRC_BACNETBVLLORIGUNICASTNPDU_H_

#include "BACnetBVLL.h"
#include "BACnetNpdu.h"

class BACnetBvllOrigUnicastNpdu : public BACnetBVLL {

private:
	BACnetNpdu *npdu;

protected:
	virtual void print(ostream& o) const;

public:
	BACnetBvllOrigUnicastNpdu();
	BACnetBvllOrigUnicastNpdu(BACnetNpdu *bac_npdu);
	virtual ~BACnetBvllOrigUnicastNpdu();

	BACnetNpdu const *get_npdu(void) const;
	void set_npdu(BACnetNpdu *bac_npdu);

	size_t get_length(void) const;
	void encode(BACnetBuffer &buff);

	size_t decode(BACnetBuffer &buff);

};

#endif /* BACNETAPP_SRC_BACNETBVLLORIGUNICASTNPDU_H_ */
