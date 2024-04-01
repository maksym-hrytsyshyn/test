#include "surgeon.h"
#include <iostream>
#include <string>
#include <vector>
#include "datetime.h"
using namespace std;

Surgeon::Surgeon(const string& name, const string& specialization) : Doctor(name, specialization) {}

void Surgeon::addSchedule(const pair<int, int> time) {
    schedule.push_back(time);
}

void Surgeon::displayInfo() const {
    cout << "Name: " << getName() << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "Schedule:" << endl;
    for (const auto& scheduleItem : schedule) {
        cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
    }
}

void Surgeon::bookAppointment(const DateTime& time) {
    cout << "Appointment booked with " << getName() << " at " << formatDate(time) << endl;
}

const vector<pair<int, int>>& Surgeon::getSchedule() const {
    return schedule;
}