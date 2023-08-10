/*
 * BACnetEnums.h
 *
 *  Created on: Apr 3, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMS_H_
#define BACNETAPP_SRC_BACNETENUMS_H_

enum paraFunc_t {
	READ,
	WRITE
};

enum scanRate_t {
	ONE_SEC,
	TWO_SEC,
	FIVE_SEC,
	TEN_SEC
};

enum devRslvSts_t {
	UNRESOLVED,
	WAITING,
	RESOLVED
};


#endif /* BACNETAPP_SRC_BACNETENUMS_H_ */
