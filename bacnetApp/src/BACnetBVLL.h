/*
 * BACnetBVLL.h
 *
 *  Created on: Sep 22, 2016
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETBVLL_H_
#define BACNETAPP_SRC_BACNETBVLL_H_

#include "BACnetEnumBvlcFunction.h"
#include "BACnetDeviceAddress.h"
#include "BACnetBuffer.h"

class BACnetBVLL {
private:
	uint8_t bvlc_type;
	BACnetBvlcFunction const *bvlc_func;
	uint16_t bvlc_len;

protected:
   virtual void print(ostream& o) const = 0;

public:
	BACnetBVLL();
	BACnetBVLL(BACnetBvlcFunction const *bvlcFunc);
	virtual ~BACnetBVLL();

	static uint8_t const BVLL_FOR_BACNET_IP = 0x81;	/** BVLL for BACnet/IP*/

	uint8_t get_bvlc_type(void) const;
	BACnetBvlcFunction const *get_bvlc_function(void) const;
	uint16_t get_bvlc_length(void) const;

	void set_bvlc_type(uint8_t type);
	void set_bvlc_function(BACnetBvlcFunction const *bvlcFunc);
	void set_bvlc_length(uint16_t len);

	virtual size_t get_length(void) const = 0;
	virtual void encode(BACnetBuffer &buff) = 0;

	size_t decode(BACnetBuffer &buff);

	friend std::ostream& operator<< (std::ostream &out, const BACnetBVLL &bvll);

};

/* make sure to put this function into the header file */
inline std::ostream& operator<< (std::ostream& o, const BACnetBVLL& bvll)
{
  bvll.print(o); // delegate the work to a polymorphic member function.
  return o;
}



#endif /* BACNETAPP_SRC_BACNETBVLL_H_ */
