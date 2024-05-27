using NUnit.Framework;
using System;
using System.Collections.Generic;
using Project.Models;

namespace Project.Tests
{
    // Concrete subclass of Doctor for testing
    public class TestDoctor : Doctor
    {
        private List<KeyValuePair<int, int>> _schedule = new();

        public TestDoctor(string name, string specialization) : base(name, specialization) { }

        public override void DisplayInfo()
        {
            Console.WriteLine($"Name: {Name}, Specialization: {Specialization}");
        }

        public override List<KeyValuePair<int, int>> GetSchedule()
        {
            return _schedule;
        }

        public override void BookAppointment(Data time)
        {
            _schedule.Add(new KeyValuePair<int, int>(time.Day, time.Hour));
        }
    }

    [TestFixture]
    public class DoctorTests
    {
        private TestDoctor _doctor;

        [SetUp]
        public void SetUp()
        {
            _doctor = new TestDoctor("Dr. Smith", "Cardiology");
        }

        [Test]
        public void GetName_ShouldReturnName()
        {
            // Arrange
            // No specific arrangement needed as doctor name is set in SetUp

            // Act
            string result = _doctor.GetName();

            // Assert
            Assert.AreEqual("Dr. Smith", result);
        }

        [Test]
        public void GetSpecialization_ShouldReturnSpecialization()
        {
            // Arrange
            // No specific arrangement needed as doctor specialization is set in SetUp

            // Act
            string result = _doctor.GetSpecialization();

            // Assert
            Assert.AreEqual("Cardiology", result);
        }

        [Test]
        public void GetDayOfWeek_ShouldReturnCorrectDayName()
        {
            // Arrange
            // No specific arrangement needed

            // Act & Assert
            Assert.AreEqual("Monday", _doctor.GetDayOfWeek(1));
            Assert.AreEqual("Tuesday", _doctor.GetDayOfWeek(2));
            Assert.AreEqual("Wednesday", _doctor.GetDayOfWeek(3));
            Assert.AreEqual("Thursday", _doctor.GetDayOfWeek(4));
            Assert.AreEqual("Friday", _doctor.GetDayOfWeek(5));
            Assert.AreEqual("Saturday", _doctor.GetDayOfWeek(6));
            Assert.AreEqual("Sunday", _doctor.GetDayOfWeek(7));
            Assert.AreEqual("Unknown", _doctor.GetDayOfWeek(0));
        }

        [Test]
        public void GetSchedule_ShouldReturnSchedule()
        {
            // Arrange
            var expectedSchedule = new List<KeyValuePair<int, int>>
            {
                new KeyValuePair<int, int>(1, 10),
                new KeyValuePair<int, int>(3, 14)
            };
            _doctor.BookAppointment(new Data { Day = 1, Hour = 10 });
            _doctor.BookAppointment(new Data { Day = 3, Hour = 14 });

            // Act
            var result = _doctor.GetSchedule();

            // Assert
            CollectionAssert.AreEqual(expectedSchedule, result);
        }

        [Test]
        public void BookAppointment_ShouldAddToSchedule()
        {
            // Arrange
            var appointmentTime = new Data { Day = 2, Hour = 11 };
            var expectedSchedule = new List<KeyValuePair<int, int>>
            {
                new KeyValuePair<int, int>(2, 11)
            };

            // Act
            _doctor.BookAppointment(appointmentTime);
            var result = _doctor.GetSchedule();

            // Assert
            CollectionAssert.AreEqual(expectedSchedule, result);
        }
    }
}
