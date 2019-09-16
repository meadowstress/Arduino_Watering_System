#ifndef TIME_H_
#define TIME_H_

class TIME
{
  private:
    long h;
    long min;

  public:
    TIME()
    {
      h = 0;
      min = 0;
    }

    TIME(long iH, long iMin)
    {
      h = iH;
      min = iMin;
    }
    long get_H(){return h;}
    long get_Min(){return min;}

	void set_H(long iH)
	{
		if(iH >= 0 && iH < 24)
			h = iH;
		else
			h = 0;
	}

	void set_Min(long iMin)
	{
		if(iMin >= 0 && iMin < 60)
			min = iMin;
		else
			min = 0;
	}

	void set_Time(long iH, long iMin)
	{
		TIME t;
		t.set_H(iH);
		t.set_Min(iMin);

		h = t.get_H();
		min = t.get_Min();
	}

    void print();
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
