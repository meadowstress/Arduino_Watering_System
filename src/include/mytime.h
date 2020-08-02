// #include <Arduino.h> // Enable on Hardware
#include "mock_arduino.h"  //Enable for Test

#ifndef TIME_H_
#define TIME_H_

class TIME
{
 private:
    short h;
    short min;
    short sec;

 public:
    TIME()
    {
        h   = 0;
        min = 0;
        sec = 0;
    }

    TIME(short iH, short iMin, short iSec)
    {
        h   = iH;
        min = iMin;
        sec = iSec;
    }
    short get_H() { return h; }
    short get_Min() { return min; }
    short get_Sec() { return sec; }

    void set_H(short iH)
    {
        if (iH > -24 && iH < 24)
            h = iH;
        else
            h = iH % 24;
    }

    void set_Min(short iMin)
    {
        if (iMin > -60 && iMin < 60)
            min = iMin;
        else
            min = iMin % 60;
    }

    void set_Sec(short iSec)
    {
        if (iSec > -60 && iSec < 60)
            sec = iSec;
        else
            sec = iSec % 60;
    }

    void set_Time(short iH, short iMin, short iSec)
    {
        set_H(iH);
        set_Min(iMin);
        set_Sec(iSec);
    }

    void print();
    void println();
    void printSD();
    void printlnSD();
    unsigned long Time2Ticks();
    bool operator>(const TIME& c);
    const bool operator>(const TIME& c) const;
    bool operator>=(const TIME& c);
    const bool operator>=(const TIME& c) const;
    bool operator<(const TIME& c);
    const bool operator<(const TIME& c) const;
    bool operator<=(const TIME& c);
    const bool operator<=(const TIME& c) const;
    bool operator==(const TIME& c);
    const bool operator==(const TIME& c) const;
    TIME operator+(const TIME& t);
    const TIME operator+(const TIME& t) const;
    TIME operator-(const TIME& t);
    const TIME operator-(const TIME& t) const;
};

#endif /* TIME_H_ */
