/*
 * BACnetStringUtil.cpp
 *
 *  Created on: May 3, 2017
 *      Author: 8w4
 */

#include "BACnetStringUtil.h"


int get_digits(string const &s) {

	int first = 0;
	int last = 0;

	for(unsigned int i=0; i<s.length(); i++) {
		while(!isdigit(s[i])) {
			i++;
			if(i>s.length()) {
				return -1;
			}
		}
		first = i;

		while(isdigit(s[i])) {
			i++;
			if(i>s.length()) {
				return -1;
			}
		}
		last = i;
	}

	int rv = -1;

	try {
		rv = strToUint32(string(s, first, last-first));
	} catch (exception &e) {
		cout << e.what() << endl;
		rv = -1;
	}

	return rv;
}

int parse_array_element(string const &s) {

	/** Limit the max array-size to 65535*/
	const int MAX_SIZE = 5;

	/** Iterator to walk through the string char by char*/
	std::string::const_iterator itr = s.begin();

	/** First character is '[' advance one...*/
	itr++;

	/** Char array to hold the value to convert.*/
	char a[MAX_SIZE] = {'\0', '\0', '\0', '\0', '\0'};


	for(int i=0; i<MAX_SIZE; i++) {
		if(isdigit(*itr)) {
			a[i] = *itr++;
		}
		else {
			break;
		}
	}

	int rv = -1;

	try {
		rv = strToUint16(a);
	} catch (exception &e) {
		cout << e.what() << endl;
		rv = -1;
	}
	return rv;
}

/** Split by comma */
std::list<bacIocShArgs> parseIocShArgs(string const &inpStr) {

	stringstream ss;

	bacIocShArgs arg;
	std::list<bacIocShArgs> tmpList;

	std::string::const_iterator itr = inpStr.begin();
	std::string::const_iterator fChar = inpStr.end();

	while(itr != inpStr.end()) {

		arg.argName.clear();
		arg.argValue.clear();

		/** Set/Reset first character marker to here...*/
		fChar = inpStr.end();

		/** Ignore any leading white spaces and advance the marker to the first non-white space character*/
		while(isspace((*itr)) != 0 && itr != inpStr.end()) {
			itr++;
		}

		/** the start of a word*/
		if(itr != inpStr.end()) {

			/** Mark the first character*/
			fChar = itr;

			/** Iterate thru the word...*/
			while(isalpha((*itr)) || (*itr) == '_') {

				if(itr == inpStr.end()) {
					ss << "ERROR! parseIocShArgs(): End of string was reached while parsing the argument name!" << endl;
					ss << "Example Syntax: <argumentName>=<argumentValue> apdu_timeout=300" << endl;
					throw std::invalid_argument(ss.str());
				}
				itr++;
			}

			/** Mark last character */
			arg.argName = string(fChar, itr);

			/** Dealing with spaces in between the equal sign " xx =    xxx"*/

			/** Ignore any leading white spaces and advance the marker to the first non-white space character*/
			while(isspace((*itr)) != 0) {
				if(itr == inpStr.end()) {
					ss << "ERROR! parseIocShArgs(): End of string was reached while parsing the argument name!" << endl;
					ss << "Example Syntax: <argumentName>=<argumentValue> apdu_timeout=300" << endl;
					throw std::invalid_argument(ss.str());
				}
				itr++;
			}

			/** this must be the equal sign '=' */
			if((*itr) != '=') {
				ss << "ERROR! parseIocShArgs(): The argument-name and argument-value must be separated by an "
						"equal sign '='!" << endl;
				throw std::invalid_argument(ss.str());
			}

			/** increment over the equal sign */
			itr++;

			/** Check out of bounds: Always having to check for out of bounds on this iterator*/
			if(itr == inpStr.end()) {
				ss << "ERROR! parseIocShArgs(): End of string was reached while parsing the argument value!" << endl;
				ss << "Example Syntax: <argumentName>=<argumentValue> apdu_timeout=300" << endl;
				throw std::invalid_argument(ss.str());
			}

			/** Ignore any leading white spaces and advance the marker to the first non-white space character*/
			while(isspace((*itr)) != 0) {

				if(itr == inpStr.end()) {
					ss << "ERROR! parseIocShArgs(): End of string was reached while parsing the argument name!" << endl;
					ss << "Example Syntax: <argumentName>=<argumentValue> apdu_timeout=300" << endl;
					throw std::invalid_argument(ss.str());
				}
				itr++;
			}

			/** ---- Now get the argument value ---- */

			/** Check for out of bounds again.*/
			if(itr == inpStr.end()) {
				ss << "ERROR! parseIocShArgs(): End of string was reached while parsing the argument value!" << endl;
				ss << "Example Syntax: <argumentName>=<argumentValue> apdu_timeout=300" << endl;
				throw std::invalid_argument(ss.str());
			}

			/** Mark the first character, again.*/
			fChar = itr;

			/** Iterate thru the word...*/
			while(isalnum((*itr))) {
				if(itr == inpStr.end()) {
					ss << "ERROR! parseIocShArgs(): End of string was reached while parsing the argument value!" << endl;
					ss << "Example Syntax: <argumentName>=<argumentValue> apdu_timeout=300" << endl;
					throw std::invalid_argument(ss.str());
				}
				itr++;
			}

			arg.argValue = string(fChar, itr);

			tmpList.push_back(arg);

			/** remove any trailing white spaces*/
			while(isspace((*itr)) != 0 && itr != inpStr.end()) {
				itr++;
			}

			/** Increment past the optional comma, separating multiple arguments.*/
			if((*itr) == ',') {
				itr++;
			}
		}
	}

	return tmpList;
}

/**
 *
 * Parse the string by whitespace and return a standard list of strings
 *
 * */
std::list<string>parse_string_by_whitespace(string const &s) {

	/**
	 * Iterate over the entire string and split all words into individual strings by white spaces
	 * and store in a list.
	 * */

	/** List to hold strings that were separated by white spaces.*/
	std::list<string> str_list;


	for(unsigned int i = 0; i<s.size(); i++) {

		/** Ignore any leading white spaces and advance the marker to the first non-white space character*/
		while(isspace(s[i]) != 0 && i<s.size()) {
			i++;
		}

		/** Marker for the first non-white space character in the word*/
		int first = i;

		/** Iterate over all of the non-whitespace characters.*/
		while(isspace(s[i]) == 0 && i<s.size()) {
			i++;
		}

		/** Marker for the last non-white space character in the word*/
		int last = i;

		/** Use the string constructor with the first and last markers and insert the word into the list.*/
		str_list.push_back(string(s, first, last-first));
		//cout << "My Word: \"" << string(s, first, last-first) << "\"" << endl;
	}

	return str_list;
}

uint16_t strToUint16(string const &s) {

	/** Strange... sizeof(unsigned long) returns 8 bytes... but it can hold larger.
	 * I was trying to test overflow with strtoul() and discovered that to trigger overflow
	 * and set errno I had to enter a really large number: 18446744073709551616
	 * Apparently a system variable __WORDSIZE, whether it's 32 or 64 bits
	 * determines the size of the UL.*/

	#define UINT16TMAX 0xFFFF

	ostringstream errstr;
	char *endptr;

	errno = 0;
	unsigned long ul = strtoul(s.c_str(), &endptr, 0);

	/** Now, check for errors...*/

	/** Overflow: strtoul sets errno to ERANGE for overflow and underflow.*/
	if((errno == ERANGE && (ul == ULONG_MAX || (ul == 0)))
			|| (errno != 0 && ul == 0)) {
		cout << "ul: " << ul << ", endptr: " << ((int) (*endptr)) << endl;
		errstr << "strToUint16: stroul() has returned errno(" << errno << "), while trying"
				" to convert \"" << s << "\" to an unsigned long." << endl;
		throw std::invalid_argument(errstr.str());
	}
	/** Empty String...*/
	else if(endptr == s.c_str()) {
		errstr << "strToUint16: null or empty string argument" << endl;
		throw std::invalid_argument(errstr.str());
	}

	/** Must have been a valid string...*/


	/** Now check the width for uint16_t and complain to the user if the result from strtoul() is greater than 16bits*/
	if(ul > UINT16TMAX) {
		cout << "strToUint16: strtoul() returned a value (" << ul << ") greater than UINT16TMAX" << endl;
		return UINT16TMAX;
	}

	//cout << "ul: " << ul << ", endptr: " << ((int) (*endptr)) << endl;
	return ul;
}

uint32_t strToUint32(string const &s) {

	/** Strange... sizeof(unsigned long) returns 8 bytes... but it can hold larger.
	 * I was trying to test overflow with strtoul() and discovered that to trigger overflow
	 * and set errno I had to enter a really large number: 18446744073709551616
	 * Apparently a system variable __WORDSIZE, whether it's 32 or 64 bits
	 * determines the size of the UL.*/

	#define UINT32TMAX 0xFFFFFFFF

	ostringstream errstr;
	char *endptr;

	errno = 0;
	unsigned long ul = strtoul(s.c_str(), &endptr, 0);

	/** Now, check for errors...*/

	/** Overflow: strtoul sets errno to ERANGE for overflow and underflow.*/
	if((errno == ERANGE && (ul == ULONG_MAX || (ul == 0)))
			|| (errno != 0 && ul == 0)) {
		cout << "ul: " << ul << ", endptr: " << ((int) (*endptr)) << endl;
		errstr << "strToUint32: stroul() has returned errno(" << errno << "), while trying"
				" to convert \"" << s << "\" to an unsigned long." << endl;
		throw std::invalid_argument(errstr.str());
	}
	/** Empty String...*/
	else if(endptr == s.c_str()) {
		errstr << "strToUint32: null or empty string argument" << endl;
		throw std::invalid_argument(errstr.str());
	}

	/** Must have been a valid string...*/


	/** Now check the width for strToUint32 and throw if the result from strtoul is greater than 32bits*/
	if(ul > UINT32TMAX) {
		cout << "strToUint32: strtoul() returned a value (" << ul << ") greater than UINT32TMAX" << endl;
		return UINT32TMAX;
	}

	//cout << "ul: " << ul << ", endptr: " << ((int) (*endptr)) << endl;
	return ul;
}





