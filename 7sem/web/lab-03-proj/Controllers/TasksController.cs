using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Mvc.Rendering;
using lab_3.Data;
using lab_3.Models;
using System.Linq;

namespace lab_3.Controllers
{
    public class TasksController : Controller
    {
        private readonly ApplicationDbContext _context;

        public TasksController(ApplicationDbContext context)
        {
            _context = context;
        }

        // Просмотр списка задач
        public async Task<IActionResult> Index(string statusFilter, string sortOrder)
        {
            var tasks = _context.Tasks
                .Include(t => t.Executor)
                .Include(t => t.Project)
                .Include(t => t.Author)
                .AsQueryable();

            // Фильтрация по статусу
            if (!string.IsNullOrEmpty(statusFilter))
            {
                // Преобразуйте строку в соответствующее значение перечисления
                if (Enum.TryParse<lab_3.Models.TaskStatus>(statusFilter, out var status))
                {
                    tasks = tasks.Where(t => t.Status == status);
                }
            }

            // Сортировка
            switch (sortOrder)
            {
                case "title_desc":
                    tasks = tasks.OrderByDescending(t => t.Title);
                    break;
                case "author":
                    tasks = tasks.OrderBy(t => t.Author.FirstName);
                    break;
                case "author_desc":
                    tasks = tasks.OrderByDescending(t => t.Author.FirstName);
                    break;
                case "project":
                    tasks = tasks.OrderBy(t => t.Project.Name);
                    break;
                case "project_desc":
                    tasks = tasks.OrderByDescending(t => t.Project.Name);
                    break;
                case "priority":
                    tasks = tasks.OrderBy(t => t.Priority);
                    break;
                case "priority_desc":
                    tasks = tasks.OrderByDescending(t => t.Priority);
                    break;
                default:
                    tasks = tasks.OrderBy(t => t.Title); // Сортировка по умолчанию
                    break;
            }

            // Подготовка ViewBag для фильтрации
            ViewBag.CurrentSort = sortOrder;
            ViewBag.StatusFilter = statusFilter;

            return View(await tasks.ToListAsync());
        }



        // Просмотр деталей задачи
        public async System.Threading.Tasks.Task<IActionResult> Details(int? id)
        {
            if (id == null) return NotFound();

            var task = await _context.Tasks
                .Include(t => t.Author)
                .Include(t => t.Executor)
                .Include(t => t.Project)
                .FirstOrDefaultAsync(m => m.Id == id);

            if (task == null) return NotFound();

            return View(task);
        }

        // Отображение формы создания задачи (GET)
        public IActionResult Create()
        {
            ViewData["AuthorId"] = new SelectList(_context.Employees, "Id", "FirstName"); // Список авторов
            ViewData["ExecutorId"] = new SelectList(_context.Employees, "Id", "FirstName"); // Список исполнителей
            ViewData["ProjectId"] = new SelectList(_context.Projects, "Id", "Name"); // Список проектов

            // Заполняем ViewBag данными для выпадающих списков
            ViewData["Employees"] = new SelectList(_context.Employees, "Id", "FirstName");
            ViewData["Projects"] = new SelectList(_context.Projects, "Id", "Name");
            return View(new lab_3.Models.Task()); // Передаем новую задачу в представление
        }

        // Создание задачи (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async System.Threading.Tasks.Task<IActionResult> Create([Bind("Title,AuthorId,ExecutorId,ProjectId,Status,Comment,Priority")] lab_3.Models.Task task)
        {
            task.Author = await _context.Employees.FindAsync(task.AuthorId);
            task.Executor = await _context.Employees.FindAsync(task.ExecutorId);
            task.Project = await _context.Projects.FindAsync(task.ProjectId);

            _context.Add(task);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index)); // Перенаправляем на список задач
        }

        // Редактирование задачи (GET)
        public async System.Threading.Tasks.Task<IActionResult> Edit(int? id)
        {
            if (id == null) return NotFound();

            var task = await _context.Tasks.FindAsync(id);
            if (task == null) return NotFound();

            ViewData["Employees"] = new SelectList(_context.Employees, "Id", "FirstName", task.ExecutorId);
            ViewData["Projects"] = new SelectList(_context.Projects, "Id", "Name", task.ProjectId);
            return View(task);
        }

        // Редактирование задачи (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async System.Threading.Tasks.Task<IActionResult> Edit(int id, [Bind("Id,Title,AuthorId,ExecutorId,ProjectId,Status,Comment,Priority")] lab_3.Models.Task task)
        {
            if (id != task.Id) return NotFound();
            task.Author = await _context.Employees.FindAsync(task.AuthorId);
            task.Executor = await _context.Employees.FindAsync(task.ExecutorId);
            task.Project = await _context.Projects.FindAsync(task.ProjectId);
            _context.Update(task);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        // Удаление задачи (GET)
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var task = await _context.Tasks
                .Include(t => t.Executor)
                .Include(t => t.Project)
                .Include(t => t.Author)
                .FirstOrDefaultAsync(m => m.Id == id);

            if (task == null)
            {
                return NotFound();
            }

            return View(task); // Отправляем задачу в представление для подтверждения удаления
        }

        // Удаление задачи (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Delete(int id)
        {
            var task = await _context.Tasks.FindAsync(id);
            if (task != null)
            {
                _context.Tasks.Remove(task);
                await _context.SaveChangesAsync(); // Сохраняем изменения
            }

            return RedirectToAction(nameof(Index)); // Перенаправляем на список задач
        }

        private bool TaskExists(int id)
        {
            return _context.Tasks.Any(e => e.Id == id);
        }
    }
}
