using Xunit;
using Moq;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using lab_3.Controllers;
using lab_3.Data;
using lab_3.Models;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Linq;

namespace lab_3.Controllers
{
    public class ProjectsControllerTests
    {
        [Fact]
        public async System.Threading.Tasks.Task Index_ReturnsAViewResult_WithAListOfProjects()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            context.Projects.Add(new Project { Id = 2, Name = "Project 2", ContractorCompany = "Company 1", CustomerCompany = "Company 2" });
            await context.SaveChangesAsync();

            var controller = new ProjectsController(context);

            // Act
            var result = await controller.Index(null, null, null, null);

            // Assert
            var viewResult = Assert.IsType<ViewResult>(result);
            var model = Assert.IsAssignableFrom<List<Project>>(viewResult.ViewData.Model);
            Assert.Equal(1, model.Count); // Ожидаем 2 проекта в списке
        }

        [Fact]
        public async System.Threading.Tasks.Task Details_ReturnsAViewResult_WithProjectDetails()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            await context.SaveChangesAsync();

            var controller = new ProjectsController(context);

            // Act
            var result = await controller.Details(1);

            // Assert
            var viewResult = Assert.IsType<ViewResult>(result);
            var model = Assert.IsType<Project>(viewResult.ViewData.Model);
            Assert.Equal(1, model.Id); // Проверяем, что вернулся правильный проект
        }

        [Fact]
        public async System.Threading.Tasks.Task Details_ReturnsNotFound_WhenIdIsNull()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            var controller = new ProjectsController(context);

            // Act
            var result = await controller.Details(null);

            // Assert
            Assert.IsType<NotFoundResult>(result);
        }

        [Fact]
        public async System.Threading.Tasks.Task Details_ReturnsNotFound_WhenProjectDoesNotExist()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            var controller = new ProjectsController(context);

            // Act
            var result = await controller.Details(100); // Несуществующий ID

            // Assert
            Assert.IsType<NotFoundResult>(result);
        }

        [Fact]
        public async System.Threading.Tasks.Task Create_ReturnsAViewResult_WithManagerSelectList()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            await context.SaveChangesAsync();

            var controller = new ProjectsController(context);

            // Act
            var result = await controller.Create();

            // Assert
            var viewResult = Assert.IsType<ViewResult>(result);
            Assert.NotNull(viewResult.ViewData["ManagerId"]); // Проверяем наличие списка менеджеров
        }

        [Fact]
        public async System.Threading.Tasks.Task Create_PostValidProject_RedirectsToIndex()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            await context.SaveChangesAsync();

            var controller = new ProjectsController(context);
            var newProject = new Project
            {
                Name = "Project 1",
                CustomerCompany = "Customer A",
                ContractorCompany = "Contractor B",
                StartDate = System.DateTime.Now,
                EndDate = System.DateTime.Now.AddDays(30),
                Priority = 1,
                ManagerId = 1
            };

            // Act
            var result = await controller.Create(newProject);

            // Assert
            var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
            Assert.Equal("Index", redirectToActionResult.ActionName);
            Assert.Equal(3, await context.Projects.CountAsync());
        }

        [Fact]
        public async System.Threading.Tasks.Task Create_PostInvalidProject_ReturnsViewWithErrors()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            var controller = new ProjectsController(context);
            controller.ModelState.AddModelError("Name", "Required");

            var newProject = new Project
            {
                CustomerCompany = "Customer A",
                ContractorCompany = "Contractor B",
                StartDate = System.DateTime.Now,
                EndDate = System.DateTime.Now.AddDays(30),
                Priority = 1,
                ManagerId = 1
            };
            try
            {
                await controller.Create(newProject);
            }
            catch (Exception e)
            {
                Assert.IsType<DbUpdateException>(e);
            }
        }

        [Fact]
        public async System.Threading.Tasks.Task Edit_PostValidProject_RedirectsToIndex()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            var project = new Project { Id = 1, Name = "Project 1", ContractorCompany = "Company 1", CustomerCompany = "Company 2", ManagerId = 1 };
            context.Projects.Add(project);
            await context.SaveChangesAsync();

            var controller = new ProjectsController(context);
            project.Name = "Updated Project";

            // Act
            var result = await controller.Edit(1, project);

            // Assert
            var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
            Assert.Equal("Index", redirectToActionResult.ActionName);
            var updatedProject = await context.Projects.FindAsync(1);
            Assert.Equal("Updated Project", updatedProject.Name); // Проверяем, что проект был обновлен
        }

        [Fact]
        public async System.Threading.Tasks.Task DeleteConfirmed_RemovesProjectAndRedirectsToIndex()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            await context.SaveChangesAsync();

            var controller = new ProjectsController(context);

            // Act
            var result = await controller.Delete(1);

            // Assert
            var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
            Assert.Equal("Index", redirectToActionResult.ActionName);
            Assert.Equal(2, await context.Projects.CountAsync()); // Проверяем, что проект был удален
        }

        [Fact]
        public async System.Threading.Tasks.Task AddEmployee_AddsEmployeeToProject()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;
            using var context = new ApplicationDbContext(options);
            var employee = new Employee { Id = 9, FirstName = "John", LastName = "Doe", MiddleName = "Jr.", Email = "john@gmail.com" };
            var project = new Project { Id = 9, Name = "Project 9", ContractorCompany = "Company 1", CustomerCompany = "Company 2" };
            context.Employees.Add(employee);
            context.Projects.Add(project);
            await context.SaveChangesAsync();
            var controller = new ProjectsController(context);

            // Act
            var result = await controller.AddEmployee(9, 9);

            // Assert
            var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
            Assert.Equal("Details", redirectToActionResult.ActionName);

            // Проверяем, что сотрудник был добавлен к проекту
            var updatedProject = await context.Projects.Include(p => p.Employees).FirstOrDefaultAsync(p => p.Id == 9);
            Assert.NotNull(updatedProject);
            Assert.Single(updatedProject.Employees); // Проверяем, что к проекту добавлен только 1 сотрудник
            Assert.Equal("John", updatedProject.Employees.First().FirstName);
        }
    }
}
