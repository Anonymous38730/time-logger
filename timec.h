#include "stringc.h"

#ifndef TIMEC_H
#define TIMEC_H

class Time {
public:
    // Time();
    ~Time();
    Time(int h = 0, int m = 0, int s = 0, int ms = 0);
    Time(Time &t);
    int getMS() const;
    int getS() const;
    int getM() const;
    int getH() const;
    // void setMS();
    // void setS();
    // void setM();
    // void setH();
    void set(int h = 0, int m = 0, int s = 0, int ms = 0);
    static Time getCurrentTime();
    Time &operator -=(Time t);
    Time &operator +=(Time t);
    Time operator -(Time t);
    Time operator +(Time t);
    void subtractMS(int ms);
    void addMS(int ms);
    int compare(Time t);
    String toString();
    Time &operator =(Time t);
private:
    int h_;
    int m_;
    int s_;
    int ms_;
    void setRaw(int h, int m, int s, int ms);
    void clamp();
    void normalize();
};

#endif // TIMEC_H
