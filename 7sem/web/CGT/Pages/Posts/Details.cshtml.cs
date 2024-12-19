using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Options;
using f1news.Data;
using f1news.Models;
using System.Linq;

namespace f1news.Pages.Posts
{
    [Authorize]
    public class DetailsModel : PageModel
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<IdentityUser> _userManager;
        private readonly AdminSettings _adminSettings;

        public DetailsModel(
            ApplicationDbContext context,
            UserManager<IdentityUser> userManager,
            IOptions<AdminSettings> adminSettings)
        {
            _context = context;
            _userManager = userManager;
            _adminSettings = adminSettings.Value;
        }

        [BindProperty]
        public Post Post { get; set; }

        [BindProperty]
        public string NewCommentAuthor { get; set; }

        [BindProperty]
        public string NewCommentContent { get; set; }

        public List<Comment> Comments { get; set; } // Для хранения списка комментариев

        public IActionResult OnGet(int id)
        {
            Post = _context.Posts
                .Include(p => p.Comments) // Подгружаем связанные комментарии
                .FirstOrDefault(p => p.Id == id);

            if (Post == null)
            {
                return NotFound();
            }

            Comments = Post.Comments.ToList(); // Инициализируем список комментариев
            return Page();
        }



        public IActionResult OnPostAddComment(int id, string newCommentAuthor, string newCommentContent)
        {
            if (string.IsNullOrWhiteSpace(newCommentAuthor) || string.IsNullOrWhiteSpace(newCommentContent))
            {
                ModelState.AddModelError(string.Empty, "Имя автора и текст комментария не могут быть пустыми.");
                return RedirectToPage(new { id });
            }
        
            var post = _context.Posts.Find(id);
            if (post == null)
            {
                return NotFound();
            }
        
            var newComment = new Comment
            {
                PostId = id,
                Author = newCommentAuthor,
                Content = newCommentContent,
                CreatedAt = DateTime.Now
            };
        
            _context.Comments.Add(newComment); // Добавляем комментарий в таблицу
            _context.SaveChanges(); // Сохраняем изменения в базе данных
        
            return RedirectToPage(new { id }); // Перезагружаем страницу поста
        }

    }
}
