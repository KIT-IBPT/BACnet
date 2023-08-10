/*
 * BACnetRpmResult.h
 *
 *  Created on: Aug 17, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETRPMRESULT_H_
#define BACNETAPP_SRC_BACNETRPMRESULT_H_

#include "BACnetObjIdentifier.h"
#include "BACnetPropRefValue.h"

using namespace std;

typedef std::list<BACnetPropRefValue> propRefValLst_t;

class BACnetRpmResult {
private:
	BACnetObjIdentifier objId;
	std::list<BACnetPropRefValue> propRefVal;

public:
	BACnetRpmResult();
	virtual ~BACnetRpmResult();

	void setData(BACnetObjIdentifier &objId, propRefValLst_t &pRefLst);
	void clearData(void);
	size_t getPropRefValListSize(void) const;
	BACnetObjIdentifier const &getObjectId(void) const;

	propRefValLst_t::const_iterator getPropRefValueListBegin(void) const;
	propRefValLst_t::const_iterator getPropRefValueListEnd(void) const;

};

#endif /* BACNETAPP_SRC_BACNETRPMRESULT_H_ */
