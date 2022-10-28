#include "log.h"
#include "timec.h"
//#include <malloc.h>
#include <cstdio>

#define LOG_INC 2

Log::Log() {
    size_ = LOG_INC;
    entries_ = new Entry[size_];
    used_ = 0;
}

Log::~Log() {
    //printf("Deleting Log\n");
    clear();
    //printf("Finishing deleting Log\n");
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
    //printf("Clearing, %p\n", entries_);
    size_ = LOG_INC;
    delete[] entries_;
    entries_ = new Entry[size_];
    used_ = 0;
    //printf("Finished clearing, %p\n", entries_);
    return *this;
}

Log &Log::info(String S, Time t) {
    insert(Entry(S, t, Entry::info), timeIndex(t));
    return *this;
    // Entry E(S, t, Entry::info);
    // entries_[used_++] = E;
    // resize();
    // return *this;
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
    // Entry E(S, t, Entry::error);
    // entries_[used_++] = E;
    // resize();
    // return *this;
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

String Log::stringify() {
    String out;
    for (int i = 0; i < used_; i++) {
        Time tt = entries_[i].getTime();
        Entry::Type typet = entries_[i].getType();
        String St = entries_[i].getString();
        out <<=
            tt.stringify()
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

Log::Entry::Entry() { // redo
    String S;
    Time t;
    string_ = S;
    time_ = t;
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

// Log::Log() {
//     size = LOG_INC;
//     //entries = (Entry**)malloc(size * sizeof(Entry*));
//     entries = new Entry*[size];
//     // проверка на выделенность?
//     index = 0;
// }

// Log::~Log() {
//     clear();
//     //free(entries);
//     delete[] entries;
// }

// void Log::info(char *text, Time time) {
//     entries[index++] = new Entry(text, time, Entry::Type::info);
//     resize();
// }

// void Log::info(char *text) {
//     info(text, Time::getCurrentTime());
// }

// void Log::error(char *text, Time time) {
//     entries[index++] = new Entry(text, time, Entry::Type::error);
//     resize();
// }

// void Log::error(char *text) {
//     error(text, Time::getCurrentTime());
// }

// void Log::resize() {
//     if (index >= size) {
//         size = index + LOG_INC;
//         //entries = (Entry**)realloc(entries, (index + LOG_INC) * sizeof(Entry*));
//         Entry **newEntries = new Entry*[size];
//         for (int i = 0; i < index; i++) newEntries[i] = entries[i];
//         delete[] entries;
//         entries = newEntries;
//         // проверка на выделенность?
//     }
// }

// Log::Entry::Entry(char *text, Time time, Entry::Type type) {
//     //this->text = text;
//     int tsize=0;
//     for (char *t = text; *t; t++, tsize++);
//     //this->text = (char*)malloc((tsize + 1) * sizeof(char));
//     this->text = new char[tsize+1];
//     // проверка на выделенность?
//     for (int i = 0; i < tsize + 1; i++) this->text[i] = text[i];
//     this->time = time;
//     this->type = type;
// }

// Log::Entry::~Entry() {
//     delete[] text;
// }

// char *Log::Entry::getText() {
//     return text;
// }

// Time Log::Entry::getTime() {
//     return time;
// }

// Log::Entry::Type Log::Entry::getType() {
//     return type;
// }

// void Log::print() {
//     for (int i = 0; i < index; i++) {
//         char* textt = entries[i]->getText();
//         Time timet = entries[i]->getTime();
//         Entry::Type typet = entries[i]->getType();
//         timet.print();
//         // std::cout <<
//         //     //timet.getH() << ":" << timet.getM() << ":" << timet.getS() << "." << timet.getMS() << // время
//         //     "\t[" << ((typet == Entry::Type::info) ? "i" : (typet == Entry::Type::error) ? "!" : " ") << "] " << // тип: [i] [!] [ ]
//         //     textt << std::endl; // содержание
//         printf("\t[%c] %s\n", ((typet == Entry::Type::info) ? 'i' : (typet == Entry::Type::error) ? '!' : ' '), textt);
//     }
// }

// int Log::getLength() const {
//     return index;
// }

// void Log::clear() {
//     for (int i = 0; i < index; i++) delete entries[i];
//     index = 0;
//     size = LOG_INC;
//     //entries = (Entry**)realloc(entries, size * sizeof(Entry*));
//     delete[] entries;
//     entries = new Entry*[size];
//     // проверка на выделенность?
// }

// // Log Log::copy() {
// //     Log l;
// //     for (int i = 0; i < index; i++) {
// //         l.entries[l.index++] = new Entry(entries[i]->getText(), entries[i]->getTime(), entries[i]->getType());;
// //         l.resize();
// //     }
// //     return l;
// // }

// Log &Log::operator =(const Log &log) {
//     clear();
//     for (int i = 0, length = log.getLength(); i < length; i++) {
//         Entry *e = log.entries[i];
//         entries[index++] = new Entry(e->getText(), e->getTime(), e->getType());
//         resize();
//     }
//     return *this;
// }

// Log Log::head(int n) {
//     Log out;
//     for (int i = 0; i < n && i < index; i++) {
//         Entry *e = entries[i];
//         out.entries[out.index++] = new Entry(e->getText(), e->getTime(), e->getType());
//         out.resize();
//     }
//     return out;
// }

// Log Log::head(Time time) {
//     Log out;
//     int endIndex = 0;
//     for (int i = 0; i < index; i++) {
//         if (time.compare(entries[i]->getTime()) >= 0) endIndex = i;
//     }
//     for (int i = 0; i < endIndex+1 && i < index; i++) {
//         Entry *e = entries[i];
//         out.entries[out.index++] = new Entry(e->getText(), e->getTime(), e->getType());
//         out.resize();
//     }
//     return out;
// }

// Log Log::tail(int n) {
//     Log out;
//     int startIndex = (n < index) ? index - n : 0;
//     for (int i = startIndex; i < index; i++) {
//         Entry *e = entries[i];
//         out.entries[out.index++] = new Entry(e->getText(), e->getTime(), e->getType());
//         out.resize();
//     }
//     return out;
// }

// Log Log::tail(Time time) {
//     Log out;
//     int startIndex = index;
//     for (int i = index-1; i >= 0; i--) {
//         if (time.compare(entries[i]->getTime()) <= 0) startIndex = i;
//     }
//     for (int i = startIndex; i < index; i++) {
//         Entry *e = entries[i];
//         out.entries[out.index++] = new Entry(e->getText(), e->getTime(), e->getType());
//         out.resize();
//     }
//     return out;
// }