/*
 * BACnetDefs.h
 *
 *  Created on: Sep 7, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETDEFS_H_
#define BACNETAPP_SRC_BACNETDEFS_H_

#include "BACnetEnumUnconfirmedService.h"
#include "BACnetEnumPDUChoice.h"
#include "BACnetEnumMessagePriority.h"
#include "BACnetEnumSegmentation.h"
#include "BACnetEnumApplicationDataType.h"
#include "BACnetEnumTagChoice.h"
#include "BACnetEnumPropertyIdentifier.h"
#include "BACnetEnumMaxSegAccepted.h"
#include "BACnetEnumMaxApduAccepted.h"
#include "BACnetEnumConfSvc.h"
#include "BACnetEnumSingle.h"
#include "BACnetEnumTsmState.h"

#define DEF_BACNET_PORT 0xBAC0 /** 47808*/

typedef struct confirmedReqPci_t {
	bool segmentedMessage;
	bool moreFollows;
	bool segmetedResponseAccepted;
	BACnetMaxSegmentsAccepted const *maxSegments;
	BACnetMaxApduLenAccepted const *maxApduLen;
	uint8_t invokeId;
	uint8_t sequenceNum;
	uint8_t windowSize;

} Confirmed_Req_PCI;


#endif /* BACNETAPP_SRC_BACNETDEFS_H_ */
