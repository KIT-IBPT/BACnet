/*
 * Tsm.cpp
 *
 *  Created on: May 22, 2018
 *      Author: 8w4
 */

#include <sstream>

#include "Tsm.h"
#include "BACnetConnection.h"
#include "BACnetDevice.h"

Tsm::Tsm()
: startTime(), TimeoutMilliseconds(0), NumberOfRetries(0), retryCount(0), invokeId(0),
  tsmState(&BACnetEnumTsmState::IDLE), addr(), npdu(), apdu(NULL), buff(), con(NULL), callback(NULL),
  varCallback(NULL), rpmCallBack(NULL), next(NULL)
{
	startTime.tv_sec = 0;
	startTime.tv_nsec = 0;
}

Tsm::~Tsm() {
	// TODO Auto-generated destructor stub
}

void Tsm::init(BACnetVariable *var, uint8_t invkId, BACnetTsmState const *tsmSTATE, BACnetDeviceAddress &addr,
		BACnetNpdu &nPDU, BACnetApdu &aPDU, BACnetBuffer &bUFF)
{
	clock_gettime(CLOCK_MONOTONIC, &startTime);
	this->retryCount = 0;
	this->varCallback = var;
	this->rpmCallBack = NULL;
	this->invokeId = invkId;
	this->tsmState = tsmSTATE;
	this->addr = addr;
	this->npdu = nPDU;
	this->apdu = &aPDU;
	this->buff = bUFF;
}

void Tsm::init(const std::list<BACnetVariable *> &rpmLst, uint8_t invkId, BACnetTsmState const *tsmSTATE,
			BACnetDeviceAddress &addr, BACnetNpdu &nPDU, BACnetRpmReq &rpmReq, BACnetBuffer &bUFF)
{
	clock_gettime(CLOCK_MONOTONIC, &startTime);
	this->retryCount = 0;
	this->varCallback = NULL;
	this->rpmCallBack = &rpmLst;
	this->invokeId = invkId;
	this->tsmState = tsmSTATE;
	this->addr = addr;
	this->npdu = nPDU;
	this->apdu = &rpmReq;
	this->buff = bUFF;
}

void Tsm::setNext(Tsm *next) {
	this->next = next;
}

Tsm *Tsm::getNext(void) {
	return this->next;
}

void Tsm::setTimeout(uint16_t timeout) {
	this->TimeoutMilliseconds = timeout;
}

void Tsm::setNumberOfRetries(uint8_t retries) {
	this->NumberOfRetries = retries;
}

void Tsm::setConnection(BACnetConnection *con) {
	this->con = con;
}

void Tsm::setCallback(BACnetDevice *callback) {
	this->callback = callback;
}

int Tsm::send(void) {

	/** Call back to the device and increment a tx-counter*/
	this->incrementTx(*this->callback);
	return this->con->sendBuffer(buff, addr);
}

BACnetApdu const *Tsm::getApdu(void) const {
	return this->apdu;
}

BACnetBuffer const &Tsm::getBuffer(void) const {
	return this->buff;
}

struct timespec const *Tsm::getStartTime(void) {
	return &startTime;
}

void Tsm::process(void) {

	ostringstream ss;

	struct timespec ts;

	if(*tsmState != BACnetEnumTsmState::IDLE) {

		/** Process the timer...*/
		clock_gettime(CLOCK_MONOTONIC, &ts);

		/** Time Difference In Milliseconds: Convert seconds to milliseconds (sec*1000) and
		 * convert nanoseconds to milliseconds (nanosec / 1000000) */
		uint64_t milliSecDiff = ((ts.tv_sec*1000) + (ts.tv_nsec/1000000)) -
				((startTime.tv_sec*1000) + (startTime.tv_nsec/1000000));

		if(milliSecDiff > (uint64_t) ((retryCount * TimeoutMilliseconds) + TimeoutMilliseconds)) {
			if(retryCount < NumberOfRetries) {

				this->retryCount++;

				ss << "This TSM has timed out {" << endl;

				/** Timeout info */
				ss << " Timeout Info: {Timeout (ms): " << milliSecDiff << ", Retries: " <<
						(unsigned int) retryCount << "}" << endl;

				/** Device Name*/
				if(this->callback != NULL) {
					ss << " Device Name: " << this->callback->getDeviceName() << endl;
					ss << " Device Instance: " << this->callback->getDeviceInstanceId() << endl;
				}
				else {
					ss << " Device Name: is NULL" << endl;
					ss << " Device Instance: is NULL" << endl;
				}

				/** PDU-Type & Service-Type*/
				if(this->apdu != NULL) {
					ss << " PDU-Type: " << this->apdu->getPduType()->getName() << endl;
					ss << " Service-Type: " << this->apdu->getServiceChoice()->getName() << endl;

					/** UNCONFIRMED_REQUEST do not have invoke-Id's*/
					if(this->apdu->getPduType() != &BACnetEnumPDUChoice::UNCONFIRMED_REQUEST) {
						ss << " Invoke-Id: " << (unsigned int) this->invokeId << endl;
					}
				}
				else {
					ss << " PDU-Type: is NULL" << endl;
					ss << " Service-Type: is NULL" << endl;
				}

				/** Object and  Property info for single variable*/
				if(this->varCallback != NULL) {
					ss << " Object-Id: " << this->varCallback->getObjectType().getName();
					ss << ":" << this->varCallback->getObjectInstance() << endl;
					ss << " Object-Property: " << this->varCallback->getObjectProperty().getName() << endl;
					if(this->varCallback->hasArrayIndex()) {
						ss << " Array Index: " << this->varCallback->getArrayIndex() << endl;
					}
				}

				/** Object and  Property info for RPM (i.e., multiple variables)*/
				if(this->rpmCallBack != NULL) {

					std::list<BACnetVariable *>::const_iterator itr = this->rpmCallBack->begin();

					ss << " List of Objects and Properties {" << endl;

					while(itr != this->rpmCallBack->end()) {

						int cntr = std::distance(this->rpmCallBack->begin(), itr);

						ss << "  Element[" << cntr << "] {" << endl;
						ss << "   Object-Id: " << (*itr)->getObjectType().getName();
						ss << ":" << (*itr)->getObjectInstance() << endl;
						ss << "   Object-Property: " << (*itr)->getObjectProperty().getName() << endl;

						if((*itr)->hasArrayIndex()) {
							ss << "   Array Index: " << (*itr)->getArrayIndex() << endl;
						}

						ss << "  }" << endl;

						itr++;
					}
					ss << " }" << endl;
				}

				ss << "} Re-sending the message now!" << endl;

				cout << ss.str() << endl;

				this->send();
			}
			else {
				cout << "This TSM has timed out: timeout: " << milliSecDiff << ", Retries: " << (unsigned int) retryCount <<
						", and there are no more retries left. Alert the application that the message failed." << endl;
				this->tsmState = &BACnetEnumTsmState::IDLE;

				/** TODO: Do some sort of callback and let the parent know what happened.*/
				this->callback->tsmApduTimeoutHandler(*this);
			}
		}
	}
}

BACnetVariable *Tsm::getCallbackVariable(void) const {
	return this->varCallback;
}

const std::list<BACnetVariable *> *Tsm::getRpmCallbackVariable(void) const {
	return this->rpmCallBack;
}

void Tsm::incrementTx(BACnetDevice &d) {
	d.incTx();
}

