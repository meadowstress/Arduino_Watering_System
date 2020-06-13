#include<Arduino.h>

#ifndef TIME_H_
#define TIME_H_

class TIME
{
 private:
    byte h;
    byte min;

 public:
    TIME()
    {
        h   = 0;
        min = 0;
    }

    TIME(byte iH, byte iMin)
    {
        h   = iH;
        min = iMin;
    }
    byte get_H() { return h; }
    byte get_Min() { return min; }

    void set_H(byte iH)
    {
        if (iH >= 0 && iH < 24)
            h = iH;
        else
            h = 0;
    }

    void set_Min(byte iMin)
    {
        if (iMin >= 0 && iMin < 60)
            min = iMin;
        else
            min = 0;
    }

    void set_Time(byte iH, byte iMin)
    {
        TIME t;
        t.set_H(iH);
        t.set_Min(iMin);

        h   = t.get_H();
        min = t.get_Min();
    }

    void print();
    void println();
    //unsigned long Time2Ticks();
    bool operator>(const TIME& c);
    bool operator>=(const TIME& c);
    bool operator<(const TIME& c);
    bool operator<=(const TIME& c);
    bool operator==(const TIME& c);
    TIME operator+(const TIME& t);
    TIME operator-(const TIME& t);
};

#endif /* TIME_H_ */
