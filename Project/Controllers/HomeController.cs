using Microsoft.AspNetCore.Mvc;
using Project.Models;

namespace Project.Controllers
{
    public class HomeController : Controller
    {
        private readonly MedCard<string, MedicalRecord> _medCard;
        
        public HomeController(MedCard<string, MedicalRecord> medCard)
        {
            _medCard = medCard;
        }
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult Privacy()
        {
            return View();
        }

        [HttpGet]
        public ActionResult Register()
        {
            return View();
        }
        
        [HttpPost]
        public ActionResult Register(MedicalRecord medicalRecord)
        {
            if (ModelState.IsValid)
            {
                string patientId = _medCard.MakeMedCard(medicalRecord, out _);
                ViewBag.PatientId = patientId;
                return RedirectToAction("RegistrationSuccess");
            }
            return View(medicalRecord);
        }

        public ActionResult RegistrationSuccess()
        {
            if (ViewBag.PatientId == null)
            {
                return RedirectToAction("Register");
            }
            return View();
        }
        public IActionResult Records()
        {
            var medicalRecords = _medCard.GetAllKeys();
            return View();
        }
    }
}