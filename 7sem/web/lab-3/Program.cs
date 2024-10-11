using Microsoft.EntityFrameworkCore;
using lab_3.Data;
using Pomelo.EntityFrameworkCore.MySql.Infrastructure;

var applicationBuilder = WebApplication.CreateBuilder(args);

// Настройка MVC
ConfigureServices(applicationBuilder.Services);

// Создание приложения
var application = applicationBuilder.Build();

// Настройка маршрутизации и обработки ошибок
ConfigureMiddleware(application);

// Запуск приложения
application.Run();

void ConfigureServices(IServiceCollection services)
{
    // Добавление поддержки MVC
    services.AddControllersWithViews();

    // Конфигурация подключения к базе данных MySQL
    var connection = applicationBuilder.Configuration.GetConnectionString("DefaultConnection");
    services.AddDbContext<ApplicationDbContext>(options =>
        options.UseMySql(connection, new MySqlServerVersion(new Version(9, 0, 1))));
}

void ConfigureMiddleware(WebApplication app)
{
    // Конфигурация обработки ошибок для производственного окружения
    if (!app.Environment.IsDevelopment())
    {
        app.UseExceptionHandler("/Home/Error");
        app.UseHsts();
    }

    app.UseHttpsRedirection();
    app.UseStaticFiles();

    app.UseRouting();
    app.UseAuthorization();

    // Определение маршрутов для контроллеров
    app.MapControllerRoute(
        name: "default",
        pattern: "{controller=Home}/{action=Index}/{id?}");
}
