#ifndef FILL_H
#define FILL_H

#include "appointment.h"
#include "medcard.h"
#include "medicalrecord.h"
#include <string>

string generateRandomID();

void fill(Appointment& appointment, MedCard<string, MedicalRecord>& medicalRecords);

#endif /* FILL_H */
