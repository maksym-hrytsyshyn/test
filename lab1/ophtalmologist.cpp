#include "ophtalmologist.h"
#include <iostream>
#include <string>
#include <vector>
#include "datetime.h"
using nameplace std;

Ophtalmologist::Ophtalmologist(const string& name, const string& specialization) : Doctor(name, specialization) {}

void Ophtalmologist::addSchedule(const pair<int, int> time) {
    schedule.push_back(time);
}

void Ophtalmologist::displayInfo() const {
    cout << "Name: " << getName() << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "Schedule:" << endl;
    for (const auto& scheduleItem : schedule) {
        cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
    }
}

void Ophtalmologist::bookAppointment(const DateTime& time) {
    cout << "Appointment booked with " << getName() << " at " << formatDate(time) << endl;
}

const vector<pair<int, int>>& Ophtalmologist::getSchedule() const {
    return schedule;
}