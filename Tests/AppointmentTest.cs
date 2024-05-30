using NUnit.Framework;
using System;
using System.Collections.Generic;
using Project.Models;

namespace Project.Tests
{
    [TestFixture]
    public class AppointmentTests
    {
        private Appointment _appointment;
        private MedicalRecord _medicalRecord;

        [SetUp]
        public void SetUp()
        {
            _appointment = new Appointment();
            _medicalRecord = new MedicalRecord();
        }

        [Test]
        public void AddDoctor_WhenCalled_ShouldAddDoctorToList()
        {
            // Arrange
            var doctor = new Pediatrician("Dr. Smith", "Pediatrics");

            // Act
            _appointment.AddDoctor(doctor);

            // Assert
            Assert.IsTrue(_appointment._doctors.ContainsKey("Pediatrics"));
            Assert.Contains(doctor, _appointment._doctors["Pediatrics"]);
        }

        [Test]
        public void AddDoctor_WhenSpecializationNotExists_ShouldCreateNewSpecialization()
        {
            // Arrange
            var doctor = new Pediatrician("Dr. Smith", "Pediatrics");

            // Act
            _appointment.AddDoctor(doctor);

            // Assert
            Assert.IsTrue(_appointment._doctors.ContainsKey("Pediatrics"));
        }

        [Test]
        public void FindNearestAvailableDateTime_WhenDoctorsAvailable_ShouldReturnNextAvailableDateTime()
        {
            // Arrange
            var doctor = new Pediatrician("Dr. Smith", "Pediatrics");
            doctor.AddSchedule(new KeyValuePair<int, int>(2, 10)); // Monday at 10 AM
            _appointment.AddDoctor(doctor);

            // Act
            var nextAvailableDateTime = _appointment.FindNearestAvailableDateTime("Pediatrics");

            // Assert
            // Assuming today is Monday
            var expectedDateTime = DateTime.Today.AddDays(1).AddHours(10); // Next Monday at 10 AM
               Assert.AreEqual(expectedDateTime, nextAvailableDateTime);
        }

        [Test]
        public void GetAppointments_ShouldReturnAppointmentsFromPatient()
        {
            // Arrange
            var dateTime = new Data(2024, 5, 29);
            _medicalRecord.Appointments.Add(new KeyValuePair<string, Data>("Dr. Smith", dateTime));

            // Act
            var appointments = _appointment.GetAppointments(_medicalRecord);

            // Assert
            Assert.AreEqual(1, appointments.Count);
            Assert.Contains(new KeyValuePair<string, Data>("Dr. Smith", dateTime), appointments);
        }

        [Test]
        public void AddAppointment_WhenAppointmentTimeIsTaken_ShouldReturnFalse()
        {
            // Arrange
            var dateTime = new Data(2024, 5, 29);
            _medicalRecord.Appointments.Add(new KeyValuePair<string, Data>("Dr. Smith", dateTime));

            // Act
            var result = _appointment.AddAppointment(_medicalRecord, "Dr. Smith", dateTime);

            // Assert
            Assert.IsFalse(result);
        }

        [Test]
        public void DisplayDoctors_WhenSpecializationExists_ShouldDisplayDoctorInfo()
        {
            // Arrange
            var doctor = new Pediatrician("Dr. Smith", "Pediatrics");
            _appointment.AddDoctor(doctor);

            // Act & Assert
            Assert.DoesNotThrow(() => _appointment.DisplayDoctors("Pediatrics"));
        }

        [Test]
        public void DisplaySpecializations_WhenDoctorsExist_ShouldDisplaySpecializations()
        {
            // Arrange
            var doctor = new Pediatrician("Dr. Smith", "Pediatrics");
            _appointment.AddDoctor(doctor);

            // Act & Assert
            Assert.DoesNotThrow(() => _appointment.DisplaySpecializations(_appointment));
        }
    }
}