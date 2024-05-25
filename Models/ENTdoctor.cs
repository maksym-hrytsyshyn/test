﻿namespace Project.Models;

using System;
using System.Collections.Generic;

public class EnTdoctor(string name, string specialization) : Doctor(name, specialization)
{
    private List<KeyValuePair<int, int>> _schedule = new();

    public void AddSchedule(KeyValuePair<int, int> time)
    {
        _schedule.Add(time);
    }

    public override void DisplayInfo()
    {
        Console.WriteLine("Name: " + GetName());
        Console.WriteLine("Specialization: " + specialization);
        Console.WriteLine("Schedule:");
        foreach (var scheduleItem in _schedule)
        {
            Console.WriteLine($"{GetDayOfWeek(scheduleItem.Key)} at {scheduleItem.Value}:00");
        }
    }

    public override void BookAppointment(Data time)
    {
        Console.WriteLine($"Appointment booked with {name} at {time}");
    }

    public override List<KeyValuePair<int, int>> GetSchedule()
    {
        return _schedule;
    }
    
}
