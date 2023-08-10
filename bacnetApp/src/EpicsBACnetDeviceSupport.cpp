/*
 * EpicsBACnetDeviceSupport.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: 8w4
 */

#include <iostream>
#include <sstream>
#include <stdlib.h>

// EPICS Base
#include "alarm.h"
#include "cvtTable.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "recGbl.h"
#include "recSup.h"
#include "devSup.h"
#include "link.h"
#include "aiRecord.h"
#include "aoRecord.h"
#include "stringinRecord.h"
#include "mbbiRecord.h"
#include "mbboRecord.h"
#include "longinRecord.h"
#include "longoutRecord.h"
#include "EpicsBACnetDriverSupport.h"
#include "epicsThread.h"
#include "epicsMutex.h"
#include "initHooks.h"

#include "epicsExport.h"
#include "epicsMath.h"

#include "BACnetInstIOParser.h"
#include "BACnetBoolean.h"
#include "BACnetUnsignedInt.h"
#include "BACnetSignedInt.h"
#include "BACnetReal.h"
#include "BACnetDouble.h"
#include "BACnetEnumerated.h"
#include "BACnetDate.h"
#include "BACnetTime.h"
#include "BACnetBitString.h"
#include "BACnetCharacterString.h"
#include "BACnetOctetString.h"
#include "BACnetVariable.h"
#include "BACnetAppObjId.h"
#include "BACnetStringUtil.h"
#include "BACnetEnumTxRxEr.h"
#include "DevTxRxErGrp.h"

using namespace std;


static void processInitHooks (initHookState state) {

  if ( state == initHookAtEnd ) {
    cout << "initHookAtEnd - possibly initialize list of output PVs and signal periodic threads" << endl;
    cout << "initHookAtEnd - possibly adjust thread priorities and scheduling" << endl;
  }

}

static long dev_init( int afterDBinit ) {

static int firstBefore=1, firstAfter=1;

  if ( !afterDBinit && firstBefore ) {

    cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "dev_init - after rec init flag = " << afterDBinit << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";

    int status = initHookRegister ( processInitHooks );
    if ( status ) {
      cout << "dev_init - init hook install failed" << endl;
    }

    firstBefore = 0;

  }

  if ( afterDBinit && firstAfter ) {

    cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "dev_init - after rec init flag = " << afterDBinit << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";

    cout << "dev_init - possibly start periodic threads that process lists" << endl;

    firstAfter = 0;

    BACnetDevice::initialize();

  }

  return 0;

}

/** AI Support... */
static long init_rec_ai_devstats(aiRecord *rec) {

	BACnetDevice *dev = NULL;

	/** Split the string by white-spaces into a list of strings*/
	std::list<string> strList = parse_string_by_whitespace(rec->inp.value.instio.string);

	if(strList.size() < 2) {
		/** We have to at least have a device name and a statistic tag: tx, rx, or er*/
		cout << "" << endl;
		return 0;
	}

	std::list<string>::const_iterator itr = strList.begin();

	/** Lookup the device by its name. The name here must match a name defined in the st.cmd file*/
	dev = BACnetDevice::findDeviceByName((*itr));

	/** If the device-name wasn't found? Complain and set record to invalid*/
	if(!dev) {
		cout << "Device name \"" << (*itr) << "\" NOT Found! " << endl;
		return 0;
	}

	/** Don't worry about the end because we checked for it up above (<2?)*/
	itr++;

	/** What is the second parameter? tx? rx? er?*/
	try {
		const BACnetTxRxErChoice &txRxErChoice = BACnetEnumTxRxEr::getEnumByName((*itr));

		/** Now I need to store the pointer to the device-object along with the reference to the enumeration...*/
		DevTxRxErGrp *grp = new DevTxRxErGrp(*dev, txRxErChoice);

		/** Store the BACnetVariable in device-private*/
		rec->dpvt = (void *) grp;

		/** Setting record's UDF to false*/
		rec->udf = false;
		return 0;

	} catch (exception &e) {
		cout << "ERROR in init_rec_ais:" << endl;
		cout << e.what() << endl;
		cout << "Setting this \"" << rec->name << "\" to invalid..." << endl;
		return 0;
	}

}

static long read_ai_devstats(aiRecord *rec) {

	/** Get the BACnetVariable stored in device-private...*/
	DevTxRxErGrp *grp = (DevTxRxErGrp *) rec->dpvt;

	/** If the BACnetVariable is not valid then complain*/
	if(!grp) {
		cout << "ERROR! read_ai_devstats: Could not retrieve object from " << rec->name << "->dpvt" << endl;
		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);
		return 0;
	}

	const BACnetDevice &dev = grp->getDevice();
	const BACnetTxRxErChoice &txRxErChoice = grp->getTxRxErChoice();

	if(txRxErChoice == BACnetEnumTxRxEr::TX) {
		rec->rval = dev.getTx();
		return 0;
	}
	else if(txRxErChoice == BACnetEnumTxRxEr::RX) {
		rec->rval = dev.getRx();
		return 0;
	}
	else if(txRxErChoice == BACnetEnumTxRxEr::ER) {
		rec->rval = dev.getEr();
		return 0;
	}

	cout << "ERROR! While in \"read_ais()\" for \"" << rec->name <<
			"\" undefined enum choice" << endl;
	recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);
	return 0;
}

/** AI Support... */
static long init_rec_ai(aiRecord *rec) {

	/** Note: record's UDF is already set to TRUE so it is already in an undefined state.
	 * All you have to do is set it to FALSE if all is successful */

	cout << "-> init_rec_ai: " << rec->name << endl;

	BACnetInstIOParser ioParser;
	BACnetVariable const *var = NULL;

	try {

		/** Try to parse the inout string: Must be at least 4 parameters:
		 * device-name object-type object-instance property-id */
		ioParser.parseInstIOString(rec->inp.value.instio.string);

	} catch (exception &e) {
		cout << "ERROR in init_rec_ai:" << endl;
		cout << e.what() << endl;
		cout << "Setting this \"" << rec->name << "\" to invalid..." << endl;
		return 0;
	}

	/** Lookup the device by its name. The name here must match a name defined in the st.cmd file*/
	BACnetDevice *dev = BACnetDevice::findDeviceByName(ioParser.getDeviceName());

	/** If the device-name wasn't found? Complain and set record to invalid*/
	if(!dev) {
		cout << "Device name \"" << ioParser.getDeviceName() << "\" NOT Found! " << endl;
		return 0;
	}

	/** If we have made it this far then all must be good, so register the object/property/reference*/
	var = dev->registerObjectProperty(BACnetEnumVarFunc::READ, ioParser.getObjPropRef());

	/** Store the BACnetVariable in device-private*/
	rec->dpvt = (void *) var;

	/** Setting record's UDF to false*/
	rec->udf = false;

	return 0;
}

static long read_ai(aiRecord *rec) {

	if(BACnet_verbosity > 1) {
		cout << "-> read_ai: " << rec->name << endl;
	}

	/** Get the BACnetVariable stored in device-private...*/
	BACnetVariable *var = (BACnetVariable *) rec->dpvt;

	/** If the BACnetVariable is not valid then complain*/
	if(!var) {
		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);
		return 0;
	}

	if(var->hasError()) {

		stringstream ss;

		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);

		ss << "record: \"" << rec->name << "\" {" << endl;
		ss << "record.INP String \"" << rec->inp.value.instio.string << "\"" << endl;

		ss << "Object-Property-Reference {" << endl;
		ss << "Object-Type: \"" << var->getObjectType().getName() << "\", Object-Instance: \"" <<
				var->getObjectInstance() << "\", Property-Id: \"" <<
				var->getObjectProperty().getName() << "\"";
		if(var->hasArrayIndex()) {
			ss << ", Array-Index: \"" << var->getArrayIndex() << "\"";
		}
		if(var->getVariableFunction() == BACnetEnumVarFunc::WRITE) {
			ss << ", Write-Priority: \"" << var->getObjectPropertyReference().getWritePriority() << "\"";
		}
		ss << endl << "} Object-Property-Reference" << endl;

		ss << var->getErrorString() << endl;

		ss << "} record: \"" << rec->name << "\"" << endl;

		cout << ss.str() << endl;

		return 0;
	}

	if(!var->hasDataInPropValList()) {

		cout << "ERROR! While in \"read_ai()\" for \"" << rec->name <<
				"\" the data-list size from the device is less than one (1)" << endl;
		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);
		return 0;
	}

	/** But for now let's just work with single-data, so get the top of the list...*/
	const BACnetAppDataType *dataValue = var->getConstPropValListTop();

	BACnetApplicationDataTypeChoice const &DATA_TYPE = dataValue->getDataType();

	if(DATA_TYPE == BACnetEnumApplicationDataType::NNULL) {
		/** Not sure what to do here... Set record to invalid, maybe?*/
		rec->val = epicsNAN;
		return 2;
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::BOOLEAN) {
		const BACnetBoolean *bacbool = dynamic_cast<const BACnetBoolean *>(dataValue);
		if(bacbool) {
			if(bacbool->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bacbool->getValue();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::UNSIGNED_INTEGER) {
		const BACnetUnsignedInt *bacui = dynamic_cast<const BACnetUnsignedInt *>(dataValue);
		if(bacui) {
			if(bacui->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bacui->getValue();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::SIGNED_INTEGER) {
		const BACnetSignedInt *bacsint = dynamic_cast<const BACnetSignedInt *>(dataValue);
		if(bacsint) {
			if(bacsint->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bacsint->getValue();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::REAL) {
		const BACnetReal *bacreal = dynamic_cast<const BACnetReal *>(dataValue);
		if(bacreal) {
			if(bacreal->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->val = bacreal->getValue();
			return 2;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::DOUBLE) {
		const BACnetDouble *bacdouble = dynamic_cast<const BACnetDouble *>(dataValue);
		if(bacdouble) {
			if(bacdouble->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->val = bacdouble->getValue();
			return 2;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::OCTET_STRING) {

		/** I do not know if this data-type works. I cannot find an Octet-String Object to test this on.
		 * 99.9% of the folks use just AI, AO, AV, BI, BO, BV, Multi-State in, and Multi-State out BACnet object types.
		 * */
		const BACnetOctetString *bacoctetstr = dynamic_cast<const BACnetOctetString *>(dataValue);
		if(bacoctetstr) {
			if(bacoctetstr->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bacoctetstr->getBytesAsUint32t();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::CHARACTER_STRING) {

		/** Note. This really doesn't do much good to only return 4-bytes for character string.
		 * You should use the string record instead.
		 * */
		const BACnetCharacterString *baccharstr = dynamic_cast<const BACnetCharacterString *>(dataValue);
		if(baccharstr) {
			if(baccharstr->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = baccharstr->getBytesAsUint32t();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::BIT_STRING) {
		/** Note: the bits will be in reverse order from original read.
		 * So if you read 0xDF (1101 1111) you will see 0xFB (1111 1011) */
		const BACnetBitString *bacbitstr = dynamic_cast<const BACnetBitString *>(dataValue);
		if(bacbitstr) {
			if(bacbitstr->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bacbitstr->getBytesAsUint32t();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::ENUMERATED) {
		const BACnetEnumerated *bacenum = dynamic_cast<const BACnetEnumerated *>(dataValue);
		if(bacenum) {
			if(bacenum->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bacenum->getValue();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::DATE) {

		const BACnetDate *bacdate = dynamic_cast<const BACnetDate *>(dataValue);
		if(bacdate) {
			if(bacdate->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bacdate->getDateAsUnsignedInt();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::TIME) {

		const BACnetTime *bactime = dynamic_cast<const BACnetTime *>(dataValue);
		if(bactime) {
			if(bactime->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bactime->getTimeAsUnsignedInt();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER) {

		const BACnetAppObjId *bacobjid = dynamic_cast<const BACnetAppObjId *>(dataValue);
		if(bacobjid) {
			if(bacobjid->isNull()) {
				rec->val = epicsNAN;
				return 2;
			}
			rec->rval = bacobjid->getBytesAsUint32t();
			return 0;
		}

	}

	recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);

	return -1;

}

/** AO Support... */
static long init_rec_ao(aoRecord *rec) {

	/** Note: record's UDF is already set to TRUE so it is already in an undefined state.
	 * All you have to do is set it to FALSE if all is successful */

	cout << "-> init_rec_ao: " << rec->name << endl;

	BACnetInstIOParser ioParser;
	BACnetVariable const *var = NULL;

	try {

		/** Try to parse the inout string: Must be at least 4 parameters:
		 * device-name object-type object-instance property-id */
		ioParser.parseInstIOString(rec->out.value.instio.string);

	} catch (exception &e) {
		cout << "ERROR in init_rec_ao:" << endl;
		cout << e.what() << endl;
		cout << "Setting this \"" << rec->name << "\" to invalid..." << endl;
		return 0;
	}

	/** Lookup the device by its name. The name here must match a name defined in the st.cmd file*/
	BACnetDevice *dev = BACnetDevice::findDeviceByName(ioParser.getDeviceName());

	/** If the device-name wasn't found? Complain and set record to invalid*/
	if(!dev) {
		cout << "Device name \"" << ioParser.getDeviceName() << "\" NOT Found! " << endl;
		return 0;
	}

	/** If we have made it this far then all must be good, so register the object/property/reference*/

	/**
	 * Here we have to pass in the data-type specifier from the out-string so we know how to write the data
	 * across the network. I.e., how to format the data for encoding.
	 * Because we checked for NULL getDataTypeFormat() above it is safe to pass a reference.*/

	/** We can specify a format to write the data, otherwise we will lookup the format by object type.
	 * the latter option is the safest.*/
	try {
		if(ioParser.getDataTypeFormat() != NULL) {
			/** This must be used for writing a null value to release a commanded value in the priority-array.
			 * Note: The rec.val field is ignored and not touched when writing nulls.
			 * */
			var = dev->registerObjectProperty(BACnetEnumVarFunc::WRITE, ioParser.getObjPropRef(), *ioParser.getDataTypeFormat());
		}
		else {
			/** Lookup the data-type for writing. */
			cout << "-> Looking up a datatype for " << rec->name << endl;
			var = dev->registerObjectProperty(BACnetEnumVarFunc::WRITE, ioParser.getObjPropRef());
		}
	} catch (exception &e) {
		cout << "ERROR in init_rec_ao:" << endl;
		cout << e.what() << endl;
		cout << "Setting this \"" << rec->name << "\" to invalid..." << endl;
		return 0;
	}

	/** Store the BACnetVariable in device-private*/
	rec->dpvt = (void *) var;

	/** Setting record's UDF to false*/
	rec->udf = false;

	return 0;
}

static long write_ao(aoRecord *rec) {
	/** Get the BACnetVariable stored in device-private...*/
	BACnetVariable *var = (BACnetVariable *) rec->dpvt;

	/** If the BACnetVariable is not valid then complain*/
	if(!var) {
		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);
		return 0;
	}

	if(!var->hasDataInPropValList()) {

		cout << "ERROR! While in \"write_ao()\" for \"" << rec->name <<
				"\" the data-list size from the device is less than one (1)" << endl;
		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);
		return 0;
	}

	/** But for now let's just work with single-data, so get the top of the list...*/
	BACnetAppDataType *dataValue = var->getPropValListTop();

	BACnetApplicationDataTypeChoice const &DATA_TYPE = dataValue->getDataType();

	cout << "->>Writing " << rec->name << ", datatype: " << DATA_TYPE.getName() << endl;

	if(DATA_TYPE == BACnetEnumApplicationDataType::NNULL) {
		/** Not sure what to do here... We can't write a value to a BACnetNull type.
		 * Set record to invalid, maybe?*/
		BACnetNull *bacnull = dynamic_cast<BACnetNull *>(dataValue);
		if(bacnull) {
			/** Ignoring the rec.val field and only sending a null value to release priority-array*/
			var->setWriteFlag();
			return 0;
		}

		return 0;
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::BOOLEAN) {
		BACnetBoolean *bacbool = dynamic_cast<BACnetBoolean *>(dataValue);
		if(bacbool) {
			bool b = (rec->val > 0) ? 1 : 0;
			bacbool->setValue(b);
			var->setWriteFlag();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::UNSIGNED_INTEGER) {
		BACnetUnsignedInt *bacui = dynamic_cast<BACnetUnsignedInt *>(dataValue);
		if(bacui) {
			uint32_t ui32 = (uint32_t) rec->val;
			bacui->setValue(ui32);
			var->setWriteFlag();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::SIGNED_INTEGER) {
		BACnetSignedInt *bacsint = dynamic_cast<BACnetSignedInt *>(dataValue);
		if(bacsint) {
			uint32_t ui32 = (uint32_t) rec->val;
			bacsint->setValue(ui32);
			var->setWriteFlag();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::REAL) {
		BACnetReal *bacreal = dynamic_cast<BACnetReal *>(dataValue);
		if(bacreal) {
			float flt = (float) rec->val;
			bacreal->setValue(flt);
			var->setWriteFlag();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::DOUBLE) {
		BACnetDouble *bacdouble = dynamic_cast<BACnetDouble *>(dataValue);
		if(bacdouble) {
			double dbl = (double) rec->val;
			bacdouble->setValue(dbl);
			var->setWriteFlag();
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::ENUMERATED) {
		BACnetEnumerated *bacenum = dynamic_cast<BACnetEnumerated *>(dataValue);
		if(bacenum) {
			uint32_t ui32 = (uint32_t) rec->val;
			bacenum->setValue(ui32);
			var->setWriteFlag();
			return 0;
		}
	}

	return 0;
}

static long init_rec_si(stringinRecord *rec) {

	/** Note: record's UDF is already set to TRUE so it is already in an undefined state.
	 * All you have to do is set it to FALSE if all is successful */

	cout << "-> init_rec_si: " << rec->name << endl;

	BACnetInstIOParser ioParser;
	BACnetVariable const *var = NULL;

	try {

		/** Try to parse the inout string: Must be at least 4 parameters:
		 * device-name object-type object-instance property-id */
		ioParser.parseInstIOString(rec->inp.value.instio.string);

	} catch (exception &e) {
		cout << "ERROR in init_rec_ai:" << endl;
		cout << e.what() << endl;
		cout << "Setting this \"" << rec->name << "\" to invalid..." << endl;
		return 0;
	}

	/** Lookup the device by its name. The name here must match a name defined in the st.cmd file*/
	BACnetDevice *dev = BACnetDevice::findDeviceByName(ioParser.getDeviceName());

	/** If the device-name wasn't found? Complain and set record to invalid*/
	if(!dev) {
		cout << "Device name \"" << ioParser.getDeviceName() << "\" NOT Found! " << endl;
		return 0;
	}

	/** If we have made it this far then all must be good, so register the object/property/reference*/
	var = dev->registerObjectProperty(BACnetEnumVarFunc::READ, ioParser.getObjPropRef());

	/** Store the BACnetVariable in device-private*/
	rec->dpvt = (void *) var;

	/** Setting record's UDF to false*/
	rec->udf = false;

	return 0;
}

static long read_si(stringinRecord *rec) {

	if(BACnet_verbosity > 1) {
		cout << "-> read_si: " << rec->name << endl;
	}

	/** Get the BACnetVariable stored in device-private...*/
	BACnetVariable *var = (BACnetVariable *) rec->dpvt;

	/** If the BACnetVariable is not valid then complain*/
	if(!var) {
		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);
		return 0;
	}

	if(var->hasError()) {

		stringstream ss;

		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);

		ss << "record: \"" << rec->name << "\" {" << endl;
		ss << "record.INP String \"" << rec->inp.value.instio.string << "\"" << endl;

		ss << "Object-Property-Reference {" << endl;
		ss << "Object-Type: \"" << var->getObjectType().getName() << "\", Object-Instance: \"" <<
				var->getObjectInstance() << "\", Property-Id: \"" <<
				var->getObjectProperty().getName() << "\"";
		if(var->hasArrayIndex()) {
			ss << ", Array-Index: \"" << var->getArrayIndex() << "\"";
		}
		if(var->getVariableFunction() == BACnetEnumVarFunc::WRITE) {
			ss << ", Write-Priority: \"" << var->getObjectPropertyReference().getWritePriority() << "\"";
		}
		ss << endl << "} Object-Property-Reference" << endl;

		ss << var->getErrorString() << endl;

		ss << "} record: \"" << rec->name << "\"" << endl;

		cout << ss.str() << endl;

		return 0;
	}

	if(!var->hasDataInPropValList()) {

		cout << "ERROR! While in \"read_si()\" for \"" << rec->name <<
				"\" the data-list size from the device is less than one (1)" << endl;
		recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);
		return 0;
	}

	/** But for now let's just work with single-data, so get the top of the list...*/
	const BACnetAppDataType *dataValue = var->getConstPropValListTop();

	BACnetApplicationDataTypeChoice const &DATA_TYPE = dataValue->getDataType();

	if(DATA_TYPE == BACnetEnumApplicationDataType::NNULL) {
		/** Not sure what to do here... Set record to invalid, maybe?*/
		BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
		return 0;
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::BOOLEAN) {
		const BACnetBoolean *bacbool = dynamic_cast<const BACnetBoolean *>(dataValue);
		if(bacbool) {
			if(bacbool->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacbool->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::UNSIGNED_INTEGER) {
		const BACnetUnsignedInt *bacui = dynamic_cast<const BACnetUnsignedInt *>(dataValue);
		if(bacui) {
			if(bacui->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacui->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::SIGNED_INTEGER) {
		const BACnetSignedInt *bacsint = dynamic_cast<const BACnetSignedInt *>(dataValue);
		if(bacsint) {
			if(bacsint->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
			}
			bacsint->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::REAL) {
		const BACnetReal *bacreal = dynamic_cast<const BACnetReal *>(dataValue);
		if(bacreal) {
			if(bacreal->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacreal->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::DOUBLE) {
		const BACnetDouble *bacdouble = dynamic_cast<const BACnetDouble *>(dataValue);
		if(bacdouble) {
			if(bacdouble->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacdouble->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::OCTET_STRING) {

		/** I do not know if this data-type works. I cannot find an Octet-String Object to test this on.
		 * 99.9% of the folks use just AI, AO, AV, BI, BO, BV, Multi-State in, and Multi-State out BACnet object types.
		 * */
		const BACnetOctetString *bacoctetstr = dynamic_cast<const BACnetOctetString *>(dataValue);
		if(bacoctetstr) {
			if(bacoctetstr->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacoctetstr->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::CHARACTER_STRING) {

		/** Note. This really doesn't do much good to only return 4-bytes for character string.
		 * You should use the string record instead.
		 * */
		const BACnetCharacterString *baccharstr = dynamic_cast<const BACnetCharacterString *>(dataValue);
		if(baccharstr) {
			if(baccharstr->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			baccharstr->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::BIT_STRING) {
		/** Note: the bits will be in reverse order from original read.
		 * So if you read 0xDF (1101 1111) you will see 0xFB (1111 1011) */
		const BACnetBitString *bacbitstr = dynamic_cast<const BACnetBitString *>(dataValue);
		if(bacbitstr) {
			if(bacbitstr->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacbitstr->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::ENUMERATED) {
		const BACnetEnumerated *bacenum = dynamic_cast<const BACnetEnumerated *>(dataValue);
		if(bacenum) {
			if(bacenum->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacenum->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::DATE) {

		const BACnetDate *bacdate = dynamic_cast<const BACnetDate *>(dataValue);
		if(bacdate) {
			if(bacdate->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacdate->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::TIME) {

		const BACnetTime *bactime = dynamic_cast<const BACnetTime *>(dataValue);
		if(bactime) {
			if(bactime->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bactime->toCString(rec->val, MAX_STRING_SIZE);
			return 0;
		}
	}
	if(DATA_TYPE == BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER) {

		const BACnetAppObjId *bacobjid = dynamic_cast<const BACnetAppObjId *>(dataValue);
		if(bacobjid) {
			if(bacobjid->isNull()) {
				BACnetNull::Null->toCString(rec->val, MAX_STRING_SIZE);
				return 0;
			}
			bacobjid->toCString(rec->val, MAX_STRING_SIZE);
		}

	}

	recGblSetSevr(rec,READ_ALARM,INVALID_ALARM);

	return -1;

}

/* Create the dset for devAiBacNet */
struct AI_DSET_TYPE
{
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       read;
        DEVSUPFUN       special_linconv;
}  dev_ai_bacnet =
{
        6,
        NULL,
        (DEVSUPFUN)dev_init,
        (DEVSUPFUN)init_rec_ai,
        NULL,
        (DEVSUPFUN)read_ai,
        NULL
};

/* Create the dset for devAoBacNet */
struct AO_DSET_TYPE
{
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       read;
        DEVSUPFUN       special_linconv;
}  dev_ao_bacnet =
{
        6,
        NULL,
        (DEVSUPFUN)dev_init,
        (DEVSUPFUN)init_rec_ao,
        NULL,
        (DEVSUPFUN)write_ao,
        NULL
};

struct SI_DSET_TYPE
{
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       read;
        DEVSUPFUN       special_linconv;
}  dev_si_bacnet =
{
        6,
        NULL,
        (DEVSUPFUN)dev_init,
        (DEVSUPFUN)init_rec_si,
        NULL,
        (DEVSUPFUN)read_si,
        NULL
};

epicsExportAddress(dset, dev_ai_bacnet);
epicsExportAddress(dset, dev_ao_bacnet);
epicsExportAddress(dset, dev_si_bacnet);

/* Create the dset for ... */
struct AIS_DSET_TYPE
{
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       read;
        DEVSUPFUN       special_linconv;
}  dev_ai_bacnet_stats =
{
        6,
        NULL,
        (DEVSUPFUN)dev_init,
        (DEVSUPFUN)init_rec_ai_devstats,
        NULL,
        (DEVSUPFUN)read_ai_devstats,
        NULL
};

epicsExportAddress(dset, dev_ai_bacnet_stats);

