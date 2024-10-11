using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using lab_3.Data;
using lab_3.Models;
using System.Threading.Tasks;

namespace lab_3.Controllers
{
    public class HomeController : Controller
    {
        private readonly ApplicationDbContext _dbContext;

        public HomeController(ApplicationDbContext dbContext)
        {
            _dbContext = dbContext;
        }

        public async Task<IActionResult> Index()
        {
            // Загружаем проекты, сотрудников и задачи
            var allProjects = await _dbContext.Projects.ToListAsync();
            var allEmployees = await _dbContext.Employees.ToListAsync();
            var allTasks = await _dbContext.Tasks
                .Include(t => t.Author)
                .Include(t => t.Executor)
                .Include(t => t.Project)
                .ToListAsync();

            // Формируем модель для представления
            var homeViewModel = new HomeViewModel
            {
                Projects = allProjects,
                Employees = allEmployees,
                Tasks = allTasks
            };
            
            return View(homeViewModel);
        }
    }
}
