namespace Project.Models;

public struct Data
{
    public Data(int day, int month, int year)
    {
        Day = day;
        Month = month;
        Year = year;
    }
    public int Day { get; set; }
    public int Month { get; set; }
    public int Year { get; set; }
    public int Hour { get; set; }
    public int Minute { get; set; }

    public bool IsEqual(Data other)
    {
        return Year == other.Year && Month == other.Month && Day == other.Day &&
               Hour == other.Hour && Minute == other.Minute;
    }
    
    public string FormatDate()
    {
        return $"{Day}.{Month}.{Year} {Hour}:{Minute}";
    }
    
    public string GetDayOfWeek(int day)
    {
        switch (day)
        {
            case 1:
                return "Monday";
            case 2:
                return "Tuesday";
            case 3:
                return "Wednesday";
            case 4:
                return "Thursday";
            case 5:
                return "Friday";
            case 6:
                return "Saturday";
            case 7:
                return "Sunday";
            default:
                return "Unknown";
        }
    }
    
    public static bool operator ==(Data left, Data right)
    {
        return left.IsEqual(right);
    }

    public static bool operator !=(Data left, Data right)
    {
        return !(left == right);
    }

    public override bool Equals(object obj)
    {
        if (obj is Data other)
        {
            return IsEqual(other);
        }
        return false;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Day, Month, Year, Hour, Minute);
    }
    
    
}
