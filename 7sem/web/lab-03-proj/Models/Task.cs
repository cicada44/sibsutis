namespace lab_3.Models
{
    public enum TaskStatus
    {
        ToDo,
        InProgress,
        Done
    }
    public class Task
    {
        public int Id { get; set; }
        public string Title { get; set; }

        public int AuthorId { get; set; }
        public Employee Author { get; set; } // Навигационное свойство

        public int? ExecutorId { get; set; }
        public Employee Executor { get; set; } // Навигационное свойство

        public int ProjectId { get; set; }
        public Project Project { get; set; } // Навигационное свойство

        public TaskStatus Status { get; set; }
        public int Priority { get; set; }
        public string Comment { get; set; }
    }

}
