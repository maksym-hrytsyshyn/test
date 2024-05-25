using Microsoft.AspNetCore.Mvc;
using Project.Models;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Project.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class AppointmentsController : ControllerBase
    {
        private readonly Appointment _appointment;
        private readonly MedCard<string, MedicalRecord> _medicalRecords;

        public AppointmentsController(Appointment appointment, MedCard<string, MedicalRecord> medicalRecords)
        {
            _appointment = appointment;
            _medicalRecords = medicalRecords;
        }

        [HttpPost("create")]
        public ActionResult<string> CreateMedicalCard([FromBody] MedicalRecord patient)
        {
            _medicalRecords.MakeMedCard(patient);
            return Ok("Medical card created successfully.");
        }

        [HttpPost("book")]
        public ActionResult<string> BookAppointment(string patientId, string doctorSpecialization)
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

        [HttpGet("doctors")]
        public ActionResult<IEnumerable<string>> GetSpecializations()
        {
            var specializations = new List<string>(_appointment._doctors.Keys);
            return Ok(specializations);
        }

        [HttpGet("doctors/{specialization}")]
        public ActionResult GetDoctorsBySpecialization(string specialization)
        {
            if (!_appointment._doctors.ContainsKey(specialization))
            {
                return NotFound("Specialization not found.");
            }

            var doctors = _appointment._doctors[specialization]
                .Select(doctor => new { Name = doctor.GetName(), Specialization = doctor.GetSpecialization() });
            return Ok(doctors);
        }

        [HttpGet("patient/{patientId}")]
        public ActionResult GetAppointments(string patientId)
        {
            if (!_medicalRecords.Find(patientId, out var patient))
            {
                return NotFound("Patient not found.");
            }

            return Ok(patient.Appointments);
        }

        [HttpDelete("patient/{patientId}/remove")]
        public ActionResult RemoveMedicalCard(string patientId)
        {
            if (!_medicalRecords.Find(patientId, out var patient))
            {
                return NotFound("Patient not found.");
            }

            _medicalRecords.Remove(patientId);
            return Ok("Medical card removed successfully.");
        }

        [HttpGet("patients")]
        public ActionResult GetAllMedicalCards()
        {
            var medicalCards = new List<object>();
            foreach (var key in _medicalRecords.GetAllKeys())
            {
                if (_medicalRecords.Find(key, out var record))
                {
                    medicalCards.Add(new { Id = key, record.FullName });
                }
            }
            return Ok(medicalCards);
        }
    }
}
