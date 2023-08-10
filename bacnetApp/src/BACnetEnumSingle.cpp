/*
 * BACnetEnum.cpp
 *
 *  Created on: Dec 22, 2017
 *      Author: 8w4
 */

#include <BACnetEnumSingle.h>

BACnetEnumSingle::BACnetEnumSingle(unsigned int enumValue, string enumName)
:value(enumValue), name(enumName)
{
	// TODO Auto-generated constructor stub

}

BACnetEnumSingle::~BACnetEnumSingle() {
	// TODO Auto-generated destructor stub
}

unsigned int const BACnetEnumSingle::getValue(void) const {
	return value;
}

string const &BACnetEnumSingle::getName(void) const {
	return name;
}

bool BACnetEnumSingle::operator==(BACnetEnumSingle const &other) const {

	/** See if they have the same address in memory...*/
	if(this == &other) {
		return true;
	}
	/** Walk through the structure and see if each element matches...*/
	else if(name.size() == other.name.size()) {
		if(name.compare(other.name) == 0) {
			if(value == other.value) {
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	return false;
}

bool BACnetEnumSingle::operator!=(BACnetEnumSingle const &other) const {
	/** See if they have the same address in memory...*/
	if(this == &other) {
		return false;
	}
	/** Walk through the structure and see if each element matches...*/
	else if(name.size() == other.name.size()) {
		if(name.compare(other.name) == 0) {
			if(value == other.value) {
				return false;
			}
			else
				return true;
		}
		else
			return true;
	}
	return true;
}

bool BACnetEnumSingle::operator < (BACnetEnumSingle const &rhs) const {
	cout << ">>> BACnetEnumSingle::operator < " << endl;
	return this->value < rhs.value;
}

size_t BACnetEnumSingle::getLength(void) const {

	size_t len = 0;

	if (value < 0x100) {
		len = 1;
	} else if (value < 0x10000) {
		len = 2;
		/** Table 23-1. Extensible Enumerations states that the max sixe for an enum to be 4194303 0x3FFFFF*/
	} else if (value < 0x400000) {
		len = 3;
	} else {
		len = 0;	//Maybe throw on this!? Not sure how to handle yet.
	}
	return len;
}

