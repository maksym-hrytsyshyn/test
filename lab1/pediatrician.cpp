#include "pediatrician.h"
#include <iostream>
#include <string>
#include <vector>
#include "datetime.h"
using namespace std;

    Pediatrician::Pediatrician(const string& name, const string& specialization) : Doctor(name, specialization) {}

    void Pediatrician::addSchedule(const pair<int, int> time) {
            schedule.push_back(time);
    }
    
    void Pediatrician::displayInfo() const {
            cout << "Name: " << getName() << endl;
            cout << "Specialization: " << specialization << endl;
            cout << "Schedule:" << endl;
            for (const auto& scheduleItem : schedule) {
                cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
             }
    }

    void Pediatrician::bookAppointment(const DateTime& time) override {
            cout << "Appointment booked with " << name << " at " << formatDate(time) << endl;
    }

    const vector<pair<int, int>>& Pediatrician::getSchedule() const override {
            return schedule;
    }