#include "entdoctor.h"
#include <iostream>
#include <string>
#include <vector>
#include "datetime.h"
using namespace std;

ENTDoctor::ENTDoctor(const string& name, const string& specialization) : Doctor(name, specialization) {}

void ENTDoctor::addSchedule(const pair<int, int> time) {
    schedule.push_back(time);
}

void ENTDoctor::displayInfo() const {
    cout << "Name: " << getName() << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "Schedule:" << endl;
    for (const auto& scheduleItem : schedule) {
        cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
    }
}

void ENTDoctor::bookAppointment(const DateTime& time) {
    cout << "Appointment booked with " << getName() << " at " << formatDate(time) << endl;
}

const vector<pair<int, int>>& ENTDoctor::getSchedule() const {
    return schedule;
}