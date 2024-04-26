#ifndef SURGEON_H
#define SURGEON_H

#include "doctor.h"
#include <vector>
#include <string>
using namespace std;

class Surgeon : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:
        Surgeon(const string& name, const string& specialization);
        
        void addSchedule(const pair<int, int> time);
        
        void displayInfo() const;
        

        void bookAppointment(const DateTime& time) override;

        const vector<pair<int, int>>& getSchedule() const override;
};

#endif