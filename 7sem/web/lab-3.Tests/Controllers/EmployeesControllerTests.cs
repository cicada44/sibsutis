using Xunit;
using Moq;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using lab_3.Controllers;
using lab_3.Data;
using lab_3.Models;
using System.Collections.Generic;
using System.Threading.Tasks;

public class EmployeesControllerTests
{
    [Fact]
    public async System.Threading.Tasks.Task Index_ReturnsAViewResult_WithAListOfEmployees()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);

        context.Employees.Add(new Employee { Id = 1, FirstName = "John", LastName = "Doe", MiddleName = "Jr.", Email = "john@gmail.com" });
        context.Employees.Add(new Employee { Id = 4, FirstName = "Jane", LastName = "Smith", MiddleName = "Sr.", Email = "jane@gmail.com" });
        await context.SaveChangesAsync();

        var controller = new EmployeesController(context);

        // Act
        var result = await controller.Index();

        // Assert
        var viewResult = Assert.IsType<ViewResult>(result);
        var model = Assert.IsAssignableFrom<List<Employee>>(viewResult.ViewData.Model);
        Assert.Equal(2, model.Count);
    }

    [Fact]
    public async System.Threading.Tasks.Task Details_ReturnsAViewResult_WithEmployeeDetails()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);
        context.Employees.Add(new Employee { Id = 1, FirstName = "John", LastName = "Doe", MiddleName = "Jr.", Email = "john@gmail.com" });
        await context.SaveChangesAsync();

        var controller = new EmployeesController(context);

        // Act
        var result = await controller.Details(1);

        // Assert
        var viewResult = Assert.IsType<ViewResult>(result);
        var model = Assert.IsType<Employee>(viewResult.ViewData.Model);
        Assert.Equal(1, model.Id); // Проверяем, что правильный сотрудник
    }

    [Fact]
    public async System.Threading.Tasks.Task Details_ReturnsNotFound_WhenIdIsNull()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);
        var controller = new EmployeesController(context);

        // Act
        var result = await controller.Details(null);

        // Assert
        Assert.IsType<NotFoundResult>(result);
    }

    [Fact]
    public async System.Threading.Tasks.Task Details_ReturnsNotFound_WhenEmployeeDoesNotExist()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);
        var controller = new EmployeesController(context);

        // Act
        var result = await controller.Details(100); // Несуществующий ID

        // Assert
        Assert.IsType<NotFoundResult>(result);
    }

    [Fact]
    public async System.Threading.Tasks.Task Create_PostValidEmployee_RedirectsToIndex()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);
        var controller = new EmployeesController(context);

        var newEmployee = new Employee
        {
            FirstName = "John",
            LastName = "Doe",
            MiddleName = "Test",
            Email = "john.doe@example.com"
        };

        // Act
        var result = await controller.Create(newEmployee);

        // Assert
        var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
        Assert.Equal("Index", redirectToActionResult.ActionName);
        Assert.Equal(2, await context.Employees.CountAsync()); // Проверяем, что сотрудник был добавлен
    }

    [Fact]
    public async System.Threading.Tasks.Task Create_PostInvalidEmployee_ReturnsViewWithModel()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);
        var controller = new EmployeesController(context);

        // Добавим ошибку валидации
        controller.ModelState.AddModelError("FirstName", "Required");

        var newEmployee = new Employee
        {
            LastName = "Doe",
            MiddleName = "Test",
            Email = "john.doe@example.com"
        };

        // Act
        var result = await controller.Create(newEmployee);

        // Assert
        var viewResult = Assert.IsType<ViewResult>(result);
        var model = Assert.IsType<Employee>(viewResult.ViewData.Model);
        Assert.Equal(newEmployee, model); // Модель возвращается на форму
    }

    [Fact]
    public async System.Threading.Tasks.Task Edit_PostValidEmployee_RedirectsToIndex()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);
        var employee = new Employee { Id = 5, FirstName = "John", LastName = "Doe", MiddleName = "Jr.", Email = "john@gmail.com" };
        context.Employees.Add(employee);
        await context.SaveChangesAsync();

        var controller = new EmployeesController(context);
        employee.FirstName = "Updated Name";

        // Act
        var result = await controller.Edit(5, employee);

        // Assert
        var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
        Assert.Equal("Index", redirectToActionResult.ActionName);
        var updatedEmployee = await context.Employees.FindAsync(5);
        Assert.Equal("Updated Name", updatedEmployee.FirstName); // Проверяем, что имя было обновлено
    }

    [Fact]
    public async System.Threading.Tasks.Task Edit_PostInvalidEmployee_ReturnsViewWithModel()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);
        var employee = new Employee { Id = 7, FirstName = "John", LastName = "Doe", MiddleName = "Jr.", Email = "john@gmail.com" };
        context.Employees.Add(employee);
        await context.SaveChangesAsync();

        var controller = new EmployeesController(context);
        controller.ModelState.AddModelError("FirstName", "Required"); // Добавим ошибку валидации

        // Act
        var result = await controller.Edit(7, employee);

        // Assert
        var viewResult = Assert.IsType<ViewResult>(result);
        var model = Assert.IsType<Employee>(viewResult.ViewData.Model);
        Assert.Equal(employee, model); // Модель возвращается на форму
    }

    [Fact]
    public async System.Threading.Tasks.Task DeleteConfirmed_RemovesEmployeeAndRedirectsToIndex()
    {
        // Arrange
        var options = new DbContextOptionsBuilder<ApplicationDbContext>()
            .UseInMemoryDatabase(databaseName: "TestDatabase")
            .Options;

        using var context = new ApplicationDbContext(options);
        var employee = new Employee { Id = 3, FirstName = "John", LastName = "Doe", MiddleName = "Jr.", Email = "john@gmail.com" };
        context.Employees.Add(employee);
        await context.SaveChangesAsync();

        var controller = new EmployeesController(context);

        // Act
        var result = await controller.Delete(1);

        // Assert
        var redirectToActionResult = Assert.IsType<ViewResult>(result);
        Assert.Equal(3, await context.Employees.CountAsync()); // Проверяем, что сотрудник был удален
    }

}
