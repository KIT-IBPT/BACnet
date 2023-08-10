/*
 * BACnetEnumEngUnits.h
 *
 *  Created on: Jul 11, 2018
 *      Author: 8w4
 */

#ifndef BACNETAPP_SRC_BACNETENUMENGUNITS_H_
#define BACNETAPP_SRC_BACNETENUMENGUNITS_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <list>
#include <map>

#include "BACnetEnumSingle.h"
#include "BACnetEnum.h"

using namespace std;

#define MAX_ENGUNITS_CHOICE 0xEC // 236 in decimal

class BACnetEngUnitsChoice : public BACnetEnumSingle {

public:
	BACnetEngUnitsChoice(uint16_t const enumValue, string const name);
	virtual ~BACnetEngUnitsChoice();
};

class BACnetEnumEngUnits : public BACnetEnum {
private:
	static std::map<uint16_t, BACnetEngUnitsChoice const *> objectMap;

	static std::map<uint16_t, BACnetEngUnitsChoice const *> init_map(void);
public:

	static BACnetEnumEngUnits EnumEngUnits;

	    /* Acceleration */
	static BACnetEngUnitsChoice const UNITS_METERS_PER_SECOND_PER_SECOND;
	    /* Area */
	static BACnetEngUnitsChoice const UNITS_SQUARE_METERS;
	static BACnetEngUnitsChoice const UNITS_SQUARE_CENTIMETERS;
	static BACnetEngUnitsChoice const UNITS_SQUARE_FEET;
	static BACnetEngUnitsChoice const UNITS_SQUARE_INCHES;
	    /* Currency */
	static BACnetEngUnitsChoice const UNITS_CURRENCY1;
	static BACnetEngUnitsChoice const UNITS_CURRENCY2;
	static BACnetEngUnitsChoice const UNITS_CURRENCY3;
	static BACnetEngUnitsChoice const UNITS_CURRENCY4;
	static BACnetEngUnitsChoice const UNITS_CURRENCY5;
	static BACnetEngUnitsChoice const UNITS_CURRENCY6;
	static BACnetEngUnitsChoice const UNITS_CURRENCY7;
	static BACnetEngUnitsChoice const UNITS_CURRENCY8;
	static BACnetEngUnitsChoice const UNITS_CURRENCY9;
	static BACnetEngUnitsChoice const UNITS_CURRENCY10;
	    /* Electrical */
	static BACnetEngUnitsChoice const UNITS_MILLIAMPERES;
	static BACnetEngUnitsChoice const UNITS_AMPERES;
	static BACnetEngUnitsChoice const UNITS_AMPERES_PER_METER;
	static BACnetEngUnitsChoice const UNITS_AMPERES_PER_SQUARE_METER;
	static BACnetEngUnitsChoice const UNITS_AMPERE_SQUARE_METERS;
	static BACnetEngUnitsChoice const UNITS_DECIBELS;
	static BACnetEngUnitsChoice const UNITS_DECIBELS_MILLIVOLT;
	static BACnetEngUnitsChoice const UNITS_DECIBELS_VOLT;
	static BACnetEngUnitsChoice const UNITS_FARADS;
	static BACnetEngUnitsChoice const UNITS_HENRYS;
	static BACnetEngUnitsChoice const UNITS_OHMS;
	static BACnetEngUnitsChoice const UNITS_OHM_METERS;
	static BACnetEngUnitsChoice const UNITS_MILLIOHMS;
	static BACnetEngUnitsChoice const UNITS_KILOHMS;
	static BACnetEngUnitsChoice const UNITS_MEGOHMS;
	static BACnetEngUnitsChoice const UNITS_MICROSIEMENS;
	static BACnetEngUnitsChoice const UNITS_MILLISIEMENS;
	static BACnetEngUnitsChoice const UNITS_SIEMENS;        /* 1 mho equals 1 siemens */
	static BACnetEngUnitsChoice const UNITS_SIEMENS_PER_METER;
	static BACnetEngUnitsChoice const UNITS_TESLAS;
	static BACnetEngUnitsChoice const UNITS_VOLTS;
	static BACnetEngUnitsChoice const UNITS_MILLIVOLTS;
	static BACnetEngUnitsChoice const UNITS_KILOVOLTS;
	static BACnetEngUnitsChoice const UNITS_MEGAVOLTS;
	static BACnetEngUnitsChoice const UNITS_VOLT_AMPERES;
	static BACnetEngUnitsChoice const UNITS_KILOVOLT_AMPERES;
	static BACnetEngUnitsChoice const UNITS_MEGAVOLT_AMPERES;
	static BACnetEngUnitsChoice const UNITS_VOLT_AMPERES_REACTIVE;
	static BACnetEngUnitsChoice const UNITS_KILOVOLT_AMPERES_REACTIVE;
	static BACnetEngUnitsChoice const UNITS_MEGAVOLT_AMPERES_REACTIVE;
	static BACnetEngUnitsChoice const UNITS_VOLTS_PER_DEGREE_KELVIN;
	static BACnetEngUnitsChoice const UNITS_VOLTS_PER_METER;
	static BACnetEngUnitsChoice const UNITS_DEGREES_PHASE;
	static BACnetEngUnitsChoice const UNITS_POWER_FACTOR;
	static BACnetEngUnitsChoice const UNITS_WEBERS;
	    /* Energy */
	static BACnetEngUnitsChoice const UNITS_JOULES;
	static BACnetEngUnitsChoice const UNITS_KILOJOULES;
	static BACnetEngUnitsChoice const UNITS_KILOJOULES_PER_KILOGRAM;
	static BACnetEngUnitsChoice const UNITS_MEGAJOULES;
	static BACnetEngUnitsChoice const UNITS_WATT_HOURS;
	static BACnetEngUnitsChoice const UNITS_KILOWATT_HOURS;
	static BACnetEngUnitsChoice const UNITS_MEGAWATT_HOURS;
	static BACnetEngUnitsChoice const UNITS_WATT_HOURS_REACTIVE;
	static BACnetEngUnitsChoice const UNITS_KILOWATT_HOURS_REACTIVE;
	static BACnetEngUnitsChoice const UNITS_MEGAWATT_HOURS_REACTIVE;
	static BACnetEngUnitsChoice const UNITS_BTUS;
	static BACnetEngUnitsChoice const UNITS_KILO_BTUS;
	static BACnetEngUnitsChoice const UNITS_MEGA_BTUS;
	static BACnetEngUnitsChoice const UNITS_THERMS;
	static BACnetEngUnitsChoice const UNITS_TON_HOURS;
	    /* Enthalpy */
	static BACnetEngUnitsChoice const UNITS_JOULES_PER_KILOGRAM_DRY_AIR;
	static BACnetEngUnitsChoice const UNITS_KILOJOULES_PER_KILOGRAM_DRY_AIR;
	static BACnetEngUnitsChoice const UNITS_MEGAJOULES_PER_KILOGRAM_DRY_AIR;
	static BACnetEngUnitsChoice const UNITS_BTUS_PER_POUND_DRY_AIR;
	static BACnetEngUnitsChoice const UNITS_BTUS_PER_POUND;
	    /* Entropy */
	static BACnetEngUnitsChoice const UNITS_JOULES_PER_DEGREE_KELVIN;
	static BACnetEngUnitsChoice const UNITS_KILOJOULES_PER_DEGREE_KELVIN;
	static BACnetEngUnitsChoice const UNITS_MEGAJOULES_PER_DEGREE_KELVIN;
	static BACnetEngUnitsChoice const UNITS_JOULES_PER_KILOGRAM_DEGREE_KELVIN;
	    /* Force */
	static BACnetEngUnitsChoice const UNITS_NEWTON;
	    /* Frequency */
	static BACnetEngUnitsChoice const UNITS_CYCLES_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_CYCLES_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_HERTZ;
	static BACnetEngUnitsChoice const UNITS_KILOHERTZ;
	static BACnetEngUnitsChoice const UNITS_MEGAHERTZ;
	static BACnetEngUnitsChoice const UNITS_PER_HOUR;
	    /* Humidity */
	static BACnetEngUnitsChoice const UNITS_GRAMS_OF_WATER_PER_KILOGRAM_DRY_AIR;
	static BACnetEngUnitsChoice const UNITS_PERCENT_RELATIVE_HUMIDITY;
	    /* Length */
	static BACnetEngUnitsChoice const UNITS_MICROMETERS;
	static BACnetEngUnitsChoice const UNITS_MILLIMETERS;
	static BACnetEngUnitsChoice const UNITS_CENTIMETERS;
	static BACnetEngUnitsChoice const UNITS_KILOMETERS;
	static BACnetEngUnitsChoice const UNITS_METERS;
	static BACnetEngUnitsChoice const UNITS_INCHES;
	static BACnetEngUnitsChoice const UNITS_FEET;
	    /* Light */
	static BACnetEngUnitsChoice const UNITS_CANDELAS;
	static BACnetEngUnitsChoice const UNITS_CANDELAS_PER_SQUARE_METER;
	static BACnetEngUnitsChoice const UNITS_WATTS_PER_SQUARE_FOOT;
	static BACnetEngUnitsChoice const UNITS_WATTS_PER_SQUARE_METER;
	static BACnetEngUnitsChoice const UNITS_LUMENS;
	static BACnetEngUnitsChoice const UNITS_LUXES;
	static BACnetEngUnitsChoice const UNITS_FOOT_CANDLES;
	    /* Mass */
	static BACnetEngUnitsChoice const UNITS_MILLIGRAMS;
	static BACnetEngUnitsChoice const UNITS_GRAMS;
	static BACnetEngUnitsChoice const UNITS_KILOGRAMS;
	static BACnetEngUnitsChoice const UNITS_POUNDS_MASS;
	static BACnetEngUnitsChoice const UNITS_TONS;
	    /* Mass Flow */
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_KILOGRAMS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_KILOGRAMS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_KILOGRAMS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_POUNDS_MASS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_POUNDS_MASS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_POUNDS_MASS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_TONS_PER_HOUR;
	    /* Power */
	static BACnetEngUnitsChoice const UNITS_MILLIWATTS;
	static BACnetEngUnitsChoice const UNITS_WATTS;
	static BACnetEngUnitsChoice const UNITS_KILOWATTS;
	static BACnetEngUnitsChoice const UNITS_MEGAWATTS;
	static BACnetEngUnitsChoice const UNITS_BTUS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_KILO_BTUS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_HORSEPOWER;
	static BACnetEngUnitsChoice const UNITS_TONS_REFRIGERATION;
	    /* Pressure */
	static BACnetEngUnitsChoice const UNITS_PASCALS;
	static BACnetEngUnitsChoice const UNITS_HECTOPASCALS;
	static BACnetEngUnitsChoice const UNITS_KILOPASCALS;
	static BACnetEngUnitsChoice const UNITS_MILLIBARS;
	static BACnetEngUnitsChoice const UNITS_BARS;
	static BACnetEngUnitsChoice const UNITS_POUNDS_FORCE_PER_SQUARE_INCH;
	static BACnetEngUnitsChoice const UNITS_MILLIMETERS_OF_WATER;
	static BACnetEngUnitsChoice const UNITS_CENTIMETERS_OF_WATER;
	static BACnetEngUnitsChoice const UNITS_INCHES_OF_WATER;
	static BACnetEngUnitsChoice const UNITS_MILLIMETERS_OF_MERCURY;
	static BACnetEngUnitsChoice const UNITS_CENTIMETERS_OF_MERCURY;
	static BACnetEngUnitsChoice const UNITS_INCHES_OF_MERCURY;
	    /* Temperature */
	static BACnetEngUnitsChoice const UNITS_DEGREES_CELSIUS;
	static BACnetEngUnitsChoice const UNITS_DEGREES_KELVIN;
	static BACnetEngUnitsChoice const UNITS_DEGREES_KELVIN_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_DEGREES_KELVIN_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_DEGREES_FAHRENHEIT;
	static BACnetEngUnitsChoice const UNITS_DEGREE_DAYS_CELSIUS;
	static BACnetEngUnitsChoice const UNITS_DEGREE_DAYS_FAHRENHEIT;
	static BACnetEngUnitsChoice const UNITS_DELTA_DEGREES_FAHRENHEIT;
	static BACnetEngUnitsChoice const UNITS_DELTA_DEGREES_KELVIN;
	    /* Time */
	static BACnetEngUnitsChoice const UNITS_YEARS;
	static BACnetEngUnitsChoice const UNITS_MONTHS;
	static BACnetEngUnitsChoice const UNITS_WEEKS;
	static BACnetEngUnitsChoice const UNITS_DAYS;
	static BACnetEngUnitsChoice const UNITS_HOURS;
	static BACnetEngUnitsChoice const UNITS_MINUTES;
	static BACnetEngUnitsChoice const UNITS_SECONDS;
	static BACnetEngUnitsChoice const UNITS_HUNDREDTHS_SECONDS;
	static BACnetEngUnitsChoice const UNITS_MILLISECONDS;
	    /* Torque */
	static BACnetEngUnitsChoice const UNITS_NEWTON_METERS;
	    /* Velocity */
	static BACnetEngUnitsChoice const UNITS_MILLIMETERS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_MILLIMETERS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_METERS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_METERS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_METERS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_KILOMETERS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_FEET_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_FEET_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_MILES_PER_HOUR;
	    /* Volume */
	static BACnetEngUnitsChoice const UNITS_CUBIC_FEET;
	static BACnetEngUnitsChoice const UNITS_CUBIC_METERS;
	static BACnetEngUnitsChoice const UNITS_IMPERIAL_GALLONS;
	static BACnetEngUnitsChoice const UNITS_MILLILITERS;
	static BACnetEngUnitsChoice const UNITS_LITERS;
	static BACnetEngUnitsChoice const UNITS_US_GALLONS;
	    /* Volumetric Flow */
	static BACnetEngUnitsChoice const UNITS_CUBIC_FEET_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_CUBIC_FEET_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_CUBIC_FEET_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_CUBIC_METERS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_CUBIC_METERS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_CUBIC_METERS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_IMPERIAL_GALLONS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_MILLILITERS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_LITERS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_LITERS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_LITERS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_US_GALLONS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_US_GALLONS_PER_HOUR;
	    /* Other */
	static BACnetEngUnitsChoice const UNITS_DEGREES_ANGULAR;
	static BACnetEngUnitsChoice const UNITS_DEGREES_CELSIUS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_DEGREES_CELSIUS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_DEGREES_FAHRENHEIT_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_DEGREES_FAHRENHEIT_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_JOULE_SECONDS;
	static BACnetEngUnitsChoice const UNITS_KILOGRAMS_PER_CUBIC_METER;
	static BACnetEngUnitsChoice const UNITS_KW_HOURS_PER_SQUARE_METER;
	static BACnetEngUnitsChoice const UNITS_KW_HOURS_PER_SQUARE_FOOT;
	static BACnetEngUnitsChoice const UNITS_MEGAJOULES_PER_SQUARE_METER;
	static BACnetEngUnitsChoice const UNITS_MEGAJOULES_PER_SQUARE_FOOT;
	static BACnetEngUnitsChoice const UNITS_NO_UNITS;
	static BACnetEngUnitsChoice const UNITS_NEWTON_SECONDS;
	static BACnetEngUnitsChoice const UNITS_NEWTONS_PER_METER;
	static BACnetEngUnitsChoice const UNITS_PARTS_PER_MILLION;
	static BACnetEngUnitsChoice const UNITS_PARTS_PER_BILLION;
	static BACnetEngUnitsChoice const UNITS_PERCENT;
	static BACnetEngUnitsChoice const UNITS_PERCENT_OBSCURATION_PER_FOOT;
	static BACnetEngUnitsChoice const UNITS_PERCENT_OBSCURATION_PER_METER;
	static BACnetEngUnitsChoice const UNITS_PERCENT_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_PSI_PER_DEGREE_FAHRENHEIT;
	static BACnetEngUnitsChoice const UNITS_RADIANS;
	static BACnetEngUnitsChoice const UNITS_RADIANS_PER_SECOND;
	static BACnetEngUnitsChoice const UNITS_REVOLUTIONS_PER_MINUTE;
	static BACnetEngUnitsChoice const UNITS_SQUARE_METERS_PER_NEWTON;
	static BACnetEngUnitsChoice const UNITS_WATTS_PER_METER_PER_DEGREE_KELVIN;
	static BACnetEngUnitsChoice const UNITS_WATTS_PER_SQUARE_METER_DEGREE_KELVIN;
	static BACnetEngUnitsChoice const UNITS_PER_MILLE;
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_GRAM;
	static BACnetEngUnitsChoice const UNITS_KILOGRAMS_PER_KILOGRAM;
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_KILOGRAM;
	static BACnetEngUnitsChoice const UNITS_MILLIGRAMS_PER_GRAM;
	static BACnetEngUnitsChoice const UNITS_MILLIGRAMS_PER_KILOGRAM;
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_MILLILITER;
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_LITER;
	static BACnetEngUnitsChoice const UNITS_MILLIGRAMS_PER_LITER;
	static BACnetEngUnitsChoice const UNITS_MICROGRAMS_PER_LITER;
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_CUBIC_METER;
	static BACnetEngUnitsChoice const UNITS_MILLIGRAMS_PER_CUBIC_METER;
	static BACnetEngUnitsChoice const UNITS_MICROGRAMS_PER_CUBIC_METER;
	static BACnetEngUnitsChoice const UNITS_NANOGRAMS_PER_CUBIC_METER;
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_CUBIC_CENTIMETER;
	static BACnetEngUnitsChoice const UNITS_BECQUERELS;
	static BACnetEngUnitsChoice const UNITS_MEGABECQUERELS;
	static BACnetEngUnitsChoice const UNITS_GRAY;
	static BACnetEngUnitsChoice const UNITS_MILLIGRAY;
	static BACnetEngUnitsChoice const UNITS_MICROGRAY;
	static BACnetEngUnitsChoice const UNITS_SIEVERTS;
	static BACnetEngUnitsChoice const UNITS_MILLISIEVERTS;
	static BACnetEngUnitsChoice const UNITS_MICROSIEVERTS;
	static BACnetEngUnitsChoice const UNITS_MICROSIEVERTS_PER_HOUR;
	static BACnetEngUnitsChoice const UNITS_DECIBELS_A;
	static BACnetEngUnitsChoice const UNITS_NEPHELOMETRIC_TURBIDITY_UNIT;
	static BACnetEngUnitsChoice const UNITS_PH;
	static BACnetEngUnitsChoice const UNITS_GRAMS_PER_SQUARE_METER;
	static BACnetEngUnitsChoice const UNITS_MINUTES_PER_DEGREE_KELVIN;

	/**
	 * From Clause 21 BACnetEngineeringUnits ::= ENUMERATED
	 * Enumerated values 0-255 are reserved for definition by ASHRAE.
	 * Enumerated values -- 256-65535 may be used by others subject to the procedures
	 * and constraints described in Clause 23.
	 *
	 * */


	BACnetEngUnitsChoice const &getEnumByValue(uint32_t enumValue) const;

};

#endif /* BACNETAPP_SRC_BACNETENUMENGUNITS_H_ */
