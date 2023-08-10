/*
 * BACnetBVLLOrigBcastNPDU.h
 *
 *  Created on: Sep 22, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETBVLLORIGBCASTNPDU_H_
#define BACNETAPP_SRC_BACNETBVLLORIGBCASTNPDU_H_

#include "BACnetBVLL.h"
#include "BACnetNpdu.h"

class BACnetBVLLOrigBcastNPDU : public BACnetBVLL {

private:
	BACnetNpdu *npdu;

protected:
	virtual void print(ostream& o) const;

public:
	BACnetBVLLOrigBcastNPDU();
	BACnetBVLLOrigBcastNPDU(BACnetNpdu *bac_npdu);
	virtual ~BACnetBVLLOrigBcastNPDU();

	BACnetNpdu const *get_npdu(void) const;
	void set_npdu(BACnetNpdu *bac_npdu);

	size_t get_length(void) const;
	void encode(BACnetBuffer &buff);

	size_t decode(BACnetBuffer &buff);

};

#endif /* BACNETAPP_SRC_BACNETBVLLORIGBCASTNPDU_H_ */
