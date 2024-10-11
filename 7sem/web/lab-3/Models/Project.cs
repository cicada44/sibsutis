using System.Collections.Generic;

namespace lab_3.Models
{
    public class Project
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string CustomerCompany { get; set; }
        public string ContractorCompany { get; set; }
        public DateTime StartDate { get; set; }
        public DateTime? EndDate { get; set; }
        public int Priority { get; set; }

        // Связь с руководителем проекта
        public int ManagerId { get; set; }
        public Employee Manager { get; set; }

        // Список задач проекта
        public ICollection<Task> Tasks { get; set; } = new List<Task>();

        // Список сотрудников проекта
        public ICollection<Employee> Employees { get; set; } = new List<Employee>();
    }
}
