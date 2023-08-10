/*
 * BACnetObjIdentifier.h
 *
 *  Created on: Mar 17, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETOBJIDENTIFIER_H_
#define BACNETAPP_SRC_BACNETOBJIDENTIFIER_H_

#include "BACnetEnumObjectType.h"
#include "BACnetInstance.h"
#include "BACnetBuffer.h"
#include "BACnetApplicationData.h"
#include "BACnetAppDataType.h"

using namespace std;

class BACnetObjIdentifier {

protected:
	BACnetObjectType const *obj_type;
	BACnetInstance obj_instance;

public:
	BACnetObjIdentifier();
	BACnetObjIdentifier(const BACnetObjIdentifier &objid);
	BACnetObjIdentifier(uint16_t objType, uint32_t objInstance);
	BACnetObjIdentifier(BACnetObjectType const &objType, uint32_t objInstance);

	virtual ~BACnetObjIdentifier();

	void clear(void);

	void setObjectType(BACnetObjectType const &objType);
	void setObjectInstance(uint32_t objInstance);

	const string getObjectName(void) const;
	BACnetObjectType const *getObjectType(void) const;
	BACnetInstance const &getObjectInstance(void) const;
	uint32_t getObjectInstanceAsUint32_t(void) const;
	void getObjectId(BACnetObjIdentifier &objId) const;
	static void copyObjectId(BACnetObjIdentifier &copyTo, BACnetObjIdentifier const &copyFrom);

	void decode(BACnetBuffer &buff);
	uint8_t const *decode(uint8_t const *buff);

	size_t encode(BACnetBuffer &buff) const;

	int compare(const BACnetObjIdentifier &left, const BACnetObjIdentifier &right) const;
	bool operator == (const BACnetObjIdentifier &right) const;
	bool operator != (const BACnetObjIdentifier &right) const;
	bool operator < (const BACnetObjIdentifier &rhs) const;

	friend std::ostream& operator<< (std::ostream &out, const BACnetObjIdentifier &bacObjId);

	void getBytes(uint8_t *copyTo) const;
	uint32_t getBytesAsUint32t(void) const;
	string toString(void);
	void printData(void);

	BACnetObjIdentifier &operator=(const BACnetObjIdentifier &T) {

		if(this != &T) {
			this->obj_type = T.obj_type;
			this->obj_instance = T.obj_instance;
		}
		return *this;
	}

};

#endif /* BACNETAPP_SRC_BACNETOBJIDENTIFIER_H_ */
