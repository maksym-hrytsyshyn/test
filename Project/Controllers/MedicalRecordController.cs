using Microsoft.AspNetCore.Mvc;
using Project.Models;
using System;

namespace Project.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class MedicalRecordController(
        MedCard<string, MedicalRecord> medCard,
        ILogger<MedicalRecordController> logger)
        : ControllerBase
    {
        [HttpPost("create")]
        public ActionResult<string> CreateMedicalCard([FromBody] MedicalRecord patient)
        {
            try
            {
                logger.LogInformation("Creating a new medical card.");
                
                if (ModelState.IsValid)
                {
                    var patientId = medCard.MakeMedCard(patient, out string key);
                    logger.LogInformation("Medical card created successfully with ID: " + patientId);
                    return Ok(patientId);
                }
                else
                {
                    var errorMessages = string.Join("; ", ModelState.Values
                        .SelectMany(x => x.Errors)
                        .Select(x => x.ErrorMessage));
                    return BadRequest("Invalid model state: " + errorMessages);
                }
            }
            catch (Exception ex)
            {
                return BadRequest($"Exception occurred: {ex.Message}");
            }
        }

        [HttpGet("{patientId}")]
        public ActionResult GetMedicalRecordById(string patientId)
        {
            if (!medCard.Find(patientId, out var patient))
            {
                return NotFound("Patient not found.");
            }

            return Ok(patient);
        }

        [HttpDelete("{patientId}")]
        public ActionResult RemoveMedicalCard(string patientId)
        {
            if (!medCard.Find(patientId, out var patient))
            {
                return NotFound("Patient not found.");
            }

            medCard.Remove(patientId);
            return Ok("Medical card removed successfully.");
        }

        [HttpGet]
        public ActionResult GetAllMedicalCards()
        {
            var medicalCards = new List<object>();
            foreach (var key in medCard.GetAllKeys())
            {
                if (medCard.Find(key, out var record))
                {
                    medicalCards.Add(new { Id = key, record.FullName });
                }
            }
            return Ok(medicalCards);
        }
    }
}
