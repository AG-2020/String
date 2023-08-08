//
//
// File:        logentry.cpp  
//       
// Version:     1.0
// Date:        Spring 2023
// Author:      Aidan Latessa
//
// Description: Class implementation for a log entry.
//
//

#include "string.hpp"
#include "logentry.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <utility>

int pow(const int multiplier) {
    int result = 1; 
    for (int i = 0; i < multiplier; i++) 
        result *= 10;
    
    return result;
}

int strToInt(const String s) {

    int result = 0;

    for (auto i = s.length(); i > 0; i--) {
        int charToInt = s[i - 1] - '0'; 
        if (charToInt < 0 || charToInt > 9)
            return 0;
        result += pow(s.length() - i) * charToInt;
    }

    return result;
}

String Date::get() const {
    String result = '[' + day + '/' + month + '/' + year + ']';

    return result;
}

String Time::get() const {
    String result = '[' + hour + ':' + minute + ':' + second + ']';

    return result;
}

LogEntry::LogEntry(String s) {
    std::vector<String> vec = s.split(' ');
    if (vec.size() == 10) {
        entry = s;
        host = vec[0];
        std::vector<String> timeVec = vec[3].split(':');
        time = Time(strToInt(timeVec[1]), strToInt(timeVec[2]), strToInt(timeVec[3]));
        std::vector<String> dateVec = timeVec[0].split('/');
        date = Date(dateVec[0].substr(1, 2), dateVec[1], strToInt(dateVec[2]));

        request = vec[5] + vec[6] + vec[7];
        status = vec[8];
        number_of_bytes = strToInt(vec[9]);
    }
}

std::vector<LogEntry> parse(std::istream& in) {
    std::vector<LogEntry> result;
    char* line = new char[200];
    while(in.getline(line, std::streamsize(200))) {
        String s(line);
        LogEntry newEntry(s);
        result.push_back(newEntry);
    }
    return result;
}

String LogEntry::getEntry() const {
    return entry;
}

String LogEntry::getHost() const {
    return host;
}

int LogEntry::getBytes() const {
    return number_of_bytes;
}

void output_all(std::ostream& out, const std::vector<LogEntry>& entries) { 
    for (auto& i : entries) 
        out << i.getEntry() << std::endl;
}

std::ostream& operator<<(std::ostream& out, const LogEntry& e) {
    out << e.getEntry() << std::endl;
    return out;
}

void by_host(std::ostream& out, const std::vector<LogEntry>& entries) {
    for (auto i : entries) 
        out << i.getHost() << std::endl;   
}

int byte_count(const std::vector<LogEntry> & entries) {
    int result = 0;
    for (auto i : entries) 
        result += i.getBytes();
    
    return result;
}

void output_ip(std::ostream& out, const std::vector<LogEntry>& entries) {
    std::map<String, int> m{};
    int key = 0;
    for (auto i : entries) 
        m.insert(std::make_pair(i.getHost(), key++));

    for (auto i : m)
        out << i.first << std::endl;
    
}
