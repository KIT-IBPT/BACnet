/*
 * BACnetConnection.h
 *
 *  Created on: Sep 5, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETCONNECTION_H_
#define BACNETAPP_SRC_BACNETCONNECTION_H_

//System
#include <stdint.h>
#include <string>
#include <list>
#include <map>

// EPICS Base
#include <osiSock.h>
#include "epicsMessageQueue.h"
#include "epicsThread.h"

#include "BACnetBuffer.h"
#include "BACnetDeviceAddress.h"
#include "BACnetBVLL.h"
#include "Tsm.h"


using namespace std;

#define DEFAULT_BACNET_PORT 0xBAC0

struct inAddrComp {
	bool operator() (const struct in_addr &lhs, const struct in_addr &rhs) const
	{return lhs.s_addr < rhs.s_addr;}
};

class BACnetConnection {

private:

	/** A total count of the objects using this connection*/
	int refCount;

	/** file descriptor*/
	SOCKET bacnetSocket;

	/** Default BACnet port, stored in network byte order.*/
	uint16_t bacnetPort;

	/** Network Interface Name*/
	string ifName;

	/** IPv4 Address*/
	struct in_addr addr;

	/** Broadcast Address*/
	struct in_addr broadaddr;

	/** Netmask*/
	struct in_addr netmask;

	/** Hardware/MAC address*/
	uint8_t hwaddr[6];

	static std::map<string, BACnetConnection *> connectionMap;
	static std::map<struct in_addr, BACnetConnection *, inAddrComp> ipToConnMap;

	static int addIpToMap(struct in_addr const * const addr, BACnetConnection *con);
	static int addConnToMap(string const &ifname, uint16_t const port, BACnetConnection *conn);

	static int maxSocket;

	static epicsMessageQueue *sndQue;

	/** Throws exception*/
	void initialize(string const &ifname);

	SOCKET getSocket(void);

	static bool isIamMessage(BACnetBuffer &buff, BACnetObjIdentifier &objId);
	static void decodeAddressInfo(BACnetBuffer &buff, const struct sockaddr_in &socketIpAddr, BACnetDeviceAddress &srcAddr);

	static epicsEvent *pevent1;
	static epicsEvent *pevent2;

	static bool bvllIsValid(BACnetBuffer &buff, int rcvd, const struct sockaddr_in &sockIpAddr, BACnetDeviceAddress &addr);

public:
	BACnetConnection();
	BACnetConnection(string const &ifname);
	BACnetConnection(string const &ifname, uint16_t port);

	virtual ~BACnetConnection();

	static BACnetConnection *create (string const &ifname, uint16_t port, int level);
	static BACnetConnection *getConnectionByKey(string const &key);

	static void release(BACnetConnection *con, int level);

	static int recvAll(BACnetDeviceAddress &src, BACnetBuffer &buff);
	static void sendThread(void *p);

	static void start(void);
	static void stop(void);

	/** Throws...*/
	void connect();
	void disconnect();

	int sendBuffer(BACnetBuffer &buff, BACnetDeviceAddress const &dest);
	void sendTsm(Tsm *tsm);
	int sendBip(BACnetBVLL &bip, BACnetDeviceAddress const &dest);
	int recvFrom(BACnetDeviceAddress &src, BACnetBuffer &buff);

	string const &getInterfaceName(void) const;
	struct in_addr const * const getIpAddress(void) const;
	struct in_addr const * const getBroadcastAddress(struct in_addr *addr) const;
	void getBroadcastAddress(BACnetDeviceAddress &addr) const;
	struct in_addr const * const getNetmask(void) const;
	uint8_t const * const getHardwareAddress(void) const;
	uint16_t getPortAsNetworkByteOrder(void) const;
	uint16_t getPortAsHostByteOrder(void) const;

	string getIpAddressToString(void) const;
	string getBroadcastAddressToString(void) const;
	string getNetmaskToString(void) const;
	string getHardwareAddressToString(void) const;

	static string convertNetAddrToString(struct in_addr const *addr);
};

#endif /* BACNETAPP_SRC_BACNETCONNECTION_H_ */
