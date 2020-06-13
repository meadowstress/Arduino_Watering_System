// #include <Arduino.h> // Enable on Hardware
#include "mock/mock_arduino.h"  //Enable for Test

#ifndef TIME_H_
#define TIME_H_

class TIME
{
 private:
    short h;
    short min;

 public:
    TIME()
    {
        h   = 0;
        min = 0;
    }

    TIME(short iH, short iMin)
    {
        h   = iH;
        min = iMin;
    }
    short get_H() { return h; }
    short get_Min() { return min; }

    void set_H(short iH)
    {
        if (iH >= 0 && iH < 24)
            h = iH;
        else
            h = 0;
    }

    void set_Min(short iMin)
    {
        if (iMin >= 0 && iMin < 60)
            min = iMin;
        else
            min = 0;
    }

    void set_Time(short iH, short iMin)
    {
        TIME t;
        t.set_H(iH);
        t.set_Min(iMin);

        h   = t.get_H();
        min = t.get_Min();
    }

    void print();
    void println();
    unsigned long Time2Ticks();
    bool operator>(const TIME& c);
    bool operator>=(const TIME& c);
    bool operator<(const TIME& c);
    bool operator<=(const TIME& c);
    bool operator==(const TIME& c);
    TIME operator+(const TIME& t);
    TIME operator-(const TIME& t);
};

#endif /* TIME_H_ */
