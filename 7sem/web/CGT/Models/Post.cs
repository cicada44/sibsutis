using System.ComponentModel.DataAnnotations;
using System.Collections.Generic; // Для ICollection
using f1news.Models;

namespace f1news.Models
{
    public class Post
    {
        public int Id { get; set; }

        [Required]
        [StringLength(100)]
        public string Title { get; set; }

        [Required]
        public string Content { get; set; }

        public DateTime CreatedAt { get; set; } = DateTime.Now;

        public ICollection<Comment> Comments { get; set; } = new List<Comment>();
    }
}
