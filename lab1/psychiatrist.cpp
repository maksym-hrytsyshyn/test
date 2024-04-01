#include "psychiatrist.h"
#include <iostream>
#include <string>
#include <vector>
#include "datetime.h"   

using namespace std;

Psychiatrist::Psychiatrist(const string& name, const string& specialization) : Doctor(name, specialization) {}

void Psychiatrist::addSchedule(const pair<int, int> time) {
    schedule.push_back(time);
}

void Psychiatrist::displayInfo() const {
    cout << "Name: " << getName() << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "Schedule:" << endl;
    for (const auto& scheduleItem : schedule) {
        cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
    }
}

void Psychiatrist::bookAppointment(const DateTime& time) {
    cout << "Appointment booked with " << getName() << " at " << formatDate(time) << endl;
}

const vector<pair<int, int>>& Psychiatrist::getSchedule() const {
    return schedule;
}