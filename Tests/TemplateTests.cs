using NUnit.Framework;
using System;
using System.Collections.Generic;
using Project.Controllers;
using Project.Models;

namespace Project.Tests
{
    [TestFixture]
    public class MedCardTests
    {
        private MedCard<string, MedicalRecord> _medCard;

        [SetUp]
        public void SetUp()
        {
            _medCard = new MedCard<string, MedicalRecord>();
        }

        [Test]
        public void Insert_ShouldAddNewElementToHashTable()
        {
            // Arrange
            string key = "12345";
            var record = new MedicalRecord { FullName = "John Doe" };

            // Act
            _medCard.Insert(key, record);

            // Assert
            Assert.IsTrue(_medCard.Find(key, out var result));
            Assert.AreEqual(record.FullName, result.FullName);
        }

        [Test]
        public void Find_ShouldReturnTrueAndOutputValueIfKeyExists()
        {
            // Arrange
            string key = "12345";
            var record = new MedicalRecord { FullName = "John Doe" };
            _medCard.Insert(key, record);

            // Act
            bool found = _medCard.Find(key, out var result);

            // Assert
            Assert.IsTrue(found);
            Assert.AreEqual(record.FullName, result.FullName);
        }

        [Test]
        public void Find_ShouldReturnFalseIfKeyDoesNotExist()
        {
            // Arrange
            string key = "12345";

            // Act
            bool found = _medCard.Find(key, out var result);

            // Assert
            Assert.IsFalse(found);
            Assert.IsNull(result);
        }

        [Test]
        public void Update_ShouldModifyValueIfKeyExists()
        {
            // Arrange
            string key = "12345";
            var record = new MedicalRecord { FullName = "John Doe" };
            _medCard.Insert(key, record);
            var updatedRecord = new MedicalRecord { FullName = "Jane Doe" };

            // Act
            _medCard.Update(key, updatedRecord);

            // Assert
            Assert.IsTrue(_medCard.Find(key, out var result));
            Assert.AreEqual(updatedRecord.FullName, result.FullName);
        }

        [Test]
        public void Remove_ShouldDeleteElementIfKeyExists()
        {
            // Arrange
            string key = "12345";
            var record = new MedicalRecord { FullName = "John Doe" };
            _medCard.Insert(key, record);

            // Act
            _medCard.Remove(key);

            // Assert
            Assert.IsFalse(_medCard.Find(key, out var result));
        }

        [Test]
        public void GetAllKeys_ShouldReturnAllKeys()
        {
            // Arrange
            string key1 = "12345";
            string key2 = "67890";
            _medCard.Insert(key1, new MedicalRecord { FullName = "John Doe" });
            _medCard.Insert(key2, new MedicalRecord { FullName = "Jane Doe" });

            // Act
            var keys = _medCard.GetAllKeys();

            // Assert
            Assert.Contains(key1, keys);
            Assert.Contains(key2, keys);
        }

        // Dummy classes to enable compilation
        public class MedicalRecord
        {
            public string FullName { get; set; }
            public Data DateOfBirth { get; set; }
        }

        public class Data
        {
            public int Day { get; set; }
            public int Month { get; set; }
            public int Year { get; set; }
        }

        public static class DataGenerator
        {
            public static string GenerateRandomId()
            {
                return Guid.NewGuid().ToString();
            }
        }
    }
}
