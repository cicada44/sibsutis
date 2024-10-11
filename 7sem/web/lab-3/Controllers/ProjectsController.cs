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
            var projects = _context.Projects
                .Include(p => p.Tasks)
                .Include(p => p.Manager)
                .AsQueryable();

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
            projects = sortOrder switch
            {
                "name_desc" => projects.OrderByDescending(p => p.Name),
                "date_asc" => projects.OrderBy(p => p.StartDate),
                "date_desc" => projects.OrderByDescending(p => p.StartDate),
                "priority_asc" => projects.OrderBy(p => p.Priority),
                "priority_desc" => projects.OrderByDescending(p => p.Priority),
                _ => projects.OrderBy(p => p.Name) // Сортировка по имени по умолчанию
            };

            return View(await projects.ToListAsync());
        }

        // Просмотр деталей проекта
        public async Task<IActionResult> Details(int? id)
        {
            if (!id.HasValue) return NotFound();

            var project = await _context.Projects
                .Include(p => p.Employees) // Включаем сотрудников проекта
                .Include(p => p.Tasks)     // Если хотите также видеть задачи
                .Include(p => p.Manager)    // Если нужно также отображать менеджера
                .FirstOrDefaultAsync(p => p.Id == id);

            return project == null ? NotFound() : View(project);
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

            if (!ModelState.IsValid)
            {
                var errors = ModelState.Values.SelectMany(v => v.Errors);
                foreach (var error in errors)
                {
                    Console.WriteLine(error.ErrorMessage);
                }
                return View(project);
            }

            _context.Add(project);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        // Редактирование проекта (GET)
        public async Task<IActionResult> Edit(int? id)
        {
            if (!id.HasValue) return NotFound();

            ViewData["ManagerId"] = new SelectList(await _context.Employees.ToListAsync(), "Id", "FirstName");
            var project = await _context.Projects.FindAsync(id);

            return project == null ? NotFound() : View(project);
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
            if (!id.HasValue) return NotFound();

            var project = await _context.Projects.FirstOrDefaultAsync(p => p.Id == id);
            return project == null ? NotFound() : View(project);
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
            if (!id.HasValue) return NotFound();

            var project = await _context.Projects
                .Include(p => p.Employees) // Включаем сотрудников проекта
                .FirstOrDefaultAsync(p => p.Id == id);

            if (project == null) return NotFound();

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

            if (!project.Employees.Contains(employee))
            {
                project.Employees.Add(employee);
                await _context.SaveChangesAsync();
            }

            return RedirectToAction(nameof(Details), new { id = project.Id });
        }
    }
}
