using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace lab_4.Models
{
    public class Reader
    {
        public int Id { get; set; }

        [Required]
        public string FullName { get; set; }

        public DateTime BirthDate { get; set; }

        public List<Book> BorrowedBooks { get; set; } = new List<Book>();  // Список выданных книг
    }
}
