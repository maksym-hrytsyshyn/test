#ifndef APPOINTMENT_H
#define APPOINTMENT_H


#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include "doctor.h"
#include "datetime.h"
using namespace std;

class Appointment {
private:
    unordered_map<string, vector<Doctor*>> doctors;

public:
    list<pair<string, DateTime>> appointments;

    void addDoctor(Doctor* doctor);

    DateTime findNearestAvailableDateTime(const string& specialization);

    const list<pair<string, DateTime>>& getAppointments() const;

    void addAppointment(const string& doctorName, const DateTime& dateTime);

    void displayDoctors(const string& specialization) const;
};

#endif /* APPOINTMENT_H */
