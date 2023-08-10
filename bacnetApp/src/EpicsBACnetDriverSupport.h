
#ifndef __EpicsBACnetDriverSupport_h
#define EpicsBACnetDriverSupport_h

#include <stdint.h>
#include <string>
#include <list>
#include <map>

#include "BACnetEnums.h"
#include "BACnetObjIdentifier.h"
#include "BACnetEnumPropertyIdentifier.h"
#include "BACnetDrvProperties.h"
#include "BACnetDevice.h"

#ifdef BUILD_WITH_EPICS
// EPICS Base
#include "epicsTypes.h"
#include "dbCommon.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include <drvSup.h>      /* EPICS driver support library         */

#include <epicsExport.h>
#include <epicsMutex.h>
#include <epicsThread.h>

#endif

using namespace std;

#define DEFAULT_BACNET_PORT 0xBAC0


static long drvBacnetReport (void);

static long drvBacnetInit (void);

#endif
