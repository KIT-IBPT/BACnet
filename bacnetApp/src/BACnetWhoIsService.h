/*
 * BACnetWhoIsService.h
 *
 *  Created on: Sep 6, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETWHOISSERVICE_H_
#define BACNETAPP_SRC_BACNETWHOISSERVICE_H_

#include "BACnetBuffer.h"
#include "BACnetInstance.h"
#include "BACnetApdu.h"


using namespace std;


class BACnetWhoIsService : public BACnetApdu {
private:

	BACnetInstance lowRangeInst;
	BACnetInstance highRangeInst;

public:
	BACnetWhoIsService();
	BACnetWhoIsService(int devInstance);
	BACnetWhoIsService(int lowInstance, int highInstance);

	virtual ~BACnetWhoIsService();

	uint32_t getLowRangeInstance() const;
	uint32_t getHighRangeInstance() const;

	/** Get the length of encoding */
	size_t get_length(void) const;

	/** Encode this whoIs service into a buffer */
	int encode(BACnetBuffer &buff);

};

#endif /* BACNETAPP_SRC_BACNETWHOISSERVICE_H_ */
