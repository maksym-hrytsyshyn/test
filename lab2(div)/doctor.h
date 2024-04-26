#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <vector>
#include "datetime.h"

using namespace std;

class Doctor {
    protected:
        string name;
        string specialization;

    public:
        Doctor(const string& name, const string& specialization);
        
        virtual ~Doctor() {}

        const string& getName() const;

        const string& getSpecialization() const;

        virtual void displayInfo() const = 0; 
        virtual const vector<pair<int, int>>& getSchedule() const = 0;
        virtual void bookAppointment(const DateTime& time) = 0;
};

#endif