using NUnit.Framework;
using System;
using System.Collections.Generic;
using Project.Models;

namespace Project.Tests
{
    [TestFixture]
    public class MedicalRecordTests
    {
        private MedicalRecord _medicalRecord;

        [SetUp]
        public void Setup()
        {
            // Arrange
            _medicalRecord = new MedicalRecord
            {
                FullName = "John Doe",
                DateOfBirth = new Data { Day = 15, Month = 5, Year = 1990 },
                Appointments = new List<KeyValuePair<string, Data>>
                {
                    new KeyValuePair<string, Data>("Appointment 1", new Data { Year = 2024, Month = 5, Day = 27 }),
                    new KeyValuePair<string, Data>("Appointment 2", new Data { Year = 2024, Month = 6, Day = 10 })
                }
            };
        }


        [Test]
        public void FullName_ShouldBeSetCorrectly()
        {
            // Arrange
            var fullName = "John Doe";

            // Act
            _medicalRecord.FullName = fullName;

            // Assert
            Assert.AreEqual(fullName, _medicalRecord.FullName);
        }

        [Test]
        public void DateOfBirth_ShouldBeSetCorrectly()
        {
            // Arrange
            var dateOfBirth = new Data(1990, 5, 15);

            // Act
            _medicalRecord.DateOfBirth = dateOfBirth;

            // Assert
            Assert.AreEqual(dateOfBirth, _medicalRecord.DateOfBirth);
        }

        [Test]
        public void Appointments_ShouldBeInitialized()
        {
            // Assert
            Assert.IsNotNull(_medicalRecord.Appointments);
            Assert.IsInstanceOf<List<KeyValuePair<string, Data>>>(_medicalRecord.Appointments);
        }

        [Test]
        public void GetBirthdate_ShouldReturnFormattedDate()
        {
            // Act
            var birthdate = _medicalRecord.GetBirthdate();

            // Assert
            Assert.That(birthdate, Is.EqualTo("15.5.1990 0:0"));
        }
        
        

    }
}