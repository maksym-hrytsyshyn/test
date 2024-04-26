#include "fill.h"
#include "pediatrician.h"
#include "surgeon.h"
#include "ophthalmologist.h"
#include "psychiatrist.h"
#include "entdoctor.h"
#include "medicalrecord.h"
#include "datetime.h"
#include "appointment.h"
#include "medcard.h"
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;


string generateRandomID() {
    string result;
    for (int i = 0; i < 8; ++i) {
        result += to_string(rand() % 10);
    }
    return result;
}

void fill(Appointment& appointment, MedCard<string, MedicalRecord>& medicalRecords) {
    Pediatrician* ped1 = new Pediatrician("Drs. Melnyk", "Pediatrics");
    ped1->addSchedule({1, 9});   // Перше число це: Понеділок = 1, ..., Неділя = 7; друге - година
    ped1->addSchedule({3, 10});
    ped1->addSchedule({5, 11});

    Pediatrician* ped2 = new Pediatrician("Dr. Kovalenko", "Pediatrics");
    ped2->addSchedule({2, 14});
    ped2->addSchedule({4, 12});
    ped2->addSchedule({6, 13});

    Surgeon* sur1 = new Surgeon("Drs. Bondarenko", "Surgery");
    sur1->addSchedule({1, 10});
    sur1->addSchedule({3, 14});
    sur1->addSchedule({5, 8});

    Surgeon* sur2 = new Surgeon("Dr. Shevchenko", "Surgery");
    sur2->addSchedule({2, 10});
    sur2->addSchedule({4, 15});
    sur2->addSchedule({6, 11});

    Ophthalmologist* oph1 = new Ophthalmologist("Drs. Boyko", "Ophthalmology");
    oph1->addSchedule({1, 14});
    oph1->addSchedule({3, 12});
    oph1->addSchedule({5, 11});

    Ophthalmologist* oph2 = new Ophthalmologist("Dr. Kovalchuk", "Ophthalmology");
    oph2->addSchedule({2, 9});
    oph2->addSchedule({4, 9});
    oph2->addSchedule({5, 17});

    Psychiatrist* psy1 = new Psychiatrist("Drs. Koval", "Psychiatry");
    psy1->addSchedule({1, 11});
    psy1->addSchedule({3, 11});
    psy1->addSchedule({5, 13});

    Psychiatrist* psy2 = new Psychiatrist("Dr. Tkachenko", "Psychiatry");
    psy2->addSchedule({2, 11});
    psy2->addSchedule({4, 12});
    psy2->addSchedule({6, 11});

    ENTDoctor* ent1 = new ENTDoctor("Drs. Kravchenko", "Otolaryngology");
    ent1->addSchedule({2, 14});
    ent1->addSchedule({3, 12});

    ENTDoctor* ent2 = new ENTDoctor("Dr. Oliinyk", "Otolaryngology");
    ent2->addSchedule({1, 10});
    ent2->addSchedule({4, 8});

    MedicalRecord patient1;
    string id1, id2, id3;
    id1 = generateRandomID();
    patient1.fullName = "Ivan Ivanenko";
    patient1.dateOfBirth = {1, 1, 2000}; 
    medicalRecords.insert(id1, patient1);  

    MedicalRecord patient2;
    id2 = generateRandomID();
    patient2.fullName = "Petro Petrenko";
    patient2.dateOfBirth = {2, 2, 1980};
    medicalRecords.insert(id2, patient2);

    MedicalRecord patient3;
    id3 = generateRandomID();
    patient3.fullName = "Olena Oleksandrenko";
    patient3.dateOfBirth = {3, 3, 1990};
    medicalRecords.insert(id3, patient3); 


    appointment.addDoctor(ped1);
    appointment.addDoctor(ped2);
    appointment.addDoctor(sur1);
    appointment.addDoctor(sur2);
    appointment.addDoctor(oph1);
    appointment.addDoctor(oph2);
    appointment.addDoctor(psy1);
    appointment.addDoctor(psy2);
    appointment.addDoctor(ent1);
    appointment.addDoctor(ent2);
}
