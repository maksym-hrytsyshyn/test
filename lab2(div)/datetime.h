#ifndef DATETIME_H
#define DATETIME_H

#include <string>
using namespace std;

struct DateTime {
    int day;
    int month;
    int year;
    int hour;
    int minute;

    bool isEqual(const DateTime& other) const;
};

string formatDate(const DateTime& date);
string getDayOfWeek(int day);

#endif /* DATETIME_H */