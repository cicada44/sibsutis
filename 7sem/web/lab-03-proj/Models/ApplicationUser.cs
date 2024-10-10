using Microsoft.AspNetCore.Identity;

namespace lab_3.Models // Замените на ваше пространство имен
{
    public class ApplicationUser : IdentityUser
    {
        // Добавьте дополнительные свойства, если это необходимо
        public string FirstName { get; set; }
        public string LastName { get; set; }
    }
}