#include "appointment.h"
#include "doctor.h"
#include "datetime.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <ctime>
using namespace std;

void Appointment::addDoctor(Doctor* doctor) {
    doctors[doctor->getSpecialization()].push_back(doctor);
}

DateTime Appointment::findNearestAvailableDateTime(const string& specialization) {
        time_t t = time(nullptr);
        tm currentTime = *localtime(&t);

        int currentDayOfWeek = currentTime.tm_wday == 0 ? 7 : currentTime.tm_wday; 
        int currentHour = currentTime.tm_hour;
        int currentMinute = currentTime.tm_min;

        bool found = false;
        for (Doctor* doctor : doctors[specialization]) {
            for (const auto& schedule : doctor->getSchedule()) {
                int targetDayOfWeek = schedule.first;
                int targetHour = schedule.second;

                if (targetDayOfWeek > currentDayOfWeek || 
                    (targetDayOfWeek == currentDayOfWeek && targetHour > currentHour) ||
                    (targetDayOfWeek == currentDayOfWeek && targetHour == currentHour && schedule.second > currentMinute)) {
                    int daysToAdd = targetDayOfWeek - currentDayOfWeek;
                    if (daysToAdd < 0) {
                        daysToAdd += 7;
                    }

                    time_t nextTime = t + daysToAdd * 24 * 3600; 
                    tm nextDate = *localtime(&nextTime);

                    DateTime nearestDate;
                    nearestDate.day = nextDate.tm_mday;
                    nearestDate.month = nextDate.tm_mon + 1;
                    nearestDate.year = nextDate.tm_year + 1900;
                    nearestDate.hour = targetHour;
                    nearestDate.minute = 00;

                    found = true;
                    return nearestDate;
                }
            }
        }
        if (!found && !doctors[specialization].empty()) {
            int daysToAdd = 7 - currentDayOfWeek + doctors[specialization].front()->getSchedule().front().first;
            time_t nextTime = t + daysToAdd * 24 * 3600; 
            tm nextDate = *localtime(&nextTime);

            DateTime nearestDate;
            nearestDate.day = nextDate.tm_mday;
            nearestDate.month = nextDate.tm_mon + 1;
            nearestDate.year = nextDate.tm_year + 1900;
            nearestDate.hour = doctors[specialization].front()->getSchedule().front().second;
            nearestDate.minute = 00;

            return nearestDate;
        }

        return {0, 0, 0}; 
    }

    const list<pair<string, DateTime>>& Appointment::getAppointments() const {
        return appointments;
    }

    void Appointment::addAppointment(const string& doctorName, const DateTime& dateTime) {
        appointments.push_back(make_pair(doctorName, dateTime));
    }

    void Appointment::displayDoctors(const string& specialization) const {
    for (const auto& doctor : doctors.at(specialization)) {
        doctor->displayInfo();
        cout << endl;
    }
}

