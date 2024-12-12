using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using lab_3.Data;
using lab_3.Models;
using System.Linq;
using System.Threading.Tasks;

namespace lab_3.Controllers
{
    public class EmployeesController : Controller
    {
        private readonly ApplicationDbContext _context;

        public EmployeesController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            var employeeList = await _context.Employees.ToListAsync();
            return View(employeeList);
        }

        // Получение информации о сотруднике
        public async Task<IActionResult> Details(int? id)
        {
            if (!id.HasValue) return NotFound();
            var employeeDetail = await _context.Employees
                .Include(e => e.Projects)
                .FirstOrDefaultAsync(m => m.Id == id);
                
            return employeeDetail == null ? NotFound() : View(employeeDetail);
        }

        // Отображение формы для создания нового сотрудника (GET)
        public IActionResult Create()
        {
            return View();
        }

        // Обработка данных формы создания сотрудника (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("FirstName,LastName,MiddleName,Rank,Email")] Employee employee)
        {
            if (!ModelState.IsValid) return View(employee);

            _context.Add(employee);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        // Получение информации о редактируемом сотруднике (GET)
        public async Task<IActionResult> Edit(int? id)
        {
            if (!id.HasValue) return NotFound();

            var employeeToEdit = await _context.Employees.FindAsync(id);
            return employeeToEdit == null ? NotFound() : View(employeeToEdit);
        }

        // Обработка данных формы редактирования сотрудника (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,FirstName,LastName,MiddleName,Rank,Email")] Employee employee)
        {
            if (id != employee.Id) return NotFound();
            if (!ModelState.IsValid) return View(employee);

            try
            {
                _context.Update(employee);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!EmployeeExists(employee.Id)) return NotFound();
                throw;
            }
        }

        // Получение информации о сотруднике для удаления (GET)
        public async Task<IActionResult> Delete(int? id)
        {
            if (!id.HasValue) return NotFound();

            var employeeToDelete = await _context.Employees.FirstOrDefaultAsync(m => m.Id == id);
            return employeeToDelete == null ? NotFound() : View(employeeToDelete);
        }

        // Обработка удаления сотрудника (POST)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var employeeToRemove = await _context.Employees.FindAsync(id);
            if (employeeToRemove != null)
            {
                _context.Employees.Remove(employeeToRemove);
                await _context.SaveChangesAsync();
            }

            return RedirectToAction(nameof(Index));
        }

        private bool EmployeeExists(int id)
        {
            return _context.Employees.Any(e => e.Id == id);
        }
    }
}
