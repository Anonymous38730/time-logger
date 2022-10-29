#include "timec.h"
//#include <time.h>
#include <sys/time.h>
#include "stringc.h"

Time Time::getCurrentTime() {
    //int curTime = time(nullptr);
    struct timeval ct;
    gettimeofday(&ct, nullptr);
    long curTime = ct.tv_sec;
    return Time(
        (int)(curTime / (60*60) % 24),
        (int)(curTime / (60) % 60),
        (int)(curTime % 60),
        (int)(ct.tv_usec / 1000)
    );
}

// Time::Time() {
//     h = m = s = ms = 0;
// }

Time::Time(int h, int m, int s, int ms) {
    h_ = h;
    m_ = m;
    s_ = s;
    ms_ = ms;
    clamp();
}

Time::~Time() {
    // ???
}

Time::Time(Time &t) {
    h_ = t.h_;
    m_ = t.m_;
    s_ = t.s_;
    ms_ = t.ms_;
}

void Time::clamp() {
    if (h_ >= 24) h_ = 24-1;
    if (h_ < 0) h_ = 0;
    if (m_ >= 60) m_ = 60-1;
    if (m_ < 0) m_ = 0;
    if (s_ >= 60) s_ = 60-1;
    if (s_ < 0) s_ = 0;
    if (ms_ >= 1000) ms_ = 1000-1;
    if (ms_ < 0) ms_ = 0;
}

void Time::normalize() {
    while (ms_ < 0) {
        ms_ += 1000;
        s_ -= 1;
    }
    while (ms_ >= 1000) {
        ms_ -= 1000;
        s_ += 1;
    }
    while (s_ < 0) {
        s_ += 60;
        m_ -= 1;
    }
    while (s_ >= 60) {
        s_ -= 60;
        m_ += 1;
    }
    while (m_ < 0) {
        m_ += 60;
        h_ -= 1;
    }
    while (m_ >= 60) {
        m_ -= 60;
        h_ += 1;
    }
    if (h_ < 0) {
        h_ = 0;
        m_ = 0;
        s_ = 0;
        ms_ = 0;
    }
    if (h_ >= 24) {
        h_ = 24-1;
        m_ = 60-1;
        s_ = 60-1;
        ms_ = 1000-1;
    }
}

int Time::getMS() const {
    return ms_;
}

int Time::getS() const {
    return s_;
}

int Time::getM() const {
    return m_;
}

int Time::getH() const {
    return h_;
}

void Time::setRaw(int h, int m, int s, int ms) {
    h_ = h;
    m_ = m;
    s_ = s;
    ms_ = ms;
}

void Time::set(int h, int m, int s, int ms) {
    setRaw(h, m, s, ms);
    clamp();
}

Time &Time::operator +=(Time t) {
    h_ += t.h_;
    m_ += t.m_;
    s_ += t.s_;
    ms_ += t.ms_;
    normalize();
    return *this;
}

Time &Time::operator -=(Time t) {
    h_ -= t.h_;
    m_ -= t.m_;
    s_ -= t.s_;
    ms_ -= t.ms_;
    normalize();
    return *this;
}

Time Time::operator +(Time t) {
    Time out(*this);
    out += t;
    return out;
}

Time Time::operator -(Time t) {
    Time out(*this);
    out -= t;
    return out;
}

void Time::addMS(int ms) {
    ms_ += ms;
    normalize();
}

void Time::subtractMS(int ms) {
    ms_ -= ms;
    normalize();
}

int Time::compare(Time t) {
    if (h_ > t.h_) return 1;
    if (h_ < t.h_) return -1;
    if (m_ > t.m_) return 1;
    if (m_ < t.m_) return -1;
    if (s_ > t.s_) return 1;
    if (s_ < t.s_) return -1;
    if (ms_ > t.ms_) return 1;
    if (ms_ < t.ms_) return -1;
    return 0;
}

String Time::toString() {
    char out[] = "00:00:00.000";
    // Часы
    out[0] = h_ / 10 % 10 + '0';
    out[1] = h_ % 10 + '0';
    // Минуты
    out[3] = m_ / 10 % 10 + '0';
    out[4] = m_ % 10 + '0';
    // Секунды
    out[6] = s_ / 10 % 10 + '0';
    out[7] = s_ % 10 + '0';
    // Миллисекунды
    out[9] = ms_ / 100 % 10 + '0';
    out[10] = ms_ / 10 % 10 + '0';
    out[11] = ms_ % 10 + '0';
    return String(out);
}

Time &Time::operator =(Time t) {
    h_ = t.h_;
    m_ = t.m_;
    s_ = t.s_;
    ms_ = t.ms_;
    return *this;
}
