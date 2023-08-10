/*
 * TsmPool.cpp
 *
 *  Created on: May 25, 2018
 *      Author: 8w4
 */

#include "TsmPool.h"
#include "BACnetWhoIsService.h"
#include "BACnetDevice.h"

TsmPool::TsmPool(size_t size, uint16_t TimeoutMillisec, uint8_t NumberOfRetries, BACnetConnection *con,
		BACnetDevice &calllback)
:poolSize(size), callback(calllback)
{
	cout << "TsmPool::TsmPool(size_t size) " << size << endl;
	tsm = new Tsm[size];

	for(unsigned int i=0; i<(size-1); i++) {
		tsm[i].setTimeout(TimeoutMillisec);
		tsm[i].setNumberOfRetries(NumberOfRetries);
		tsm[i].setConnection(con);
		tsm[i].setCallback(&this->callback);
		tsm[i].setNext(&tsm[i+1]);
	}
	poolHead = &tsm[0];
	tsm[size-1].setNext(NULL);

	actListHead = NULL;
	actListTail = NULL;
}

TsmPool::~TsmPool() {
	delete[] tsm;
}

Tsm *TsmPool::create(void) {

	/** Two lists: The main pool from which all tsms come from and then there is the Active-List
	 * which is a list of TSMs that are actively in use...*/

	Tsm *nuTsm = poolHead;
	if(poolHead != NULL) {
		poolHead = nuTsm->getNext();

		if(actListHead == NULL) {
			actListHead = nuTsm;
			actListTail = nuTsm;

			actListHead->setNext(NULL);

		}
		else {
			nuTsm->setNext(actListHead);
			actListHead = nuTsm;
		}
	}

	return nuTsm;
}

void TsmPool::freeTsm(Tsm *freeTsm) {

	/** Remove from active-list first.*/

	if(freeTsm == NULL) {
		return;
	}

	if(freeTsm == actListHead) {
		actListHead = freeTsm->getNext();
		if(actListHead == NULL) {
			actListTail = NULL;
		}
		freeTsm->setNext(poolHead);
		poolHead = freeTsm;
		return;
	}

	Tsm *pp = actListHead;

	if(pp) {
		while(pp != NULL) {
			cout << "pp->getInvokeId(): " << pp->getInvokeId() << ", Next id: " << pp->getNext()->getInvokeId() << endl;
			if(pp->getNext() == freeTsm) {
				pp->setNext(freeTsm->getNext());

				/** End of list?*/
				if(freeTsm == actListTail) {
					actListTail = pp;
				}
				break;
			}
			pp = pp->getNext();
		}
	}

	freeTsm->setNext(poolHead);
	poolHead = freeTsm;
}

Tsm *TsmPool::createConfirmed(BACnetVariable &var, uint8_t invokeId, BACnetDeviceAddress &destAddr, BACnetNpdu &nPDU,
		BACnetApdu &aPDU, BACnetBuffer &bUFF)
{
	Tsm *nuTsm = create();
	nuTsm->init(&var, invokeId, &BACnetEnumTsmState::AWAIT_RESPONSE, destAddr, nPDU, aPDU, bUFF);
	return nuTsm;
}

Tsm *TsmPool::createConfirmed(const std::list<BACnetVariable *> &rpmLst, uint8_t invokeId,
		BACnetDeviceAddress &destAddr, BACnetNpdu &nPDU, BACnetRpmReq &rpmReq, BACnetBuffer &bUFF)
{
	Tsm *nuTsm = create();
	nuTsm->init(rpmLst, invokeId, &BACnetEnumTsmState::AWAIT_RESPONSE, destAddr, nPDU, rpmReq, bUFF);
	return nuTsm;
}

Tsm *TsmPool::createUnconfirmed(BACnetDeviceAddress &destAddr, BACnetNpdu &nPDU, BACnetApdu &aPDU, BACnetBuffer &bUFF)
{
	Tsm *nuTsm = NULL;

	/** TSMs aren't supposed to be created for unconfirmed services, according to the BACnet standard,
	 * but an I-AM response is supposed to follow a WHO-IS service request, so it only makes sense to keep track
	 * of when you send a WHO-IS service request so that you can re-send it if a device doesn't reply with an I-AM.
	 * So If this is a Who-Is message then we will wait for an I-AM reply*/
	if(*aPDU.getPduType() == BACnetEnumPDUChoice::UNCONFIRMED_REQUEST) {
		if(*aPDU.getServiceChoice() == BACnetEnumUnconfirmedService::WHO_IS) {
			nuTsm = create();
			nuTsm->init(NULL, 0, &BACnetEnumTsmState::AWAIT_IAM, destAddr, nPDU, aPDU, bUFF);
		}
	}
	else {
		/** TODO: probably need to throw if either of the two conditions above are not true.*/
	}

	return nuTsm;
}

int TsmPool::getAvailable(void) {
	int n = 0;

	Tsm *t = poolHead;
	while(t != NULL) {
		n++;
		t = t->getNext();
	}
	return n;
}

int TsmPool::getActiveListSize(void) {
	int n = 0;

	Tsm *t = actListHead;
	while(t != NULL) {
		n++;
		t = t->getNext();
	}
	return n;
}

void TsmPool::report(void) {

	cout << "getAvailable(): " << getAvailable() << endl;
	cout << "getActiveListSize(): " << getActiveListSize() << endl;

	Tsm *t = actListHead;
	while(t != NULL) {
		cout << "actListHead->getInvokeId(): " << (unsigned int) t->getInvokeId() << endl;
		t = t->getNext();
	}
}


void TsmPool::process(void) {
	Tsm *t = actListHead;
	while(t != NULL) {
		t->process(); //TODO: do something with Tsm...
		t = t->getNext();
	}
}

Tsm *TsmPool::findWhoIs(uint32_t inst) {
	Tsm *t = actListHead;
	while(t != NULL) {
		if(*t->getApdu()->getPduType() == BACnetEnumPDUChoice::UNCONFIRMED_REQUEST) {
			if(*t->getApdu()->getServiceChoice() == BACnetEnumUnconfirmedService::WHO_IS) {
				BACnetWhoIsService *whois = (BACnetWhoIsService *) t->getApdu();
				if(inst == whois->getHighRangeInstance()) {
					return t;
				}
			}
		}
		t = t->getNext();
	}
	return t;
}

Tsm *TsmPool::findByInvokeId(uint8_t const invokeId) {
	Tsm *t = actListHead;
	while(t != NULL) {
		if(t->getInvokeId() == invokeId) {
			return t;
		}
		t = t->getNext();
	}
	return t;
}

void TsmPool::setApduTimeout(uint32_t nuTimeout) {
	for(unsigned int i=0; i<(poolSize-1); i++) {
		tsm[i].setTimeout(nuTimeout);
	}
}

void TsmPool::setApduRetries(uint32_t nuRetry) {
	for(unsigned int i=0; i<(poolSize-1); i++) {
		tsm[i].setNumberOfRetries(nuRetry);
	}
}

void TsmPool::setApduTOutandRtry(uint32_t nuTimeout, uint32_t nuRetry) {
	for(unsigned int i=0; i<(poolSize-1); i++) {
		tsm[i].setTimeout(nuTimeout);
		tsm[i].setNumberOfRetries(nuRetry);
	}
}


