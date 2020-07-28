#include "time.h"
#include "mock/mock_arduino.h"  // Enable for Testing
#include "PS_func.h"

//#include <Arduino.h> // Enable on Hardware
//#include <HardwareSerial.h> // Enable on Hardware

void TIME::print()
{
    Serial.print(h);
    Serial.print(":");
    Serial.print(min);
    Serial.print(":");
    Serial.print(sec);
}

void TIME::println()
{
    Serial.print(h);
    Serial.print(":");
    Serial.println(min);
    Serial.print(":");
    Serial.print(sec);
}

void TIME::printSD()
{
    PumpControl.printToSDFile(h);
    PumpControl.printToSDFile(":");
    PumpControl.printToSDFile(min);
    PumpControl.printToSDFile(":");
    PumpControl.printToSDFile(sec);
}

void TIME::printlnSD()
{
    PumpControl.printToSDFile(h);
    PumpControl.printToSDFile(":");
    PumpControl.printlnToSDFile(min);
    PumpControl.printToSDFile(":");
    PumpControl.printlnToSDFile(sec);
}

unsigned long TIME::Time2Ticks()
{
    unsigned long ticks = 0;

    if (h >= 0 && min >= 0 && sec >= 0)
    {
        ticks = 1000L * sec;
        ticks = ticks + 1000L * 3600L * h;
        ticks = ticks + min * 1000L * 60L;
        ticks = ticks + sec * 1000L;
    }

    else
        ticks = 0;

    return (ticks);
}

bool TIME::operator>(const TIME& c)
{
    if (h > c.h)
        return true;

    else if (h == c.h && min > c.min)
        return true;

    else if (h == c.h && min == c.min && sec > c.sec)
        return true;

    else
        return false;
}

const bool TIME::operator>(const TIME& c) const
{
    if (h > c.h)
        return true;

    else if (h == c.h && min > c.min)
        return true;

    else if (h == c.h && min == c.min && sec > c.sec)
        return true;

    else
        return false;
}

bool TIME::operator>=(const TIME& c)
{
    if (h > c.h)
        return true;

    else if (h == c.h && min == c.min && sec == c.sec)
        return true;

    else if (h == c.h && min > c.min)
        return true;

    else if (h == c.h && min == c.min && sec > c.sec)
        return true;

    else
        return false;
}

const bool TIME::operator>=(const TIME& c) const
{
    if (h > c.h)
        return true;

    else if (h == c.h && min == c.min && sec == c.sec)
        return true;

    else if (h == c.h && min > c.min)
        return true;

    else if (h == c.h && min == c.min && sec > c.sec)
        return true;

    else
        return false;
}

bool TIME::operator<(const TIME& c)
{
    if (h < c.h)
        return true;

    else if (h == c.h && min < c.min)
        return true;

    else if (min == c.min && sec < c.sec)
        return true;

    else if (h == c.h && min == c.min && sec < c.sec)
        return true;

    else
        return false;
}

const bool TIME::operator<(const TIME& c) const
{
    if (h < c.h)
        return true;

    else if (h == c.h && min < c.min)
        return true;

    else if (min == c.min && sec < c.sec)
        return true;

    else if (h == c.h && min == c.min && sec < c.sec)
        return true;

    else
        return false;
}

bool TIME::operator<=(const TIME& c)
{
    if (h < c.h)
        return true;

    else if (h == c.h && min == c.min && sec == c.sec)
        return true;

    else if (h == c.h && min < c.min)
        return true;

    else if (h == c.h && min == c.min && sec < c.sec)
        return true;

    else
        return false;
}

const bool TIME::operator<=(const TIME& c) const
{
    if (h < c.h)
        return true;

    else if (h == c.h && min == c.min && sec == c.sec)
        return true;

    else if (h == c.h && min < c.min)
        return true;

    else if (h == c.h && min == c.min && sec < c.sec)
        return true;

    else
        return false;
}

bool TIME::operator==(const TIME& c)
{
    if (h == c.h && min == c.min && sec == c.sec)
        return true;

    else
        return false;
}

const bool TIME::operator==(const TIME& c) const
{
    if (h == c.h && min == c.min && sec == c.sec)
        return true;

    else
        return false;
}

TIME TIME::operator+(const TIME& t)
{
    TIME t1(0, 0, 0);

    // hours
    short h_buffer = (h + t.h), min_buffer = (min + t.min),
          sec_buffer = (sec + t.sec);

    if (h_buffer >= 0 && h_buffer < 24)
        t1.h = (h_buffer);
    else if (h_buffer >= 24)
        t1.h = (h_buffer % 24);
    else if (h_buffer < 0 && h_buffer > -24)
        t1.h = (h_buffer);
    else if (h_buffer <= -24)
        t1.h = (h_buffer % 24);

    // minutes
    if (min_buffer > 0 && min_buffer < 60)
        t1.min = (min_buffer);
    else if (min_buffer >= 60 && min_buffer < 120)
    {
        t1.h++;
        min_buffer = min_buffer - 60;
        t1.min     = (min_buffer);
    }

    else if (min_buffer < 0 && min_buffer > -60)
        t1.min = (min_buffer);
    else if (min_buffer <= -60 && min_buffer > -120)
    {
        t1.h--;
        min_buffer = min_buffer + 60;
        t1.min     = (min_buffer);
    }

    if (t1.h > 0 && t1.min < 0)
    {
        t1.h--;
        t1.min = 60 + t1.min;
    }

    // seconds
    if (sec_buffer > 0 && sec_buffer < 60)
        t1.sec = (sec_buffer);
    else if (sec_buffer >= 60 && sec_buffer < 120)
    {
        t1.min++;
        sec_buffer = sec_buffer - 60;
        t1.sec     = (sec_buffer);
    }

    else if (sec_buffer < 0 && sec_buffer > -60)
        t1.sec = (sec_buffer);

    else if (sec_buffer <= -60 && sec_buffer > -120)
    {
        t1.min--;
        sec_buffer = sec_buffer + 60;
        t1.sec     = (sec_buffer);
    }

    if (t1.min > 0 && t1.sec < 0)
    {
        t1.min--;
        t1.sec = 60 + t1.sec;
    }

    return (t1);
}

const TIME TIME::operator+(const TIME& t) const
{
    TIME t1(0, 0, 0);

    // hours
    short h_buffer = (h + t.h), min_buffer = (min + t.min),
          sec_buffer = (sec + t.sec);

    if (h_buffer >= 0 && h_buffer < 24)
        t1.h = (h_buffer);
    else if (h_buffer >= 24)
        t1.h = (h_buffer % 24);
    else if (h_buffer < 0 && h_buffer > -24)
        t1.h = (h_buffer);
    else if (h_buffer <= -24)
        t1.h = (h_buffer % 24);

    // minutes
    if (min_buffer > 0 && min_buffer < 60)
        t1.min = (min_buffer);
    else if (min_buffer >= 60 && min_buffer < 120)
    {
        t1.h++;
        min_buffer = min_buffer - 60;
        t1.min     = (min_buffer);
    }

    else if (min_buffer < 0 && min_buffer > -60)
        t1.min = (min_buffer);
    else if (min_buffer <= -60 && min_buffer > -120)
    {
        t1.h--;
        min_buffer = min_buffer + 60;
        t1.min     = (min_buffer);
    }

    if (t1.h > 0 && t1.min < 0)
    {
        t1.h--;
        t1.min = 60 + t1.min;
    }

    // seconds
    if (sec_buffer > 0 && sec_buffer < 60)
        t1.sec = (sec_buffer);
    else if (sec_buffer >= 60 && sec_buffer < 120)
    {
        t1.min++;
        sec_buffer = sec_buffer - 60;
        t1.sec     = (sec_buffer);
    }

    else if (sec_buffer < 0 && sec_buffer > -60)
        t1.sec = (sec_buffer);

    else if (sec_buffer <= -60 && sec_buffer > -120)
    {
        t1.min--;
        sec_buffer = sec_buffer + 60;
        t1.sec     = (sec_buffer);
    }

    if (t1.min > 0 && t1.sec < 0)
    {
        t1.min--;
        t1.sec = 60 + t1.sec;
    }

    return (t1);
}

TIME TIME::operator-(const TIME& t)
{
    TIME t1(0, 0, 0);
    short h_buffer = (h - t.h), min_buffer = (min - t.min),
          sec_buffer(sec - t.sec);

    // hours
    if (h_buffer >= 0 && h_buffer < 24)
        t1.h = h_buffer;
    else if (h_buffer >= 24)
        t1.h = h_buffer % 24;
    else if (h_buffer < 0 && h_buffer > -24)
        t1.h = (h_buffer);
    else if (h_buffer <= -24)
        t1.h = (h_buffer % 24);

    // minutes
    if (min_buffer >= 0 && min_buffer < 60)
        t1.min = (min_buffer);
    else if (min_buffer >= 60 && min_buffer < 120)
    {
        t1.h++;
        min_buffer = min_buffer - 60;
        t1.min     = (min_buffer);
    }

    else if (min_buffer < 0 && min_buffer > -60)
        t1.min = (min_buffer);
    else if (min_buffer <= -60 && min_buffer > -120)
    {
        t1.h--;
        min_buffer = min_buffer + 60;
        t1.min     = (min_buffer);
    }

    if (t1.h > 0 && t1.min < 0)
    {
        t1.h--;
        t1.min = 60 + t1.min;
    }

    // seconds
    if (sec_buffer >= 0 && sec_buffer < 60)
        t1.sec = (sec_buffer);
    else if (sec_buffer >= 60 && sec_buffer < 120)
    {
        t1.min++;
        sec_buffer = sec_buffer - 60;
        t1.sec     = (sec_buffer);
    }

    else if (sec_buffer < 0 && sec_buffer > -60)
        t1.sec = (sec_buffer);
    else if (sec_buffer <= -60 && sec_buffer > -120)
    {
        t1.min--;
        sec_buffer = sec_buffer + 60;
        t1.sec     = (sec_buffer);
    }

    if (t1.min > 0 && t1.sec < 0)
    {
        t1.min--;
        t1.sec = 60 + t1.sec;
    }

    return (t1);
}

const TIME TIME::operator-(const TIME& t) const
{
    TIME t1(0, 0, 0);
    short h_buffer = (h - t.h), min_buffer = (min - t.min),
          sec_buffer(sec - t.sec);

    // hours
    if (h_buffer >= 0 && h_buffer < 24)
        t1.h = h_buffer;
    else if (h_buffer >= 24)
        t1.h = h_buffer % 24;
    else if (h_buffer < 0 && h_buffer > -24)
        t1.h = (h_buffer);
    else if (h_buffer <= -24)
        t1.h = (h_buffer % 24);

    // minutes
    if (min_buffer >= 0 && min_buffer < 60)
        t1.min = (min_buffer);
    else if (min_buffer >= 60 && min_buffer < 120)
    {
        t1.h++;
        min_buffer = min_buffer - 60;
        t1.min     = (min_buffer);
    }

    else if (min_buffer < 0 && min_buffer > -60)
        t1.min = (min_buffer);
    else if (min_buffer <= -60 && min_buffer > -120)
    {
        t1.h--;
        min_buffer = min_buffer + 60;
        t1.min     = (min_buffer);
    }

    if (t1.h > 0 && t1.min < 0)
    {
        t1.h--;
        t1.min = 60 + t1.min;
    }

    // seconds
    if (sec_buffer >= 0 && sec_buffer < 60)
        t1.sec = (sec_buffer);
    else if (sec_buffer >= 60 && sec_buffer < 120)
    {
        t1.min++;
        sec_buffer = sec_buffer - 60;
        t1.sec     = (sec_buffer);
    }

    else if (sec_buffer < 0 && sec_buffer > -60)
        t1.sec = (sec_buffer);
    else if (sec_buffer <= -60 && sec_buffer > -120)
    {
        t1.min--;
        sec_buffer = sec_buffer + 60;
        t1.sec     = (sec_buffer);
    }

    if (t1.min > 0 && t1.sec < 0)
    {
        t1.min--;
        t1.sec = 60 + t1.sec;
    }

    return (t1);
}
