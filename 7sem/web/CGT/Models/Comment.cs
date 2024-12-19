using System;
using System.ComponentModel.DataAnnotations;

namespace f1news.Models
{
    public class Comment
    {
        public int Id { get; set; }

        [Required]
        public int PostId { get; set; } // Связь с постом

        [Required]
        [StringLength(50)]
        public string Author { get; set; }

        [Required]
        public string Content { get; set; }

        public DateTime CreatedAt { get; set; } = DateTime.Now;

        public Post Post { get; set; } // Навигационное свойство
    }
}
