namespace Project.Models;

public class Appointment
{
    public Dictionary<string, List<Doctor>> _doctors = new Dictionary<string, List<Doctor>>();

    public void AddDoctor(Doctor doctor)
    {
        string specialization = doctor.GetSpecialization();
        if (!_doctors.ContainsKey(specialization))
        {
            _doctors[specialization] = new List<Doctor>();
        }
        _doctors[specialization].Add(doctor);
    }

    public DateTime FindNearestAvailableDateTime(string specialization)
    {
        DateTime currentTime = DateTime.Now;
        int currentDayOfWeek = (int)currentTime.DayOfWeek == 0 ? 7 : (int)currentTime.DayOfWeek;
        int currentHour = currentTime.Hour;
        int currentMinute = currentTime.Minute;

        bool found = false;
        foreach (Doctor doctor in _doctors[specialization])
        {
            foreach (var schedule in doctor.GetSchedule())
            {
                int targetDayOfWeek = schedule.Key;
                int targetHour = schedule.Value;

                if (targetDayOfWeek > currentDayOfWeek ||
                    (targetDayOfWeek == currentDayOfWeek && targetHour > currentHour) ||
                    (targetDayOfWeek == currentDayOfWeek && targetHour == currentHour && schedule.Value > currentMinute))
                {
                    int daysToAdd = targetDayOfWeek - currentDayOfWeek;
                    if (daysToAdd < 0)
                    {
                        daysToAdd += 7;
                    }

                    DateTime nextDate = currentTime.AddDays(daysToAdd);
                    nextDate = nextDate.Date + TimeSpan.FromHours(targetHour);

                    found = true;
                    return nextDate;
                }
            }
        }

        if (!found && _doctors.ContainsKey(specialization) && _doctors[specialization].Count > 0)
        {
            int daysToAdd = 7 - currentDayOfWeek + _doctors[specialization][0].GetSchedule()[0].Key;
            DateTime nextDate = currentTime.AddDays(daysToAdd);
            nextDate = nextDate.Date + TimeSpan.FromHours(_doctors[specialization][0].GetSchedule()[0].Value);

            return nextDate;
        }

        return DateTime.MinValue;
    }

    public List<KeyValuePair<string, Data>> GetAppointments(MedicalRecord patient)
    {
        return patient.Appointments;
    }

    public bool AddAppointment(MedicalRecord patient, string doctorName, Data dateTime)
    {
        foreach (var appointment in patient.Appointments)
        {
            if (appointment.Value == dateTime)
            {
                Console.WriteLine("Appointment time is already taken. Please choose another time.");
                return false;
            }
        }

        patient.Appointments.Add(new KeyValuePair<string, Data>(doctorName, dateTime));
        return true;
    }

    public IEnumerable<Doctor> GetAllDoctors()
    {
        return _doctors.Values.SelectMany(doctors => doctors);
    }

    public IEnumerable<Doctor> GetDoctorsBySpecialization(string specialization)
    {
        if (_doctors.ContainsKey(specialization))
        {
            return _doctors[specialization];
        }
        return Enumerable.Empty<Doctor>();
    }
}
