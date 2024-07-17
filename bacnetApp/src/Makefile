TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

USR_CXXFLAGS += -fpermissive -DBUILD_WITH_EPICS

#=============================
# Build the IOC support library

#LIBRARY_IOC += bacnetSupport

# xxxRecord.h will be created from xxxRecord.dbd
#DBDINC += xxxRecord
# Install devXxxSoft.dbd into <top>/dbd
#DBD += xxxSupport.dbd

# Compile and add the code to the support library
#bacnetSupport_SRCS += xxxRecord.c
#bacnetSupport_SRCS += devXxxSoft.c

# Link locally-provided code into the support library,
# rather than directly into the IOC application.
#bacnetSupport_SRCS += dbSubExample.c
#bacnetSupport_SRCS += bacnetHello.c
#bacnetSupport_SRCS += initTrace.c

#bacnetSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# Build the IOC application

PROD_IOC = bacnet
# bacnet.dbd will be created and installed
DBD += bacnet.dbd
DBDCAT += bacnetSupport.dbd

# bacnet.dbd will be made up from these files:
bacnet_DBD += base.dbd
bacnet_DBD += BACnet.dbd
#bacnet_DBD += xxxSupport.dbd
#bacnet_DBD += dbSubExample.dbd
#bacnet_DBD += bacnetHello.dbd
#bacnet_DBD += initTrace.dbd
bacnetSupport_DBD += BACnet.dbd

# Add all the support libraries needed by this IOC
#bacnet_LIBS += xxx

LIBRARY += bacnetlib
bacnetlib_SRCS += drvBACnetRegister.cpp
bacnetlib_SRCS += BACnetEnumSingle.cpp
bacnetlib_SRCS += BACnetEnum.cpp
bacnetlib_SRCS += BACnetBuffer.cpp
bacnetlib_SRCS += BACnetApdu.cpp
bacnetlib_SRCS += BACnetConnection.cpp
bacnetlib_SRCS += BACnetDeviceAddress.cpp
bacnetlib_SRCS += BACnetWhoIsService.cpp
bacnetlib_SRCS += BACnetReadPropertyService.cpp
bacnetlib_SRCS += BACnetReadPropAck.cpp
bacnetlib_SRCS += BACnetRpmReq.cpp
bacnetlib_SRCS += BACnetRpmAck.cpp
bacnetlib_SRCS += BACnetPropRefValue.cpp
bacnetlib_SRCS += BACnetRpmResult.cpp
bacnetlib_SRCS += BACnetWritePropService.cpp
bacnetlib_SRCS += BACnetIamService.cpp
bacnetlib_SRCS += BACnetComplexAckService.cpp
bacnetlib_SRCS += BACnetNpdu.cpp
bacnetlib_SRCS += BACnetWhoIsRequest.cpp
bacnetlib_SRCS += BACnetWhoIsResponse.cpp
bacnetlib_SRCS += EpicsBACnetDeviceSupport.cpp
bacnetlib_SRCS += EpicsBACnetDriverSupport.cpp
bacnetlib_SRCS += BACnetEnumTagChoice.cpp
bacnetlib_SRCS += BACnetConfSvcChoice.cpp
bacnetlib_SRCS += BACnetEnumConfSvc.cpp
bacnetlib_SRCS += BACnetEnumUnconfirmedService.cpp
bacnetlib_SRCS += BACnetEnumPDUChoice.cpp
bacnetlib_SRCS += BACnetEnumMessagePriority.cpp
bacnetlib_SRCS += BACnetEnumBvlcFunction.cpp
bacnetlib_SRCS += BACnetEnumMaxApduAccepted.cpp
bacnetlib_SRCS += BACnetEnumMaxSegAccepted.cpp
bacnetlib_SRCS += BACnetEnumSegmentation.cpp
bacnetlib_SRCS += BACnetEnumApplicationDataType.cpp
bacnetlib_SRCS += BACnetBVLL.cpp
bacnetlib_SRCS += BACnetBVLLOrigBcastNPDU.cpp
bacnetlib_SRCS += BACnetBvllOrigUnicastNpdu.cpp
bacnetlib_SRCS += BACnetBvllForwardedNpdu.cpp
bacnetlib_SRCS += BACnetTag.cpp
bacnetlib_SRCS += BACnetEnumObjectType.cpp
bacnetlib_SRCS += BACnetInstance.cpp
bacnetlib_SRCS += BACnetObjIdentifier.cpp
bacnetlib_SRCS += BACnetAppObjId.cpp
bacnetlib_SRCS += BACnetEnumPropertyIdentifier.cpp
bacnetlib_SRCS += BACnetStringUtil.cpp
bacnetlib_SRCS += BACnetDrvProperties.cpp
bacnetlib_SRCS += BACnetDevice.cpp
bacnetlib_SRCS += BACnetEnumTsmState.cpp
bacnetlib_SRCS += Tsm.cpp
bacnetlib_SRCS += TsmPool.cpp
bacnetlib_SRCS += MessageIn.cpp
bacnetlib_SRCS += MessagePool.cpp
bacnetlib_SRCS += BACnetComplexAck.cpp
bacnetlib_SRCS += BACnetApplicationData.cpp
bacnetlib_SRCS += BACnetAppDataType.cpp
bacnetlib_SRCS += BACnetBitString.cpp
bacnetlib_SRCS += BACnetCharacterString.cpp
bacnetlib_SRCS += BACnetOctetString.cpp
bacnetlib_SRCS += BACnetReal.cpp
bacnetlib_SRCS += BACnetDouble.cpp
bacnetlib_SRCS += BACnetBoolean.cpp
bacnetlib_SRCS += BACnetEnumerated.cpp
bacnetlib_SRCS += BACnetUnsignedInt.cpp
bacnetlib_SRCS += BACnetSignedInt.cpp
bacnetlib_SRCS += BACnetNull.cpp
bacnetlib_SRCS += BACnetTime.cpp
bacnetlib_SRCS += BACnetDate.cpp
bacnetlib_SRCS += ProtocolSvcSupported.cpp
bacnetlib_SRCS += BACnetBinaryPV.cpp
bacnetlib_SRCS += BACnetEnumSvcSupChoice.cpp
bacnetlib_SRCS += BACnetEnumVarFunc.cpp
bacnetlib_SRCS += BACnetEnumBinary.cpp
bacnetlib_SRCS += BACnetEnumCharSet.cpp
bacnetlib_SRCS += BACnetEnumEngUnits.cpp
bacnetlib_SRCS += BACnetEnumErrorClass.cpp
bacnetlib_SRCS += BACnetEnumErrorCode.cpp
bacnetlib_SRCS += BACnetObjPropRef.cpp
bacnetlib_SRCS += BACnetVariable.cpp
bacnetlib_SRCS += BACnetInstIOParser.cpp
bacnetlib_SRCS += BACnetErrorPdu.cpp
bacnetlib_SRCS += BACnetPropertyRef.cpp
bacnetlib_SRCS += BnetReadAccessSpec.cpp
bacnetlib_SRCS += BACnetEnumTxRxEr.cpp
bacnetlib_SRCS += DevTxRxErGrp.cpp
bacnetlib_LIBS += $(EPICS_BASE_IOC_LIBS)

# bacnet_registerRecordDeviceDriver.cpp derives from bacnet.dbd
bacnet_SRCS += bacnet_registerRecordDeviceDriver.cpp
#bacnet_SRCS += EpicsBACnetDeviceSupport.cpp

# Build the main IOC entry point on workstation OSs.
bacnet_SRCS_DEFAULT += bacnetMain.cpp
bacnet_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#bacnet_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Link in the code from the support library
#bacnet_LIBS += bacnetSupport

# NOTE: To build SNL programs, SNCSEQ must be defined
# in the <top>/configure/RELEASE file


# Finally link to the EPICS Base libraries
bacnet_LIBS += $(EPICS_BASE_IOC_LIBS)
bacnet_LIBS += bacnetlib

PROD_HOST += whois
whois_SRCS += whoisMain.cpp
whois_LIBS += bacnetlib
whois_LIBS += $(EPICS_BASE_IOC_LIBS)

PROD_HOST += readprop
readprop_SRCS += readPropMain.cpp
readprop_LIBS += bacnetlib
readprop_LIBS += $(EPICS_BASE_IOC_LIBS)


#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

