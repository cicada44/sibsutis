using System.Collections.Generic;

namespace lab_3.Models
{
    public class Employee
    {
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string MiddleName { get; set; }
        public string Email { get; set; }

        // Инициализация коллекций в конструкторе
        public ICollection<Task> Tasks { get; set; } = new List<Task>();

        // Список сотрудников проекта
        public ICollection<Project> Projects { get; set; } = new List<Project>(); // Один работник может быть в нескольких проектах
        public ICollection<Project> ManagedProjects { get; set; } = new List<Project>(); // Если сотрудник может управлять несколькими проектами
    }
}
