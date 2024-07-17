/*
 * BACnetVariable.cpp
 *
 *  Created on: Jun 28, 2018
 *      Author: 8w4
 */

#include <stdexcept>
#include <sstream>

#include "BACnetVariable.h"
#include "BACnetBitString.h"
#include "BACnetReal.h"
#include "BACnetDouble.h"
#include "BACnetBoolean.h"
#include "BACnetEnumerated.h"
#include "BACnetUnsignedInt.h"
#include "BACnetSignedInt.h"
#include "ProtocolSvcSupported.h"
#include "BACnetBinaryPV.h"
#include "BACnetNull.h"
#include "BACnetCharacterString.h"
#include "BACnetOctetString.h"
#include "BACnetTime.h"
#include "BACnetDate.h"
#include "BACnetEnumEngUnits.h"
#include "BACnetDevice.h"
#include "BACnetAppObjId.h"



BACnetVariable::BACnetVariable(BACnetVarFuncChoice const &varFunc, BACnetObjPropRef const &objectPropRef,
		const BACnetDevice &dev)
:func(varFunc), objPropRef(objectPropRef), err(), errPresent(false), timeoutErrPresent(false),
 doWrite(false), lock(), devCallback(dev)
{
	BACnetAppDataType *pv = NULL;
	pv = determineDataType(this->objPropRef);

	/** for printing errors...*/
	ostringstream errstr;

	/** Just an FYI*/
	if(pv == NULL && this->func == BACnetEnumVarFunc::WRITE) {
		errstr << "ERROR! BACnetVariable::BACnetVariable: Could not determine the data-type for object-type \"" <<
				this->getObjectType().getName() << "\", Object-instance \"" << this->getObjectInstance() <<
				"\", object-property \"" << this->getObjectProperty().getName() << "\"" << endl;
		throw std::invalid_argument(errstr.str());
	}

}

BACnetVariable::BACnetVariable(BACnetVarFuncChoice const &varFunc, BACnetObjPropRef const &objectPropRef,
			BACnetApplicationDataTypeChoice const &dataType, const BACnetDevice &dev)
:func(varFunc), objPropRef(objectPropRef), err(), errPresent(false), timeoutErrPresent(false),
 doWrite(false), lock(), devCallback(dev)
{
	BACnetAppDataType *pv = NULL;
	pv = createDataType(&dataType);

	/** for printing errors...*/
	ostringstream errstr;

	if(pv == NULL) {
		errstr << " -> ERROR! BACnetVariable::BACnetVariable: "
				"could not create a data-type based the data-type format specifier provided ("
				<< dataType.getName() << ")" << endl;
		throw std::invalid_argument(errstr.str());
	}

	addToPropValList(*pv);
}

BACnetVariable::~BACnetVariable() {
	//cout << "BACnetVariable::~BACnetVariable() {" << endl;
	std::list<BACnetAppDataType *>::iterator itr = propValList.begin();
	while(itr != propValList.end()) {
		if((*itr)) {
			delete (*itr);
		}
		itr++;
	}
}

BACnetVarFuncChoice const &BACnetVariable::getVariableFunction(void) const {
	return this->func;
}

BACnetObjPropRef const &BACnetVariable::getObjectPropertyReference(void) const {
	return this->objPropRef;
}

BACnetObjIdentifier const &BACnetVariable::getObjectIdentifier(void) const {
	return this->objPropRef.getObjectId();
}

BACnetObjectType const &BACnetVariable::getObjectType(void) const {
	return *this->objPropRef.getObjectId().getObjectType();
}

uint32_t const BACnetVariable::getObjectInstance(void) const {
	return this->objPropRef.getObjectId().getObjectInstanceAsUint32_t();
}

BACnetPropertyType const &BACnetVariable::getObjectProperty(void) const {
	return *this->objPropRef.getPropertyId();
}

int BACnetVariable::getArrayIndex(void) const {
	return this->objPropRef.getArrayIndex();
}

void BACnetVariable::decode(std::list<BACnetApplicationData> &pvDataList) {

	/** */
	std::list<BACnetAppDataType *>::iterator itrTypeList = this->propValList.begin();

	/** First pass: this list should be empty...*/
	bool isEmpty = this->propValList.empty();

	/** If propValList is empty then we could not create the proper data type during initialization,
	 * and the type will have to be created here, during decoding.*/

	BACnetAppDataType *pv = NULL;
	std::list<BACnetApplicationData>::iterator itrDataList = pvDataList.begin();
	BACnetApplicationDataTypeChoice const *dataType = NULL;

	/** If the list is empty, then that means that we couldn't determine the data-type during initialization
	 * and need to do it here as we decode the octets.
	 * */
	if(isEmpty) {

		if(BACnet_verbosity > 1) {
			cout << ">>>> BACnetVariable::decode: propValList is empty. <<<<" << endl;
		}

		/** Now we must decode the pvData first to see what data-type the data is so that we
		 * can create the proper objects to support the data... e.g., Reals... Booleans... etc.*/

		/** Create a temporary list to hold the data-objects so that we don't have to lock and unlock
		 * the mutex multiple times for multiple items. The just do one lock/unlock at the end to copy the list.
		 * */
		propValList_t templist;

		while(itrDataList != pvDataList.end()) {

			/** Get the data-type to know how to handle/decode the data.*/
			dataType = (*itrDataList).getAppDataType();

			if(dataType) {
				pv = createDataType(dataType);
			}

			if(pv) {
				pv->decode(*itrDataList);
				templist.push_back(pv);
			}

			itrDataList++;
		}

		/** Lock the list and copy the contents over from the templist to the actual list.
		 * I think this will keep others from accessing the list if it was in the middle of adding data elements.
		 * */
		this->lock.lock();
		this->propValList = templist;
		this->lock.unlock();
	}
	else {

		if(BACnet_verbosity > 1) {
			cout << ">>>> BACnetVariable::decode: propValList is NOT empty. <<<<" << endl;
		}

		/** If the list is not empty then the size of the incoming pvDataList and the propValList
		 * must be the same size..*/
		if(this->propValList.size() != pvDataList.size()) {
			cout << "ERROR! BACnetVariable::decode: PropertyTypeList size (" << this->propValList.size() <<
					") and PvDataList size (" << pvDataList.size() << ") must be equal!" << endl;
			return;
		}

		/** Iterate thru the lists and decode the pvData into the propValData*/
		while(itrTypeList != this->propValList.end()) {

			pv = *itrTypeList;

			if(pv) {

				/** Stupid BACnetNull data type! So, in some cases a data type can switch between BACnetNull
				 * and other BACnet data types. e.g., BACnetReal, BACnetBoolean, etc.
				 *
				 * */
				if(pv->getDataType() == BACnetEnumApplicationDataType::NNULL &&
						(*itrDataList).getAppDataType() != &BACnetEnumApplicationDataType::NNULL) {

					/** Get the new data type that used to be BACnetNull but is now something else. */
					pv = createDataType((*itrDataList).getAppDataType());
				}

				if(pv) {
					pv->decode(*itrDataList);
				}
			}

			itrTypeList++;
			itrDataList++;
		}

	}
	this->errPresent = false;
	this->timeoutErrPresent = false;
}

void BACnetVariable::decode(BACnetApplicationData &pvData) {
	(*this->propValList.begin())->decode(pvData);
	this->errPresent = false;
	this->timeoutErrPresent = false;
}

void BACnetVariable::decode(const BACnetApplicationData &pvData) {
	(*this->propValList.begin())->decode(pvData);
	this->errPresent = false;
	this->timeoutErrPresent = false;
}

void BACnetVariable::printData(void) const {

	std::list<BACnetAppDataType *>::const_iterator itr = this->propValList.begin();

	while(itr != this->propValList.end()) {
		(*itr)->printData();
		itr++;
	}
}

BACnetApplicationDataTypeChoice const *BACnetVariable::getAppDataType(void) {
	if(this->propValList.size() > 0) {
		return &(*this->propValList.begin())->getDataType();
	}
	return NULL;
}

bool BACnetVariable::hasDataInPropValList(void) const {
	return (this->propValList.size() > 0);
}

bool BACnetVariable::hasArrayIndex(void) const {
	return (this->objPropRef.getArrayIndex() > 0);
}

bool BACnetVariable::hasError(void) const {
	return this->errPresent || this->timeoutErrPresent;
}

void BACnetVariable::setError(const BACnetErrorPdu &bacError) {
	this->err = bacError;
	this->errPresent = true;
	this->timeoutErrPresent = false;
}

void BACnetVariable::setTimeoutError() {
	this->timeoutErrPresent = true;
}

string BACnetVariable::getErrorString(void) const {
	if (this->timeoutErrPresent) {
		return "Communication-Timeout";
	} else {
		return this->err.toString();
	}
}

const propValList_t &BACnetVariable::getPropValList(void) {
	return this->propValList;
}

const BACnetAppDataType *BACnetVariable::getConstPropValListTop(void) {
	return (*this->propValList.begin());
}

BACnetAppDataType *BACnetVariable::getPropValListTop(void) {
	return (*this->propValList.begin());
}

void BACnetVariable::addToPropValList(BACnetAppDataType &appDataType) {
	this->lock.lock();
	this->propValList.push_back(&appDataType);
	this->lock.unlock();
}

void BACnetVariable::addToPropValList(propValList_t const &appDataTypeList) {
	this->lock.lock();
	this->propValList = appDataTypeList;
	this->lock.unlock();
}

template <class T>
void BACnetVariable::createPriorityArrayList(propValList_t &pvList) {

	BACnetAppDataType *pAppType = NULL;

	/** create the whole array (16-elements long)*/
	for(int i=0; i<16; i++) {
		pAppType = new T();
		pvList.push_back(pAppType);
	}
}

BACnetAppDataType *BACnetVariable::determineAnalogInputDataType(BACnetPropertyType const &prop, int const arrayIndex) {

	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetReal();
		addToPropValList(*pAppType);
		return pAppType;
	}
	return NULL;
}

BACnetAppDataType *BACnetVariable::determineAnalogOutputDataType(BACnetPropertyType const &prop, int const arrayIndex) {

	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetReal();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRIORITY_ARRAY) {

		propValList_t tempList;

		/** (-1) means grab the whole array (16-elements long)*/
		if(arrayIndex == (-1)) {
			createPriorityArrayList<BACnetReal>(tempList);
		}
		else {
			/** We are only interested in a specific element of the array.*/
			pAppType = new BACnetReal();
			tempList.push_back(pAppType);
		}

		/** Assigning the whole list and Only locking the list for assignment */
		addToPropValList(tempList);

		return pAppType;

	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_UNITS) {
		pAppType = new BACnetEnumerated(BACnetEnumEngUnits::EnumEngUnits);
		addToPropValList(*pAppType);
		return pAppType;
	}
	return NULL;
}

BACnetAppDataType *BACnetVariable::determineAnalogValueDataType(BACnetPropertyType const &prop, int const arrayIndex) {

	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetReal();
		addToPropValList(*pAppType);
		return pAppType;
	}
	return NULL;
}

BACnetAppDataType *BACnetVariable::determineBinaryInputDataType(BACnetPropertyType const &prop, int const arrayIndex) {

	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetBinaryPV();
		addToPropValList(*pAppType);
		return pAppType;
	}

	return NULL;
}

BACnetAppDataType *BACnetVariable::determineBinaryOutputDataType(BACnetPropertyType const &prop, int const arrayIndex) {

	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetBinaryPV();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRIORITY_ARRAY) {

		cout << "if(prop == BACnetEnumPropertyIdentifier::PROP_PRIORITY_ARRAY) { arrayIndex: " << arrayIndex << endl;

		propValList_t tempList;

		/** (-1) means grab the whole array (16-elements long)*/
		if(arrayIndex == (-1)) {
			createPriorityArrayList<BACnetBinaryPV>(tempList);
		}
		else {
			/** We are only interested in a specific element of the array.*/
			pAppType = new BACnetBinaryPV();
			tempList.push_back(pAppType);
		}

		/** Assigning the whole list and Only locking the list for assignment */
		addToPropValList(tempList);

		return pAppType;
	}
	return NULL;
}

BACnetAppDataType *BACnetVariable::determineBinaryValueDataType(BACnetPropertyType const &prop, int const arrayIndex) {

	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetBinaryPV();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRIORITY_ARRAY) {

		propValList_t tempList;

		/** (-1) means grab the whole array (16-elements long)*/
		if(arrayIndex == (-1)) {
			createPriorityArrayList<BACnetBinaryPV>(tempList);
		}
		else {
			/** We are only interested in a specific element of the array.*/
			pAppType = new BACnetBinaryPV();
			tempList.push_back(pAppType);
		}

		/** Assigning the whole list and Only locking the list for assignment */
		addToPropValList(tempList);

		return pAppType;
	}
	return NULL;
}

BACnetAppDataType *BACnetVariable::determineDeviceValueDataType(BACnetPropertyType const &prop, int const arrayIndex) {

	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PROTOCOL_SERVICES_SUPPORTED) {
		pAppType = new ProtocolSvcSupported();
		addToPropValList(*pAppType);
		return pAppType;
	}



	return NULL;
}

BACnetAppDataType *BACnetVariable::determineMSInputDataType(BACnetPropertyType const &prop, int const arrayIndex) {
	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetUnsignedInt();
		addToPropValList(*pAppType);
		return pAppType;
	}

	return NULL;
}

BACnetAppDataType *BACnetVariable::determineMSOutputDataType(BACnetPropertyType const &prop, int const arrayIndex) {
	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetUnsignedInt();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRIORITY_ARRAY) {

		propValList_t tempList;

		/** (-1) means grab the whole array (16-elements long)*/
		if(arrayIndex == (-1)) {
			createPriorityArrayList<BACnetUnsignedInt>(tempList);
		}
		else {
			/** We are only interested in a specific element of the array.*/
			pAppType = new BACnetUnsignedInt();
			tempList.push_back(pAppType);
		}

		/** Assigning the whole list and Only locking the list for assignment */
		addToPropValList(tempList);

		return pAppType;

	}

	return NULL;
}

BACnetAppDataType *BACnetVariable::determineMSValueDataType(BACnetPropertyType const &prop, int const arrayIndex) {
	BACnetAppDataType *pAppType = NULL;

	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_IDENTIFIER) {
		pAppType = new BACnetAppObjId();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_NAME) {
		pAppType = new BACnetCharacterString();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_OBJECT_TYPE) {
		pAppType = new BACnetEnumerated();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRESENT_VALUE) {
		pAppType = new BACnetUnsignedInt();
		addToPropValList(*pAppType);
		return pAppType;
	}
	if(prop == BACnetEnumPropertyIdentifier::PROP_PRIORITY_ARRAY) {

		propValList_t tempList;

		/** (-1) means grab the whole array (16-elements long)*/
		if(arrayIndex == (-1)) {
			createPriorityArrayList<BACnetUnsignedInt>(tempList);
		}
		else {
			/** We are only interested in a specific element of the array.*/
			pAppType = new BACnetUnsignedInt();
			tempList.push_back(pAppType);
		}

		/** Assigning the whole list and Only locking the list for assignment */
		addToPropValList(tempList);

		return pAppType;

	}

	return NULL;
}

BACnetAppDataType *BACnetVariable::determineDataType(BACnetObjPropRef const &objPropRef) {

	BACnetObjectType const *objTyp = objPropRef.getObjectType();

	BACnetAppDataType *pAppType = NULL;

	if(objTyp) {

		/** Is the object type one of the standard types? */
		if(*objTyp == BACnetEnumObjectType::OBJECT_ANALOG_INPUT) {
			pAppType = determineAnalogInputDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_ANALOG_OUTPUT) {
			pAppType = determineAnalogOutputDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_ANALOG_VALUE) {
			pAppType = determineAnalogValueDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_BINARY_INPUT) {
			pAppType = determineBinaryInputDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_BINARY_OUTPUT) {
			pAppType = determineBinaryOutputDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_BINARY_VALUE) {
			pAppType = determineBinaryValueDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_DEVICE) {
			pAppType = determineDeviceValueDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_MULTI_STATE_INPUT) {
			pAppType = determineMSInputDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_MULTI_STATE_OUTPUT) {
			pAppType = determineMSOutputDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}
		if(*objTyp == BACnetEnumObjectType::OBJECT_MULTI_STATE_VALUE) {
			pAppType = determineMSValueDataType(*objPropRef.getPropertyId(), objPropRef.getArrayIndex());
			return pAppType;
		}

	}

	return NULL;
}

BACnetAppDataType *BACnetVariable::createDataType(BACnetApplicationDataTypeChoice const *dataType) {

	BACnetAppDataType *pv = NULL;

	if(dataType) {

		if(*dataType == BACnetEnumApplicationDataType::NNULL) {

			/** Static Null*/
			pv = BACnetNull::Null;
		}
		if(*dataType == BACnetEnumApplicationDataType::BOOLEAN) {
			pv = new BACnetBoolean();
		}
		if(*dataType == BACnetEnumApplicationDataType::UNSIGNED_INTEGER) {
			pv = new BACnetUnsignedInt();
		}
		if(*dataType == BACnetEnumApplicationDataType::SIGNED_INTEGER) {
			pv = new BACnetSignedInt();
		}
		if(*dataType == BACnetEnumApplicationDataType::REAL) {
			pv = new BACnetReal();
		}
		if(*dataType == BACnetEnumApplicationDataType::DOUBLE) {
			pv = new BACnetDouble();
		}
		if(*dataType == BACnetEnumApplicationDataType::OCTET_STRING) {
			pv = new BACnetOctetString();
		}
		if(*dataType == BACnetEnumApplicationDataType::CHARACTER_STRING) {
			pv = new BACnetCharacterString();
		}
		if(*dataType == BACnetEnumApplicationDataType::BIT_STRING) {
			pv = new BACnetBitString();
		}
		if(*dataType == BACnetEnumApplicationDataType::ENUMERATED) {
			pv = new BACnetEnumerated();
		}
		if(*dataType == BACnetEnumApplicationDataType::DATE) {
			pv = new BACnetDate();
		}
		if(*dataType == BACnetEnumApplicationDataType::TIME) {
			pv = new BACnetTime();
		}
		if(*dataType == BACnetEnumApplicationDataType::BACNET_OBJECT_IDENTIFIER) {
			pv = new BACnetAppObjId();
		}
	}

	return pv;

}

bool BACnetVariable::getDoWrite(void) const {
	return this->doWrite;
}

void BACnetVariable::setWriteFlag(void) {

	if(this->propValList.size() < 1) {

		/** This object for writing values should've been created during record-init*/
		cout << "ERROR! BACnetVariable::setWriteFlag: Could not write value because the property/value list is empty." << endl;
		return;
	}

	propValList_t::const_iterator itr = this->propValList.begin();

	/** Flag for writing.*/
	this->doWrite = true;

}

void BACnetVariable::clearWriteFlag(void) {
	/** Flag for writing.*/
	this->doWrite = false;
}


