#ifndef ENTDOCTOR_H
#define ENTDOCTOR_H

#include "doctor.h"
#include "datetime.h"
#include <vector>
#include <string>
using namespace std;

class ENTDoctor : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:

        ENTDoctor(const string& name, const string& specialization);
        
        void addSchedule(const pair<int, int> time);

        void displayInfo() const;

        void bookAppointment(const DateTime& time) override;

        const vector<pair<int, int>>& getSchedule() const override;
};

#endif /* ENTDOCTOR_H */