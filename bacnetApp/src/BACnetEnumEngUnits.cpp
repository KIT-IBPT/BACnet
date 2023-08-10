/*
 * BACnetEnumEngUnits.cpp
 *
 *  Created on: Jul 11, 2018
 *      Author: 8w4
 */

#include <BACnetEnumEngUnits.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

BACnetEngUnitsChoice::BACnetEngUnitsChoice(uint16_t const enumValue, string const name)
: BACnetEnumSingle::BACnetEnumSingle(enumValue, name)
{

	if(enumValue > MAX_ENGUNITS_CHOICE) {
		stringstream ss;

		ss << "\tError: BACnetVarFuncChoice::BACnetVarFuncChoice(uint8_t const enumValue, string const name):"
				" The valid range for a BACnet Binary Choice is 0-" << MAX_ENGUNITS_CHOICE << endl;
		throw std::invalid_argument(ss.str());
	}

}

BACnetEngUnitsChoice::~BACnetEngUnitsChoice() {
	// TODO Auto-generated destructor stub
}

BACnetEnumEngUnits BACnetEnumEngUnits::EnumEngUnits;

/* Acceleration */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_METERS_PER_SECOND_PER_SECOND = BACnetEngUnitsChoice(166, "UNITS_METERS_PER_SECOND_PER_SECOND");
/* Area */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SQUARE_METERS = BACnetEngUnitsChoice(0, "UNITS_SQUARE_METERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SQUARE_CENTIMETERS = BACnetEngUnitsChoice(116, "UNITS_SQUARE_CENTIMETERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SQUARE_FEET = BACnetEngUnitsChoice(1, "UNITS_SQUARE_FEET");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SQUARE_INCHES = BACnetEngUnitsChoice(115, "UNITS_SQUARE_INCHES");
/* Currency */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY1 = BACnetEngUnitsChoice(105, "UNITS_CURRENCY1");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY2 = BACnetEngUnitsChoice(106, "UNITS_CURRENCY2");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY3 = BACnetEngUnitsChoice(107, "UNITS_CURRENCY3");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY4 = BACnetEngUnitsChoice(108, "UNITS_CURRENCY4");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY5 = BACnetEngUnitsChoice(109, "UNITS_CURRENCY5");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY6 = BACnetEngUnitsChoice(110, "UNITS_CURRENCY6");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY7 = BACnetEngUnitsChoice(111, "UNITS_CURRENCY7");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY8 = BACnetEngUnitsChoice(112, "UNITS_CURRENCY8");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY9 = BACnetEngUnitsChoice(113, "UNITS_CURRENCY9");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CURRENCY10 = BACnetEngUnitsChoice(114, "UNITS_CURRENCY10");
/* Electrical */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIAMPERES = BACnetEngUnitsChoice(2, "UNITS_MILLIAMPERES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_AMPERES = BACnetEngUnitsChoice(3, "UNITS_AMPERES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_AMPERES_PER_METER = BACnetEngUnitsChoice(167, "UNITS_AMPERES_PER_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_AMPERES_PER_SQUARE_METER = BACnetEngUnitsChoice(168, "UNITS_AMPERES_PER_SQUARE_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_AMPERE_SQUARE_METERS = BACnetEngUnitsChoice(169, "UNITS_AMPERE_SQUARE_METERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DECIBELS = BACnetEngUnitsChoice(199, "UNITS_DECIBELS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DECIBELS_MILLIVOLT = BACnetEngUnitsChoice(200, "UNITS_DECIBELS_MILLIVOLT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DECIBELS_VOLT = BACnetEngUnitsChoice(201, "UNITS_DECIBELS_VOLT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_FARADS = BACnetEngUnitsChoice(170, "UNITS_FARADS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_HENRYS = BACnetEngUnitsChoice(171, "UNITS_HENRYS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_OHMS = BACnetEngUnitsChoice(4, "UNITS_OHMS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_OHM_METERS = BACnetEngUnitsChoice(172, "UNITS_OHM_METERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIOHMS = BACnetEngUnitsChoice(145, "UNITS_MILLIOHMS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOHMS = BACnetEngUnitsChoice(122, "UNITS_KILOHMS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGOHMS = BACnetEngUnitsChoice(123, "UNITS_MEGOHMS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MICROSIEMENS = BACnetEngUnitsChoice(190, "UNITS_MICROSIEMENS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLISIEMENS = BACnetEngUnitsChoice(202, "UNITS_MILLISIEMENS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SIEMENS = BACnetEngUnitsChoice(173, "UNITS_SIEMENS");        /* 1 mho equals 1 siemens */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SIEMENS_PER_METER = BACnetEngUnitsChoice(174, "UNITS_SIEMENS_PER_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_TESLAS = BACnetEngUnitsChoice(175, "UNITS_TESLAS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_VOLTS = BACnetEngUnitsChoice(5, "UNITS_VOLTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIVOLTS = BACnetEngUnitsChoice(124, "UNITS_MILLIVOLTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOVOLTS = BACnetEngUnitsChoice(6, "UNITS_KILOVOLTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAVOLTS = BACnetEngUnitsChoice(7, "UNITS_MEGAVOLTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_VOLT_AMPERES = BACnetEngUnitsChoice(8, "UNITS_VOLT_AMPERES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOVOLT_AMPERES = BACnetEngUnitsChoice(9, "UNITS_KILOVOLT_AMPERES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAVOLT_AMPERES = BACnetEngUnitsChoice(10, "UNITS_MEGAVOLT_AMPERES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_VOLT_AMPERES_REACTIVE = BACnetEngUnitsChoice(11, "UNITS_VOLT_AMPERES_REACTIVE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOVOLT_AMPERES_REACTIVE = BACnetEngUnitsChoice(12, "UNITS_KILOVOLT_AMPERES_REACTIVE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAVOLT_AMPERES_REACTIVE = BACnetEngUnitsChoice(13, "UNITS_MEGAVOLT_AMPERES_REACTIVE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_VOLTS_PER_DEGREE_KELVIN = BACnetEngUnitsChoice(176, "UNITS_VOLTS_PER_DEGREE_KELVIN");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_VOLTS_PER_METER = BACnetEngUnitsChoice(177, "UNITS_VOLTS_PER_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_PHASE = BACnetEngUnitsChoice(14, "UNITS_DEGREES_PHASE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_POWER_FACTOR = BACnetEngUnitsChoice(15, "UNITS_POWER_FACTOR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WEBERS = BACnetEngUnitsChoice(178, "UNITS_WEBERS");
/* Energy */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_JOULES = BACnetEngUnitsChoice(16, "UNITS_JOULES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOJOULES = BACnetEngUnitsChoice(17, "UNITS_KILOJOULES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOJOULES_PER_KILOGRAM = BACnetEngUnitsChoice(125, "UNITS_KILOJOULES_PER_KILOGRAM");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAJOULES = BACnetEngUnitsChoice(126, "UNITS_MEGAJOULES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WATT_HOURS = BACnetEngUnitsChoice(18, "UNITS_WATT_HOURS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOWATT_HOURS = BACnetEngUnitsChoice(19, "UNITS_KILOWATT_HOURS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAWATT_HOURS = BACnetEngUnitsChoice(146, "UNITS_MEGAWATT_HOURS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WATT_HOURS_REACTIVE = BACnetEngUnitsChoice(203, "UNITS_WATT_HOURS_REACTIVE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOWATT_HOURS_REACTIVE = BACnetEngUnitsChoice(204, "UNITS_KILOWATT_HOURS_REACTIVE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAWATT_HOURS_REACTIVE = BACnetEngUnitsChoice(205, "UNITS_MEGAWATT_HOURS_REACTIVE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_BTUS = BACnetEngUnitsChoice(20, "UNITS_BTUS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILO_BTUS = BACnetEngUnitsChoice(147, "UNITS_KILO_BTUS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGA_BTUS = BACnetEngUnitsChoice(148, "UNITS_MEGA_BTUS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_THERMS = BACnetEngUnitsChoice(21, "UNITS_THERMS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_TON_HOURS = BACnetEngUnitsChoice(22, "UNITS_TON_HOURS");
/* Enthalpy */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_JOULES_PER_KILOGRAM_DRY_AIR = BACnetEngUnitsChoice(23, "UNITS_JOULES_PER_KILOGRAM_DRY_AIR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOJOULES_PER_KILOGRAM_DRY_AIR = BACnetEngUnitsChoice(149, "UNITS_KILOJOULES_PER_KILOGRAM_DRY_AIR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAJOULES_PER_KILOGRAM_DRY_AIR = BACnetEngUnitsChoice(150, "UNITS_MEGAJOULES_PER_KILOGRAM_DRY_AIR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_BTUS_PER_POUND_DRY_AIR = BACnetEngUnitsChoice(24, "UNITS_BTUS_PER_POUND_DRY_AIR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_BTUS_PER_POUND = BACnetEngUnitsChoice(117, "UNITS_BTUS_PER_POUND");
/* Entropy */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_JOULES_PER_DEGREE_KELVIN = BACnetEngUnitsChoice(127, "UNITS_JOULES_PER_DEGREE_KELVIN");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOJOULES_PER_DEGREE_KELVIN = BACnetEngUnitsChoice(151, "UNITS_KILOJOULES_PER_DEGREE_KELVIN");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAJOULES_PER_DEGREE_KELVIN = BACnetEngUnitsChoice(152, "UNITS_MEGAJOULES_PER_DEGREE_KELVIN");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_JOULES_PER_KILOGRAM_DEGREE_KELVIN = BACnetEngUnitsChoice(128, "UNITS_JOULES_PER_KILOGRAM_DEGREE_KELVIN");
/* Force */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_NEWTON = BACnetEngUnitsChoice(153, "UNITS_NEWTON");
/* Frequency */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CYCLES_PER_HOUR = BACnetEngUnitsChoice(25, "UNITS_CYCLES_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CYCLES_PER_MINUTE = BACnetEngUnitsChoice(26, "UNITS_CYCLES_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_HERTZ = BACnetEngUnitsChoice(27, "UNITS_HERTZ");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOHERTZ = BACnetEngUnitsChoice(129, "UNITS_KILOHERTZ");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAHERTZ = BACnetEngUnitsChoice(130, "UNITS_MEGAHERTZ");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PER_HOUR = BACnetEngUnitsChoice(131, "UNITS_PER_HOUR");
/* Humidity */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_OF_WATER_PER_KILOGRAM_DRY_AIR = BACnetEngUnitsChoice(28, "UNITS_GRAMS_OF_WATER_PER_KILOGRAM_DRY_AIR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PERCENT_RELATIVE_HUMIDITY = BACnetEngUnitsChoice(29, "UNITS_PERCENT_RELATIVE_HUMIDITY");
/* Length */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MICROMETERS = BACnetEngUnitsChoice(194, "UNITS_MICROMETERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIMETERS = BACnetEngUnitsChoice(30, "UNITS_MILLIMETERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CENTIMETERS = BACnetEngUnitsChoice(118, "UNITS_CENTIMETERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOMETERS = BACnetEngUnitsChoice(193, "UNITS_KILOMETERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_METERS = BACnetEngUnitsChoice(31, "UNITS_METERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_INCHES = BACnetEngUnitsChoice(32, "UNITS_INCHES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_FEET = BACnetEngUnitsChoice(33, "UNITS_FEET");
/* Light */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CANDELAS = BACnetEngUnitsChoice(179, "UNITS_CANDELAS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CANDELAS_PER_SQUARE_METER = BACnetEngUnitsChoice(180, "UNITS_CANDELAS_PER_SQUARE_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WATTS_PER_SQUARE_FOOT = BACnetEngUnitsChoice(34, "UNITS_WATTS_PER_SQUARE_FOOT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WATTS_PER_SQUARE_METER = BACnetEngUnitsChoice(35, "UNITS_WATTS_PER_SQUARE_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_LUMENS = BACnetEngUnitsChoice(36, "UNITS_LUMENS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_LUXES = BACnetEngUnitsChoice(37, "UNITS_LUXES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_FOOT_CANDLES = BACnetEngUnitsChoice(38, "UNITS_FOOT_CANDLES");
/* Mass */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIGRAMS = BACnetEngUnitsChoice(196, "UNITS_MILLIGRAMS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS = BACnetEngUnitsChoice(195, "UNITS_GRAMS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOGRAMS = BACnetEngUnitsChoice(39, "UNITS_KILOGRAMS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_POUNDS_MASS = BACnetEngUnitsChoice(40, "UNITS_POUNDS_MASS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_TONS = BACnetEngUnitsChoice(41, "UNITS_TONS");
/* Mass Flow */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_SECOND = BACnetEngUnitsChoice(154, "UNITS_GRAMS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_MINUTE = BACnetEngUnitsChoice(155, "UNITS_GRAMS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOGRAMS_PER_SECOND = BACnetEngUnitsChoice(42, "UNITS_KILOGRAMS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOGRAMS_PER_MINUTE = BACnetEngUnitsChoice(43, "UNITS_KILOGRAMS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOGRAMS_PER_HOUR = BACnetEngUnitsChoice(44, "UNITS_KILOGRAMS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_POUNDS_MASS_PER_SECOND = BACnetEngUnitsChoice(119, "UNITS_POUNDS_MASS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_POUNDS_MASS_PER_MINUTE = BACnetEngUnitsChoice(45, "UNITS_POUNDS_MASS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_POUNDS_MASS_PER_HOUR = BACnetEngUnitsChoice(46, "UNITS_POUNDS_MASS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_TONS_PER_HOUR = BACnetEngUnitsChoice(156, "UNITS_TONS_PER_HOUR");
/* Power */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIWATTS = BACnetEngUnitsChoice(132, "UNITS_MILLIWATTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WATTS = BACnetEngUnitsChoice(47, "UNITS_WATTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOWATTS = BACnetEngUnitsChoice(48, "UNITS_KILOWATTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAWATTS = BACnetEngUnitsChoice(49, "UNITS_MEGAWATTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_BTUS_PER_HOUR = BACnetEngUnitsChoice(50, "UNITS_BTUS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILO_BTUS_PER_HOUR = BACnetEngUnitsChoice(157, "UNITS_KILO_BTUS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_HORSEPOWER = BACnetEngUnitsChoice(51, "UNITS_HORSEPOWER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_TONS_REFRIGERATION = BACnetEngUnitsChoice(52, "UNITS_TONS_REFRIGERATION");
/* Pressure */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PASCALS = BACnetEngUnitsChoice(53, "UNITS_PASCALS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_HECTOPASCALS = BACnetEngUnitsChoice(133, "UNITS_HECTOPASCALS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOPASCALS = BACnetEngUnitsChoice(54, "UNITS_KILOPASCALS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIBARS = BACnetEngUnitsChoice(134, "UNITS_MILLIBARS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_BARS = BACnetEngUnitsChoice(55, "UNITS_BARS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_POUNDS_FORCE_PER_SQUARE_INCH = BACnetEngUnitsChoice(56, "UNITS_POUNDS_FORCE_PER_SQUARE_INCH");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIMETERS_OF_WATER = BACnetEngUnitsChoice(206, "UNITS_MILLIMETERS_OF_WATER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CENTIMETERS_OF_WATER = BACnetEngUnitsChoice(57, "UNITS_CENTIMETERS_OF_WATER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_INCHES_OF_WATER = BACnetEngUnitsChoice(58, "UNITS_INCHES_OF_WATER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIMETERS_OF_MERCURY = BACnetEngUnitsChoice(59, "UNITS_MILLIMETERS_OF_MERCURY");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CENTIMETERS_OF_MERCURY = BACnetEngUnitsChoice(60, "UNITS_CENTIMETERS_OF_MERCURY");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_INCHES_OF_MERCURY = BACnetEngUnitsChoice(61, "UNITS_INCHES_OF_MERCURY");
/* Temperature */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_CELSIUS = BACnetEngUnitsChoice(62, "UNITS_DEGREES_CELSIUS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_KELVIN = BACnetEngUnitsChoice(63, "UNITS_DEGREES_KELVIN");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_KELVIN_PER_HOUR = BACnetEngUnitsChoice(181, "UNITS_DEGREES_KELVIN_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_KELVIN_PER_MINUTE = BACnetEngUnitsChoice(182, "UNITS_DEGREES_KELVIN_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_FAHRENHEIT = BACnetEngUnitsChoice(64, "UNITS_DEGREES_FAHRENHEIT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREE_DAYS_CELSIUS = BACnetEngUnitsChoice(65, "UNITS_DEGREE_DAYS_CELSIUS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREE_DAYS_FAHRENHEIT = BACnetEngUnitsChoice(66, "UNITS_DEGREE_DAYS_FAHRENHEIT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DELTA_DEGREES_FAHRENHEIT = BACnetEngUnitsChoice(120, "UNITS_DELTA_DEGREES_FAHRENHEIT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DELTA_DEGREES_KELVIN = BACnetEngUnitsChoice(121, "UNITS_DELTA_DEGREES_KELVIN");
/* Time */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_YEARS = BACnetEngUnitsChoice(67, "UNITS_YEARS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MONTHS = BACnetEngUnitsChoice(68, "UNITS_MONTHS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WEEKS = BACnetEngUnitsChoice(69, "UNITS_WEEKS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DAYS = BACnetEngUnitsChoice(70, "UNITS_DAYS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_HOURS = BACnetEngUnitsChoice(71, "UNITS_HOURS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MINUTES = BACnetEngUnitsChoice(72, "UNITS_MINUTES");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SECONDS = BACnetEngUnitsChoice(73, "UNITS_SECONDS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_HUNDREDTHS_SECONDS = BACnetEngUnitsChoice(158, "UNITS_HUNDREDTHS_SECONDS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLISECONDS = BACnetEngUnitsChoice(159, "UNITS_MILLISECONDS");
/* Torque */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_NEWTON_METERS = BACnetEngUnitsChoice(160, "UNITS_NEWTON_METERS");
/* Velocity */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIMETERS_PER_SECOND = BACnetEngUnitsChoice(161, "UNITS_MILLIMETERS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIMETERS_PER_MINUTE = BACnetEngUnitsChoice(162, "UNITS_MILLIMETERS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_METERS_PER_SECOND = BACnetEngUnitsChoice(74, "UNITS_METERS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_METERS_PER_MINUTE = BACnetEngUnitsChoice(163, "UNITS_METERS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_METERS_PER_HOUR = BACnetEngUnitsChoice(164, "UNITS_METERS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOMETERS_PER_HOUR = BACnetEngUnitsChoice(75, "UNITS_KILOMETERS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_FEET_PER_SECOND = BACnetEngUnitsChoice(76, "UNITS_FEET_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_FEET_PER_MINUTE = BACnetEngUnitsChoice(77, "UNITS_FEET_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILES_PER_HOUR = BACnetEngUnitsChoice(78, "UNITS_MILES_PER_HOUR");
/* Volume */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CUBIC_FEET = BACnetEngUnitsChoice(79, "UNITS_CUBIC_FEET");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CUBIC_METERS = BACnetEngUnitsChoice(80, "UNITS_CUBIC_METERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_IMPERIAL_GALLONS = BACnetEngUnitsChoice(81, "UNITS_IMPERIAL_GALLONS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLILITERS = BACnetEngUnitsChoice(197, "UNITS_MILLILITERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_LITERS = BACnetEngUnitsChoice(82, "UNITS_LITERS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_US_GALLONS = BACnetEngUnitsChoice(83, "UNITS_US_GALLONS");
/* Volumetric Flow */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CUBIC_FEET_PER_SECOND = BACnetEngUnitsChoice(142, "UNITS_CUBIC_FEET_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CUBIC_FEET_PER_MINUTE = BACnetEngUnitsChoice(84, "UNITS_CUBIC_FEET_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CUBIC_FEET_PER_HOUR = BACnetEngUnitsChoice(191, "UNITS_CUBIC_FEET_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CUBIC_METERS_PER_SECOND = BACnetEngUnitsChoice(85, "UNITS_CUBIC_METERS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CUBIC_METERS_PER_MINUTE = BACnetEngUnitsChoice(165, "UNITS_CUBIC_METERS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_CUBIC_METERS_PER_HOUR = BACnetEngUnitsChoice(135, "UNITS_CUBIC_METERS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_IMPERIAL_GALLONS_PER_MINUTE = BACnetEngUnitsChoice(86, "UNITS_IMPERIAL_GALLONS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLILITERS_PER_SECOND = BACnetEngUnitsChoice(198, "UNITS_MILLILITERS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_LITERS_PER_SECOND = BACnetEngUnitsChoice(87, "UNITS_LITERS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_LITERS_PER_MINUTE = BACnetEngUnitsChoice(88, "UNITS_LITERS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_LITERS_PER_HOUR = BACnetEngUnitsChoice(136, "UNITS_LITERS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_US_GALLONS_PER_MINUTE = BACnetEngUnitsChoice(89, "UNITS_US_GALLONS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_US_GALLONS_PER_HOUR = BACnetEngUnitsChoice(192, "UNITS_US_GALLONS_PER_HOUR");
/* Other */
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_ANGULAR = BACnetEngUnitsChoice(90, "UNITS_DEGREES_ANGULAR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_CELSIUS_PER_HOUR = BACnetEngUnitsChoice(91, "UNITS_DEGREES_CELSIUS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_CELSIUS_PER_MINUTE = BACnetEngUnitsChoice(92, "UNITS_DEGREES_CELSIUS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_FAHRENHEIT_PER_HOUR = BACnetEngUnitsChoice(93, "UNITS_DEGREES_FAHRENHEIT_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DEGREES_FAHRENHEIT_PER_MINUTE = BACnetEngUnitsChoice(94, "UNITS_DEGREES_FAHRENHEIT_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_JOULE_SECONDS = BACnetEngUnitsChoice(183, "UNITS_JOULE_SECONDS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOGRAMS_PER_CUBIC_METER = BACnetEngUnitsChoice(186, "UNITS_KILOGRAMS_PER_CUBIC_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KW_HOURS_PER_SQUARE_METER = BACnetEngUnitsChoice(137, "UNITS_KW_HOURS_PER_SQUARE_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KW_HOURS_PER_SQUARE_FOOT = BACnetEngUnitsChoice(138, "UNITS_KW_HOURS_PER_SQUARE_FOOT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAJOULES_PER_SQUARE_METER = BACnetEngUnitsChoice(139, "UNITS_MEGAJOULES_PER_SQUARE_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGAJOULES_PER_SQUARE_FOOT = BACnetEngUnitsChoice(140, "UNITS_MEGAJOULES_PER_SQUARE_FOOT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_NO_UNITS = BACnetEngUnitsChoice(95, "UNITS_NO_UNITS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_NEWTON_SECONDS = BACnetEngUnitsChoice(187, "UNITS_NEWTON_SECONDS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_NEWTONS_PER_METER = BACnetEngUnitsChoice(188, "UNITS_NEWTONS_PER_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PARTS_PER_MILLION = BACnetEngUnitsChoice(96, "UNITS_PARTS_PER_MILLION");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PARTS_PER_BILLION = BACnetEngUnitsChoice(97, "UNITS_PARTS_PER_BILLION");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PERCENT = BACnetEngUnitsChoice(98, "UNITS_PERCENT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PERCENT_OBSCURATION_PER_FOOT = BACnetEngUnitsChoice(143, "UNITS_PERCENT_OBSCURATION_PER_FOOT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PERCENT_OBSCURATION_PER_METER = BACnetEngUnitsChoice(144, "UNITS_PERCENT_OBSCURATION_PER_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PERCENT_PER_SECOND = BACnetEngUnitsChoice(99, "UNITS_PERCENT_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PER_MINUTE = BACnetEngUnitsChoice(100, "UNITS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PER_SECOND = BACnetEngUnitsChoice(101, "UNITS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PSI_PER_DEGREE_FAHRENHEIT = BACnetEngUnitsChoice(102, "UNITS_PSI_PER_DEGREE_FAHRENHEIT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_RADIANS = BACnetEngUnitsChoice(103, "UNITS_RADIANS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_RADIANS_PER_SECOND = BACnetEngUnitsChoice(184, "UNITS_RADIANS_PER_SECOND");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_REVOLUTIONS_PER_MINUTE = BACnetEngUnitsChoice(104, "UNITS_REVOLUTIONS_PER_MINUTE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SQUARE_METERS_PER_NEWTON = BACnetEngUnitsChoice(185, "UNITS_SQUARE_METERS_PER_NEWTON");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WATTS_PER_METER_PER_DEGREE_KELVIN = BACnetEngUnitsChoice(189, "UNITS_WATTS_PER_METER_PER_DEGREE_KELVIN");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_WATTS_PER_SQUARE_METER_DEGREE_KELVIN = BACnetEngUnitsChoice(141, "UNITS_WATTS_PER_SQUARE_METER_DEGREE_KELVIN");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PER_MILLE = BACnetEngUnitsChoice(207, "UNITS_PER_MILLE");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_GRAM = BACnetEngUnitsChoice(208, "UNITS_GRAMS_PER_GRAM");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_KILOGRAMS_PER_KILOGRAM = BACnetEngUnitsChoice(209, "UNITS_KILOGRAMS_PER_KILOGRAM");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_KILOGRAM = BACnetEngUnitsChoice(210, "UNITS_GRAMS_PER_KILOGRAM");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIGRAMS_PER_GRAM = BACnetEngUnitsChoice(211, "UNITS_MILLIGRAMS_PER_GRAM");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIGRAMS_PER_KILOGRAM = BACnetEngUnitsChoice(212, "UNITS_MILLIGRAMS_PER_KILOGRAM");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_MILLILITER = BACnetEngUnitsChoice(213, "UNITS_GRAMS_PER_MILLILITER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_LITER = BACnetEngUnitsChoice(214, "UNITS_GRAMS_PER_LITER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIGRAMS_PER_LITER = BACnetEngUnitsChoice(215, "UNITS_MILLIGRAMS_PER_LITER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MICROGRAMS_PER_LITER = BACnetEngUnitsChoice(216, "UNITS_MICROGRAMS_PER_LITER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_CUBIC_METER = BACnetEngUnitsChoice(217, "UNITS_GRAMS_PER_CUBIC_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIGRAMS_PER_CUBIC_METER = BACnetEngUnitsChoice(218, "UNITS_MILLIGRAMS_PER_CUBIC_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MICROGRAMS_PER_CUBIC_METER = BACnetEngUnitsChoice(219, "UNITS_MICROGRAMS_PER_CUBIC_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_NANOGRAMS_PER_CUBIC_METER = BACnetEngUnitsChoice(220, "UNITS_NANOGRAMS_PER_CUBIC_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_CUBIC_CENTIMETER = BACnetEngUnitsChoice(221, "UNITS_GRAMS_PER_CUBIC_CENTIMETER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_BECQUERELS = BACnetEngUnitsChoice(222, "UNITS_BECQUERELS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MEGABECQUERELS = BACnetEngUnitsChoice(224, "UNITS_MEGABECQUERELS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAY = BACnetEngUnitsChoice(225, "UNITS_GRAY");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLIGRAY = BACnetEngUnitsChoice(226, "UNITS_MILLIGRAY");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MICROGRAY = BACnetEngUnitsChoice(227, "UNITS_MICROGRAY");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_SIEVERTS = BACnetEngUnitsChoice(228, "UNITS_SIEVERTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MILLISIEVERTS = BACnetEngUnitsChoice(229, "UNITS_MILLISIEVERTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MICROSIEVERTS = BACnetEngUnitsChoice(230, "UNITS_MICROSIEVERTS");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MICROSIEVERTS_PER_HOUR = BACnetEngUnitsChoice(231, "UNITS_MICROSIEVERTS_PER_HOUR");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_DECIBELS_A = BACnetEngUnitsChoice(232, "UNITS_DECIBELS_A");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_NEPHELOMETRIC_TURBIDITY_UNIT = BACnetEngUnitsChoice(233, "UNITS_NEPHELOMETRIC_TURBIDITY_UNIT");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PH = BACnetEngUnitsChoice(234, "UNITS_PH");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_GRAMS_PER_SQUARE_METER = BACnetEngUnitsChoice(235, "UNITS_GRAMS_PER_SQUARE_METER");
BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_MINUTES_PER_DEGREE_KELVIN = BACnetEngUnitsChoice(236, "UNITS_MINUTES_PER_DEGREE_KELVIN");
/* Enumerated values 0-255 are reserved for definition by ASHRAE. */
/* Enumerated values 256-65535 may be used by others subject to */
/* the procedures and constraints described in Clause 23. */
/* The last enumeration used in this version is 236. */
//MAX_UNITS = 237,
/* do the proprietary range inside of enum so that
   compilers will allocate adequate sized datatype for enum
   which is used to store decoding */
//BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PROPRIETARY_RANGE_MIN = BACnetEngUnitsChoice(256, "UNITS_PROPRIETARY_RANGE_MIN");
//BACnetEngUnitsChoice const BACnetEnumEngUnits::UNITS_PROPRIETARY_RANGE_MAX = 65535
///

std::map<uint16_t, BACnetEngUnitsChoice const *> BACnetEnumEngUnits::objectMap = BACnetEnumEngUnits::init_map();


std::map<uint16_t, BACnetEngUnitsChoice const *> BACnetEnumEngUnits::init_map() {

	std::map<uint16_t, BACnetEngUnitsChoice const *> lmap;

	/* Acceleration */
	lmap[UNITS_METERS_PER_SECOND_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_METERS_PER_SECOND_PER_SECOND;
	/* Area */
	lmap[UNITS_SQUARE_METERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SQUARE_METERS;
	lmap[UNITS_SQUARE_CENTIMETERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SQUARE_CENTIMETERS;
	lmap[UNITS_SQUARE_FEET.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SQUARE_FEET;
	lmap[UNITS_SQUARE_INCHES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SQUARE_INCHES;
	/* Currency */
	lmap[UNITS_CURRENCY1.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY1;
	lmap[UNITS_CURRENCY2.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY2;
	lmap[UNITS_CURRENCY3.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY3;
	lmap[UNITS_CURRENCY4.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY4;
	lmap[UNITS_CURRENCY5.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY5;
	lmap[UNITS_CURRENCY6.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY6;
	lmap[UNITS_CURRENCY7.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY7;
	lmap[UNITS_CURRENCY8.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY8;
	lmap[UNITS_CURRENCY9.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY9;
	lmap[UNITS_CURRENCY10.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CURRENCY10;
	/* Electrical */
	lmap[UNITS_MILLIAMPERES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIAMPERES;
	lmap[UNITS_AMPERES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_AMPERES;
	lmap[UNITS_AMPERES_PER_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_AMPERES_PER_METER;
	lmap[UNITS_AMPERES_PER_SQUARE_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_AMPERES_PER_SQUARE_METER;
	lmap[UNITS_AMPERE_SQUARE_METERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_AMPERE_SQUARE_METERS;
	lmap[UNITS_DECIBELS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DECIBELS;
	lmap[UNITS_DECIBELS_MILLIVOLT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DECIBELS_MILLIVOLT;
	lmap[UNITS_DECIBELS_VOLT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DECIBELS_VOLT;
	lmap[UNITS_FARADS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_FARADS;
	lmap[UNITS_HENRYS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_HENRYS;
	lmap[UNITS_OHMS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_OHMS;
	lmap[UNITS_OHM_METERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_OHM_METERS;
	lmap[UNITS_MILLIOHMS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIOHMS;
	lmap[UNITS_KILOHMS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOHMS;
	lmap[UNITS_MEGOHMS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGOHMS;
	lmap[UNITS_MICROSIEMENS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MICROSIEMENS;
	lmap[UNITS_MILLISIEMENS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLISIEMENS;
	lmap[UNITS_SIEMENS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SIEMENS;        /* 1 mho equals 1 siemens */
	lmap[UNITS_SIEMENS_PER_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SIEMENS_PER_METER;
	lmap[UNITS_TESLAS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_TESLAS;
	lmap[UNITS_VOLTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_VOLTS;
	lmap[UNITS_MILLIVOLTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIVOLTS;
	lmap[UNITS_KILOVOLTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOVOLTS;
	lmap[UNITS_MEGAVOLTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAVOLTS;
	lmap[UNITS_VOLT_AMPERES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_VOLT_AMPERES;
	lmap[UNITS_KILOVOLT_AMPERES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOVOLT_AMPERES;
	lmap[UNITS_MEGAVOLT_AMPERES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAVOLT_AMPERES;
	lmap[UNITS_VOLT_AMPERES_REACTIVE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_VOLT_AMPERES_REACTIVE;
	lmap[UNITS_KILOVOLT_AMPERES_REACTIVE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOVOLT_AMPERES_REACTIVE;
	lmap[UNITS_MEGAVOLT_AMPERES_REACTIVE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAVOLT_AMPERES_REACTIVE;
	lmap[UNITS_VOLTS_PER_DEGREE_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_VOLTS_PER_DEGREE_KELVIN;
	lmap[UNITS_VOLTS_PER_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_VOLTS_PER_METER;
	lmap[UNITS_DEGREES_PHASE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_PHASE;
	lmap[UNITS_POWER_FACTOR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_POWER_FACTOR;
	lmap[UNITS_WEBERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WEBERS;
	/* Energy */
	lmap[UNITS_JOULES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_JOULES;
	lmap[UNITS_KILOJOULES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOJOULES;
	lmap[UNITS_KILOJOULES_PER_KILOGRAM.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOJOULES_PER_KILOGRAM;
	lmap[UNITS_MEGAJOULES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAJOULES;
	lmap[UNITS_WATT_HOURS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WATT_HOURS;
	lmap[UNITS_KILOWATT_HOURS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOWATT_HOURS;
	lmap[UNITS_MEGAWATT_HOURS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAWATT_HOURS;
	lmap[UNITS_WATT_HOURS_REACTIVE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WATT_HOURS_REACTIVE;
	lmap[UNITS_KILOWATT_HOURS_REACTIVE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOWATT_HOURS_REACTIVE;
	lmap[UNITS_MEGAWATT_HOURS_REACTIVE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAWATT_HOURS_REACTIVE;
	lmap[UNITS_BTUS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_BTUS;
	lmap[UNITS_KILO_BTUS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILO_BTUS;
	lmap[UNITS_MEGA_BTUS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGA_BTUS;
	lmap[UNITS_THERMS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_THERMS;
	lmap[UNITS_TON_HOURS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_TON_HOURS;
	/* Enthalpy */
	lmap[UNITS_JOULES_PER_KILOGRAM_DRY_AIR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_JOULES_PER_KILOGRAM_DRY_AIR;
	lmap[UNITS_KILOJOULES_PER_KILOGRAM_DRY_AIR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOJOULES_PER_KILOGRAM_DRY_AIR;
	lmap[UNITS_MEGAJOULES_PER_KILOGRAM_DRY_AIR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAJOULES_PER_KILOGRAM_DRY_AIR;
	lmap[UNITS_BTUS_PER_POUND_DRY_AIR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_BTUS_PER_POUND_DRY_AIR;
	lmap[UNITS_BTUS_PER_POUND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_BTUS_PER_POUND;
	/* Entropy */
	lmap[UNITS_JOULES_PER_DEGREE_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_JOULES_PER_DEGREE_KELVIN;
	lmap[UNITS_KILOJOULES_PER_DEGREE_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOJOULES_PER_DEGREE_KELVIN;
	lmap[UNITS_MEGAJOULES_PER_DEGREE_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAJOULES_PER_DEGREE_KELVIN;
	lmap[UNITS_JOULES_PER_KILOGRAM_DEGREE_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_JOULES_PER_KILOGRAM_DEGREE_KELVIN;
	/* Force */
	lmap[UNITS_NEWTON.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_NEWTON;
	/* Frequency */
	lmap[UNITS_CYCLES_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CYCLES_PER_HOUR;
	lmap[UNITS_CYCLES_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CYCLES_PER_MINUTE;
	lmap[UNITS_HERTZ.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_HERTZ;
	lmap[UNITS_KILOHERTZ.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOHERTZ;
	lmap[UNITS_MEGAHERTZ.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAHERTZ;
	lmap[UNITS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PER_HOUR;
	/* Humidity */
	lmap[UNITS_GRAMS_OF_WATER_PER_KILOGRAM_DRY_AIR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_OF_WATER_PER_KILOGRAM_DRY_AIR;
	lmap[UNITS_PERCENT_RELATIVE_HUMIDITY.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PERCENT_RELATIVE_HUMIDITY;
	/* Length */
	lmap[UNITS_MICROMETERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MICROMETERS;
	lmap[UNITS_MILLIMETERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIMETERS;
	lmap[UNITS_CENTIMETERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CENTIMETERS;
	lmap[UNITS_KILOMETERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOMETERS;
	lmap[UNITS_METERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_METERS;
	lmap[UNITS_INCHES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_INCHES;
	lmap[UNITS_FEET.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_FEET;
	/* Light */
	lmap[UNITS_CANDELAS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CANDELAS;
	lmap[UNITS_CANDELAS_PER_SQUARE_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CANDELAS_PER_SQUARE_METER;
	lmap[UNITS_WATTS_PER_SQUARE_FOOT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WATTS_PER_SQUARE_FOOT;
	lmap[UNITS_WATTS_PER_SQUARE_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WATTS_PER_SQUARE_METER;
	lmap[UNITS_LUMENS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_LUMENS;
	lmap[UNITS_LUXES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_LUXES;
	lmap[UNITS_FOOT_CANDLES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_FOOT_CANDLES;
	/* Mass */
	lmap[UNITS_MILLIGRAMS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIGRAMS;
	lmap[UNITS_GRAMS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS;
	lmap[UNITS_KILOGRAMS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOGRAMS;
	lmap[UNITS_POUNDS_MASS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_POUNDS_MASS;
	lmap[UNITS_TONS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_TONS;
	/* Mass Flow */
	lmap[UNITS_GRAMS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_SECOND;
	lmap[UNITS_GRAMS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_MINUTE;
	lmap[UNITS_KILOGRAMS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOGRAMS_PER_SECOND;
	lmap[UNITS_KILOGRAMS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOGRAMS_PER_MINUTE;
	lmap[UNITS_KILOGRAMS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOGRAMS_PER_HOUR;
	lmap[UNITS_POUNDS_MASS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_POUNDS_MASS_PER_SECOND;
	lmap[UNITS_POUNDS_MASS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_POUNDS_MASS_PER_MINUTE;
	lmap[UNITS_POUNDS_MASS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_POUNDS_MASS_PER_HOUR;
	lmap[UNITS_TONS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_TONS_PER_HOUR;
	/* Power */
	lmap[UNITS_MILLIWATTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIWATTS;
	lmap[UNITS_WATTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WATTS;
	lmap[UNITS_KILOWATTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOWATTS;
	lmap[UNITS_MEGAWATTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAWATTS;
	lmap[UNITS_BTUS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_BTUS_PER_HOUR;
	lmap[UNITS_KILO_BTUS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILO_BTUS_PER_HOUR;
	lmap[UNITS_HORSEPOWER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_HORSEPOWER;
	lmap[UNITS_TONS_REFRIGERATION.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_TONS_REFRIGERATION;
	/* Pressure */
	lmap[UNITS_PASCALS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PASCALS;
	lmap[UNITS_HECTOPASCALS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_HECTOPASCALS;
	lmap[UNITS_KILOPASCALS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOPASCALS;
	lmap[UNITS_MILLIBARS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIBARS;
	lmap[UNITS_BARS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_BARS;
	lmap[UNITS_POUNDS_FORCE_PER_SQUARE_INCH.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_POUNDS_FORCE_PER_SQUARE_INCH;
	lmap[UNITS_MILLIMETERS_OF_WATER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIMETERS_OF_WATER;
	lmap[UNITS_CENTIMETERS_OF_WATER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CENTIMETERS_OF_WATER;
	lmap[UNITS_INCHES_OF_WATER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_INCHES_OF_WATER;
	lmap[UNITS_MILLIMETERS_OF_MERCURY.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIMETERS_OF_MERCURY;
	lmap[UNITS_CENTIMETERS_OF_MERCURY.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CENTIMETERS_OF_MERCURY;
	lmap[UNITS_INCHES_OF_MERCURY.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_INCHES_OF_MERCURY;
	/* Temperature */
	lmap[UNITS_DEGREES_CELSIUS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_CELSIUS;
	lmap[UNITS_DEGREES_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_KELVIN;
	lmap[UNITS_DEGREES_KELVIN_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_KELVIN_PER_HOUR;
	lmap[UNITS_DEGREES_KELVIN_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_KELVIN_PER_MINUTE;
	lmap[UNITS_DEGREES_FAHRENHEIT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_FAHRENHEIT;
	lmap[UNITS_DEGREE_DAYS_CELSIUS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREE_DAYS_CELSIUS;
	lmap[UNITS_DEGREE_DAYS_FAHRENHEIT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREE_DAYS_FAHRENHEIT;
	lmap[UNITS_DELTA_DEGREES_FAHRENHEIT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DELTA_DEGREES_FAHRENHEIT;
	lmap[UNITS_DELTA_DEGREES_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DELTA_DEGREES_KELVIN;
	/* Time */
	lmap[UNITS_YEARS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_YEARS;
	lmap[UNITS_MONTHS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MONTHS;
	lmap[UNITS_WEEKS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WEEKS;
	lmap[UNITS_DAYS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DAYS;
	lmap[UNITS_HOURS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_HOURS;
	lmap[UNITS_MINUTES.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MINUTES;
	lmap[UNITS_SECONDS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SECONDS;
	lmap[UNITS_HUNDREDTHS_SECONDS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_HUNDREDTHS_SECONDS;
	lmap[UNITS_MILLISECONDS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLISECONDS;
	/* Torque */
	lmap[UNITS_NEWTON_METERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_NEWTON_METERS;
	/* Velocity */
	lmap[UNITS_MILLIMETERS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIMETERS_PER_SECOND;
	lmap[UNITS_MILLIMETERS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIMETERS_PER_MINUTE;
	lmap[UNITS_METERS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_METERS_PER_SECOND;
	lmap[UNITS_METERS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_METERS_PER_MINUTE;
	lmap[UNITS_METERS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_METERS_PER_HOUR;
	lmap[UNITS_KILOMETERS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOMETERS_PER_HOUR;
	lmap[UNITS_FEET_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_FEET_PER_SECOND;
	lmap[UNITS_FEET_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_FEET_PER_MINUTE;
	lmap[UNITS_MILES_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILES_PER_HOUR;
	/* Volume */
	lmap[UNITS_CUBIC_FEET.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CUBIC_FEET;
	lmap[UNITS_CUBIC_METERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CUBIC_METERS;
	lmap[UNITS_IMPERIAL_GALLONS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_IMPERIAL_GALLONS;
	lmap[UNITS_MILLILITERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLILITERS;
	lmap[UNITS_LITERS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_LITERS;
	lmap[UNITS_US_GALLONS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_US_GALLONS;
	/* Volumetric Flow */
	lmap[UNITS_CUBIC_FEET_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CUBIC_FEET_PER_SECOND;
	lmap[UNITS_CUBIC_FEET_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CUBIC_FEET_PER_MINUTE;
	lmap[UNITS_CUBIC_FEET_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CUBIC_FEET_PER_HOUR;
	lmap[UNITS_CUBIC_METERS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CUBIC_METERS_PER_SECOND;
	lmap[UNITS_CUBIC_METERS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CUBIC_METERS_PER_MINUTE;
	lmap[UNITS_CUBIC_METERS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_CUBIC_METERS_PER_HOUR;
	lmap[UNITS_IMPERIAL_GALLONS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_IMPERIAL_GALLONS_PER_MINUTE;
	lmap[UNITS_MILLILITERS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLILITERS_PER_SECOND;
	lmap[UNITS_LITERS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_LITERS_PER_SECOND;
	lmap[UNITS_LITERS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_LITERS_PER_MINUTE;
	lmap[UNITS_LITERS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_LITERS_PER_HOUR;
	lmap[UNITS_US_GALLONS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_US_GALLONS_PER_MINUTE;
	lmap[UNITS_US_GALLONS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_US_GALLONS_PER_HOUR;
	/* Other */
	lmap[UNITS_DEGREES_ANGULAR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_ANGULAR;
	lmap[UNITS_DEGREES_CELSIUS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_CELSIUS_PER_HOUR;
	lmap[UNITS_DEGREES_CELSIUS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_CELSIUS_PER_MINUTE;
	lmap[UNITS_DEGREES_FAHRENHEIT_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_FAHRENHEIT_PER_HOUR;
	lmap[UNITS_DEGREES_FAHRENHEIT_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DEGREES_FAHRENHEIT_PER_MINUTE;
	lmap[UNITS_JOULE_SECONDS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_JOULE_SECONDS;
	lmap[UNITS_KILOGRAMS_PER_CUBIC_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOGRAMS_PER_CUBIC_METER;
	lmap[UNITS_KW_HOURS_PER_SQUARE_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KW_HOURS_PER_SQUARE_METER;
	lmap[UNITS_KW_HOURS_PER_SQUARE_FOOT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KW_HOURS_PER_SQUARE_FOOT;
	lmap[UNITS_MEGAJOULES_PER_SQUARE_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAJOULES_PER_SQUARE_METER;
	lmap[UNITS_MEGAJOULES_PER_SQUARE_FOOT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGAJOULES_PER_SQUARE_FOOT;
	lmap[UNITS_NO_UNITS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_NO_UNITS;
	lmap[UNITS_NEWTON_SECONDS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_NEWTON_SECONDS;
	lmap[UNITS_NEWTONS_PER_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_NEWTONS_PER_METER;
	lmap[UNITS_PARTS_PER_MILLION.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PARTS_PER_MILLION;
	lmap[UNITS_PARTS_PER_BILLION.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PARTS_PER_BILLION;
	lmap[UNITS_PERCENT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PERCENT;
	lmap[UNITS_PERCENT_OBSCURATION_PER_FOOT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PERCENT_OBSCURATION_PER_FOOT;
	lmap[UNITS_PERCENT_OBSCURATION_PER_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PERCENT_OBSCURATION_PER_METER;
	lmap[UNITS_PERCENT_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PERCENT_PER_SECOND;
	lmap[UNITS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PER_MINUTE;
	lmap[UNITS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PER_SECOND;
	lmap[UNITS_PSI_PER_DEGREE_FAHRENHEIT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PSI_PER_DEGREE_FAHRENHEIT;
	lmap[UNITS_RADIANS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_RADIANS;
	lmap[UNITS_RADIANS_PER_SECOND.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_RADIANS_PER_SECOND;
	lmap[UNITS_REVOLUTIONS_PER_MINUTE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_REVOLUTIONS_PER_MINUTE;
	lmap[UNITS_SQUARE_METERS_PER_NEWTON.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SQUARE_METERS_PER_NEWTON;
	lmap[UNITS_WATTS_PER_METER_PER_DEGREE_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WATTS_PER_METER_PER_DEGREE_KELVIN;
	lmap[UNITS_WATTS_PER_SQUARE_METER_DEGREE_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_WATTS_PER_SQUARE_METER_DEGREE_KELVIN;
	lmap[UNITS_PER_MILLE.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PER_MILLE;
	lmap[UNITS_GRAMS_PER_GRAM.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_GRAM;
	lmap[UNITS_KILOGRAMS_PER_KILOGRAM.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_KILOGRAMS_PER_KILOGRAM;
	lmap[UNITS_GRAMS_PER_KILOGRAM.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_KILOGRAM;
	lmap[UNITS_MILLIGRAMS_PER_GRAM.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIGRAMS_PER_GRAM;
	lmap[UNITS_MILLIGRAMS_PER_KILOGRAM.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIGRAMS_PER_KILOGRAM;
	lmap[UNITS_GRAMS_PER_MILLILITER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_MILLILITER;
	lmap[UNITS_GRAMS_PER_LITER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_LITER;
	lmap[UNITS_MILLIGRAMS_PER_LITER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIGRAMS_PER_LITER;
	lmap[UNITS_MICROGRAMS_PER_LITER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MICROGRAMS_PER_LITER;
	lmap[UNITS_GRAMS_PER_CUBIC_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_CUBIC_METER;
	lmap[UNITS_MILLIGRAMS_PER_CUBIC_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIGRAMS_PER_CUBIC_METER;
	lmap[UNITS_MICROGRAMS_PER_CUBIC_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MICROGRAMS_PER_CUBIC_METER;
	lmap[UNITS_NANOGRAMS_PER_CUBIC_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_NANOGRAMS_PER_CUBIC_METER;
	lmap[UNITS_GRAMS_PER_CUBIC_CENTIMETER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_CUBIC_CENTIMETER;
	lmap[UNITS_BECQUERELS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_BECQUERELS;
	lmap[UNITS_MEGABECQUERELS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MEGABECQUERELS;
	lmap[UNITS_GRAY.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAY;
	lmap[UNITS_MILLIGRAY.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLIGRAY;
	lmap[UNITS_MICROGRAY.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MICROGRAY;
	lmap[UNITS_SIEVERTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_SIEVERTS;
	lmap[UNITS_MILLISIEVERTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MILLISIEVERTS;
	lmap[UNITS_MICROSIEVERTS.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MICROSIEVERTS;
	lmap[UNITS_MICROSIEVERTS_PER_HOUR.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MICROSIEVERTS_PER_HOUR;
	lmap[UNITS_DECIBELS_A.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_DECIBELS_A;
	lmap[UNITS_NEPHELOMETRIC_TURBIDITY_UNIT.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_NEPHELOMETRIC_TURBIDITY_UNIT;
	lmap[UNITS_PH.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_PH;
	lmap[UNITS_GRAMS_PER_SQUARE_METER.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_GRAMS_PER_SQUARE_METER;
	lmap[UNITS_MINUTES_PER_DEGREE_KELVIN.getValue()] = (BACnetEngUnitsChoice const *) &UNITS_MINUTES_PER_DEGREE_KELVIN;

	return lmap;
}

BACnetEngUnitsChoice const &BACnetEnumEngUnits::getEnumByValue(uint32_t enumValue) const {

	std::map<uint16_t, BACnetEngUnitsChoice const *>::iterator itr = objectMap.find(enumValue);

	/** If the object DOES exist, itr will point to it. Otherwise iter points to the object.end()*/
	if(itr != objectMap.end()) {
		return *itr->second;
	}
	else {
		ostringstream os;
		os << (unsigned int) enumValue;
		std::string s = "Invalid Enum Value (" + os.str() + "): BACnetEnumEngUnits::getEnumByValue(uint16_t enumValue)\n";
		throw std::invalid_argument(s);
	}
}

