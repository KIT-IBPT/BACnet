/*
 * BACnetDrvProperties.h
 *
 *  Created on: May 3, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETDRVPROPERTIES_H_
#define BACNETAPP_SRC_BACNETDRVPROPERTIES_H_

#include <stdint.h>
#include <string>

#include "BACnetEnums.h"
#include "BACnetObjIdentifier.h"
#include "BACnetEnumPropertyIdentifier.h"

class BACnetDrvProperties {

private:

	string inout;

	/** EPICS Name/alias that maps back to an instance number in st.cmd file*/
	string devName;

	/** objId is the object-type with the object-instance*/
	BACnetObjIdentifier *objId;

	/** propId is the property of the object: e.g., name, present-value, units, etc.*/
	BACnetPropertyType *propId;

	/** Optional Parameters Below: */

	/** Optional Array-Index */
	int aIndex;

	/** Optional Write-Priority*/
	int writePri;

	/** Optional Scan-Rate*/
	scanRate_t scaRate;

public:
	BACnetDrvProperties();
	BACnetDrvProperties(string const &instioStr);
	virtual ~BACnetDrvProperties();

	int parse(string const &instioStr);

	string const getInOutString() const;
	string const getDeviceName() const;
	BACnetObjIdentifier *getObjectId() const;
	BACnetPropertyType *getPropertyId() const;
	int getArrayIndex() const;
	int getWritePriority() const;
	scanRate_t getScanRate() const;
};

#endif /* BACNETAPP_SRC_BACNETDRVPROPERTIES_H_ */
