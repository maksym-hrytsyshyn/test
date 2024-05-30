using Microsoft.AspNetCore.Mvc;
using Project.Models;
using System.Collections.Generic;
using System.Linq;

namespace Project.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class DoctorController : ControllerBase
    {
        private readonly Appointment _appointment;
        private MedCard<string, MedicalRecord> _medicalRecords;

        public DoctorController(Appointment appointment, MedCard<string, MedicalRecord> medicalRecords)
        {
            _appointment = appointment;
            _medicalRecords = medicalRecords;
        }

        [HttpGet]
        public ActionResult<IEnumerable<Doctor>> GetAllDoctors()
        {
            var allDoctors = _appointment.GetAllDoctors();
            if (!allDoctors.Any())
            {
                return NotFound("No doctors found.");
            }

            return Ok(allDoctors);
        }

        [HttpGet("{specialization}")]
        public ActionResult<IEnumerable<Doctor>> GetDoctorsBySpecialization(string specialization)
        {
            var doctorsBySpecialization = _appointment.GetDoctorsBySpecialization(specialization);
            if (!doctorsBySpecialization.Any())
            {
                return NotFound($"Doctors with specialization '{specialization}' not found.");
            }

            return Ok(doctorsBySpecialization);
        }
        
        [HttpPost("addappointment")]
        public ActionResult<string> AddAppointment(string patientId, string doctorSpecialization)
        {
            if (!_medicalRecords.Find(patientId, out var patient))
            {
                return NotFound("Patient not found.");
            }

            var nearestDateTime = _appointment.FindNearestAvailableDateTime(doctorSpecialization);

            if (nearestDateTime == DateTime.MinValue)
            {
                return BadRequest("No available appointments for this specialization.");
            }

            var appointmentData = new Data(nearestDateTime.Day, nearestDateTime.Month, nearestDateTime.Year)
            {
                Hour = nearestDateTime.Hour,
                Minute = nearestDateTime.Minute
            };

            if (_appointment.AddAppointment(patient, doctorSpecialization, appointmentData))
            {
                _medicalRecords.Update(patientId, patient);
                return Ok("Appointment booked successfully.");
            }

            return BadRequest("Appointment time is already taken. Please choose another time.");
        }

        [HttpDelete("removeappointment")]
        public ActionResult<string> RemoveAppointment(string patientId, string doctorSpecialization)
        {
            if (!_medicalRecords.Find(patientId, out var patient))
            {
                return NotFound("Patient not found.");
            }

            // Знаходимо запис до лікаря, що відповідає спеціалізації
            var appointments = patient.Appointments.Where(app => app.Key == doctorSpecialization).ToList();

            if (appointments.Count == 0)
            {
                return NotFound("Appointment not found.");
            }

            // Видаляємо перший знайдений запис
            patient.Appointments.Remove(appointments.First());

            // Оновлюємо дані пацієнта в медичній картці
            _medicalRecords.Update(patientId, patient);

            return Ok("Appointment removed successfully.");
        }


    }
}