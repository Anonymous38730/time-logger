#include "stringc.h"
#include <cstdio>

String::String() {
    text_ = new char[1];
    // проверка на выделенность?
    length_ = 0;
    *text_ = '\0';
}

String::~String() {
    delete[] text_;
}

int String::length(char *s) {
    if (!s) return 0;
    int len = 0;
    for (; s[len]; len++);
    return len;
}

int String::length(String &S) {
    return S.length();
}

int String::length() const {
    return length_;
}

String::String(char *s) {
    if (!s) {
        text_ = new char[1];
        // проверка на выделенность?
        length_ = 0;
        *text_ = '\0';
        return;
    }
    length_ = String::length(s);
    text_ = new char[1 + length_];
    // проверка на выделенность?
    for (int i = 0; i <= length_; i++) text_[i] = s[i];
}

String::String(String &S) {
    length_ = S.length();
    char *s = S.text_;
    text_ = new char[1 + length_];
    // проверка на выделенность?
    for (int i = 0; i <= length_; i++) text_[i] = s[i];
}

String &String::operator =(String S) {
    delete[] text_;
    length_ = S.length();
    char *s = S.text_;
    text_ = new char[1 + length_];
    // проверка на выделенность?
    for (int i = 0; i <= length_; i++) text_[i] = s[i];
    return *this;
}

char *String::getText() const {
    return text_;
}

String &String::operator <<=(char *s) {
    if (!s) return *this;
    int len2 = String::length(s);
    char *newText = new char[1 + length_ + len2];
    // проверка на выделенность?
    char *index = newText;
    for (char *ctext = text_; *ctext; ctext++, index++) *index = *ctext;
    for (char *ctext = s; *ctext; ctext++, index++) *index = *ctext;
    *index = '\0';
    delete[] text_;
    length_ += len2;
    text_ = newText;
    return *this;
}

String &String::operator <<=(String S) {
    (*this) <<= S.text_;
    return *this;
}

String String::operator <<(char *s) {
    String out(*this);
    out <<= s;
    return out;
}

String String::operator <<(String S) {
    String out(*this);
    out <<= S;
    return out;
}