Application Time Constants
==========================

For Temperatures around 30 degrees Celcius the following time constants should
be used:

Plants on top t = 40000 ms for 4 Plants
Plants on bottom t = 15000 ms for 2 Plants

At 30 Degrees a bazil plant in bare sun needs estimately 1.4 l of Water per
day which is a full plant can of mine.

Temperature Measurement
=======================
The thermometer measures estimately 10 degrees Celcius too much since it heatens
up in the sun. Due to that the usual reference temperature range is 35°C - 45°C
which you can find in the former Watering Time Constants below. Which is also
the Range where the application watering time constats are picked as well.


Former Watering Time Constants
==============================

//Watering parameters for top plants
const float maxTemp = 55.0F;
const unsigned int timeMaxTempTop = 60000;
const unsigned int timeMaxTempBottom = 20000;

const float temp2 = 45.0F;
const unsigned int timeTemp2Top = 40000;
const unsigned int timeTemp2Bottom = 15000;

const float temp3 = 35.0F;
const unsigned int timeTemp3Top = 30000;
const unsigned int timeTemp3Bottom = 10000;

const float temp4 = 25.0F;
const unsigned int timeTemp4Top = 20000;
const unsigned int timeTemp4Bottom = 8000;

const float lowTemp = 18.0F;
const unsigned int timeLowTempTop = 8000;
const unsigned int timeLowTempBottom = 4000;

//Water Times
const TIME t1_water(11, 30);
const TIME t2_water(15, 30);
const unsigned int t_valve = 100;
const unsigned int t_half_can = 15000;


Expectations for Unit Tests
===========================

The unit test expect the following point of times for watering:
11:30 Uhr and 15:30 Uhr otherwiste the unit tests will fail.