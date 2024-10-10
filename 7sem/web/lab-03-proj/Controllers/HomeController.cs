using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using lab_3.Data;
using lab_3.Models;
using System.Threading.Tasks;

namespace lab_3.Controllers
{
    public class HomeController : Controller
    {
        private readonly ApplicationDbContext _context;

        public HomeController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            // Получаем все проекты, сотрудников и задачи
            var projects = await _context.Projects.ToListAsync();
            var employees = await _context.Employees.ToListAsync();
            var tasks = await _context.Tasks
                .Include(t => t.Author)
                .Include(t => t.Executor)
                .Include(t => t.Project)
                .ToListAsync();

            // Создаем объект для передачи в представление
            var viewModel = new HomeViewModel
            {
                Projects = projects,
                Employees = employees,
                Tasks = tasks
            };

            return View(viewModel);
        }
    }
}
