using Microsoft.AspNetCore.Mvc;
using Project.Models;

namespace Project.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class MedicalRecordsController : ControllerBase
    {
        private readonly MedCard<string, MedicalRecord> _medicalRecords;

        public MedicalRecordsController(MedCard<string, MedicalRecord> medicalRecords)
        {
            _medicalRecords = medicalRecords;
        }

        [HttpPost("create")]
        public ActionResult<string> CreateMedicalCard([FromBody] MedicalRecord patient)
        {
            _medicalRecords.MakeMedCard(patient);
            return Ok("Medical card created successfully.");
        }

        [HttpGet("{patientId}")]
        public ActionResult GetMedicalRecordById(string patientId)
        {
            if (!_medicalRecords.Find(patientId, out var patient))
            {
                return NotFound("Patient not found.");
            }

            return Ok(patient);
        }

        [HttpDelete("{patientId}")]
        public ActionResult RemoveMedicalCard(string patientId)
        {
            if (!_medicalRecords.Find(patientId, out var patient))
            {
                return NotFound("Patient not found.");
            }

            _medicalRecords.Remove(patientId);
            return Ok("Medical card removed successfully.");
        }

        [HttpGet]
        public ActionResult GetAllMedicalCards()
        {
            var medicalCards = new List<object>();
            foreach (var key in _medicalRecords.GetAllKeys())
            {
                if (_medicalRecords.Find(key, out var record))
                {
                    medicalCards.Add(new { Id = key, record.FullName });
                }
            }
            return Ok(medicalCards);
        }
    }
}