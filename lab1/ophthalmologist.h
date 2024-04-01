#ifndef OPHTHALMOLOGIST_H
#define OPHTHALMOLOGIST_H

#include "doctor.h"
#include "datetime.h"
#include <vector>
#include <string>

using namespace std;

class Ophthalmologist : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:
        Ophthalmologist(const string& name, const string& specialization);
        
        void addSchedule(const pair<int, int> time);

        void displayInfo() const;

        void bookAppointment(const DateTime& time) override;

        const vector<pair<int, int>>& getSchedule() const override;
};

#endif /* OPHTHALMOLOGIST_H */
