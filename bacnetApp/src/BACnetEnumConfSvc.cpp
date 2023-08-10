/*
 * BACnetEnumConfSvc.cpp
 *
 *  Created on: Dec 20, 2017
 *      Author: 8w4
 */

#include <stdexcept>
#include <iostream>
#include <sstream>

#include "BACnetEnumConfSvc.h"

BACnetConfSvcChoice const BACnetEnumConfSvc::ACKNOWLEDGE_ALARM = BACnetConfSvcChoice(0, "ACKNOWLEDGE_ALARM");
BACnetConfSvcChoice const BACnetEnumConfSvc::COV_NOTIFICATION = BACnetConfSvcChoice(1, "COV_NOTIFICATION");
BACnetConfSvcChoice const BACnetEnumConfSvc::EVENT_NOTIFICATION = BACnetConfSvcChoice(2, "EVENT_NOTIFICATION");
BACnetConfSvcChoice const BACnetEnumConfSvc::GET_ALARM_SUMMARY = BACnetConfSvcChoice(3, "GET_ALARM_SUMMARY");
BACnetConfSvcChoice const BACnetEnumConfSvc::GET_ENROLLMENT_SUMMARY = BACnetConfSvcChoice(4, "GET_ENROLLMENT_SUMMARY");
BACnetConfSvcChoice const BACnetEnumConfSvc::SUBSCRIBE_COV = BACnetConfSvcChoice(5, "SUBSCRIBE_COV");
BACnetConfSvcChoice const BACnetEnumConfSvc::ATOMIC_READ_FILE = BACnetConfSvcChoice(6, "ATOMIC_READ_FILE");
BACnetConfSvcChoice const BACnetEnumConfSvc::ATOMIC_WRITE_FILE = BACnetConfSvcChoice(7, "ATOMIC_WRITE_FILE");
BACnetConfSvcChoice const BACnetEnumConfSvc::ADD_LIST_ELEMENT = BACnetConfSvcChoice(8, "ADD_LIST_ELEMENT");
BACnetConfSvcChoice const BACnetEnumConfSvc::REMOVE_LIST_ELEMENT = BACnetConfSvcChoice(9, "REMOVE_LIST_ELEMENT");
BACnetConfSvcChoice const BACnetEnumConfSvc::CREATE_OBJECT = BACnetConfSvcChoice(10, "CREATE_OBJECT");
BACnetConfSvcChoice const BACnetEnumConfSvc::DELETE_OBJECT = BACnetConfSvcChoice(11, "DELETE_OBJECT");
BACnetConfSvcChoice const BACnetEnumConfSvc::READ_PROPERTY = BACnetConfSvcChoice(12, "READ_PROPERTY");
BACnetConfSvcChoice const BACnetEnumConfSvc::READ_PROP_CONDITIONAL = BACnetConfSvcChoice(13, "READ_PROP_CONDITIONAL");
BACnetConfSvcChoice const BACnetEnumConfSvc::READ_PROP_MULTIPLE = BACnetConfSvcChoice(14, "READ_PROP_MULTIPLE");
BACnetConfSvcChoice const BACnetEnumConfSvc::WRITE_PROPERTY = BACnetConfSvcChoice(15, "WRITE_PROPERTY");
BACnetConfSvcChoice const BACnetEnumConfSvc::WRITE_PROP_MULTIPLE = BACnetConfSvcChoice(16, "WRITE_PROP_MULTIPLE");
BACnetConfSvcChoice const BACnetEnumConfSvc::DEVICE_COMMUNICATION_CONTROL = BACnetConfSvcChoice(17, "DEVICE_COMMUNICATION_CONTROL");
BACnetConfSvcChoice const BACnetEnumConfSvc::PRIVATE_TRANSFER = BACnetConfSvcChoice(18, "PRIVATE_TRANSFER");
BACnetConfSvcChoice const BACnetEnumConfSvc::TEXT_MESSAGE = BACnetConfSvcChoice(19, "TEXT_MESSAGE");
BACnetConfSvcChoice const BACnetEnumConfSvc::REINITIALIZE_DEVICE = BACnetConfSvcChoice(20, "REINITIALIZE_DEVICE");
BACnetConfSvcChoice const BACnetEnumConfSvc::VT_OPEN = BACnetConfSvcChoice(21, "VT_OPEN");
BACnetConfSvcChoice const BACnetEnumConfSvc::VT_CLOSE = BACnetConfSvcChoice(22, "VT_CLOSE");
BACnetConfSvcChoice const BACnetEnumConfSvc::VT_DATA = BACnetConfSvcChoice(23, "VT_DATA");
BACnetConfSvcChoice const BACnetEnumConfSvc::AUTHENTICATE = BACnetConfSvcChoice(24, "AUTHENTICATE");
BACnetConfSvcChoice const BACnetEnumConfSvc::REQUEST_KEY = BACnetConfSvcChoice(25, "REQUEST_KEY");
BACnetConfSvcChoice const BACnetEnumConfSvc::READ_RANGE = BACnetConfSvcChoice(26, "READ_RANGE");
BACnetConfSvcChoice const BACnetEnumConfSvc::LIFE_SAFETY_OPERATION = BACnetConfSvcChoice(27, "LIFE_SAFETY_OPERATION");
BACnetConfSvcChoice const BACnetEnumConfSvc::SUBSCRIBE_COV_PROPERTY = BACnetConfSvcChoice(28, "SUBSCRIBE_COV_PROPERTY");
BACnetConfSvcChoice const BACnetEnumConfSvc::GET_EVENT_INFORMATION = BACnetConfSvcChoice(29, "GET_EVENT_INFORMATION");


std::map<uint16_t, BACnetConfSvcChoice const *> BACnetEnumConfSvc::objectMap = BACnetEnumConfSvc::init_map();


std::map<uint16_t, BACnetConfSvcChoice const *> BACnetEnumConfSvc::init_map() {

	std::map<uint16_t, BACnetConfSvcChoice const *> lmap;

	lmap[ACKNOWLEDGE_ALARM.getValue()] = (BACnetConfSvcChoice const *) &ACKNOWLEDGE_ALARM;
	lmap[COV_NOTIFICATION.getValue()] = (BACnetConfSvcChoice const *) &COV_NOTIFICATION;
	lmap[EVENT_NOTIFICATION.getValue()] = (BACnetConfSvcChoice const *) &EVENT_NOTIFICATION;
	lmap[GET_ALARM_SUMMARY.getValue()] = (BACnetConfSvcChoice const *) &GET_ALARM_SUMMARY;
	lmap[GET_ENROLLMENT_SUMMARY.getValue()] = (BACnetConfSvcChoice const *) &GET_ENROLLMENT_SUMMARY;
	lmap[SUBSCRIBE_COV.getValue()] = (BACnetConfSvcChoice const *) &SUBSCRIBE_COV;
	lmap[ATOMIC_READ_FILE.getValue()] = (BACnetConfSvcChoice const *) &ATOMIC_READ_FILE;
	lmap[ATOMIC_WRITE_FILE.getValue()] = (BACnetConfSvcChoice const *) &ATOMIC_WRITE_FILE;
	lmap[ADD_LIST_ELEMENT.getValue()] = (BACnetConfSvcChoice const *) &ADD_LIST_ELEMENT;
	lmap[REMOVE_LIST_ELEMENT.getValue()] = (BACnetConfSvcChoice const *) &REMOVE_LIST_ELEMENT;
	lmap[CREATE_OBJECT.getValue()] = (BACnetConfSvcChoice const *) &CREATE_OBJECT;
	lmap[DELETE_OBJECT.getValue()] = (BACnetConfSvcChoice const *) &DELETE_OBJECT;
	lmap[READ_PROPERTY.getValue()] = (BACnetConfSvcChoice const *) &READ_PROPERTY;
	lmap[READ_PROP_CONDITIONAL.getValue()] = (BACnetConfSvcChoice const *) &READ_PROP_CONDITIONAL;
	lmap[READ_PROP_MULTIPLE.getValue()] = (BACnetConfSvcChoice const *) &READ_PROP_MULTIPLE;
	lmap[WRITE_PROPERTY.getValue()] = (BACnetConfSvcChoice const *) &WRITE_PROPERTY;
	lmap[WRITE_PROP_MULTIPLE.getValue()] = (BACnetConfSvcChoice const *) &WRITE_PROP_MULTIPLE;
	lmap[DEVICE_COMMUNICATION_CONTROL.getValue()] = (BACnetConfSvcChoice const *) &DEVICE_COMMUNICATION_CONTROL;
	lmap[PRIVATE_TRANSFER.getValue()] = (BACnetConfSvcChoice const *) &PRIVATE_TRANSFER;
	lmap[TEXT_MESSAGE.getValue()] = (BACnetConfSvcChoice const *) &TEXT_MESSAGE;
	lmap[REINITIALIZE_DEVICE.getValue()] = (BACnetConfSvcChoice const *) &REINITIALIZE_DEVICE;
	lmap[VT_OPEN.getValue()] = (BACnetConfSvcChoice const *) &VT_OPEN;
	lmap[VT_CLOSE.getValue()] = (BACnetConfSvcChoice const *) &VT_CLOSE;
	lmap[VT_DATA.getValue()] = (BACnetConfSvcChoice const *) &VT_DATA;
	lmap[AUTHENTICATE.getValue()] = (BACnetConfSvcChoice const *) &AUTHENTICATE;
	lmap[REQUEST_KEY.getValue()] = (BACnetConfSvcChoice const *) &REQUEST_KEY;
	lmap[READ_RANGE.getValue()] = (BACnetConfSvcChoice const *) &READ_RANGE;
	lmap[LIFE_SAFETY_OPERATION.getValue()] = (BACnetConfSvcChoice const *) &LIFE_SAFETY_OPERATION;
	lmap[SUBSCRIBE_COV_PROPERTY.getValue()] = (BACnetConfSvcChoice const *) &SUBSCRIBE_COV_PROPERTY;
	lmap[GET_EVENT_INFORMATION.getValue()] = (BACnetConfSvcChoice const *) &GET_EVENT_INFORMATION;

	return lmap;
}

BACnetConfSvcChoice const &BACnetEnumConfSvc::getEnumByValue(uint16_t enumValue) {

	std::map<uint16_t, BACnetConfSvcChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << enumValue;
		std::string s = "Invalid Enum value (" + os.str() + "): BACnetConfSvcChoice const &BACnetEnumConfSvc::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}






