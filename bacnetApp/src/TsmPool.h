/*
 * TsmPool.h
 *
 *  Created on: May 25, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_TSMPOOL_H_
#define BACNETAPP_SRC_TSMPOOL_H_

#include "Tsm.h"


using namespace std;

class BACnetDevice;

class TsmPool {
private:
	const uint32_t poolSize;
	Tsm *tsm;
	Tsm *poolHead;
	Tsm *actListHead;
	Tsm *actListTail;

	BACnetDevice &callback;

public:
	TsmPool(size_t size, uint16_t TimeoutMillisec, uint8_t NumberOfRetries, BACnetConnection *con, BACnetDevice &callback);
	virtual ~TsmPool();

	Tsm *create(void);
	Tsm *createUnconfirmed(BACnetDeviceAddress &destAddr, BACnetNpdu &nPDU, BACnetApdu &aPDU, BACnetBuffer &bUFF);

	Tsm *createConfirmed(BACnetVariable &var, uint8_t invokeId, BACnetDeviceAddress &destAddr, BACnetNpdu &nPDU,
			BACnetApdu &aPDU, BACnetBuffer &bUFF);

	Tsm *createConfirmed(const std::list<BACnetVariable *> &rpmLst, uint8_t invokeId,
			BACnetDeviceAddress &destAddr, BACnetNpdu &nPDU, BACnetRpmReq &rpmReq, BACnetBuffer &bUFF);

	void freeTsm(Tsm *oldTsm);

	int getAvailable(void);
	int getActiveListSize(void);

	void report(void);

	void process(void);

	Tsm *findWhoIs(uint32_t inst);
	Tsm *findByInvokeId(uint8_t const invokeId);

	void setApduTimeout(uint32_t nuTimeout);
	void setApduRetries(uint32_t nuRetry);
	void setApduTOutandRtry(uint32_t nuTimeout, uint32_t nuRetry);

};

#endif /* BACNETAPP_SRC_TSMPOOL_H_ */
