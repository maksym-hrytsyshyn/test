using NUnit.Framework;
using Project.Models;

namespace Project.Tests
{
    [TestFixture]
    public class DataTests
    {
        [Test]
        public void IsEqual_ShouldReturnTrueForEqualData()
        {
            // Arrange
            var data1 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };
            var data2 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };

            // Act
            bool result = data1.IsEqual(data2);

            // Assert
            Assert.IsTrue(result);
        }

        [Test]
        public void IsEqual_ShouldReturnFalseForDifferentData()
        {
            // Arrange
            var data1 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };
            var data2 = new Data(2, 1, 2020) { Hour = 10, Minute = 30 };

            // Act
            bool result = data1.IsEqual(data2);

            // Assert
            Assert.IsFalse(result);
        }

        [Test]
        public void FormatDate_ShouldReturnFormattedString()
        {
            // Arrange
            var data = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };
            string expected = "1.1.2020 10:30";

            // Act
            string result = data.FormatDate();

            // Assert
            Assert.AreEqual(expected, result);
        }

        [Test]
        public void GetDayOfWeek_ShouldReturnCorrectDayName()
        {
            // Arrange
            var data = new Data();

            // Act & Assert
            Assert.AreEqual("Monday", data.GetDayOfWeek(1));
            Assert.AreEqual("Tuesday", data.GetDayOfWeek(2));
            Assert.AreEqual("Wednesday", data.GetDayOfWeek(3));
            Assert.AreEqual("Thursday", data.GetDayOfWeek(4));
            Assert.AreEqual("Friday", data.GetDayOfWeek(5));
            Assert.AreEqual("Saturday", data.GetDayOfWeek(6));
            Assert.AreEqual("Sunday", data.GetDayOfWeek(7));
            Assert.AreEqual("Unknown", data.GetDayOfWeek(0));
        }

        [Test]
        public void EqualityOperator_ShouldReturnTrueForEqualData()
        {
            // Arrange
            var data1 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };
            var data2 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };

            // Act
            bool result = data1 == data2;

            // Assert
            Assert.IsTrue(result);
        }

        [Test]
        public void InequalityOperator_ShouldReturnFalseForEqualData()
        {
            // Arrange
            var data1 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };
            var data2 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };

            // Act
            bool result = data1 != data2;

            // Assert
            Assert.IsFalse(result);
        }

        [Test]
        public void Equals_ShouldReturnTrueForEqualData()
        {
            // Arrange
            var data1 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };
            var data2 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };

            // Act
            bool result = data1.Equals(data2);

            // Assert
            Assert.IsTrue(result);
        }

        [Test]
        public void GetHashCode_ShouldReturnSameHashCodeForEqualData()
        {
            // Arrange
            var data1 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };
            var data2 = new Data(1, 1, 2020) { Hour = 10, Minute = 30 };

            // Act
            int hash1 = data1.GetHashCode();
            int hash2 = data2.GetHashCode();

            // Assert
            Assert.AreEqual(hash1, hash2);
        }
    }
}
