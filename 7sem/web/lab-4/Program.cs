using Microsoft.EntityFrameworkCore;
using lab_4.Data;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddControllers();

// connect db
var connectionString = builder.Configuration.GetConnectionString("DefaultConnection");
builder.Services.AddDbContext<ApplicationDbContext>(options =>
    options.UseMySql(connectionString, new MySqlServerVersion(new Version(9, 0, 1))));

// document API
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Swagger configuration
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI(c =>
    {
        c.SwaggerEndpoint("/swagger/v1/swagger.json", "Library API v1");
        c.RoutePrefix = string.Empty;  // Swagger UI page
    });
}

app.UseAuthorization();
app.MapControllers();

app.Run();
