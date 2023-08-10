/*
 * BACnetDevice.h
 *
 *  Created on: May 5, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETDEVICE_H_
#define BACNETAPP_SRC_BACNETDEVICE_H_

#include <stdint.h>
#include <string>

#include "BACnetConnection.h"
#include "BACnetDeviceAddress.h"
#include "BACnetObjIdentifier.h"
#include "BACnetWhoIsService.h"
#include "BACnetIamService.h"
#include "BACnetReadPropertyService.h"
#include "BACnetReadPropAck.h"
#include "BACnetComplexAck.h"
#include "BACnetWritePropService.h"
#include "TsmPool.h"
#include "MessagePool.h"
#include "BACnetApplicationData.h"
#include "ProtocolSvcSupported.h"
#include "BACnetObjPropRef.h"
#include "BACnetVariable.h"
#include "BnetReadAccessSpec.h"
#include "BACnetRpmReq.h"
#include "BACnetRpmAck.h"

#include "epicsMutex.h"
#include "epicsMessageQueue.h"

using namespace std;

#define DEFAULT_APDU_TIMEOUT 3000
#define DEFAULT_APDU_RETRIES 3

extern int BACnet_verbosity;

class BACnetDevice;

/** Map the device address as a string (ip:port:network:addr) to the object for easy retrieval */
typedef std::map<string, BACnetDevice *> addrToDevMap_t;

/** Map the device-instance to the object for easy retrieval */
typedef std::map<uint32_t, BACnetDevice *> instToDevMap_t;

/** Map the EPICS Name to the object for easy retrieval */
typedef std::map<string, BACnetDevice *> nameToDevMap_t;

/** Standard list of BACnetVariables*/
typedef std::list<BACnetVariable *> BACnetVariableList_t;

typedef std::list<BACnetVariableList_t> ListOfBacVarList_t;

class BACnetDevice {

private:
	string name;

	BACnetObjIdentifier objId;
	uint32_t maxApduLengthAccepted;
	BACnetSegmentation const *segmentationSupported;
	uint16_t vendorId;

	BACnetDeviceAddress addr;
	BACnetConnection *transport;

	epicsMutex lock;

	epicsMessageQueue rcvQue;

	TsmPool *tsmp;

	MessagePool *msgp;

	BACnetWhoIsService whois;

	BACnetReadPropertyService rps;
	BACnetRpmReq *rpmReq;

	BACnetWritePropService wps;

	/** map of key-names to device objects.*/
	static addrToDevMap_t addrToDevMap;

	/** Map of key-instances to device objects.*/
	static instToDevMap_t instToDevMap;

	/** Map of EPICS names to device objects.*/
	static nameToDevMap_t nameToDevMap;

	void registerInstance(uint32_t devInst);
	void registerAddress(string devAddrStr);
	void registerEpicsName(string devNameStr);

	static void verifyDeviceName(string const namestr);

	/* APDU Timeout in Milliseconds */
	uint16_t TimeoutMilliseconds;

	/* Number of APDU Retries */
	uint8_t NumberOfRetries;

	/** If greater than zero (0) then it is used to limit the size of the RPM message buffer*/
	uint16_t rpmBufferLimit;

	/** Used to disable RPM messaging even though the device supports it*/
	bool rpmDisable;

	enum BINDSTATUS {
		UNBOUND,
		WAITING_TO_BIND,
		BOUND
	};

	BINDSTATUS bindStatus;

	enum SVCSUPSTATUS {
		UNINITIALIZED,
		WAITING_FOR_REPLY,
		INITIALIZED
	};

	SVCSUPSTATUS serviceSupStatus;

	enum RPMSTATE {
		ZERO,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN
	};

	RPMSTATE rpmState;

	BACnetVariable *protoSvsSup;

	BACnetVariableList_t vars;
	BACnetVariableList_t varReadList;
	BACnetVariableList_t varWriteList;

	BACnetVariableList_t::const_iterator readIter;
	BACnetVariableList_t::const_iterator wpIter;

	BACnetVariableList_t::const_iterator rpmItr;

	ListOfBacVarList_t listOfRpmLists;
	ListOfBacVarList_t::const_iterator listOfRpmListsItr;

	ListOfBacVarList_t::const_iterator &processRpm(ListOfBacVarList_t::const_iterator &itr);
	BACnetVariableList_t::const_iterator &processRp(BACnetVariableList_t::const_iterator &itr);
	BACnetVariableList_t::const_iterator &processWp(BACnetVariableList_t::const_iterator &itr);
	void processRpmRpWp(void);
	void processRpWp(void);

	uint8_t invokeId;

	uint32_t tx;
	uint32_t rx;
	uint32_t er;

	void incTx(void);
	void incRx(void);
	void incEr(void);

	friend void Tsm::incrementTx(BACnetDevice &d);

	uint8_t requestInvokeId(void);

	static void procDevListThread(void *p);

	void sendReadPropertyReq(uint8_t invokeId, BACnetVariable &var);
	void sendReadPropertyMult(uint8_t invokeId, const std::list<BACnetVariable *> &rpmLst);
	void sendWritePropertyReq(uint8_t invokeId, BACnetVariable &var);

	void processMessageIn(MessageIn &msgIn);
	void unconfirmedReqHandler(BACnetBuffer &buff, BACnetDeviceAddress &addr);
	void iAmAckHandler(BACnetBuffer &buff, BACnetDeviceAddress &addr);
	void simpleAckHandler(BACnetBuffer &buff);
	void complexAckHandler(BACnetBuffer &buff);
	void readPropertyAckHandler(BACnetBuffer &buff, BACnetComplexAck &cak);
	void readPropMultAckHandler(BACnetBuffer &buff, BACnetComplexAck &cak);
	void verifyRpmResult(const BACnetVariable &bacVar, const BACnetObjIdentifier &objId,
			const BACnetPropertyType &propId, int arrayIndx);
	void bacnetErrorHandler(BACnetBuffer &buff);

	void initReadList(void);

	bool isServiceSupported(BACnetSvcSupChoice const &bacService) const;

	BACnetVariableList_t::const_iterator &firstPass(BACnetVariableList_t::const_iterator &itr);

	void createRpmList(BACnetVariableList_t &listIn, ListOfBacVarList_t &listOut);
	bool isRpmType(const BACnetApplicationDataTypeChoice &dataT,
			const BACnetPropertyType &prop, int &dataSize);

	void setApduTimeout(const string &strVal);
	void setApduRetries(const string &strVal);
	void setRpmBufferLimit(const string &strVal);
	void setRpmDisable(const string &strVal);

	static epicsEvent *pevent1;
	static epicsEvent *pevent2;

public:
	BACnetDevice();
	BACnetDevice(string const &devName, uint32_t devInst, string const &ifName, uint16_t devPort);
	virtual ~BACnetDevice();

	int sendTo(BACnetBVLL &bip, BACnetDeviceAddress const &dest) const;
	int recvFrom(BACnetDeviceAddress &src, BACnetBuffer &buff) const;

	void decodeIamData(BACnetDeviceAddress const &srcAddr, BACnetIamService const &iAm);

	void makeGlobalBroadcastAddress(BACnetDeviceAddress &addr) const;

	BACnetDeviceAddress const *getAddressData(void) const;
	string getDeviceName(void) const;
	uint32_t getDeviceInstanceId(void) const;
	BACnetObjIdentifier const *getObjectId(void) const;
	uint32_t getInstanceId(void) const;
	uint16_t getDevicePort(void) const;

	uint32_t getMaxApduLengthAccepted(void) const;
	BACnetSegmentation const *getSegmentationSupported(void) const;
	uint16_t getVendorId(void) const;

	bool isBound(void) const;

	void bindAddress(void);

	void sendWhoIsReqGlobal(void);
	void sendReadPropProtocolServicesSupported(void);

	BACnetConnection * const getTransport(void) const;

	void report(void) const;

	void process(void);

	void queMsgIn(BACnetDeviceAddress &srcAddr, BACnetBuffer &buff);

	void tsmApduTimeoutHandler(Tsm &tsm);

	BACnetVariable const *registerObjectProperty(BACnetVarFuncChoice const &func,
			BACnetObjPropRef const &ref, BACnetApplicationDataTypeChoice const &dataType);
	BACnetVariable const *registerObjectProperty(BACnetVarFuncChoice const &func, BACnetObjPropRef const &ref);
	BACnetVariable const *registerObjectProperty(BACnetVarFuncChoice const &func, BACnetObjectType const &objTyp,
			uint32_t objInst, BACnetPropertyType const &propId, int arrayIndex);
	BACnetVariable const *registerObjectProperty(BACnetVarFuncChoice const &func, BACnetObjectType const &objTyp,
			uint32_t objInst, BACnetPropertyType const &propId);

	void listVariables(void);

	static BACnetDevice *create(string const &devName, uint32_t devInst, string const &ifName, uint16_t devPort);
	static BACnetDevice *findDeviceByInst(uint32_t devInst);
	static BACnetDevice *findDeviceByAddress(BACnetDeviceAddress const &addr);
	static BACnetDevice *findDeviceByName(string const &epicsName);
	static size_t getInstMapSize(void);
	static size_t getAddrMapSize(void);
	static instToDevMap_t const *getDeviceList(void);
	static void start(void);
	static void stop(void);
	static void initialize(void);
	static bool sortVarsByObjIdProp(const BACnetVariable *first, const BACnetVariable *second);
	static void listDevices(void);

	void setIocShArgs(const string &argStr);

	uint32_t getTx(void) const;
	uint32_t getRx(void) const;
	uint32_t getEr(void) const;

};

#endif /* BACNETAPP_SRC_BACNETDEVICE_H_ */
