using NUnit.Framework;
using System.Collections.Generic;
using System.IO;
using Project.Models;

namespace Project.Tests
{
    [TestFixture]
    public class OphthalmologistTests
    {
        private Ophthalmologist _ophthalmologist;

        [SetUp]
        public void SetUp()
        {
            _ophthalmologist = new Ophthalmologist("Dr. Smith", "Ophthalmology");
        }

        [Test]
        public void AddSchedule_ShouldAddScheduleToOphthalmologist()
        {
            // Arrange
            var scheduleItem = new KeyValuePair<int, int>(2, 14); // Tuesday at 14:00

            // Act
            _ophthalmologist.AddSchedule(scheduleItem);

            // Assert
            Assert.Contains(scheduleItem, _ophthalmologist.GetSchedule());
        }

        [Test]
        public void GetSchedule_ShouldReturnCorrectSchedule()
        {
            // Arrange
            var schedule1 = new KeyValuePair<int, int>(2, 14); // Tuesday at 14:00
            var schedule2 = new KeyValuePair<int, int>(3, 10); // Wednesday at 10:00
            _ophthalmologist.AddSchedule(schedule1);
            _ophthalmologist.AddSchedule(schedule2);

            // Act
            var schedule = _ophthalmologist.GetSchedule();

            // Assert
            Assert.AreEqual(2, schedule.Count);
            Assert.AreEqual(schedule1, schedule[0]);
            Assert.AreEqual(schedule2, schedule[1]);
        }

        [Test]
        public void DisplayInfo_ShouldOutputCorrectInformation()
        {
            // Arrange
            var schedule1 = new KeyValuePair<int, int>(2, 14); // Tuesday at 14:00
            var schedule2 = new KeyValuePair<int, int>(3, 10); // Wednesday at 10:00
            _ophthalmologist.AddSchedule(schedule1);
            _ophthalmologist.AddSchedule(schedule2);
            var expectedOutput = $"Name: Dr. Smith\nSpecialization: Ophthalmology\nSchedule:\nTuesday at 14:00\nWednesday at 10:00\n";

            // Redirect console output
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _ophthalmologist.DisplayInfo();

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

            // Redirect console output
            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _ophthalmologist.BookAppointment(appointmentTime);

                // Assert
                var result = sw.ToString().Replace("\r", ""); // Remove carriage return character for cross-platform compatibility
                Assert.AreEqual(expectedOutput, result);
            }
        }
    }
}
