#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <unordered_map>
#include <list>
using namespace std;

struct DateTime {
    int day;
    int month;
    int year;
    int hour;
    int minute;
};

string formatDate(const DateTime& date) {
    return to_string(date.day) + "." + to_string(date.month) + "." + to_string(date.year) + " " + to_string(date.hour) + ":" + to_string(date.minute);
}

string getDayOfWeek(int day) {
    switch(day) {
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";
        case 7:
            return "Sunday";
        default:
            return "Unknown";
    }
}

class Doctor {
    protected:
        string name;
        string specialization;

    public:
        Doctor(const string& name, const string& specialization) : name(name), specialization(specialization) {}
        
        virtual ~Doctor() {}

        const string& getName() const {
            return name;
        }

        const string& getSpecialization() const {
            return specialization;
        }

        virtual void displayInfo() const = 0; 
        virtual const vector<pair<int, int>>& getSchedule() const = 0;
        virtual void bookAppointment(const DateTime& time) = 0;
};

class Pediatrician : public Doctor {
    private:
        vector<pair<int, int>> schedule;
    public:
        Pediatrician(const string& name, const string& specialization) : Doctor(name, specialization) {}

        void addSchedule(const pair<int, int> time) {
            schedule.push_back(time);
        }

        void displayInfo() const {
            cout << "Name: " << getName() << endl;
            cout << "Specialization: " << specialization << endl;
            cout << "Schedule:" << endl;
            for (const auto& scheduleItem : schedule) {
                cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
             }
        }

        void bookAppointment(const DateTime& time) override {
            cout << "Appointment booked with " << name << " at " << formatDate(time) << endl;
        }

        const vector<pair<int, int>>& getSchedule() const override {
            return schedule;
        }
};

class Surgeon : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:
        Surgeon(const string& name, const string& specialization) : Doctor(name, specialization) {}
        
        void addSchedule(const pair<int, int> time) {
            schedule.push_back(time);
        }
        
        void displayInfo() const {
            cout << "Name: " << getName() << endl;
            cout << "Specialization: " << specialization << endl;
            cout << "Schedule:" << endl;
            for (const auto& scheduleItem : schedule) {
                cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
            }
        }
        

        void bookAppointment(const DateTime& time) override {
            cout << "Appointment booked with " << name << " at " << formatDate(time) << endl;
        }

        const vector<pair<int, int>>& getSchedule() const override{
            return schedule;
        }
};

class Ophthalmologist : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:
        Ophthalmologist(const string& name, const string& specialization) : Doctor(name, specialization) {}
        
        void addSchedule(const pair<int, int> time) {
            schedule.push_back(time);
        }

        void displayInfo() const {
            cout << "Name: " << getName() << endl;
            cout << "Specialization: " << specialization << endl;
            cout << "Schedule:" << endl;
            for (const auto& scheduleItem : schedule) {
                cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
            }
        }

        void bookAppointment(const DateTime& time) override {
            cout << "Appointment booked with " << name << " at " << formatDate(time) << endl;
        }

        const vector<pair<int, int>>& getSchedule() const override {
            return schedule;
        }
};

class Psychiatrist : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:
        Psychiatrist(const string& name, const string& specialization) : Doctor(name, specialization) {}
        
        void addSchedule(const pair<int, int> time) {
            schedule.push_back(time);
        }

        void displayInfo() const {
            cout << "Name: " << getName() << endl;
            cout << "Specialization: " << specialization << endl;
            cout << "Schedule:" << endl;
            for (const auto& scheduleItem : schedule) {
                cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
            }
        }

        void bookAppointment(const DateTime& time) override {
            cout << "Appointment booked with " << name << " at " << formatDate(time) << endl;
        }

        const vector<pair<int, int>>& getSchedule() const override {
            return schedule;
        }
};

class ENTdoctor : public Doctor {
    private:
        vector<pair<int, int>> schedule;

    public:
        ENTdoctor(const string& name, const string& specialization) : Doctor(name, specialization) {}
        
        void addSchedule(const pair<int, int> time) {
            schedule.push_back(time);
        }

        void displayInfo() const {
            cout << "Name: " << getName() << endl;
            cout << "Specialization: " << specialization << endl;
            cout << "Schedule:" << endl;
            for (const auto& scheduleItem : schedule) {
                cout << getDayOfWeek(scheduleItem.first) << " at " << scheduleItem.second << ":00" << endl;
            }
        }

        void bookAppointment(const DateTime& time) override {
            cout << "Appointment booked with " << name << " at " << formatDate(time) << endl;
        }

        const vector<pair<int, int>>& getSchedule() const override {
            return schedule;
        }

};

class Appointment {
private:
    unordered_map<string, vector<Doctor*>> doctors;

public:
    list<pair<string, DateTime>> appointments;

    void addDoctor(Doctor* doctor) {
        doctors[doctor->getSpecialization()].push_back(doctor);
    }

    DateTime findNearestAvailableDateTime(const string& specialization) {
        time_t t = time(nullptr);
        tm currentTime = *localtime(&t);

        int currentDayOfWeek = currentTime.tm_wday == 0 ? 7 : currentTime.tm_wday; 
        int currentHour = currentTime.tm_hour;
        int currentMinute = currentTime.tm_min;

        bool found = false;
        for (Doctor* doctor : doctors[specialization]) {
            for (const auto& schedule : doctor->getSchedule()) {
                int targetDayOfWeek = schedule.first;
                int targetHour = schedule.second;

                if (targetDayOfWeek > currentDayOfWeek || 
                    (targetDayOfWeek == currentDayOfWeek && targetHour > currentHour) ||
                    (targetDayOfWeek == currentDayOfWeek && targetHour == currentHour && schedule.second > currentMinute)) {
                    int daysToAdd = targetDayOfWeek - currentDayOfWeek;
                    if (daysToAdd < 0) {
                        daysToAdd += 7;
                    }

                    time_t nextTime = t + daysToAdd * 24 * 3600; 
                    tm nextDate = *localtime(&nextTime);

                    DateTime nearestDate;
                    nearestDate.day = nextDate.tm_mday;
                    nearestDate.month = nextDate.tm_mon + 1;
                    nearestDate.year = nextDate.tm_year + 1900;
                    nearestDate.hour = targetHour;
                    nearestDate.minute = 00;

                    found = true;
                    return nearestDate;
                }
            }
        }

        if (!found && !doctors[specialization].empty()) {
            int daysToAdd = 7 - currentDayOfWeek + doctors[specialization].front()->getSchedule().front().first;
            time_t nextTime = t + daysToAdd * 24 * 3600; 
            tm nextDate = *std::localtime(&nextTime);

            DateTime nearestDate;
            nearestDate.day = nextDate.tm_mday;
            nearestDate.month = nextDate.tm_mon + 1;
            nearestDate.year = nextDate.tm_year + 1900;
            nearestDate.hour = doctors[specialization].front()->getSchedule().front().second;
            nearestDate.minute = 00;

            return nearestDate;
        }

        return {0, 0, 0}; 
    }

    const list<pair<string, DateTime>>& getAppointments() const {
        return appointments;
    }

    void addAppointment(const string& doctorName, const DateTime& dateTime) {
        appointments.push_back(make_pair(doctorName, dateTime));
    }

    void displayDoctors(const string& specialization) const {
    for (const auto& doctor : doctors.at(specialization)) {
        doctor->displayInfo();
        cout << endl;
    }
}
};

void fill(Appointment& appointment) {
    Pediatrician* ped1 = new Pediatrician("Drs. Melnyk", "Pediatrics");
        ped1->addSchedule({1, 9});   // Перше число це: Понеділок = 1, ..., Неділя = 7; друге - година
        ped1->addSchedule({3, 10});
        ped1->addSchedule({5,11});

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

    ENTdoctor* ent1 = new ENTdoctor("Drs. Kravchenko", "Otolaryngology");
        ent1->addSchedule({2, 14});
        ent1->addSchedule({3, 12});

    ENTdoctor* ent2 = new ENTdoctor("Dr. Oliinyk", "Otolaryngology");
        ent2->addSchedule({1, 10});
        ent2->addSchedule({4, 8});


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
