using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.IO;
using Project.Models;

namespace Project.Tests
{
    [TestFixture]
    public class SurgeonTests
    {
        private Surgeon _surgeon;

        [SetUp]
        public void SetUp()
        {
            _surgeon = new Surgeon("Dr. Smith", "Surgery");
        }

        [Test]
        public void AddSchedule_ShouldAddScheduleToSurgeon()
        {
            // Arrange
            var scheduleItem = new KeyValuePair<int, int>(1, 10); // Monday at 10:00

            // Act
            _surgeon.AddSchedule(scheduleItem);

            // Assert
            var schedule = _surgeon.GetSchedule();
            Assert.Contains(scheduleItem, schedule);
        }

        [Test]
        public void GetSchedule_ShouldReturnCorrectSchedule()
        {
            // Arrange
            var schedule1 = new KeyValuePair<int, int>(1, 10); // Monday at 10:00
            var schedule2 = new KeyValuePair<int, int>(3, 11); // Wednesday at 11:00
            _surgeon.AddSchedule(schedule1);
            _surgeon.AddSchedule(schedule2);

            // Act
            var schedule = _surgeon.GetSchedule();

            // Assert
            Assert.AreEqual(2, schedule.Count);
            Assert.Contains(schedule1, schedule);
            Assert.Contains(schedule2, schedule);
        }

        [Test]
        public void DisplayInfo_ShouldOutputCorrectInformation()
        {
            // Arrange
            var schedule1 = new KeyValuePair<int, int>(1, 10); // Monday at 10:00
            var schedule2 = new KeyValuePair<int, int>(3, 11); // Wednesday at 11:00
            _surgeon.AddSchedule(schedule1);
            _surgeon.AddSchedule(schedule2);
            var expectedOutput = $"Name: Dr. Smith\nSpecialization: Surgery\nSchedule:\nMonday at 10:00\nWednesday at 11:00\n";

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _surgeon.DisplayInfo();

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
            var expectedOutput = $"Appointment booked with Dr. Smith at {appointmentTime}\n";

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _surgeon.BookAppointment(appointmentTime);

                // Assert
                var result = sw.ToString().Replace("\r", ""); // Remove carriage return character for cross-platform compatibility
                Assert.AreEqual(expectedOutput, result);
            }
        }
    }
}
