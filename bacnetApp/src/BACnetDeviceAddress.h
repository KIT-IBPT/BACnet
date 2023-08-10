/*
 * BACnetDeviceAddress.h
 *
 *  Created on: Sep 6, 2017
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETDEVICEADDRESS_H_
#define BACNETAPP_SRC_BACNETDEVICEADDRESS_H_

#include <iostream>
#include <stdint.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define MAX_MAC_LENGTH 6
#define BACNET_BROADCAST_NETWORK 0xFFFF

class BACnetDeviceAddress {
private:

	/** IPV4 address and ip_port.*/
	struct in_addr ipv4_addr;	/** In network byte order.*/
	uint16_t ip_port;			/** In network byte order.*/

	/** Remote Network number */
	uint16_t network;

	/** Address on remote network.*/
	uint8_t addr_len;
	uint8_t addr[MAX_MAC_LENGTH];

public:
	BACnetDeviceAddress();
	BACnetDeviceAddress(BACnetDeviceAddress const &oldAddr);
	BACnetDeviceAddress(struct in_addr const * const ipv4, uint16_t const port);

	BACnetDeviceAddress(struct in_addr const * const ipv4, uint16_t const port,
			uint16_t const netwrk, uint8_t const address_length, uint8_t const * const address);

	virtual ~BACnetDeviceAddress();

	/** Copy the parameter 'addrData' to the local object, i.e., this.*/
	void setAddressData(BACnetDeviceAddress const &addrData);

	/** Stored in network byte order.*/
	void setIpAddress(struct in_addr const *ipv4);

	void setSockaddrIn(sockaddr_in const *sockaddrin);

	/** port parameter is passed in host byte order*/
	void setIpPortAs_htons(uint16_t const port);

	/** port parameter is passed in network byte order*/
	void setIpPortAs_ntohs(uint16_t const port);

	void setRemoteNetwork(uint16_t const netwrk);
	void setRemoteNetworkAddress(uint8_t const *src, uint8_t const src_len);
	void makeGlobalBroadcast(struct in_addr const *ipv4, uint16_t const port);

	/** Stored in network byte order.*/
	struct in_addr const * const getIpAddress(void) const;
	/** Stored in network byte order.*/
	uint16_t getIpPortAsNetworkByteOrder(void) const;
	uint16_t getIpPortAsHostByteOrder(void) const;
	uint16_t getRemoteNetwork(void) const;
	uint8_t getRemoteNetworkAddressLength(void) const;
	uint8_t const *const getRemoteNetowrkAddress(void) const;
	void getAddressData(BACnetDeviceAddress &addr) const;
	static void copyAddressData(BACnetDeviceAddress &copyTo, BACnetDeviceAddress const &copyFrom);

	string getIpAddressAsString(void) const;
	string getPortAsString(void) const;
	string getRemoteAddressAsString(void) const;
	string getAddressAsString(void) const;

	bool isBound(void) const;

	friend std::ostream& operator<< (std::ostream &out, const BACnetDeviceAddress &bacaddr);

	void clear(void);
	bool operator == (const BACnetDeviceAddress &right) const;

};

#endif /* BACNETAPP_SRC_BACNETDEVICEADDRESS_H_ */
