using Microsoft.AspNetCore.Mvc;
using Project.Models;
using System.Linq;

namespace Project.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class DoctorsController : ControllerBase
    {
        private readonly Appointment _appointment;

        public DoctorsController(Appointment appointment)
        {
            _appointment = appointment;
        }

        [HttpGet("{specialization}")]
        public ActionResult GetDoctorsBySpecialization(string specialization)
        {
            if (!_appointment._doctors.ContainsKey(specialization))
            {
                return NotFound("Specialization not found.");
            }

            var doctors = _appointment._doctors[specialization];
            var result = doctors.Select(doctor => new
            {
                Name = doctor.GetName(),
                Specialization = doctor.GetSpecialization()
            });

            return Ok(result);
        }
    }
}