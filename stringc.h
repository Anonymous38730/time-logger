#ifndef STRINGC_H
#define STRINGC_H

class String {
public:
    String();
    String(char *s);
    String(String &S);
    ~String();
    String &operator <<=(String S);
    String &operator <<=(char *s);
    String operator <<(String S);
    String operator <<(char *s);
    int length() const;
    static int length(char *s);
    static int length(String S);
    char *getText() const;
    String &operator =(String S);
private:
    char *text_;
    int length_;
};

#endif // STRINGC_H