#include "log.h"
#include "timec.h"
//#include <cstdio>

#define LOG_INC 2

Log::Log() {
    size_ = LOG_INC;
    entries_ = new Entry[size_];
    used_ = 0;
}

Log::~Log() {
    clear();
    delete[] entries_;
}

Log::Log(Log &L) {
    size_ = L.size_;
    entries_ = new Entry[size_];
    used_ = L.used_;
    for (int i = 0; i < used_; i++) entries_[i] = L.entries_[i];
}

int Log::getLength() const {
    return used_;
}

Log &Log::clear() {
    size_ = LOG_INC;
    delete[] entries_;
    entries_ = new Entry[size_];
    used_ = 0;
    return *this;
}

Log &Log::info(String S, Time t) {
    insert(Entry(S, t, Entry::info), timeIndex(t));
    return *this;
}

Log &Log::info(char *s, Time t) {
    info(String(s), t);
    return *this;
}

Log &Log::info(String S) {
    info(S, Time::getCurrentTime());
    return *this;
}

Log &Log::info(char *s) {
    info(String(s));
    return *this;
}

Log &Log::error(String S, Time t) {
    insert(Entry(S, t, Entry::error), timeIndex(t));
    return *this;
}

Log &Log::error(char *s, Time t) {
    error(String(s), t);
    return *this;
}

Log &Log::error(String S) {
    error(S, Time::getCurrentTime());
    return *this;
}

Log &Log::error(char *s) {
    error(String(s));
    return *this;
}

String Log::toString() {
    String out;
    for (int i = 0; i < used_; i++) {
        Time tt = entries_[i].getTime();
        Entry::Type typet = entries_[i].getType();
        String St = entries_[i].getString();
        out <<=
            tt.toString()
            << (char *)" [" << (
                (typet == Entry::info) ? (char *)"i" : (
                    (typet == Entry::error) ? (char *)"!" : (char *)" "
                )
            ) << (char *)"] "
            << St
            << (char *)"\n";
    }
    return out;
}

void Log::resize() {
    if (used_ >= size_) {
        size_ = used_ + LOG_INC;
        Entry *newEntries = new Entry[size_];
        for (int i = 0; i < used_; i++) newEntries[i] = entries_[i];
        delete[] entries_;
        entries_ = newEntries;
    }
}

Log::Entry::Entry() {
    string_ = String();
    time_ = Time();
}

Log::Entry::Entry(String S, Time t, Type type) {
    string_ = S;
    time_ = t;
    type_ = type;
}

Log::Entry::~Entry() {
    // ???
}

Log::Entry::Entry(Entry &E) {
    string_ = E.string_;
    time_ = E.time_;
    type_ = E.type_;
}

Time Log::Entry::getTime() {
    return time_;
}

String Log::Entry::getString() {
    return string_;
}

Log::Entry::Type Log::Entry::getType() {
    return type_;
}

Log::Entry &Log::Entry::operator =(Log::Entry E) {
    string_ = E.string_;
    time_ = E.time_;
    type_ = E.type_;
    return *this;
}

void Log::insert(Log::Entry E, int index) {
    if (index < 0 || index >= size_) return;
    used_++;
    resize();
    for (int i = used_; i > index; i--) entries_[i] = entries_[i-1];
    entries_[index] = E;
}

int Log::timeIndex(Time t) {
    int i = used_-1;
    for (; i >= 0; i--) {
        if (t.compare(entries_[i].getTime()) >= 0) break;
    }
    return i + 1;
}

Log &Log::operator =(Log &L) {
    clear();
    for (int i = 0; i < L.used_; i++) {
        insert(L.entries_[i], i);
    }
    return *this;
}

Log Log::head(int n) {
    Log out;
    for (int i = 0; i < n && i < used_; i++) {
        out.insert(entries_[i], out.used_);
    }
    return out;
}

Log Log::head(Time t) {
    return head(timeIndex(t));
}

Log Log::tail(int n) {
    Log out;
    int i = used_ - n;
    if (i < 0) i = 0;
    for (; i < used_; i++) {
        out.insert(entries_[i], out.used_);
    }
    return out;
}

Log Log::tail(Time t) {
    return tail(used_ - timeIndex(t));
}
