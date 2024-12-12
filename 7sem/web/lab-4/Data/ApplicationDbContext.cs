using Microsoft.EntityFrameworkCore;
using lab_4.Models;

namespace lab_4.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options) { }

        public DbSet<Book> Books { get; set; }
        public DbSet<Reader> Readers { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            modelBuilder.Entity<Reader>()
                .HasMany(r => r.BorrowedBooks)
                .WithMany(); // связь многие-ко-многим для книг и читателей
        }
    }
}
