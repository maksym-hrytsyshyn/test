#include "medicalrecord.h"
#include <string>
#include "datetime.h"
using namespace std;    

string MedicalRecord::getBirthdate() const {
    return formatDate(dateOfBirth);
}