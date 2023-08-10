/*
 * BACnetInstance.h
 *
 *  Created on: Mar 17, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETINSTANCE_H_
#define BACNETAPP_SRC_BACNETINSTANCE_H_

#include <iostream>
#include <stdint.h>

#include "BACnetBuffer.h"

using namespace std;

#define MAX_BACNET_INSTANCE 0x3FFFFF	/** 4194303 */
#define NULL_BACNET_INSTANCE 0x400000	/** 4194304 */

class BACnetInstance {

	friend class BACnetObjIdentifier;

private:
	uint32_t instance;

	void setInstance(uint32_t newInstance);
	void setToNullInstance(void);

	int compare(const BACnetInstance &left, const BACnetInstance &right) const;

public:

	BACnetInstance();
	BACnetInstance(const BACnetInstance &inst);
	BACnetInstance(uint32_t inst);
	virtual ~BACnetInstance();

	bool operator == (const BACnetInstance &right) const;
	bool operator != (const BACnetInstance &right) const;
	bool operator < (const BACnetInstance &right) const;
	bool operator > (const BACnetInstance &right) const;

	uint32_t get_instance(void) const;
	size_t get_length(void) const;
	int encode(BACnetBuffer &buff);

};

#endif /* BACNETAPP_SRC_BACNETINSTANCE_H_ */
