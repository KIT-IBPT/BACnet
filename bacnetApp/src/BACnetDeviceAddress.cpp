/*
 * BACnetDeviceAddress.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: 8w4
 */

#include "BACnetDeviceAddress.h"

#include <cstring>
#include <sstream>
#include <stdexcept>
#include <iomanip>

BACnetDeviceAddress::BACnetDeviceAddress() {

	memset(&ipv4_addr, 0, sizeof(in_addr));
	ip_port = 0;
	network = 0;
	addr_len = 0;
	memset(addr, 0, MAX_MAC_LENGTH);
}

BACnetDeviceAddress::BACnetDeviceAddress(BACnetDeviceAddress const &oldAddr) {

	copyAddressData(*this, oldAddr);
}

BACnetDeviceAddress::BACnetDeviceAddress(struct in_addr const * const ipv4, uint16_t const port) {

	memcpy(&ipv4_addr, ipv4, sizeof(in_addr));
	ip_port = htons(port);

	network = 0;
	addr_len = 0;
	memset(addr, 0, MAX_MAC_LENGTH);
}

BACnetDeviceAddress::BACnetDeviceAddress(struct in_addr const * const ipv4, uint16_t const port,
		uint16_t const net, uint8_t const address_length, uint8_t const * const address) {

	memcpy(&ipv4_addr, ipv4, sizeof(in_addr));
	ip_port = htons(port);

	network = net;
	addr_len = address_length;
	memset(addr, 0, MAX_MAC_LENGTH);
	memcpy(&addr, address, addr_len);

}

BACnetDeviceAddress::~BACnetDeviceAddress() {
	// TODO Auto-generated destructor stub
}

void BACnetDeviceAddress::setAddressData(BACnetDeviceAddress const &addrData) {
	memcpy(&this->ipv4_addr, &addrData.ipv4_addr, sizeof(in_addr));
	this->ip_port = addrData.ip_port;

	this->network = addrData.network;
	this->addr_len = addrData.addr_len;
	memcpy(this->addr, &addrData.addr, addr_len);
}

void BACnetDeviceAddress::setIpAddress(struct in_addr const *ipv4) {
	memcpy(&ipv4_addr, ipv4, sizeof(in_addr));
}

void BACnetDeviceAddress::setSockaddrIn(sockaddr_in const *sockaddrin) {
	memcpy(&ipv4_addr, &sockaddrin->sin_addr, sizeof(in_addr));
	this->ip_port = sockaddrin->sin_port;
}

/** port parameter is passed in host byte order*/
void BACnetDeviceAddress::setIpPortAs_htons(uint16_t const port) {
	ip_port = htons(port);
}

/** port parameter is passed in network byte order*/
void BACnetDeviceAddress::setIpPortAs_ntohs(uint16_t const port) {
	ip_port = port;
}

void BACnetDeviceAddress::setRemoteNetwork(uint16_t const netwrk) {
	network = netwrk;
}

void BACnetDeviceAddress::setRemoteNetworkAddress(uint8_t const *src, uint8_t const src_len) {
	addr_len = src_len;
	memcpy(&addr, src, addr_len);
}

void BACnetDeviceAddress::getAddressData(BACnetDeviceAddress &addr) const {
	copyAddressData(addr, *this);
}

void BACnetDeviceAddress::copyAddressData(BACnetDeviceAddress &copyTo, BACnetDeviceAddress const &copyFrom) {

	memcpy(&copyTo.ipv4_addr, &copyFrom.ipv4_addr, sizeof(in_addr));
	copyTo.ip_port = copyFrom.ip_port;

	copyTo.network = copyFrom.network;
	copyTo.addr_len = copyFrom.addr_len;
	memcpy(&copyTo.addr, &copyFrom.addr, copyTo.addr_len);

}

void BACnetDeviceAddress::makeGlobalBroadcast(struct in_addr const *ipv4, uint16_t const port) {

	memcpy(&ipv4_addr, ipv4, sizeof(in_addr));	//Must be an IP-Broadcast address from network card.
	ip_port = htons(port);

	network = BACNET_BROADCAST_NETWORK;
	addr_len = 0;
	memset(addr, 0, MAX_MAC_LENGTH);
}

struct in_addr const * const BACnetDeviceAddress::getIpAddress(void) const {
	return &ipv4_addr;
}

/** Network byte order*/
uint16_t BACnetDeviceAddress::getIpPortAsNetworkByteOrder() const {
	return ip_port;
}

/** Host byte order*/
uint16_t BACnetDeviceAddress::getIpPortAsHostByteOrder() const {
	return ntohs(ip_port);
}

uint16_t BACnetDeviceAddress::getRemoteNetwork(void) const {
	return network;
}

uint8_t BACnetDeviceAddress::getRemoteNetworkAddressLength(void) const {
	return addr_len;
}

uint8_t const * const BACnetDeviceAddress::getRemoteNetowrkAddress(void) const {
	return addr;
}

string BACnetDeviceAddress::getIpAddressAsString(void) const {

	char c[INET_ADDRSTRLEN];
	string str = inet_ntop(AF_INET, &ipv4_addr, c, INET_ADDRSTRLEN);

	return str;
}

string BACnetDeviceAddress::getPortAsString(void) const {
	stringstream ss;
	ss << ntohs(this->ip_port);
	return ss.str();
}

string BACnetDeviceAddress::getRemoteAddressAsString(void) const {

	stringstream ss;

	if(addr_len > 0) {
		for(int i=0; i<addr_len; i++) {
			if(i < (addr_len-1)) {
				ss << "0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) addr[i] << ':';
			}
			else {
				ss << "0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) addr[i];
			}
		}
	}
	else {
		ss << "NONE";
	}

	return ss.str();
}

string BACnetDeviceAddress::getAddressAsString(void) const {
	stringstream ss;

	ss << getIpAddressAsString() << ":" << getPortAsString() << ":" << getRemoteNetwork() <<
			":" << getRemoteAddressAsString();
	return ss.str();
}

bool BACnetDeviceAddress::isBound(void) const {
	if(this->ipv4_addr.s_addr > 0) {
		return true;
	}
	return false;
}

std::ostream& operator<< (std::ostream &out, const BACnetDeviceAddress &bacaddr)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "BACnetDeviceAddress {" << endl;
    out << "\tIPv4 Address: " << bacaddr.getIpAddressAsString() << endl;
    out << "\tIPv4 Port: " << ntohs(bacaddr.ip_port) << endl;
    out << "\tNetwork: " << bacaddr.network << endl;
    out << "\tRemote Address Length: " << (unsigned int) bacaddr.addr_len << endl;
    out << "\tRemote Address: " << bacaddr.getRemoteAddressAsString() << endl;
    out << "} BACnetDeviceAddress" << endl;

    return out;
}

void BACnetDeviceAddress::clear(void) {
	memset(&ipv4_addr, 0, sizeof(in_addr));
	ip_port = 0;
	network = 0;
	addr_len = 0;
	memset(addr, 0, MAX_MAC_LENGTH);
}

bool BACnetDeviceAddress::operator == (const BACnetDeviceAddress &right) const {

	if(this->ipv4_addr.s_addr == right.ipv4_addr.s_addr) {
		if(this->ip_port == right.ip_port) {
			if(this->network == right.network) {
				if(this->addr_len == right.addr_len) {
					if(this->addr_len > 0) {
						for(int i=0; i<this->addr_len; i++) {
							if(this->addr[i] != right.addr[i]) {
								return false;
							}
						}
						return true;
					}
					else {
						return true;
					}
				}
			}
		}
	}
	return false;
}

