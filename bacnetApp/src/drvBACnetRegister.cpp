/*
 * drvBACnetRegister.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: 8w4
 */
#include <iostream>


#include "iocsh.h"
#include "epicsExport.h"
#include "BACnetDevice.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

// Define a BACnet Device
static const iocshArg DrvBACnetDefineDeviceArg0 = {"name", iocshArgString };
static const iocshArg DrvBACnetDefineDeviceArg1 = {"instance", iocshArgInt };
static const iocshArg DrvBACnetDefineDeviceArg2 = {"ifName", iocshArgString };
static const iocshArg DrvBACnetDefineDeviceArg3 = {"port", iocshArgInt };

static const iocshArg *const DrvBACnetDefineDeviceArgs[4] = {
		&DrvBACnetDefineDeviceArg0, &DrvBACnetDefineDeviceArg1,
		&DrvBACnetDefineDeviceArg2, &DrvBACnetDefineDeviceArg3};

static const iocshFuncDef DrvBACnetDefineDeviceDef = {"drvBACnetDefineDevice",
		4, DrvBACnetDefineDeviceArgs };

static void DrvBACnetDefineDeviceCall(const iocshArgBuf * args) {

	/** Validate pointers to strings parameters...*/

	/** Validate the name parameter is not empty*/

	if(!args[0].sval) {
		cout << "ERROR! Name parameter must not be empty in function DrvBACnetDefineDevice(...) Could not register BACnet device." << endl;
		return;
	}

	/** Validate the ifName parameter is not empty*/
	if(!args[2].sval) {
		cout << "ERROR! ifName parameter must not be empty in function DrvBACnetDefineDevice(...) Could not register BACnet device." << endl;
		return;
	}

// Putting this here for now... probably needs to go into a common include file...
#define DEFAULT_BACNET_PORT 0xBAC0

	uint16_t tmpPort = DEFAULT_BACNET_PORT;

	/** Port was not defined. Use the default.*/
	if(args[3].ival != 0) {
		tmpPort = args[3].ival;
	}

	BACnetDevice *dev = NULL;

	try {
		/** EPICS name, BACnet-Instance, network-interface-name, port*/
		dev = BACnetDevice::create(args[0].sval, args[1].ival, args[2].sval, tmpPort);

	} catch (exception &e) {
		cout << "ERROR! DrvBACnetDefineDeviceCall: Could not create BACnet device..." << endl;
		cout << e.what() << endl;
		return;
	}

	cout << "-> -> BACnetDevice created successfully..." << endl;
	cout << "-> -> Now see if you can retrieve the device by name..." << endl;

	/** Just a check to make sure the device can be found.*/

	if(dev) {
		BACnetDevice *d = BACnetDevice::findDeviceByName(args[0].sval);

		if(d) {
			cout << "SUCCESS! Device \"" << d->getDeviceName() << "\" : ("
					<< d->getDeviceInstanceId() << ") was retrieved successfully." << endl;
		}
		else {
			cout << "FAILURE! Device \"" << args[0].sval << "\" was NOT retrieved successfully." << endl;
		}
	}

}

/** Specific Parameters*/
static const iocshArg DrvBACnetSetArg0 = {"deviceName", iocshArgString };
static const iocshArg DrvBACnetSetArg1 = {"listOfArgs", iocshArgString };
static const iocshArg *const DrvBACnetSetArgs[2] = {&DrvBACnetSetArg0, &DrvBACnetSetArg1};
static const iocshFuncDef DrvBACnetSetDef = {"drvBACnetSet", 2, DrvBACnetSetArgs };
static void DrvBACnetSetCall(const iocshArgBuf * args) {

	BACnetDevice *d = BACnetDevice::findDeviceByName(args[0].sval);

	if(d == NULL) {
		cout << "ERROR! DrvBACnetSet(deviceName, ...): BACnetDevice could not be found by name \"" <<
				args[0].sval << "\"" << endl;
		return;
	}

	d->setIocShArgs(args[1].sval);

}

static const iocshArg BACnet_verbosityArg0 = {"value", iocshArgInt};
static const iocshArg *const BACnet_verbosityArgs[1] = {&BACnet_verbosityArg0};
static const iocshFuncDef BACnet_verbosityDef = {"drvBACnetVerbosity", 1, BACnet_verbosityArgs};
static void BACnet_verbosityCall(const iocshArgBuf * args) {
	BACnet_verbosity = args[0].ival;
}

static const iocshFuncDef DrvBACnetListDevicesDef = {"drvBACnetListDevices"};
static void DrvBACnetListDevicesCall(const iocshArgBuf * args) {
	BACnetDevice::listDevices();
}

static const iocshFuncDef DrvBACnetVersionDef = {"drvBACnetVersion"};
static void DrvBACnetVersionCall(const iocshArgBuf *args) {
	cout << "drvBACnetVersion: \'2.2.2\'" << endl;
}

static const iocshFuncDef DrvBACnetStartDef = {"drvBACnetStart"};
static void DrvBACnetStartCall(const iocshArgBuf *args) {
	BACnetConnection::start();
	BACnetDevice::start();
	cout << "drvBACnetStart()" << endl;
}

void drvBACnet_Register() {

	iocshRegister(&DrvBACnetDefineDeviceDef, DrvBACnetDefineDeviceCall);
	iocshRegister(&DrvBACnetSetDef, DrvBACnetSetCall);
	iocshRegister(&BACnet_verbosityDef, BACnet_verbosityCall);
	iocshRegister(&DrvBACnetListDevicesDef, DrvBACnetListDevicesCall);
	iocshRegister(&DrvBACnetVersionDef, DrvBACnetVersionCall);
	iocshRegister(&DrvBACnetStartDef, DrvBACnetStartCall);
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

epicsExportRegistrar(drvBACnet_Register);



