#ifndef APPOINTMENT_H
#define APPOINTMENT_H


#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include "doctor.h"
#include "datetime.h"
#include "medicalrecord.h"
using namespace std;

class Appointment {
private:
    unordered_map<string, vector<Doctor*>> doctors;

public:
    void addDoctor(Doctor* doctor);

    DateTime findNearestAvailableDateTime(const string& specialization);

    const list<pair<string, DateTime>>& getAppointments(MedicalRecord& patient) const;

    bool addAppointment(MedicalRecord& patient, const string& doctorName, const DateTime& dateTime);

    void displayDoctors(const string& specialization) const;

    void displaySpecializations(const Appointment& appointment);
};

#endif /* APPOINTMENT_H */
