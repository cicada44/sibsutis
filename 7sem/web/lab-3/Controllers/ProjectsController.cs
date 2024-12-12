using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Mvc.Rendering;
using lab_3.Data;
using lab_3.Models;
using System.Threading.Tasks;
using System.Linq;

namespace lab_3.Controllers
{
    public class ProjectsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public ProjectsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // Отображение списка проектов
        public async Task<IActionResult> Index(DateTime? startDate, DateTime? endDate, int? priority, string sortOrder)
        {
            // Базовый запрос для выборки проектов
            var projects = _context.Projects.Include(p => p.Tasks).Include(p => p.Manager).AsQueryable();
            // Фильтрация по диапазону дат начала
            if (startDate.HasValue && endDate.HasValue)
            {
                projects = projects.Where(p => p.StartDate >= startDate && p.StartDate <= endDate);
            }
            // Фильтрация по приоритету
            if (priority.HasValue)
            {
                projects = projects.Where(p => p.Priority == priority);
            }
            // Сортировка по различным полям
            switch (sortOrder)
            {
                case "name_desc":
                    projects = projects.OrderByDescending(p => p.Name);
                    break;
                case "date_asc":
                    projects = projects.OrderBy(p => p.StartDate);
                    break;
                case "date_desc":
                    projects = projects.OrderByDescending(p => p.StartDate);
                    break;
                case "priority_asc":
                    projects = projects.OrderBy(p => p.Priority);
                    break;
                case "priority_desc":
                    projects = projects.OrderByDescending(p => p.Priority);
                    break;
                default:
                    projects = projects.OrderBy(p => p.Name); // Сортировка по имени по умолчанию
                    break;
            }
            return View(await projects.ToListAsync());
        }

        // Просмотр деталей проекта
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }
            // Обязательно включите сотрудников при извлечении проекта
            var project = await _context.Projects
                .Include(p => p.Employees)
                .Include(p => p.Tasks)
                .Include(p => p.Manager)
                .FirstOrDefaultAsync(p => p.Id == id);
            if (project == null)
            {
                return NotFound();
            }
            return View(project);
        }


        // Создание проекта (GET)
        public async Task<IActionResult> Create()
        {
            ViewData["ManagerId"] = new SelectList(await _context.Employees.ToListAsync(), "Id", "FirstName"); // Получаем список сотрудников для выбора менеджера
            return View();
        }

        // Создание проекта (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Name,CustomerCompany,ContractorCompany,StartDate,EndDate,Priority,ManagerId")] Project project)
        {
            project.Manager = await _context.Employees.FindAsync(project.ManagerId);
            // Логирование ошибок валидации
            var errors = ModelState.Values.SelectMany(v => v.Errors);
            foreach (var error in errors)
            {
                Console.WriteLine(error.ErrorMessage);
            }
            _context.Add(project);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        // Редактирование проекта (GET)
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null) return NotFound();
            ViewData["ManagerId"] = new SelectList(await _context.Employees.ToListAsync(), "Id", "FirstName");
            var project = await _context.Projects.FindAsync(id);
            if (project == null) return NotFound();
            return View(project);
        }

        // Редактирование проекта (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name,CustomerCompany,ContractorCompany,StartDate,EndDate,Priority,ManagerId")] Project project)
        {
            if (id != project.Id) return NotFound();
            project.Manager = await _context.Employees.FindAsync(project.ManagerId);
            _context.Update(project);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        // Удаление проекта (GET)
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null) return NotFound();
            var project = await _context.Projects.FirstOrDefaultAsync(p => p.Id == id);
            if (project == null) return NotFound();
            return View(project);
        }

        // Удаление проекта (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Delete(int id)
        {
            var project = await _context.Projects.FindAsync(id);
            if (project != null)
            {
                _context.Projects.Remove(project);
                await _context.SaveChangesAsync();
            }
            return RedirectToAction(nameof(Index));
        }

        public async Task<IActionResult> AddEmployee(int? id)
        {
            if (id == null) return NotFound();

            var project = await _context.Projects
                .Include(p => p.Employees) // Включаем сотрудников проекта
                .FirstOrDefaultAsync(p => p.Id == id);

            if (project == null) return NotFound();

            // Получаем список сотрудников, которых можно добавить к проекту
            var availableEmployees = await _context.Employees.ToListAsync();

            ViewBag.Employees = new SelectList(availableEmployees, "Id", "FirstName");
            return View(project);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> AddEmployee(int id, int employeeId)
        {
            var project = await _context.Projects
                .Include(p => p.Employees)
                .FirstOrDefaultAsync(p => p.Id == id);

            if (project == null) return NotFound();

            var employee = await _context.Employees.FindAsync(employeeId);
            if (employee == null) return NotFound();

            // Добавляем сотрудника к проекту
            if (!project.Employees.Contains(employee))
            {
                project.Employees.Add(employee);
                await _context.SaveChangesAsync();
            }

            return RedirectToAction(nameof(Details), new { id = project.Id });
        }
    }
}
