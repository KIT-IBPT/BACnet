#!../../bin/linux-x86_64/bacnet

## You may have to change bacnet to something else
## everywhere it appears in this file.

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/bacnet.dbd"
bacnet_registerRecordDeviceDriver pdbbase

# /** Define BACnet Stuff... */

# /** Define a BACnet Device... (<name>, <device-instance>, nic_name, <[port]>)*/
# i.p. addr for  160.91.233.141 "ALC_ME812UE"
#drvBACnetDefineDevice("ALC_ME812UE", 22, "ens33")
#drvBACnetDefineDevice("ALC_SE6104A", 21, "ens33", 47808)
#drvBACnetDefineDevice("FieldServer", 11, "eth0")


#drvBACnetSet("ALC_SE6104A", "apdu_timeout=3000, apdu_retries=3")
#drvBACnetSet("FieldServer", "rpm_buffer_limit=500, rpm_disable=false")

## Load record instances
#dbLoadRecords "db/Test_1.db"


## Set this to see messages from mySub
#var mySubDebug 1

## Run this to trace the stages of iocInit
#traceIocInit

cd ${TOP}/iocBoot/${IOC}
iocInit

drvBACnetStart

## Start any sequence programs
#seq sncExample, "user=8w4Host"
