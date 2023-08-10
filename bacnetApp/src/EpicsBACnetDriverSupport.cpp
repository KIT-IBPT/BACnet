#include "EpicsBACnetDriverSupport.h"
//#include "BACnetNull.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include <sstream>
#include <stdint.h>
#include <list>
#include <stdexcept>
#include <limits.h>
#include <errno.h>
#include <epicsExit.h>


long drvBacnetReport (void) {

	int level = 0;
	cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "drvBacnetReport, level = " << level << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";

	return 0;

}

void stopAll(void *p) {

	/** This stops the connection thread and waits for confirmation*/
	BACnetConnection::stop();

	/** This stops the Device thread and deletes objects*/
	BACnetDevice::stop();

	cout << "Finished..." << endl;
}

long drvBacnetInit (void) {

  cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "drvBacnetInit\n";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";

  epicsAtExit(&stopAll, NULL);

  return 0;

}

#ifdef BUILD_WITH_EPICS

typedef struct DrvFuncTag {
  long int number;
  DRVSUPFUN report;
  DRVSUPFUN init;
} DrvFuncType;

DrvFuncType drvBacnet = {
  2,				/* Number of entries      */
  drvBacnetReport,	/* Report routine         */
  drvBacnetInit     /* Initialization routine */
};

epicsExportAddress(drvet,drvBacnet);

#endif








