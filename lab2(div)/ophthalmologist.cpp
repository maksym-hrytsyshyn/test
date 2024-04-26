#include "ophthalmologist.h"
#include <iostream>
#include <string>
#include <vector>
#include "datetime.h"
using namespace std;

Ophthalmologist::Ophthalmologist(const string& name, const string& specialization) : Doctor(name, specialization) {}

void Ophthalmologist::addSchedule(const pair<int, int> time) {
    schedule.push_back(time);
}

void Ophthalmologist::displayInfo() const {
    cout << "Name: " << getName() << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "Schedule:" << endl;
    for (const auto& scheduleItem : schedule) {
        cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
    }
}

void Ophthalmologist::bookAppointment(const DateTime& time) {
    cout << "Appointment booked with " << getName() << " at " << formatDate(time) << endl;
}

const vector<pair<int, int>>& Ophthalmologist::getSchedule() const {
    return schedule;
}