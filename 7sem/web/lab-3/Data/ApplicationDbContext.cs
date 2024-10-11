using Microsoft.EntityFrameworkCore;
using lab_3.Models;

namespace lab_3.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Project> Projects { get; set; }
        public DbSet<Employee> Employees { get; set; }
        public DbSet<lab_3.Models.Task> Tasks { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Настройка отношений между Employee и Task
            modelBuilder.Entity<lab_3.Models.Task>()
                .HasOne(t => t.Executor)
                .WithMany(e => e.Tasks)
                .HasForeignKey(t => t.ExecutorId)
                .OnDelete(DeleteBehavior.Restrict); // Укажите поведение при удалении, если это необходимо

            modelBuilder.Entity<lab_3.Models.Task>()
                .HasOne(t => t.Author)
                .WithMany() // У автора нет коллекции задач, поэтому указываем WithMany()
                .HasForeignKey(t => t.AuthorId)
                .OnDelete(DeleteBehavior.Restrict);

            // Настройка отношений один-ко-многим между проектом и менеджером (руководителем проекта)
            modelBuilder.Entity<Project>()
                .HasOne(p => p.Manager)  // Проект имеет одного менеджера
                .WithMany(e => e.ManagedProjects) // Один менеджер может управлять несколькими проектами
                .HasForeignKey(p => p.ManagerId) // Внешний ключ в проекте
                .OnDelete(DeleteBehavior.Restrict); // Поведение при удалении, чтобы предотвратить каскадное удаление

            // Настройка отношения многие-ко-многим между проектами и сотрудниками
            modelBuilder.Entity<Project>()
                .HasMany(p => p.Employees)
                .WithMany(e => e.Projects)
                .UsingEntity<Dictionary<string, object>>(
                    "EmployeeProject", // Явное имя промежуточной таблицы
                    j => j.HasOne<Employee>().WithMany().HasForeignKey("EmployeeId"),
                    j => j.HasOne<Project>().WithMany().HasForeignKey("ProjectId"),
                    j => j.ToTable("EmployeeProject") // Имя промежуточной таблицы
                );
        }
    }
}

