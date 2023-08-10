/*
 * BACnetDrvProperties.cpp
 *
 *  Created on: May 3, 2017
 *      Author: 8w4
 */

#include "BACnetDrvProperties.h"
#include "BACnetStringUtil.h"

BACnetDrvProperties::BACnetDrvProperties()
: inout(""), devName(""), objId(NULL), propId(NULL), aIndex(-1), writePri(-1), scaRate(ONE_SEC)
{
	// TODO Auto-generated constructor stub

}

BACnetDrvProperties::BACnetDrvProperties(string const &instioStr)
: inout(""), devName(""), objId(NULL), propId(NULL), aIndex(-1), writePri(-1), scaRate(ONE_SEC)
{
	parse(instioStr);
}

BACnetDrvProperties::~BACnetDrvProperties() {
	// TODO Auto-generated destructor stub
}

/** Throws... */
int BACnetDrvProperties::parse(string const &instioStr) {

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
	 * S= (scan rate 1, 2, 5 & 10)
	 *
	 * */

	this->inout = instioStr;

	cout << "Parsing Input Parameter List String... " << endl;

	/** List to hold parameters...*/
	std::list<string> strList = parse_string_by_whitespace(instioStr);

	cout << "Parameter list size is: " << strList.size() << endl;

	/** for printing errors...*/
	ostringstream errstr;

	/** We must have at least 4 parameters */
	if(strList.size() < 4) {
		//TODO: throw? return? ???
		errstr << " -> Error! BACnetDrvProperties::parse: input/output string \"" << instioStr <<
				"\" must have at least 4 parameters!" << endl;
		throw std::invalid_argument(errstr.str());
	}

	/** Create an iterator pointing to list members. Iterator is the only way
	 * to walk through a standard list. */
	std::list<string>::const_iterator itrStr;

	/** TODO: Delete the cout. But print for now.*/
	int i = 0;
	for (itrStr = strList.begin(); itrStr != strList.end(); ++itrStr) {
		cout << "Parameter[" << i++ << "]: \"" << *itrStr << "\"" << endl;
	}

	/** Go back to the beginning...*/
	itrStr = strList.begin();

	this->devName = *itrStr++;
	cout << "dev_name: " << this->devName << endl;

	uint16_t obj_type = strToUint16(*itrStr++);
	cout << "obj_type: " << obj_type << endl;
	uint32_t obj_inst = strToUint32(*itrStr++);
	cout << "obj_inst: " << obj_inst << endl;

	try {

		this->objId = new BACnetObjIdentifier(obj_type, obj_inst);

		/** Next parameter must be property-Id.*/
		this->propId = (BACnetPropertyType *) &BACnetEnumPropertyIdentifier::getEnumByValue(strToUint32(*itrStr++));

	} catch (exception &e) {
		cout << e.what() << endl;
		return -1;
	}



	cout << "prop_id: " << this->propId << endl;

	/** Are there more parameters? Optional ones, maybe?*/
	if(itrStr != strList.end()) {
		cout << "Optional Parameters: " << *itrStr << endl;

		/** Are one of the optional parameters an array element?*/
		if(itrStr->at(0) == '[') {
			this->aIndex = parse_array_element(*itrStr++);
			cout << "Optional Parameter \"Array Element\": " << this->aIndex << endl;
		}

		/** Write-Priority? P=?*/
		if(itrStr != strList.end()) {
			if(itrStr->at(0) == 'P') {
				this->writePri = get_digits(*itrStr++);
				cout << "Optional Parameter \"Write-Priority\": " << this->writePri << endl;
			}
		}

		/** Scan-Rate? S=?*/
		if(itrStr != strList.end()) {
			if(itrStr->at(0) == 'S') {
			int sval = get_digits(*itrStr++);
			if(sval == 3) {
				this->scaRate = TEN_SEC;
			}
			else if(sval == 2) {
				this->scaRate = FIVE_SEC;
			}
			else if(sval == 1) {
				this->scaRate = TWO_SEC;
			}
			else
				this->scaRate = ONE_SEC;
				cout << "Optional Parameter \"Scan-Rate\": " << this->scaRate << endl;
			}
		}
	}
	else
		cout << "No Optional Parameters: " << endl;

	return 1;
}

string const BACnetDrvProperties::getInOutString() const {
	return this->inout;
}

string const BACnetDrvProperties::getDeviceName() const {
	return this->devName;
}

BACnetObjIdentifier *BACnetDrvProperties::getObjectId() const {
	return this->objId;
}

BACnetPropertyType *BACnetDrvProperties::getPropertyId() const {
	return this->propId;
}

int BACnetDrvProperties::getArrayIndex() const {
	return this->aIndex;
}

int BACnetDrvProperties::getWritePriority() const {
	return this->writePri;
}

scanRate_t BACnetDrvProperties::getScanRate() const {
	return this->scaRate;
}



