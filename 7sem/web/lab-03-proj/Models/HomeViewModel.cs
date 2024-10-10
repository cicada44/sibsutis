using lab_3.Models;
using System.Collections.Generic;

namespace lab_3.Models
{
    public class HomeViewModel
    {
        public List<Project> Projects { get; set; }
        public List<Employee> Employees { get; set; }
        public List<Task> Tasks { get; set; }
    }
}
