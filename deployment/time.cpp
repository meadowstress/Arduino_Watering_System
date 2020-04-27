#include "time.h"
//#include "mock_arduino.h" // Enable for Testing

#include <Arduino.h>
#include <HardwareSerial.h>

void TIME::print()
{
	Serial.print(h);
	Serial.print(":");
	Serial.print(min);
}

void TIME::println()
{
	Serial.print(h);
	Serial.print(":");
	Serial.println(min);
}

unsigned long TIME::Time2Ticks()
{
	unsigned long ticks = 0;

	if (h >= 0 && min >= 0)
	{
		ticks = 1000L * 3600L * h;
		ticks = ticks + min * 1000L * 60L;
	}

	else
		ticks = 0;

	return (ticks);
}

bool TIME::operator>(const TIME &c)
{
	if (h > c.h)
		return true;

	else if (h == c.h && min > c.min)
		return true;

	else
		return false;
}

bool TIME::operator>=(const TIME &c)
{
	if (h > c.h)
		return true;

	else if (h == c.h && min == c.min)
		return true;

	else if (h == c.h && min > c.min)
		return true;

	else
		return false;
}

bool TIME::operator<(const TIME &c)
{
	if (h < c.h)
		return true;

	else if (h == c.h && min < c.min)
		return true;

	else
		return false;
}

bool TIME::operator<=(const TIME &c)
{
	if (h < c.h)
		return true;

	else if (h == c.h && min == c.min)
		return true;

	else if (h == c.h && min < c.min)
		return true;

	else
		return false;
}

bool TIME::operator==(const TIME &c)
{
	if (h == c.h && min == c.min)
		return true;

	else
		return false;
}

TIME TIME::operator+(const TIME &t)
{
	TIME t1;
	short h_buffer = (h + t.h), min_buffer = (min + t.min);

	if (h_buffer >= 0 && h_buffer < 24)
		t1.h = (h_buffer);
	else if (h_buffer >= 24)
		t1.h = (h_buffer % 24);
	else if (h_buffer < 0 && h_buffer > -24)
		t1.h = (h_buffer);
	else if (h_buffer <= -24)
		t1.h = (h_buffer % 24);

	if (min_buffer > 0 && min_buffer < 60)
		t1.min = (min_buffer);
	else if (min_buffer >= 60 && min_buffer < 120)
	{
		t1.h++;
		min_buffer = min_buffer - 60;
		t1.min = (min_buffer);
	}

	else if (min_buffer < 0 && min_buffer > -60)
		t1.min = (min_buffer);
	else if (min_buffer <= -60 && min_buffer > -120)
	{
		t1.h--;
		min_buffer = min_buffer + 60;
		t1.min = (min_buffer);
	}

	if (t1.h > 0 && t1.min < 0)
	{
		t1.h--;
		t1.min = 60 + t1.min;
	}
	return (t1);
}

TIME TIME::operator-(const TIME &t)
{
	TIME t1(0, 0);
	short h_buffer = (h - t.h), min_buffer = (min - t.min);

	if (h_buffer >= 0 && h_buffer < 24)
		t1.h = h_buffer;
	else if (h_buffer >= 24)
		t1.h = h_buffer % 24;
	else if (h_buffer < 0 && h_buffer > -24)
		t1.h = (h_buffer);
	else if (h_buffer <= -24)
		t1.h = (h_buffer % 24);

	if (min_buffer >= 0 && min_buffer < 60)
		t1.min = (min_buffer);
	else if (min_buffer >= 60 && min_buffer < 120)
	{
		t1.h++;
		min_buffer = min_buffer - 60;
		t1.min = (min_buffer);
	}

	else if (min_buffer < 0 && min_buffer > -60)
		t1.min = (min_buffer);
	else if (min_buffer <= -60 && min_buffer > -120)
	{
		t1.h--;
		min_buffer = min_buffer + 60;
		t1.min = (min_buffer);
	}

	if (t1.h > 0 && t1.min < 0)
	{
		t1.h--;
		t1.min = 60 + t1.min;
	}
	return (t1);
}
