#ifndef PEDIATRICIAN_H
#define PEDIATRICIAN_H

#include "doctor.h"
#include <vector>
#include <string>
#include <iostream>
#include "datetime.h"

using namespace std;

class Pediatrician : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:
        Pediatrician(const string& name, const string& specialization);

        void addSchedule(const pair<int, int> time);

        void displayInfo() const;

        void bookAppointment(const DateTime& time) override;

        const vector<pair<int, int>>& getSchedule() const override;
};

#endif /* Pediatrician_H */