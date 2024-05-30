using System;
using System.Collections.Generic;

namespace Project.Models
{
    public class MedicalRecord
    {
        public string PatientId { get; set; }
        public string FullName { get; set; }
        public Data DateOfBirth { get; set; }
        public List<KeyValuePair<string, Data>> Appointments { get; set; } = new List<KeyValuePair<string, Data>>();

        public string GetBirthdate()
        {
            return DateOfBirth.FormatDate();
        }
    }
}