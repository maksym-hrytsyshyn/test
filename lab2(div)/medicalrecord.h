#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <string>
#include <list>
#include "datetime.h"

using namespace std;

struct MedicalRecord {
    string fullName;
    DateTime dateOfBirth;
    list<pair<string, DateTime>> appointments;

    string getBirthdate() const;
};

#endif /* MEDICALRECORD_H */