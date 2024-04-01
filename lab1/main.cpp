#include "doctor.h"
#include "datetime.h"
#include "appointment.h"
#include "fill.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    Appointment appointment;
    fill(appointment);

    cout << "Welcome! \nSelect the action" << endl;

    while (true) {
        cout << "1. Add an appointment" << endl;
        cout << "2. Display all doctors" << endl;
        cout << "3. Display all appointments" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
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
                    appointment.addAppointment(doctorName, nearestDateTime);
                    cout << "Appointment booked successfully!" << endl;
                    
                } else {
                    cout << "Appointment booking canceled." << endl;
                }
            }
    } else if (choice == 2) {
        cout << "Enter the doctor's specialization: ";
        string doctorName;
        getline(cin, doctorName);
        appointment.displayDoctors(doctorName);
    } else if (choice == 3) {
        cout << "Display all appointments" << endl;
        for (const auto& appointment : appointment.getAppointments()) {
            cout << "Doctor: " << appointment.first << ", Date: " << formatDate(appointment.second) << endl;
        }
    } else if (choice == 4) {
        cout << "Exiting program..." << endl;
        break;
    } else {
        cout << "Unfortunately, we don't have such function yet" << endl;
    }
    }

    return 0;
}
