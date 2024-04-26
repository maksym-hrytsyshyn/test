#include "datetime.h"
#include <string>
using namespace std;

bool DateTime::isEqual(const DateTime& other) const {
        return year == other.year && month == other.month && day == other.day &&
               hour == other.hour && minute == other.minute;
    }
    
string formatDate(const DateTime& date) {
    return to_string(date.day) + "." + to_string(date.month) + "." + to_string(date.year) + " " + to_string(date.hour) + ":" + to_string(date.minute);
}

string getDayOfWeek(int day) {
    switch(day) {
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";
        case 7:
            return "Sunday";
        default:
            return "Unknown";
    }
}
