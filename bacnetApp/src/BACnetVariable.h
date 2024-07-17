/*
 * BACnetVariable.h
 *
 *  Created on: Jun 28, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETVARIABLE_H_
#define BACNETAPP_SRC_BACNETVARIABLE_H_

#include "BACnetObjPropRef.h"
#include "BACnetAppDataType.h"
#include "BACnetApplicationData.h"
#include "BACnetEnumVarFunc.h"
#include "BACnetErrorPdu.h"

#include "epicsMutex.h"

using namespace std;

typedef std::list<BACnetAppDataType *> propValList_t;
class BACnetDevice;

class BACnetVariable {
private:

	BACnetVarFuncChoice const &func;

	BACnetObjPropRef objPropRef;
	std::list<BACnetAppDataType *> propValList;
	BACnetErrorPdu err;
	bool errPresent;
	bool timeoutErrPresent;
	bool doWrite;

	epicsMutex lock;

	const BACnetDevice &devCallback;


	/** This method locks */
	void addToPropValList(BACnetAppDataType &appDataType);
	void addToPropValList(propValList_t const &appDataTypeList);

	template <class T>
	void createPriorityArrayList(propValList_t &pvList);

	BACnetAppDataType *determineDataType(BACnetObjPropRef const &objPropRef);

	BACnetAppDataType *determineAnalogInputDataType(BACnetPropertyType const &prop, int const arrayIndex);
	BACnetAppDataType *determineAnalogOutputDataType(BACnetPropertyType const &prop, int const arrayIndex);
	BACnetAppDataType *determineAnalogValueDataType(BACnetPropertyType const &prop, int const arrayIndex);

	BACnetAppDataType *determineBinaryInputDataType(BACnetPropertyType const &prop, int const arrayIndex);
	BACnetAppDataType *determineBinaryOutputDataType(BACnetPropertyType const &prop, int const arrayIndex);
	BACnetAppDataType *determineBinaryValueDataType(BACnetPropertyType const &prop, int const arrayIndex);

	BACnetAppDataType *determineDeviceValueDataType(BACnetPropertyType const &prop, int const arrayIndex);

	BACnetAppDataType *determineMSInputDataType(BACnetPropertyType const &prop, int const arrayIndex);
	BACnetAppDataType *determineMSOutputDataType(BACnetPropertyType const &prop, int const arrayIndex);
	BACnetAppDataType *determineMSValueDataType(BACnetPropertyType const &prop, int const arrayIndex);

	BACnetAppDataType *createDataType(BACnetApplicationDataTypeChoice const *appDataType);


public:
	BACnetVariable(BACnetVarFuncChoice const &varFunc, BACnetObjPropRef const &objectPropRef,
			const BACnetDevice &dev);
	BACnetVariable(BACnetVarFuncChoice const &varFunc, BACnetObjPropRef const &objectPropRef,
			BACnetApplicationDataTypeChoice const &dataType, const BACnetDevice &dev);
	virtual ~BACnetVariable();

	BACnetVarFuncChoice const &getVariableFunction(void) const;
	BACnetObjPropRef const &getObjectPropertyReference(void) const;
	BACnetObjIdentifier const &getObjectIdentifier(void) const;
	BACnetObjectType const &getObjectType(void) const;
	uint32_t const getObjectInstance(void) const;
	BACnetPropertyType const &getObjectProperty(void) const;
	int getArrayIndex(void) const;

	void decode(std::list<BACnetApplicationData> &pvDataList);
	void decode(BACnetApplicationData &pvData);
	void decode(const BACnetApplicationData &pvData);

	void printData(void) const;

	BACnetApplicationDataTypeChoice const *getAppDataType(void);
	bool hasDataInPropValList(void) const;
	bool hasArrayIndex(void) const;
	bool hasError(void) const;
	void setError(const BACnetErrorPdu &bacError);
	void setTimeoutError();
	string getErrorString(void) const;

	const propValList_t &getPropValList(void);
	const BACnetAppDataType *getConstPropValListTop(void);
	BACnetAppDataType *getPropValListTop(void);

	bool getDoWrite(void) const;
	void setWriteFlag(void);
	void clearWriteFlag(void);

};

#endif /* BACNETAPP_SRC_BACNETVARIABLE_H_ */
