/*
 * BACnetWhoIsService.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: 8w4
 */

#include "BACnetWhoIsService.h"
#include "BACnetDefs.h"
#include "BACnetTag.h"

#include <sstream>
#include <cstring>
#include <stdexcept>

BACnetWhoIsService::BACnetWhoIsService()
:BACnetApdu(&BACnetEnumPDUChoice::UNCONFIRMED_REQUEST, &BACnetEnumUnconfirmedService::WHO_IS),
 lowRangeInst(), highRangeInst()
{
	// TODO Auto-generated constructor stub

}

BACnetWhoIsService::BACnetWhoIsService(int devInstance)
:BACnetApdu(&BACnetEnumPDUChoice::UNCONFIRMED_REQUEST, &BACnetEnumUnconfirmedService::WHO_IS),
 lowRangeInst(devInstance), highRangeInst(devInstance)
{

}

BACnetWhoIsService::BACnetWhoIsService(int lowInstance, int highInstance)
:BACnetApdu(&BACnetEnumPDUChoice::UNCONFIRMED_REQUEST, &BACnetEnumUnconfirmedService::WHO_IS)
{

	/**
	 * 16.10.1.1.1 Device Instance Range Low Limit
	 * "If the 'Device Instance Range Low Limit' parameter is present,
	 * then the 'Device Instance Range High Limit' parameter shall also be present"
	 * */

	/** Sentinel value for no instance*/
	if(lowInstance < 0) {
		this->lowRangeInst = BACnetInstance();
		this->highRangeInst = BACnetInstance();
	}
	else {

		/** Is highRange present too?*/
		if(highInstance > 0) {
			if(highInstance >= lowInstance) {
				this->lowRangeInst = BACnetInstance(lowInstance);
				this->highRangeInst = BACnetInstance(highInstance);
			}
			else {
				/** for printing errors...*/
				ostringstream errstr;
				errstr << "Error! BACnetWhoIsService::BACnetWhoIsService(int lowInstance, int highInstance): " <<
						"lowInstance(" << lowInstance <<") is greater than highInstance(" << highInstance << ")" << endl;
				throw std::invalid_argument(errstr.str());
			}
		}
		else {
			this->lowRangeInst = BACnetInstance(lowInstance);
			this->highRangeInst = BACnetInstance(lowInstance);
		}

	}

}

BACnetWhoIsService::~BACnetWhoIsService() {
	// TODO Auto-generated destructor stub
}

uint32_t BACnetWhoIsService::getLowRangeInstance(void) const {
	return this->lowRangeInst.get_instance();
}

uint32_t BACnetWhoIsService::getHighRangeInstance(void) const {
	return this->highRangeInst.get_instance();
}

size_t BACnetWhoIsService::get_length(void) const {

	size_t len = 0;

	/** PDU Type is one octet.*/
	len += 1;

	/** Service Type is one octet.*/
	len += 1;

	/** If we have a range...?*/
	if(this->lowRangeInst.get_instance() != NULL_BACNET_INSTANCE) {

		/** Because instance_low and instance_high have a max length of three (3)
		 * then the tag portion of the encoding (i.e., tag0 and tag1) is NOT variable and therefore
		 * the length of instance_low and instance_high can fit in a single tag.*/

		/** Tag0 is a length of one (1)*/
		len += 1;

		/** number of octets to encode the instance...*/
		len += this->lowRangeInst.get_length();

		/** Tag1 is a length of one (1)*/
		len += 1;

		/** number of octets to encode the instance...*/
		len += this->highRangeInst.get_length();
	}

	return len;
}

int BACnetWhoIsService::encode(BACnetBuffer &buff) {
	//BACnetBuffer::iterator it = buff.end();

	/** First octet is PDU type...*/
	buff += (BACnetEnumPDUChoice::UNCONFIRMED_REQUEST.getValue() << 4);

	/** Second octet is service choice */
	buff += BACnetEnumUnconfirmedService::WHO_IS.getValue();

	/** We check for low instance to not be equal to NULL_BACNET_INSTANCE to let us know that a range exists or not.*/
	if(this->lowRangeInst.get_instance() != NULL_BACNET_INSTANCE) {

		BACnetTag tag = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 0, lowRangeInst.get_length());
		tag.encode(buff);
		lowRangeInst.encode(buff);

		tag = BACnetTag(&BACnetEnumTagChoice::CONTEXT_SPECIFIC_TAG, 1, highRangeInst.get_length());
		tag.encode(buff);
		highRangeInst.encode(buff);
	}

	//return (buff.end() - it);
	return 0;
}






