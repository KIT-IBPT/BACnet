/*
 * Tsm.h
 *
 *  Created on: May 22, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_TSM_H_
#define BACNETAPP_SRC_TSM_H_

#include <stdint.h>
#include <string>

#include "BACnetDefs.h"
#include "BACnetApdu.h"
#include "BACnetDeviceAddress.h"
#include "BACnetNpdu.h"
#include "BACnetVariable.h"
#include "BACnetRpmReq.h"

using namespace std;

class BACnetConnection;
class BACnetDevice;

class Tsm {

private:

	struct timespec startTime;

	/* APDU Timeout in Milliseconds */
	uint16_t TimeoutMilliseconds;

	/* Number of APDU Retries */
	uint8_t NumberOfRetries;

	/** Counter for the number of retries*/
	uint8_t retryCount;

	/** Invoke-Id of the message. Used only for confirmed messages.*/
	uint8_t invokeId;

	/** State of the TSM */
	BACnetTsmState const *tsmState;

	/**Destination */
	BACnetDeviceAddress addr;

	/** Network data*/
	BACnetNpdu npdu;

	/** APDU data*/
	BACnetApdu *apdu;

	/** A copy of encoded message in case in needs to be resent.*/
	BACnetBuffer buff;

	BACnetConnection *con;

	BACnetDevice *callback;

	BACnetVariable *varCallback;

	const std::list<BACnetVariable *> *rpmCallBack;

	Tsm *next;

	void incrementTx(BACnetDevice &d);

	/** had to make this class a friend so that BACnetDevice class could access private functions
	 * of this class. I.e., 'void incrementTx(BACnetDevice &d)' */
	friend class BACnetDevice;

public:
	Tsm();
	virtual ~Tsm();

	void init(BACnetVariable *var, uint8_t invkId, BACnetTsmState const *tsmSTATE, BACnetDeviceAddress &addr,
			BACnetNpdu &nPDU, BACnetApdu &aPDU, BACnetBuffer &bUFF);

	void init(const std::list<BACnetVariable *> &rpmLst, uint8_t invkId, BACnetTsmState const *tsmSTATE,
			BACnetDeviceAddress &addr, BACnetNpdu &nPDU, BACnetRpmReq &rpmReq, BACnetBuffer &bUFF);

	void setNext(Tsm *next);
	Tsm *getNext(void);

	void setTimeout(uint16_t timeout);
	void setNumberOfRetries(uint8_t retries);
	void setConnection(BACnetConnection *con);
	void setCallback(BACnetDevice *callback);

	int send(void);

	int getInvokeId(void) const {return invokeId;}
	BACnetApdu const *getApdu(void) const;
	BACnetBuffer const &getBuffer(void) const;

	struct timespec const *getStartTime(void);

	void process(void);

	BACnetVariable *getCallbackVariable(void) const;
	const std::list<BACnetVariable *> *getRpmCallbackVariable(void) const;

	//void incMyTx(BACnetDevice &d);

};

#endif /* BACNETAPP_SRC_TSM_H_ */
