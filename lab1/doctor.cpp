#include "doctor.h"
#include <string>
using namespace std;

Doctor::Doctor(const string& name, const string& specialization) : name(name), specialization(specialization) {}

const string& Doctor::getName() const {
    return name;
}

string& Doctor::getSpecialization() const {
    return specialization;
}
