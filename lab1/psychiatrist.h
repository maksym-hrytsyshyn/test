#ifndef PSYCHIATRIST_H
#define PSYCHIATRIST_H

#include "doctor.h"
#include <vector>
#include <string>
using namespace std;

class Psychiatrist : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:
        Psychiatrist(const string& name, const string& specialization);
        
        void addSchedule(const pair<int, int> time);

        void displayInfo() const;

        void bookAppointment(const DateTime& time) override;

        const vector<pair<int, int>>& getSchedule() const override;
};

#endif /* PSYCHIATRIST_H */