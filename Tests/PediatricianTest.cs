using NUnit.Framework;
using System.Collections.Generic;
using System.IO;
using Project.Models;


namespace Project.Tests
{
    [TestFixture]
    public class PediatricianTests
    {
        private Pediatrician _pediatrician;

        [SetUp]
        public void SetUp()
        {
            _pediatrician = new Pediatrician("Dr. Jane Doe", "Pediatrics");
        }

        [Test]
        public void AddSchedule_ShouldAddScheduleToPediatrician()
        {
            // Arrange
            var scheduleItem = new KeyValuePair<int, int>(1, 9); // Monday at 9:00

            // Act
            _pediatrician.AddSchedule(scheduleItem);

            // Assert
            var schedule = _pediatrician.GetSchedule();
            Assert.Contains(scheduleItem, schedule);
        }

        [Test]
        public void GetSchedule_ShouldReturnCorrectSchedule()
        {
            // Arrange
            var schedule1 = new KeyValuePair<int, int>(1, 9); // Monday at 9:00
            var schedule2 = new KeyValuePair<int, int>(3, 10); // Wednesday at 10:00
            _pediatrician.AddSchedule(schedule1);
            _pediatrician.AddSchedule(schedule2);

            // Act
            var schedule = _pediatrician.GetSchedule();

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
            var schedule2 = new KeyValuePair<int, int>(3, 10); // Wednesday at 10:00
            _pediatrician.AddSchedule(schedule1);
            _pediatrician.AddSchedule(schedule2);
            var expectedOutput = $"Name: Dr. Jane Doe\nSpecialization: Pediatrics\nSchedule:\nMonday at 9:00\nWednesday at 10:00\n";

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _pediatrician.DisplayInfo();

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
            var expectedOutput = $"Appointment booked with Dr. Jane Doe at {appointmentTime}\n";

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _pediatrician.BookAppointment(appointmentTime);

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
            _pediatrician.AddSchedule(schedule1);
            _pediatrician.AddSchedule(schedule2);
            var expectedOutput = $"Name: Dr. Jane Doe\nSpecialization: Pediatrics\nSchedule:\nTuesday at 10:00\nThursday at 12:00\n";

            using (var sw = new StringWriter())
            {
                Console.SetOut(sw);

                // Act
                _pediatrician.DisplayInfo();

                // Assert
                var result = sw.ToString().Replace("\r", ""); // Remove carriage return character for cross-platform compatibility
                Assert.AreEqual(expectedOutput, result);
            }
        }
    }
}
