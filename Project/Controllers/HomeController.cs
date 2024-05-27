using Microsoft.AspNetCore.Mvc;
using Project.Models;
using System.Net.Http;
using System.Threading.Tasks;

namespace Project.Controllers
{
    public class HomeController : Controller
    {

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [HttpGet]
        public IActionResult Register()
        {
            return View();
        }

        public IActionResult RegistrationSuccess()
        {
            return View();
        }
    }
}