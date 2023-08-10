/*
 * BACnetInstIOParser.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: 8w4
 */

#include "BACnetInstIOParser.h"
#include "BACnetStringUtil.h"

BACnetInstIOParser::BACnetInstIOParser()
:inout(), devName(), objId(), propId(NULL), aIndex(-1), writePri(-1), datatype(NULL)
{
	// TODO Auto-generated constructor stub

}

BACnetInstIOParser::~BACnetInstIOParser() {
	// TODO Auto-generated destructor stub
}

string BACnetInstIOParser::getDeviceName(void) const {
	return this->devName;
}

BACnetObjPropRef BACnetInstIOParser::getObjPropRef(void) const {
	return BACnetObjPropRef(this->objId, *this->propId, this->aIndex, this->writePri);
}

BACnetApplicationDataTypeChoice const *BACnetInstIOParser::getDataTypeFormat(void) const {
	return this->datatype;
}

void BACnetInstIOParser::parseInstIOString(string const &instioStr) {

	/**
	 * device-name object-type object-instance object-property [[array-element]] [P=16] [S=1]
	 *
	 * Mandatory parameters:
	 * device-name
	 * object-type
	 * object-instance
	 * object-property
	 *
	 * Optional parameters:
	 * [] array-element
	 * P= (write-priority 1 thru 16)
	 * T= Data-type format; for writing values... (e.g., val=1, write as REAL... BOOL... UNSIGNED... etc.)
	 * S= (scan rate 1, 2, 5 & 10)	//Maybe a future option
	 *
	 * */

	/** Save a copy of the inout string.*/
	this->inout = instioStr;

	cout << "Parsing Input/Output Parameter List String... " << endl;

	/** Split the string by white-spaces into a list of strings*/
	std::list<string> strList = parse_string_by_whitespace(instioStr);

	cout << "Parameter list size is: " << strList.size() << endl;

	/** for printing errors...*/
	ostringstream errstr;

	/** We must have at least 4 parameters: device-name, Object-type, Object-instance, property-id */
	if(strList.size() < 4) {
		errstr << " -> ERROR! BACnetInstIOParser::parseInstIOString: input/output string \"" << instioStr <<
				"\" must have at least 4 parameters: device-name object-type object-instance property-id" << endl;
		throw std::invalid_argument(errstr.str());
	}


	std::list<string>::const_iterator itrStr;

	/** TODO: Delete the cout. But print for now.*/
	int i = 0;
	for (itrStr = strList.begin(); itrStr != strList.end(); ++itrStr) {
		cout << "Parameter[" << i++ << "]: \"" << *itrStr << "\"" << endl;
	}

	/** Go back to the beginning...*/
	itrStr = strList.begin();

	/** Get the device-name; must be first parameter...*/
	this->devName = *itrStr++;


	/** Parameter #2: must be the enumeration for the object-type (AI, BI, Etc.)*/
	uint16_t obj_type = strToUint16(*itrStr++);

	/** Get the enum object for the object-type*/
	BACnetObjectType const &otype = BACnetEnumObjectType::getEnumByValue(obj_type);

	/** Set this object-type...*/
	this->objId.setObjectType(otype);

	/** Parameter #3: Must be the object-instance*/
	uint32_t obj_inst = strToUint32(*itrStr++);
	this->objId.setObjectInstance(obj_inst);

	/** Parameter #4: Must be the property-Id.*/
	this->propId = &BACnetEnumPropertyIdentifier::getEnumByValue(strToUint32(*itrStr++));

	/** Are there more parameters? Optional ones, maybe?*/
	if(itrStr != strList.end()) {
		//cout << "Optional Parameters: " << *itrStr << endl;

		/** Are one of the optional parameters an array element?*/
		if(itrStr->at(0) == '[') {
			this->aIndex = parse_array_element(*itrStr++);
			//cout << "Optional Parameter \"Array Element\": " << this->aIndex << endl;
		}

		/** Write-Priority? P=?*/
		if(itrStr != strList.end()) {
			if(itrStr->at(0) == 'P') {
				this->writePri = get_digits(*itrStr++);
				//cout << "Optional Parameter \"Write-Priority\": " << this->writePri << endl;
			}
		}

		/** Data-Type Format? T=?*/
		if(itrStr != strList.end()) {
			if(itrStr->at(0) == 'T') {
				int dataType = get_digits(*itrStr++);
				this->datatype = &BACnetEnumApplicationDataType::getEnumByValue(dataType);
				cout << "Optional Parameter \"Data-Type Format\": " << this->datatype->getName() << endl;
			}
		}
	}
	else {
		cout << "No Optional Parameters: " << endl;
	}

	//return 1;
}
