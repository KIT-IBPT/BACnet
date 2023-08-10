/*
 * BACnetInstIOParser.h
 *
 *  Created on: Jul 16, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETINSTIOPARSER_H_
#define BACNETAPP_SRC_BACNETINSTIOPARSER_H_

#include <stdint.h>
#include <string>

#include "BACnetObjIdentifier.h"
#include "BACnetEnumPropertyIdentifier.h"
#include "BACnetObjPropRef.h"
#include "BACnetEnumApplicationDataType.h"


using namespace std;

class BACnetInstIOParser {
private:

	string inout;

	/** EPICS Name/alias that maps back to an instance number in st.cmd file*/
	string devName;

	/** objId is the object-type with the object-instance*/
	BACnetObjIdentifier objId;

	/** propId is the property of the object: e.g., name, present-value, units, etc.*/
	BACnetPropertyType const *propId;

	/** Optional Parameters Below: */

	/** Optional Array-Index */
	int aIndex;

	/** Optional Write-Priority*/
	int writePri;

	/** Optional datatype format. Only used for writing to properties*/
	BACnetApplicationDataTypeChoice const *datatype;

public:
	BACnetInstIOParser();
	virtual ~BACnetInstIOParser();

	string getDeviceName(void) const;
	BACnetObjPropRef getObjPropRef(void) const;

	BACnetApplicationDataTypeChoice const *getDataTypeFormat(void) const;

	void parseInstIOString(string const &instioStr);
};

#endif /* BACNETAPP_SRC_BACNETINSTIOPARSER_H_ */
