using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Options;
using f1news.Data;
using f1news.Models;

namespace f1news.Pages.Posts
{
    [Authorize]
    public class EditModel : PageModel
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<IdentityUser> _userManager;
        private readonly AdminSettings _adminSettings;

        public EditModel(
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

        public IActionResult OnGet(int id)
        {
            // Проверка: текущий пользователь — администратор?
            var currentUserEmail = _userManager.GetUserName(User);
            if (currentUserEmail != _adminSettings.AdminEmail)
            {
                return Forbid(); // Запретить доступ
            }

            Post = _context.Posts.Find(id);
            if (Post == null)
            {
                return NotFound();
            }

            return Page();
        }

        public IActionResult OnPost()
        {
            // Проверка: текущий пользователь — администратор?
            var currentUserEmail = _userManager.GetUserName(User);
            if (currentUserEmail != _adminSettings.AdminEmail)
            {
                return Forbid(); // Запретить доступ
            }

            if (!ModelState.IsValid)
            {
                return Page();
            }

            _context.Posts.Update(Post);
            _context.SaveChanges();
            return RedirectToPage("/Index");
        }
    }
}
