#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <list>
#include <iterator>
#include <unordered_set>
using namespace std;

struct DateTime {
    int day;
    int month;
    int year;
    int hour;
    int minute;

    bool isEqual(const DateTime& other) const {
        return year == other.year && month == other.month && day == other.day &&
               hour == other.hour && minute == other.minute;
    }
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

string generateRandomID() {
    string result;
    for (int i = 0; i < 8; ++i) {
        result += to_string(rand() % 10);
    }
    return result;
}

struct MedicalRecord {
    string fullName;
    DateTime dateOfBirth;
    list<pair<string, DateTime>> appointments;

    string getBirthdate() const {
        return formatDate(dateOfBirth);
    }
};

template <typename Key, typename Value>
class MedCard {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    static const int size = 1000000;
    vector<Node*> table;

    int hash(const Key& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 10 + c) % size;
        }
    return hash;
    }

public:
    MedCard() : table(size, nullptr) {
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    ~MedCard() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    void insert(const Key& key, const Value& value) {
        int index = hash(key);
        Node* newNode = new Node(key, value);
        if (!table[index]) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    bool find(const Key& key, Value& value) {
        int index = hash(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void update(const Key& key, const Value& value) {
        int index = hash(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        cout << "Key not found in hash table" << endl;
    }


    void remove(const Key& key) {
        int index = hash(key);
        Node* current = table[index];
        Node* prev = nullptr;
        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void makeMedCard(MedicalRecord& patient) {
        cout << "Enter the patient's full name: ";
        getline(cin, patient.fullName);
        cout << "Enter the patient's date of birth (dd mm yyyy): ";
        cin >> patient.dateOfBirth.day >> patient.dateOfBirth.month >> patient.dateOfBirth.year;
        cin.ignore();
        cout << "Your patient's personal code: ";
        string patientID = generateRandomID();
        cout << patientID << endl;
        insert(patientID, patient);
        cout << "Patient card added successfully! Patient ID: " << patientID << endl;
    }

    vector<Key> getAllKeys() const {
        vector<Key> keys;
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current) {
                keys.push_back(current->key);
                current = current->next;
            }
        }
        return keys;
    }

};

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

    const list<pair<string, DateTime>>& getAppointments(MedicalRecord& patient) const {
        return patient.appointments;
    }

   bool addAppointment(MedicalRecord& patient, const string& doctorName, const DateTime& dateTime) {
    
        for (const auto& appointment : patient.appointments) {
            if (appointment.second.isEqual(dateTime)) {
                cout << "Appointment time is already taken. Please choose another time." << endl;
                return false; 
            }
        }

        patient.appointments.push_back(make_pair(doctorName, dateTime));
        return true; 
   }


    void displayDoctors(const string& specialization) const {
        for (const auto& doctor : doctors.at(specialization)) {
            doctor->displayInfo();
            cout << endl;
        }
    }

    void displaySpecializations(const Appointment& appointment) {
        unordered_set<string> specializations;
        for (const auto& pair : appointment.doctors) {
            for (Doctor* doctor : pair.second) {
                specializations.insert(doctor->getSpecialization());
            }
        }
        cout << "Available specializations:" << endl;
        for (const string& specialization : specializations) {
            cout << "- " << specialization << endl;
        }
    }

};

void fill(Appointment& appointment, MedCard<string, MedicalRecord>& medicalRecords) {

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