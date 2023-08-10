/*
 * BACnetEnumSingle.h
 *
 *  Created on: Dec 22, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMSINGLE_H_
#define BACNETAPP_SRC_BACNETENUMSINGLE_H_

#include <stdint.h>
#include <string>
#include <iostream>

using namespace std;

class BACnetEnumSingle {

protected:
	unsigned int const value;
	string const name;

public:
	BACnetEnumSingle(unsigned int enumValue, string enumName);
	virtual ~BACnetEnumSingle();

	unsigned int const getValue(void) const;

	string const &getName(void) const;

	bool operator==(BACnetEnumSingle const &other) const;
	bool operator!=(BACnetEnumSingle const &other) const;
	bool operator < (BACnetEnumSingle const &rhs) const;

	size_t getLength(void) const;

};

#endif /* BACNETAPP_SRC_BACNETENUMSINGLE_H_ */
