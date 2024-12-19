using Microsoft.AspNetCore.Mvc.RazorPages;
using f1news.Data;
using f1news.Models;

namespace f1news.Pages
{
    public class IndexModel : PageModel
    {
        private readonly ApplicationDbContext _context;

        public IndexModel(ApplicationDbContext context)
        {
            _context = context;
        }

        public List<Post> Posts { get; set; }

        public void OnGet()
        {
            Posts = _context.Posts.OrderByDescending(p => p.CreatedAt).ToList();
        }
    }
}
