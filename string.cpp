#include "string.hpp"

String::String() : stringSize(1) {
    str = new char[stringSize];
    str[0] = 0;
}              

String::String(char s) {
    stringSize = (s == '\0') ? 1 : 2;

    str = new char[stringSize];

    if (s != '\0') {
        str[0] = s;
        str[1] = 0;
    }
    else str[0] = 0;
}

String::String(const char s[]) {
    if (s[0] == '\0') {
        stringSize = 1;
        str = new char[stringSize];
        str[0] = s[0];
        return;
    }
    else if (s[1] == '\0') {
        stringSize = 2;
        str = new char[stringSize];
        str[0] = s[0];
        str[1] = 0;
        return;
    }

    stringSize = 0;
    while (s[stringSize] != 0)
        ++stringSize;

    stringSize++;
    str = new char[stringSize];
    for(int i = 0; i < stringSize; i++) 
        str[i] = s[i];
  
}

String::String(const String& rhs) {
    stringSize = rhs.length() + 1;
    str = new char[stringSize];
    for (int i = 0; i < stringSize; i++) 
        str[i] = rhs[i];
}

String::~String() {
    delete[] str;
}

int String::capacity() const { return stringSize - 1; }

int String::length() const { return capacity(); }

String& String::operator=(String rhs) {
    swap(rhs);
    return *this;
}

void String::swap(String& rhs) {
    char* temp = str;
    str = rhs.str;
    rhs.str = temp;

    int tempSize = stringSize;
    stringSize = rhs.stringSize;
    rhs.stringSize = tempSize;
}

char& String::operator[](int i) { return str[i]; }

char String::operator[](int i) const { return str[i]; }

String& String::operator+=(const String& rhs) {
    
    if (length() == 0 && rhs.length() == 0)
        return *this;
    if (rhs.length() == 0)
        return *this;
    
    const int oSize = length();
    stringSize = oSize + rhs.length() + 1;
    auto temp = new char[stringSize];
    for(int i = 0; i < stringSize; ++i) {
        if (i < oSize)
            temp[i] = str[i];
        else
            temp[i] = rhs[i - oSize];
    }

    delete[] str;
    str = temp;
    return *this;
}

bool String::operator==(const String& rhs) const {
    if (length() != rhs.length())
        return false;

    if (length() == 0 && rhs.length() == 0)
        return true;

    for (auto i = 0; i < rhs.length(); i++) {
        if (str[i] != rhs.str[i])
            return false;
    }

    return true;
}

bool String::operator<(const String& rhs) const {

    int i = 0;
    while ((str[i] != 0) && (rhs[i] != 0) && (str[i] == rhs[i])) i++;

    if (str[i] == 0 && rhs[i] == 0) return false;
    if (str[i] == 0)                return true;
    if (str[i] < rhs[i])            return true;

    return false;
}

String String::substr(int start, int end) const {
    String result;
    if (end < start) return result;
    if (start < 0) start = 0;
    if (end >= length()) end = length() - 1;

    for (int i = start; i <= end; ++i)
        result += str[i];
    return result;
}

int String::findch(int start, char charToFind) const {
    if (str[0] == 0 && charToFind == 0) return 0;
        for (int i = start; i < length(); i++) {
                if (str[i] == charToFind) return i;
        }

        return -1;
}

int String::findstr(int start, const String& strToFind) const {

    if (start < 0) start = 0;
    if (start >= length()) start = length() - 1;

    for (int i = start; i < length(); i++) {
        if (substr(i, i + strToFind.length() - 1) == strToFind)
            return i;
    }
    return -1;
}

std::ostream& operator<<(std::ostream& stream, const String& myStr) {

    stream << myStr.str;

    return stream;
}

std::istream& operator>>(std::istream& stream, String& myStr) {

    char buffer[256];
    stream >> buffer;
    myStr = buffer;
    return stream;
}

std::vector<String> String::split(char c) const {
    std::vector<String> vStr;
    int start = 0;
    while (findch(start, c) != -1) {
        vStr.push_back(substr(start, findch(start, c) - 1));
        start = findch(start, c) + 1;
    }
    vStr.push_back(substr(start, length()));
    return vStr;
}


String operator+(String str1, const String& str2)           { return (str1 += str2); }

bool operator==(const char charParam[], const String& str2) { return String(charParam) == str2; }
bool operator==(char charParam, const String& str2)         { return String(charParam) == str2; }

bool operator<(const char charParam[], const String& str2)  { return String(charParam) < str2; }

bool operator<(char charParam, const String& str2)          { return String(charParam) < str2; }

bool operator<=(const String& str1, const String& str2)     { return (str1 == str2) || (str1 < str2); }

bool operator!=(const String& str1, const String& str2)     { return !(str1 == str2); }

bool operator>=(const String& str1, const String& str2)     { return (str1 == str2) || (str1 > str2); }

bool operator>(const String& str1, const String& str2)      { return !(str1 < str2); }





/*

bool    operator<       (const char[],  const String&);
bool    operator<       (const String&, const char   );
bool    operator<       (char,          const String&);
bool    operator<       (const String&, const char[] );

bool    operator<=      (const String&, const String&);
bool    operator<=      (const char[],  const String&);
bool    operator<=      (const String&, const char   );
bool    operator<=      (char,          const String&);
bool    operator<=      (const String&, const char[] );

bool    operator!=      (const String&, const String&);
bool    operator!=      (const char[],  const String&);
bool    operator!=      (const String&, const char   );
bool    operator!=      (char,          const String&);
bool    operator!=      (const String&, const char[] );

bool    operator>=      (const String&, const String&);
bool    operator>=      (const char[],  const String&);
bool    operator>=      (const String&, const char   );
bool    operator>=      (char,          const String&);
bool    operator>=      (const String&, const char[] );

bool    operator>       (const String&, const String&);
bool    operator>       (const char[],  const String&);
bool    operator>       (const String&, const char   );
bool    operator>       (char,          const String&);
bool    operator>       (const String&, const char[] );

*/
