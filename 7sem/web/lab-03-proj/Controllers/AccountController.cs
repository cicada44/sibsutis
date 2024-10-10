using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;

// public class AccountController : Controller
// {
//     private readonly UserManager<ApplicationUser> _userManager;
//     private readonly SignInManager<ApplicationUser> _signInManager;

//     public AccountController(UserManager<ApplicationUser> userManager, SignInManager<ApplicationUser> signInManager)
//     {
//         _userManager = userManager;
//         _signInManager = signInManager;
//     }

//     [HttpGet]
//     public IActionResult Login()
//     {
//         return View();
//     }

//     [HttpPost]
//     [ValidateAntiForgeryToken]
//     public async Task<IActionResult> Login(LoginViewModel model)
//     {
//         if (ModelState.IsValid)
//         {
//             var result = await _signInManager.PasswordSignInAsync(model.Email, model.Password, model.RememberMe, false);
//             if (result.Succeeded)
//             {
//                 return RedirectToAction("Index", "Home");
//             }
//             ModelState.AddModelError(string.Empty, "Неверный логин или пароль.");
//         }
//         return View(model);
//     }
// }