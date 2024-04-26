#include "doctor.h"
#include "datetime.h"
#include "appointment.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "medicalrecord.h"
#include "medcard.h"
#include "fill.h"

using namespace std;

int main() {
    Appointment appointment;
    MedCard<string, MedicalRecord> medicalRecords;
    srand(time(0)); 
    fill(appointment, medicalRecords);

    cout << "Welcome!" << endl;

    cout << "Please, make a medical card for the patient." << endl;
    MedicalRecord patient;
    medicalRecords.makeMedCard(patient);
    cin.ignore();

    while (true) {
        cout << "1. Add an appointment" << endl;
        cout << "2. Display all doctors" << endl;
        cout << "3. Display all appointments \nYou can remove an appointment there" << endl;
        cout << "4. Remove the medical card" << endl;
        cout << "5. See all medical cards" << endl;
        cout << "6. Display the medical card" << endl;
        cout << "7. Exit" << endl;

        int choice;
        cin.ignore();
        cout << "Enter your choice: ";
        cin >> choice;
        

        if (choice == 1) {
            string patientID;
            cout << "Enter the patient's ID: ";
            cin >> patientID;
            cin.ignore();

            if (medicalRecords.find(patientID, patient)) {
                appointment.displaySpecializations(appointment);
                cout << "Enter the doctor's specialization: ";
                string doctorName;
                getline(cin, doctorName);

                DateTime nearestDateTime = appointment.findNearestAvailableDateTime(doctorName);

                if (nearestDateTime.day == 0) {
                    cout << "Sorry, there are no available appointments for this doctor." << endl;
                } else {
                    cout << "The nearest available appointment for " << doctorName << " is on "
                        << nearestDateTime.day << "/" << nearestDateTime.month << "/" << nearestDateTime.year << " " << nearestDateTime.hour << ":00." << endl;

                    cout << "Do you want to book this appointment? (y/n): ";
                    char choice;
                    cin >> choice;

                    if (choice == 'y') {
                        DateTime appointmentTime = nearestDateTime;
                        if (medicalRecords.find(patientID, patient)) {
                            if (appointment.addAppointment(patient, doctorName, appointmentTime)) {
                                medicalRecords.update(patientID, patient);
                            } else {
                                cout << "Unable to add record to the appointments list. Please check the appointment time and try again." << endl;
                            }
                        } else {
                            cout << "Patient with the given ID not found in base" << endl;
}

                        cout << "Appointment booked successfully!" << endl;
                        
                    } else {
                        cout << "Appointment booking canceled." << endl;
                    }
                }
            } else cout << "Patient not found!" << endl;

            cin.ignore();

        } else if (choice == 2) {
            appointment.displaySpecializations(appointment);
            cout << "Enter the doctor's specialization: ";
            string doctorName;
            cin.ignore();
            getline(cin, doctorName);
            appointment.displayDoctors(doctorName);
            cout << endl;

            cin.ignore();
        
        } else if (choice == 3) {
            string patientID;
            cout << "Enter the patient's ID: ";
            cin >> patientID;
            cin.ignore();

            if (medicalRecords.find(patientID, patient)) {
                cout << "Displaying all appointments: " << endl;
                if (!patient.appointments.empty()) {
                    int i = 1;
                    for (const auto& appointment : patient.appointments) {
                        cout << i << ". Doctor: " << appointment.first << ", Date: " << formatDate(appointment.second) << endl;
                        i++;
                    }
                } else {
                    cout << "No appointments found for this patient." << endl;
                }

                cout << "Do you want to remove an appointment? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'y') {
                    cout << "Enter the number of the appointment you want to remove: ";
                    int choice;
                    cin >> choice;
                    if (choice > 0 && choice <= patient.appointments.size()) {
                        auto it = next(patient.appointments.begin(), choice - 1);
                        patient.appointments.erase(it);
                        medicalRecords.update(patientID, patient);
                        cout << "Appointment number " << choice << " has been removed." << endl;
                        for (const auto& appointment : appointment.getAppointments(patient)) {
                            cout << "Doctor: " << appointment.first << ", Date: " << formatDate(appointment.second) << endl;
                        }
                    } else {
                        cout << "Invalid choice!" << endl;
                    } 
                } 
            } else cout << "Patient not found!" << endl;

            cin.ignore();

        } else if (choice == 4) {
            string patientID;
            cout << "Enter the patient's ID: ";
            cin >> patientID;
            cin.ignore();

            if (medicalRecords.find(patientID, patient)) {
                medicalRecords.remove(patientID);
                cout << "Patient card removed successfully!" << endl;
            } else cout << "Patient not found!" << endl;

        } else if (choice == 5) {
            cout << "All medical cards: " << endl;
            for (const auto& key : medicalRecords.getAllKeys()) {
                MedicalRecord record;
                if (medicalRecords.find(key, record)) {
                    cout << "ID: " << key << ", Повне ім'я: " << record.fullName << endl;
                } else {
                    cout << "Patient with ID " << key << " not found!" << endl;
                }
            }
            cin.ignore();

        } else if (choice == 6) {
            string patientID;
            cout << "Enter the patient's ID: ";
            cin >> patientID;
            cin.ignore();

            if (medicalRecords.find(patientID, patient)) {
                cout << "Patient ID: " << patientID << endl;
                cout << "Full name: " << patient.fullName << endl;
                cout << "Date of birth: " << patient.getBirthdate() << endl;
                cout << "Appointments: " << endl;
                for (const auto& appointment : appointment.getAppointments(patient)) {
                    cout << "Doctor: " << appointment.first << ", Date: " << formatDate(appointment.second) << endl;
                }
            } else cout << "Patient not found!" << endl;

            cin.ignore();

        } else if (choice == 7) {
            cout << "Exiting program..." << endl;
            break;
        } else {
            cout << "Unfortunately, we don't have such function yet" << endl;
        }
    }
    return 0;
}
