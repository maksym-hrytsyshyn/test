using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.IO;
using Project.Models;

namespace Project.Tests
{
    [TestFixture]
    public class EnTdoctorTests
    {
        private EnTdoctor _doctor;

        [SetUp]
        public void SetUp()
        {
            _doctor = new EnTdoctor("Dr. Jones", "ENT");
        }

        [Test]
        public void AddSchedule_ShouldAddScheduleToEnTdoctor()
        {
            // Arrange
            var scheduleItem = new KeyValuePair<int, int>(1, 9); // Monday at 9:00

            // Act
            _doctor.AddSchedule(scheduleItem);

            // Assert
            var schedule = _doctor.GetSchedule();
            Assert.Contains(scheduleItem, schedule);
        }

        [Test]
        public void GetSchedule_ShouldReturnCorrectSchedule()
        {
            // Arrange
            var schedule1 = new KeyValuePair<int, int>(1, 9); // Monday at 9:00
            var schedule2 = new KeyValuePair<int, int>(3, 14); // Wednesday at 14:00
            _doctor.AddSchedule(schedule1);
            _doctor.AddSchedule(schedule2);

            // Act
            var schedule = _doctor.GetSchedule();

            // Assert
            Assert.AreEqual(2, schedule.Count);
            Assert.Contains(schedule1, schedule);
            Assert.Contains(schedule2, schedule);
        }

        [Test]
        public void DisplayInfo_ShouldOutputCorrectInformation()
        {
            // Arrange
            var schedule1 = new KeyValuePair<int, int>(1, 9); // Monday at 9:00
            var schedule2 = new KeyValuePair<int, int>(3, 14); // Wednesday at 14:00
            _doctor.AddSchedule(schedule1);
            _doctor.AddSchedule(schedule2);
            var expectedOutput = $"Name: Dr. Jones\nSpecialization: ENT\nSchedule:\nMonday at 9:00\nWednesday at 14:00\n";

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _doctor.DisplayInfo();

                // Assert
                var result = sw.ToString().Replace("\r", ""); // Remove carriage return character for cross-platform compatibility
                Assert.AreEqual(expectedOutput, result);
            }
        }

        [Test]
        public void BookAppointment_ShouldOutputCorrectBookingMessage()
        {
            // Arrange
            var appointmentTime = new Data(15, 6, 2024) { Hour = 10, Minute = 0 };
            var expectedOutput = $"Appointment booked with Dr. Jones at {appointmentTime}\n";

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _doctor.BookAppointment(appointmentTime);

                // Assert
                var result = sw.ToString().Replace("\r", ""); // Remove carriage return character for cross-platform compatibility
                Assert.AreEqual(expectedOutput, result);
            }
        }

        [Test]
        public void AddSchedule_And_DisplayInfo_IntegrationTest()
        {
            // Arrange
            var schedule1 = new KeyValuePair<int, int>(2, 10); // Tuesday at 10:00
            var schedule2 = new KeyValuePair<int, int>(4, 12); // Thursday at 12:00
            _doctor.AddSchedule(schedule1);
            _doctor.AddSchedule(schedule2);
            var expectedOutput = $"Name: Dr. Jones\nSpecialization: ENT\nSchedule:\nTuesday at 10:00\nThursday at 12:00\n";

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _doctor.DisplayInfo();

                // Assert
                var result = sw.ToString().Replace("\r", ""); // Remove carriage return character for cross-platform compatibility
                Assert.AreEqual(expectedOutput, result);
            }
        }
    }
}
