/*
 * BACnetConnection.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: 8w4
 */

#include "BACnetConnection.h"

#include <sstream>
#include <cstring>
#include <stdexcept>
#include <iomanip>

#include "BACnetBvllOrigUnicastNpdu.h"
#include "BACnetBVLLOrigBcastNPDU.h"
#include "BACnetBvllForwardedNpdu.h"
#include "BACnetNpdu.h"
#include "BACnetDevice.h"
#include "BACnetTag.h"

std::map<string, BACnetConnection *> BACnetConnection::connectionMap;
std::map<struct in_addr, BACnetConnection *, inAddrComp> BACnetConnection::ipToConnMap;

int BACnetConnection::maxSocket = 0;

epicsMessageQueue *BACnetConnection::sndQue = new epicsMessageQueue(255, sizeof(void *));

epicsEvent *BACnetConnection::pevent1 = new epicsEvent;
epicsEvent *BACnetConnection::pevent2 = new epicsEvent;

BACnetConnection::BACnetConnection()
: refCount(0), bacnetSocket(-1), bacnetPort(htons(DEFAULT_BACNET_PORT))
{

	ifName = "null";
	memset(&addr, 0, sizeof(in_addr));
	memset(&broadaddr, 0, sizeof(in_addr));
	memset(&netmask, 0, sizeof(in_addr));
	memset(&hwaddr, 0, sizeof(hwaddr));

}

BACnetConnection::BACnetConnection(string const &ifname)
: refCount(0), bacnetSocket(-1), bacnetPort(htons(DEFAULT_BACNET_PORT))
{
	this->initialize(ifname);
	this->connect();
}

BACnetConnection::BACnetConnection(string const &ifname, uint16_t port)
: refCount(0), bacnetSocket(-1), bacnetPort(htons(port))
{
	/** Initialize the connection and get a socket and all the network interface details.*/
	this->initialize(ifname);

	/** We need the max socket for the mutiplex selec in recvAll*/
	if(this->bacnetSocket > maxSocket) {
		maxSocket = this->bacnetSocket;
	}

	/** Add the connection object to the map*/
	addConnToMap(ifname, port, this);

	/** Add the Ip address to the map.*/
	addIpToMap(&this->addr, this);

	/** Bind to the socket...*/
	this->connect();

	this->refCount++;

}

int BACnetConnection::addIpToMap(struct in_addr const * const addr, BACnetConnection *con) {

	/** Create an iterator and search for the addr.*/
	std::map<struct in_addr, BACnetConnection *>::iterator itr = ipToConnMap.find(*addr);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != ipToConnMap.end()) {
		cout << "BACnetConnection::addIpToConnMap: IP address already exists in map " << convertNetAddrToString(addr) << " just return." << endl;
		return 0;
	}
	else {
		/** Return variable to hold the status of the map.insert */
		std::pair<std::map<struct in_addr, BACnetConnection *>::iterator,bool> ret1;

		/** Try to insert the map (key, value) */
		ret1 = ipToConnMap.insert(std::pair<struct in_addr, BACnetConnection *>(*addr, con));

		if(ret1.second) {
			return 1;
		}

		/** Something went wrong. map.insert failed*/
		ostringstream os;
		std::string s = "BACnetConnection::addIpToMap(in_addr_t addr, BACnetConnection *con):\n"
				"map.insert failed " + convertNetAddrToString(addr);
		throw std::invalid_argument(s);
	}
}

int BACnetConnection::addConnToMap(string const &ifname, uint16_t const port, BACnetConnection *conn) {

	/** For string concatenation*/
	stringstream ss;

	/** Concatenate the ifname and the port to create a unique key for the map.*/
	ss << ifname << ":" << port;

	/** Return variable to hold the status of the map.insert */
	std::pair<std::map<string, BACnetConnection *>::iterator,bool> ret1;

	/** Try to insert the map (key, value) */
	ret1 = connectionMap.insert(std::pair<string, BACnetConnection *>(ss.str(), conn));

	if(ret1.second) {
		return 1;
	}

	/** Something went wrong. map.insert failed*/
	ostringstream os;
	std::string s = "BACnetConnection::addConnToMap(string const &ifname, uint16_t const port, BACnetConnection *conn):\n"
			"map.insert failed " + ss.str();
	throw std::invalid_argument(s);

}

BACnetConnection *BACnetConnection::create(string const &ifname, uint16_t port, int level) {

	/** For string concatenation*/
	stringstream ss;

	/** Concatenate the ifname and the port to create a unique key for the map.*/
	ss << ifname << ":" << port;

	/** Create an iterator and search for the key (string).*/
	std::map<string, BACnetConnection *>::iterator itr = connectionMap.find(ss.str());

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != connectionMap.end()) {
		if(level > 0) {
			cout << "BACnetConnection already created: " << ss.str() << " increment refCount and return." << endl;
		}

		/** We have a new object referencing this connection, need to increment refCount*/
		itr->second->refCount++;

		/** Return the object that has already been created.*/
		return itr->second;
	}
	else {
		if(level > 0) {
			cout << "BACnetConnection NOT found: " << ss.str() << " Creating a new one" << endl;
		}

		return new BACnetConnection(ifname, port);
//		BACnetConnection *bc = new BACnetConnection(ifname, port);
//
//		if(bc) {
//			return bc;
//		}
//		else {
//			return NULL;	/** Throw instead? I never can make up my mind which is better...*/
//		}
	}

}

void BACnetConnection::release(BACnetConnection *con, int level) {

	stringstream errStr;

	/** If the connection actually exists*/
	if(con) {
		/** If there are references then decrement the reference counter.*/
		if(con->refCount > 0) {
			if(level > 0) {
				cout << "decrementing con->refCount: " << con->refCount << endl;
			}
			con->refCount--;
		}

		/** If the connection has no more references then remove it from the maps and delete the object.*/
		if(con->refCount == 0) {

			if(level > 0) {
				cout << "con->refCount is == 0: " << endl;
			}

			/** Create an iterator and search for the addr.*/
			size_t rv = ipToConnMap.erase(con->addr);

			if(level > 0) {
				cout << "rv = ipToConnMap.erase(con->addr): " << rv << endl;
			}

			if(rv < 1) {
				errStr << "BACnetConnection::release(BACnetConnection *con): ipToConnMap.erase(con->addr) failed " << endl;
				throw std::invalid_argument(errStr.str());
			}

			/** For string concatenation*/
			stringstream ss;

			/** Concatenate the ifname and the port to create a unique key for the map.*/
			ss << con->ifName << ":" << con->getPortAsHostByteOrder();
			rv = connectionMap.erase(ss.str());

			if(level > 0) {
				cout << "rv = connectionMap.erase(ss.str()): " << rv << endl;
			}

			if(rv < 1) {
				errStr << "BACnetConnection::release(BACnetConnection *con): connectionMap.erase(ss.str()) failed " << endl;
				throw std::invalid_argument(errStr.str());
			}

			delete con;
			con = NULL;
		}
	}
	else {
		/** Something went wrong.*/
		errStr << "Error: BACnetConnection::release(BACnetConnection *con) was called but con == 0" << endl;
		throw std::invalid_argument(errStr.str());
	}
}

BACnetConnection *BACnetConnection::getConnectionByKey(string const &key) {

	std::map<string, BACnetConnection *>::iterator itr = BACnetConnection::connectionMap.find(key);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != BACnetConnection::connectionMap.end()) {
		return itr->second;
	}
	else
		return NULL;
}

BACnetConnection::~BACnetConnection() {
	//cout << "BACnetConnection::~BACnetConnection() " << endl;
	if (bacnetSocket != 0)
	{
		epicsSocketDestroy(bacnetSocket);
	}
}

string const &BACnetConnection::getInterfaceName(void) const {
	return ifName;
}

struct in_addr const * const BACnetConnection::getIpAddress(void) const {
	return &addr;
}

struct in_addr const * const BACnetConnection::getBroadcastAddress(struct in_addr *addr) const {
	if(addr) {
		memcpy(addr, &broadaddr, sizeof(in_addr));
		return &broadaddr;
	}
	return &broadaddr;
}

void BACnetConnection::getBroadcastAddress(BACnetDeviceAddress &addr) const {
	addr.setIpAddress(&broadaddr);
}

struct in_addr const * const BACnetConnection::getNetmask(void) const {
	return &netmask;
}

uint8_t const * const BACnetConnection::getHardwareAddress(void) const {
	return hwaddr;
}

uint16_t BACnetConnection::getPortAsNetworkByteOrder(void) const {
	return bacnetPort;
}

uint16_t BACnetConnection::getPortAsHostByteOrder(void) const {
	return ntohs(bacnetPort);
}

string BACnetConnection::convertNetAddrToString(struct in_addr const *addr) {

	char c[INET_ADDRSTRLEN];
	string str = inet_ntop(AF_INET, addr, c, INET_ADDRSTRLEN);

	return str;
}

/** addr To String...*/
string BACnetConnection::getIpAddressToString(void) const {

	char c[INET_ADDRSTRLEN];
	string str = inet_ntop(AF_INET, &addr, c, INET_ADDRSTRLEN);

	return str;
}

/** broadcast To String...*/
string BACnetConnection::getBroadcastAddressToString(void) const {

	char c[INET_ADDRSTRLEN];
	string str = inet_ntop(AF_INET, &broadaddr, c, INET_ADDRSTRLEN);

	return str;
}

/** netmask To String...*/
string BACnetConnection::getNetmaskToString(void) const {

	char c[INET_ADDRSTRLEN];
	string str = inet_ntop(AF_INET, &netmask, c, INET_ADDRSTRLEN);

	return str;
}

/** hwaddr To String... 00:00:00:00:00:00*/
string BACnetConnection::getHardwareAddressToString(void) const {

	const int MAX_LEN = 6;
	stringstream ss;

	for(int i=0; i<MAX_LEN; i++) {
		if(i < (MAX_LEN-1)) {
			ss << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) hwaddr[i] << ':';
		}
		else {
			ss << std::hex << (unsigned int) hwaddr[i];
		}
	}

	return ss.str();
}

SOCKET BACnetConnection::getSocket(void) {
	return this->bacnetSocket;
}

void BACnetConnection::initialize(string const &ifname) {
	stringstream ss;

	if(ifname.length() > IFNAMSIZ) {
		ss << "BACnetConnection::initialize(string const &ifname):\n"
				"\tUser supplied interface name (\"" << ifname << "\" (" << ifname.length() <<
				"))is too long when compared to IFNAMSIZ (" << IFNAMSIZ << ")" << endl;
		throw std::invalid_argument(ss.str());
	}

	/** Before we can check that ifname is a valid network interface name and
	 * get all of the network interface info we have to open a socket to use ioctl()*/

	struct sockaddr_in *addrin;

	int erno = 0;
	/* Create the UDP socket */
	bacnetSocket = epicsSocketCreate(AF_INET, SOCK_DGRAM, 0);
	erno = errno;
	if (bacnetSocket < 0 || erno != 0) {
		ss << "BACnetConnection::initialize: Failed to create socket with file descriptor: ( " << bacnetSocket
				<< ") and errno: (" << erno << ")" << strerror(erno) << endl;
		close(bacnetSocket);
		throw std::invalid_argument(ss.str());
	}

	/** Create a structure that holds the information from ioctl()*/
	struct ifreq ifReq;

	/** In order to get the sockaddr from ioctl() you have to set the
	 * interface name and family of the structure.*/
	ifReq.ifr_ifru.ifru_addr.sa_family = AF_INET;
	strncpy(ifReq.ifr_ifrn.ifrn_name, ifname.c_str(), IFNAMSIZ);

	/** First call gets the IPV4 address.*/
	int rx = ioctl(bacnetSocket, SIOCGIFADDR, &ifReq);
	erno = errno;
	if (rx < 0 || erno != 0) {
		ss.str("");
		ss << "BACnetConnection::initialize: ioctl(sfd, SIOCGIFADDR, &ifReq) Failed!\n"
				"\tFailed to get IPV4 address using name \"" << ifReq.ifr_ifrn.ifrn_name << "\""
				" and family AF_INET (" << ifReq.ifr_ifru.ifru_addr.sa_family << ")\n"
				"\tioctl() returned : ( " << rx << "), and errno: (" << erno << ") \""
				<< strerror(erno) << "\"" << endl;
		close(bacnetSocket);
		throw std::invalid_argument(ss.str());
	}

	/** The ioctl() call succeeded... therefore the name supplied must exist.*/
	this->ifName = string(ifname);
	addrin = (sockaddr_in *) &ifReq.ifr_ifru.ifru_addr;
	memcpy(&addr, &addrin->sin_addr, sizeof(in_addr));

	/** First call gets the IPV4 Broadcast address.*/
	rx = ioctl(bacnetSocket, SIOCGIFBRDADDR, &ifReq);
	erno = errno;
	if (rx < 0 || erno != 0) {
		ss.str("");
		ss << "BACnetConnection::initialize: ioctl(sfd, SIOCGIFBRDADDR, &ifReq) Failed!\n"
				"\tFailed to get IPV4 address using name \"" << ifReq.ifr_ifrn.ifrn_name << "\""
				" and family AF_INET (" << ifReq.ifr_ifru.ifru_addr.sa_family << ")\n"
				"\tioctl() returned : ( " << rx << "), and errno: (" << erno << ") \""
				<< strerror(erno) << "\"" << endl;
		close(bacnetSocket);
		throw std::invalid_argument(ss.str());
	}

	addrin = (sockaddr_in *) &ifReq.ifr_ifru.ifru_addr;
	memcpy(&broadaddr, &addrin->sin_addr, sizeof(in_addr));

	/** First call gets the IPV4 netmask.*/
	rx = ioctl(bacnetSocket, SIOCGIFNETMASK, &ifReq);
	erno = errno;
	if (rx < 0 || erno != 0) {
		ss.str("");
		ss << "BACnetConnection::initialize: ioctl(sfd, SIOCGIFNETMASK, &ifReq) Failed!\n"
				"\tFailed to get IPV4 address using name \"" << ifReq.ifr_ifrn.ifrn_name << "\""
				" and family AF_INET (" << ifReq.ifr_ifru.ifru_addr.sa_family << ")\n"
				"\tioctl() returned : ( " << rx << "), and errno: (" << erno << ") \""
				<< strerror(erno) << "\"" << endl;
		close(bacnetSocket);
		throw std::invalid_argument(ss.str());
	}

	addrin = (sockaddr_in *) &ifReq.ifr_ifru.ifru_addr;
	memcpy(&netmask, &addrin->sin_addr, sizeof(in_addr));

	/** First call gets the MAC address.*/
	rx = ioctl(bacnetSocket, SIOCGIFHWADDR, &ifReq);
	erno = errno;
	if (rx < 0 || erno != 0) {
		ss.str("");
		ss << "BACnetConnection::initialize: ioctl(sfd, SIOCGIFHWADDR, &ifReq) Failed!\n"
				"\tFailed to get IPV4 address using name \"" << ifReq.ifr_ifrn.ifrn_name << "\""
				" and family AF_INET (" << ifReq.ifr_ifru.ifru_addr.sa_family << ")\n"
				"\tioctl() returned : ( " << rx << "), and errno: (" << erno << ") \""
				<< strerror(erno) << "\"" << endl;
		close(bacnetSocket);
		throw std::invalid_argument(ss.str());
	}

	memcpy(&hwaddr, &ifReq.ifr_ifru.ifru_addr.sa_data, 6);

}

/** Throws...*/
void BACnetConnection::connect(void) {

	stringstream ss;

	int erno = 0;
	/* Create the UDP socket */
	if(bacnetSocket < 0) {
		bacnetSocket = epicsSocketCreate(AF_INET, SOCK_DGRAM, 0);
	}
	erno = errno;
	if (bacnetSocket < 0 || erno != 0) {
		ss << "BACnetConnection::connect: Failed to create socket with file descriptor: ( " << bacnetSocket
				<< ") and errno: (" << erno << ")" << strerror(erno) << endl;
		close(bacnetSocket);
		bacnetSocket = -1;
		throw std::invalid_argument(ss.str());
	}

	/* Allow us to use the same socket for sending and receiving */
	/* This makes sure that the src port is correct when sending */
	int sockopt = 1;
	int status = setsockopt(bacnetSocket, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt));

	if (status < 0) {
		close(bacnetSocket);
		bacnetSocket = -1;

		ss << "BACnetConnection::connect: setsockopt(bacnet_sfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt)) Failed!\n"
				"\tsetsockopt returned ( " << status << ")" << endl;
		throw std::invalid_argument(ss.str());
	}

	/* allow us to send a broadcast */
	status = setsockopt(bacnetSocket, SOL_SOCKET, SO_BROADCAST, &sockopt, sizeof(sockopt));

	if (status < 0) {
		close(bacnetSocket);
		bacnetSocket = -1;

		ss << "BACnetConnection::connect: setsockopt(bacnet_sfd, SOL_SOCKET, SO_BROADCAST, &sockopt, sizeof(sockopt)) Failed!\n"
				"\tsetsockopt returned ( " << status << ")" << endl;
		throw std::invalid_argument(ss.str());
	}

	/** Socket must've created successfully! Now we need to bind it to an address...*/
	struct sockaddr_in srcAddr;
	unsigned int srcAddrLen;

	memset(&srcAddr, 0, sizeof(srcAddr));			/* Clear struct; Fill it with zeros*/
	srcAddr.sin_family = AF_INET;					/* Set the family to AF_INET (i.e., Internet/IP)*/
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);	/* Pick any available IP address */
	srcAddr.sin_port = bacnetPort;					/* Set the port */


	/* Bind the socket to an address...*/
	srcAddrLen = sizeof(srcAddr);
	ss.str("");	//Clear the contents.

	int rv = bind(bacnetSocket, (struct sockaddr *) &srcAddr, srcAddrLen);
	erno = errno;
	if (rv != 0 || erno != 0)
	{
		ss << "BACnetConnection: Failed to bind socket to address:\n"
				"\tbind() return value: " << rv << "\n"
				"\terrno: " << erno << ": " << strerror(erno) << "\n"
				"\tSocket File Descriptor: " << bacnetSocket << "\n"
				"\tsrcAddr.sin_family: " << srcAddr.sin_family << "\n"
				"\tsrcAddr.sin_addr.s_addr: " << ntohl(srcAddr.sin_addr.s_addr) << "\n"
				"\tsrcAddr.sin_port: " << ntohs(srcAddr.sin_port) << endl;
		close(bacnetSocket);
		throw std::invalid_argument(ss.str());
	}

}

void BACnetConnection::disconnect(void) {
	if (bacnetSocket != 0)
	{
		epicsSocketDestroy(bacnetSocket);
	}
}

int BACnetConnection::sendBuffer(BACnetBuffer &buff, BACnetDeviceAddress const &dest) {

	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));       /* Clear struct */
	addr.sin_family = AF_INET;
	addr.sin_port = dest.getIpPortAsNetworkByteOrder();
	addr.sin_addr = *dest.getIpAddress();

	if(BACnet_verbosity > 1) {
		cout << "Hex dump before sendto...\n" << buff.hex_dump() << endl;
	}

	uint16_t bytes_sent = sendto(bacnetSocket, ((BACnetBuffer) buff).begin(), buff.get_fill_length(), 0,
			(struct sockaddr *) &addr, sizeof(addr));

	return bytes_sent;
}

void BACnetConnection::sendTsm(Tsm *tsm) {
	sndQue->send(&tsm, sizeof(void *));
}

int BACnetConnection::sendBip(BACnetBVLL &bip, BACnetDeviceAddress const &dest) {

	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));       /* Clear struct */
	addr.sin_family = AF_INET;
	addr.sin_port = dest.getIpPortAsNetworkByteOrder();
	addr.sin_addr = *dest.getIpAddress();

	BACnetBuffer buff = BACnetBuffer();

	bip.encode(buff);

	cout << "Hex dump before sendto...\n" << buff.hex_dump() << endl;

	uint16_t bytes_sent = sendto(bacnetSocket, ((BACnetBuffer) buff).begin(), buff.get_fill_length(), 0,
			(struct sockaddr *) &addr, sizeof(addr));

	return bytes_sent;
}

int BACnetConnection::recvFrom(BACnetDeviceAddress &src_addr, BACnetBuffer &buff) {

	uint16_t const MAX_MPDU = ((1 + 1 + 2)+(1476 + (1+1+2+1+7+2+1+7+1+1+2)));
	uint8_t rx_buffer[MAX_MPDU];

	memset(&rx_buffer, 0, sizeof(rx_buffer));       /* Clear struct */

	struct sockaddr_in srcAddr;
	memset(&srcAddr, 0, sizeof(srcAddr));       /* Clear struct */
	socklen_t sin_len = sizeof(srcAddr);

	int rcvd = 0;
	fd_set read_fds;
	struct timeval timeout;
	int nfds = bacnetSocket;

	FD_ZERO(&read_fds);
	FD_SET(bacnetSocket, &read_fds);

	timeout.tv_sec = 0;
	timeout.tv_usec = 1000 * 100;

	if(select(nfds + 1, &read_fds, NULL, NULL, &timeout) > 0) {
		rcvd = recvfrom(bacnetSocket, (char *) &rx_buffer[0], MAX_MPDU, 0, (struct sockaddr *) &srcAddr, &sin_len);

		/** Ignore messages sent from myself...*/
		if(srcAddr.sin_addr.s_addr == this->addr.s_addr) {
			return 0;
		}

		try {
			/** Copy the message received into the BACnetBuffer*/
			buff.encode_buffer(rx_buffer, 0, rcvd);

		} catch (exception &e) {
			cout << "ERROR! int BACnetConnection::recvFrom(BACnetDeviceAddress &src_addr, BACnetBuffer &buff)" << endl;
			cout << "-> " << e.what() << endl;
			buff.clear_buffer();
			return 0;
		}

		if(!bvllIsValid(buff, rcvd, srcAddr, src_addr)) {
			return 0;
		}

		/** Make sure it has the NPDU signature*/
		uint8_t const *peekOct = buff.getReadPointer();

		if((*peekOct++) != 0x01) {
			return 0;
		}

		/** Filter out BACnet network layer messages... they are usually from BACnet routers...*/
		if((*peekOct & 0x80)) {
			if(BACnet_verbosity > 1) {
				cout << ">> FYI: Device " << convertNetAddrToString(&srcAddr.sin_addr) <<
						" has sent a network layer message." << endl;
				cout << ">> Network Layer Message Contents: " << buff.hex_dump() << endl;
			}
			return 0;
		}

		BACnetNpdu npdu;
		try {
			npdu.decode(buff);
		} catch (exception &e) {
			if(BACnet_verbosity > 1) {
				cout << "ERROR! int BACnetConnection::recvFrom(BACnetDeviceAddress &src_addr, BACnetBuffer &buff)" << endl;
				cout << "-> " << e.what() << endl;
			}
			return 0;
		}

		if(npdu.hasSourceSpecifier()) {
			npdu.getSourceAddress(src_addr);
		}

		return rcvd;
	}

	return 0;
}

int BACnetConnection::recvAll(BACnetDeviceAddress &src_addr, BACnetBuffer &buff) {

	uint16_t const MAX_MPDU = ((1 + 1 + 2)+(1476 + (1+1+2+1+7+2+1+7+1+1+2)));
	uint8_t rx_buffer[MAX_MPDU];

	memset(&rx_buffer, 0, sizeof(rx_buffer));       /* Clear struct */

	struct sockaddr_in srcAddr;
	memset(&srcAddr, 0, sizeof(srcAddr));       /* Clear struct */
	socklen_t sin_len = sizeof(srcAddr);

	int rcvd = 0;
	struct timeval timeout;

	/** File descriptor for reading from select*/
	fd_set read_fds;

	/** Zero the file descriptor*/
	FD_ZERO(&read_fds);

	/** Max number of file descriptors plus one.*/
	int nfds = maxSocket + 1;

	/** Get an iterator to iterate over all the connection objects.*/
	std::map<string, BACnetConnection *>::iterator itr = connectionMap.begin();

	/** Iterate over all the sockets and set the proper bits in the bit-mask using FD_SET()*/
	for(; itr != connectionMap.end(); itr++) {
		FD_SET(itr->second->bacnetSocket, &read_fds);
	}

	timeout.tv_sec = 0;
	timeout.tv_usec = 1000 * 100;

	if(select(nfds, &read_fds, NULL, NULL, &timeout) > 0) {
		for(itr = connectionMap.begin(); itr != connectionMap.end(); itr++) {
			if(FD_ISSET(itr->second->bacnetSocket, &read_fds)) {

				rcvd = recvfrom(itr->second->bacnetSocket, (char *) &rx_buffer[0], MAX_MPDU, 0, (struct sockaddr *) &srcAddr, &sin_len);

				if(BACnet_verbosity > 1) {
					cout << "Received data from socket " << itr->second->bacnetSocket << endl;
					cout << "Recieved from srcAddr: " << convertNetAddrToString(&srcAddr.sin_addr) << endl;
				}

				/** Ignore messages sent from myself... So my address wouldn't have been added to the map*/
				/** Create an iterator and search for the addr.*/
				std::map<struct in_addr, BACnetConnection *>::iterator itr = ipToConnMap.find(srcAddr.sin_addr);

				/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
				if(itr != ipToConnMap.end()) {
					if(BACnet_verbosity > 1) {
						cout << "Ignore messages sent from myself...just return." << endl;
					}
					return 0;
				}

				try {
					/** Copy the message received into the BACnetBuffer*/
					buff.encode_buffer(rx_buffer, 0, rcvd);

				} catch (exception &e) {
					cout << "ERROR! int BACnetConnection::recvFrom(BACnetDeviceAddress &src_addr, BACnetBuffer &buff)" << endl;
					cout << "-> " << e.what() << endl;
					buff.clear_buffer();
					return 0;
				}

				if(!bvllIsValid(buff, rcvd, srcAddr, src_addr)) {
					return 0;
				}

				/** Make sure it has the NPDU signature*/
				uint8_t const *peekOct = buff.getReadPointer();

				if((*peekOct++) != 0x01) {
					return 0;
				}

				/** Filter out BACnet network layer messages... they are usually from BACnet routers...*/
				if((*peekOct & 0x80)) {
					if(BACnet_verbosity > 1) {
						cout << ">> FYI: Device " << convertNetAddrToString(&srcAddr.sin_addr) <<
								" has sent a network layer message." << endl;
						cout << ">> Network Layer Message Contents: " << buff.hex_dump() << endl;
					}
					return 0;
				}

				BACnetNpdu npdu;
				try {
					npdu.decode(buff);
				} catch (exception &e) {
					if(BACnet_verbosity > 1) {
						cout << "ERROR! int BACnetConnection::recvFrom(BACnetDeviceAddress &src_addr, BACnetBuffer &buff)" << endl;
						cout << "-> " << e.what() << endl;
					}
					return 0;
				}

				if(npdu.hasSourceSpecifier()) {
					npdu.getSourceAddress(src_addr);
				}

				return rcvd;

			}
		}

	}
	else {
		return 0;
	}

	return 0;
}

void BACnetConnection::decodeAddressInfo(BACnetBuffer &buff, const struct sockaddr_in &socketIpAddr,
		BACnetDeviceAddress &srcAddr) {

	BACnetBvlcFunction const &BVLC_FUNC = BACnetEnumBvlcFunction::getEnumByValue(buff[1]);

	if(BVLC_FUNC == BACnetEnumBvlcFunction::ORIGINAL_UNICAST_NPDU) {
		if(BACnet_verbosity > 1) {
			cout << BACnetEnumBvlcFunction::ORIGINAL_UNICAST_NPDU.getName() << endl;
		}

		BACnetBvllOrigUnicastNpdu bvll;
		bvll.decode(buff);

		BACnetNpdu npdu;
		npdu.decode(buff);

		if(npdu.hasSourceSpecifier()) {
			npdu.getSourceAddress(srcAddr);
		}

		/** Get IP and Port from source... */
		srcAddr.setSockaddrIn(&socketIpAddr);

	}else if(BVLC_FUNC == BACnetEnumBvlcFunction::ORIGINAL_BROADCAST_NPDU) {
		if(BACnet_verbosity > 1) {
			cout << BACnetEnumBvlcFunction::ORIGINAL_BROADCAST_NPDU.getName() << endl;
		}

		BACnetBVLLOrigBcastNPDU bcastNpdu;
		bcastNpdu.decode(buff);

		BACnetNpdu npdu;
		npdu.decode(buff);

		if(npdu.hasSourceSpecifier()) {
			npdu.getSourceAddress(srcAddr);
		}

		/** Get IP and Port from source... */
		srcAddr.setSockaddrIn(&socketIpAddr);

	}else if(BVLC_FUNC == BACnetEnumBvlcFunction::FORWARDED_NPDU) {
		if(BACnet_verbosity > 1) {
			cout << BACnetEnumBvlcFunction::FORWARDED_NPDU.getName() << endl;
		}

		BACnetBvllForwardedNpdu fnpdu;
		fnpdu.decode(buff);

		BACnetNpdu npdu;
		npdu.decode(buff);

		if(npdu.hasSourceSpecifier()) {
			npdu.getSourceAddress(srcAddr);
		}

		/** Get IP and Port of originating device from BVLL-Forwarded-NPDU. It is stored there.*/
		fnpdu.getBipOrigin(srcAddr);

	}
	else {
		stringstream ss;
		ss << "ERROR! void BACnetConnection::decodeAddressInfo(BACnetBuffer &buff, const struct sockaddr_in &socketIpAddr,"
		"BACnetDeviceAddress &srcAddr)" << endl;
		ss << "-> Unsupported BVLC-FUNCTION received. Function Name: " << BVLC_FUNC.getName() << "(" << BVLC_FUNC.getValue() << ")" << endl;
		throw std::invalid_argument(ss.str());
		return;
	}
}

bool BACnetConnection::bvllIsValid(BACnetBuffer &buff, int rcvd, const struct sockaddr_in &sockIpAddr,
		BACnetDeviceAddress &remAddr) {

	/** Ignore messages that are NOT BACnet/IP messages...*/
	if(buff[0] != BACnetBVLL::BVLL_FOR_BACNET_IP) {
		return false;
	}


	/** Check that the length is legit. check that the 16-bit encoded length matches the bytes returned from
	 * the recvfrom() function.*/
	uint16_t bvlcLength = 0;
	bvlcLength = (buff[2] << 8);
	bvlcLength |= buff[3];

	if(bvlcLength != rcvd) {
		if(BACnet_verbosity > 1) {
			cout << "FYI! BACnetConnection::recvFrom(...): BVLC Length does not match bytes received."
					" Malformed packet from address: " << convertNetAddrToString(&sockIpAddr.sin_addr) << endl;
		}
		return false;
	}

	try {

		BACnetBvlcFunction const &BVLC_FUNC = BACnetEnumBvlcFunction::getEnumByValue(buff[1]);

		/** Ignore messages that are NOT supported BVLL Types... the ones below are what I expect to receive*/
		if(BVLC_FUNC == BACnetEnumBvlcFunction::ORIGINAL_UNICAST_NPDU) {
			BACnetBvllOrigUnicastNpdu bvll;
			bvll.decode(buff);
			/** Get IP and Port from source... */
			remAddr.setSockaddrIn(&sockIpAddr);
			return true;
		}
		else if(BVLC_FUNC == BACnetEnumBvlcFunction::ORIGINAL_BROADCAST_NPDU) {
			BACnetBVLLOrigBcastNPDU bcastNpdu;
			bcastNpdu.decode(buff);
			/** Get IP and Port from source... */
			remAddr.setSockaddrIn(&sockIpAddr);
			return true;
		}
		else if(BVLC_FUNC == BACnetEnumBvlcFunction::FORWARDED_NPDU) {
			BACnetBvllForwardedNpdu fnpdu;
			fnpdu.decode(buff);
			/** Get IP and Port of originating device from BVLL-Forwarded-NPDU. It is stored there.*/
			fnpdu.getBipOrigin(remAddr);
			return true;
		}
	} catch (exception &e) {
		if(BACnet_verbosity > 1) {
			cout << "ERROR! bool BACnetConnection::bvllIsValid(BACnetBuffer &buff, "
					"int rcvd, const struct sockaddr_in &sockIpAddr,BACnetDeviceAddress &remAddr)" << endl;
			cout << "-> " << e.what() << endl;
		}
		return false;
	}

	return false;
}

void BACnetConnection::start(void) {

	cout << "++++ Starting BACnetConnection::start() ++++" << endl;

	epicsThreadCreate("sendThread", epicsThreadPriorityHigh, epicsThreadGetStackSize(epicsThreadStackMedium), &sendThread, NULL);
}

void BACnetConnection::stop(void) {
	pevent1->signal();
	pevent2->wait();

	delete pevent1;
	delete pevent2;
}

void BACnetConnection::sendThread(void *p) {

	Tsm *tsm = NULL;

	/** Source address of message received.*/
	BACnetDeviceAddress srcAddr = BACnetDeviceAddress();

	/** A buffer to hold the encoded message that was received.*/
	BACnetBuffer buff = BACnetBuffer();

	int nBytes = 0;
	BACnetDevice *dev = NULL;

	cout << "++++ Starting BACnetConnection::sendThread() ++++" << endl;

	while(true) {
		if(pevent1->tryWait()) {
			cout << "Stopping Connection thread..." << endl;
			pevent2->signal();
			return;
		}
		while(sndQue->pending() > 0) {
			sndQue->receive(&tsm, sizeof(void *), 1.0);
			if(tsm) {
				tsm->send();
			}
			else
				cout << "++++ BACnetConnection::sendThread: sndQue->pending is > 0 but dev was null +++" << endl;
		}

		/** Clear the buffer and reset the nBytes to zero...*/
		buff.clear_buffer();
		nBytes = 0;
		dev = NULL;
		srcAddr.clear();

		try {

			/** See if there is anything to receive... this uses select() and blocks with a timeout...
			 * as Kay pointed out I do not need an epicsThreadSleep() when using the select()
			 * */
			nBytes = BACnetConnection::recvAll(srcAddr, buff);

			/** */
			if(nBytes > 0) {
				if(BACnet_verbosity > 1) {
					cout << "++++ BACnetConnection::sendThread: Received " << nBytes << " bytes of data ++++" << endl;
					cout << buff.hex_dump() << endl;
				}

				/** There is a new message in the buffer, need to find which device it belongs to and put it on their queue */

				/** First step is try to match the addr info up with a device that has been created in a
				 * static device list.
				 *
				 * If the addr doesn't match up then this could be a condition where the device addr hasn't been
				 * received yet and this message is a pending I-AM message and we will have to match the device
				 * instance from the I-AM message to the device created and then load the addr info for next step
				 * in communication process.
				 * */

				dev = BACnetDevice::findDeviceByAddress(srcAddr);

				if(dev) {
					dev->queMsgIn(srcAddr, buff);
				}
				else {
					BACnetObjIdentifier objId;
					if(isIamMessage(buff, objId)) {
						dev = BACnetDevice::findDeviceByInst(objId.getObjectInstanceAsUint32_t());
						if(dev) {
							dev->queMsgIn(srcAddr, buff);
						}
					}
				}

			}
		} catch (exception &e) {
			cout << e.what() << endl;
		}
		//epicsThreadSleep(0.05);
	}
}

bool BACnetConnection::isIamMessage(BACnetBuffer &buff, BACnetObjIdentifier &objId) {

	/** This octet should be the PDU-Type octet encoded in upper 4 bits*/
	uint8_t const *ptr = buff.getReadPointer();

	BACnetPDUChoice const &PDU_TYPE = BACnetEnumPDUChoice::getEnumByValue((*(ptr++) >> 4));

	if(PDU_TYPE == BACnetEnumPDUChoice::UNCONFIRMED_REQUEST) {
		BACnetUnconfirmedServiceChoice const &UNCONF_SVC_CHOICE = BACnetEnumUnconfirmedService::getEnumByValue(*(ptr++));

		if(UNCONF_SVC_CHOICE == BACnetEnumUnconfirmedService::I_AM) {

			BACnetTag tag;
			ptr = tag.decode(ptr);

			if(tag.getTagNumber() != BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER.getValue()) {
				return false;
			}
			if(tag.getTagClass() == NULL) {
				return false;
			}
			if(*tag.getTagClass() != BACnetEnumTagChoice::APPLICATION_TAG) {
				return false;
			}
			if(tag.getLengthValueType() != 4) {
				return false;
			}

			ptr = objId.decode(ptr);
			return true;
		}
	}
	return false;
}




