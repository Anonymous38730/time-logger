#include "timec.h"

#ifndef LOG_H
#define LOG_H

class Log {
public:
    Log();
    ~Log();
    Log(Log &L);
    //Log(char *s);
    //Log(String S);
    //Log(char *s, Time t);
    //Log(String S, Time t);
    int getLength() const;
    Log &clear();
    Log &info(char *s);
    Log &info(String S);
    Log &info(char *s, Time t);
    Log &info(String S, Time t);
    Log &error(char *s);
    Log &error(String S);
    Log &error(char *s, Time t);
    Log &error(String S, Time t);
    String toString();
    Log head(int n);
    Log head(Time time);
    Log tail(int n);
    Log tail(Time time);
    Log &operator =(Log &L);
private:
    class Entry {
        //friend Log::~Log();
        public:
            enum Type {info, error};
            Entry();
            Entry(String S, Time t, Type type);
            Entry(Entry &E);
            ~Entry();
            Time getTime();
            //char *getText();
            String getString();
            Type getType();
            Entry &operator =(Entry E);
        private:
            Time time_;
            //char *text;
            String string_;
            Type type_;
    } *entries_;
    int size_;
    int used_;
    void resize();
    int timeIndex(Time t);
    void insert(Entry E, int index);
};

#endif // LOG_H