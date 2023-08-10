/*
 * BACnetStringUtil.h
 *
 *  Created on: May 3, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETSTRINGUTIL_H_
#define BACNETAPP_SRC_BACNETSTRINGUTIL_H_

#include <iostream>
#include <string>
#include <stdlib.h>

#include <sstream>
#include <stdint.h>
#include <list>
#include <stdexcept>
#include <limits.h>
#include <errno.h>

using namespace std;

struct bacIocShArgs {
	string argName;
	string argValue;

};

/** Split by comma */
std::list<bacIocShArgs> parseIocShArgs(string const &inputStr);

/** Split the inputStr into a list of strings by whitespace.*/
std::list<string>parse_string_by_whitespace(string const &inputStr);

/** Parse an array element [...] as a string and return the array-element as an int.
 * returns -1 on failure.*/
int parse_array_element(string const &s);

/** Tries to find any number in the string, skipping over everything that is not a digit
 * until it finds at least one number. returns -1 on failure.*/
int get_digits(string const &s);

/** tries to convert the string into an UINT16.
 * Throws...*/
uint16_t strToUint16(string const &s);

/** tries to convert the string into an UINT32.
 * Throws...*/
uint32_t strToUint32(string const &s);



#endif /* BACNETAPP_SRC_BACNETSTRINGUTIL_H_ */
