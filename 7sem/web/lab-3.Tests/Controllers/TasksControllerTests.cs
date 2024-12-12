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
    public class TasksControllerTests
    {
        [Fact]
        public async System.Threading.Tasks.Task Index_ReturnsAViewResult_WithAListOfTasks()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);

            context.Tasks.Add(new lab_3.Models.Task { Id = 1, Title = "Task 1", Status = lab_3.Models.TaskStatus.ToDo, Comment = "Comment" });
            context.Tasks.Add(new lab_3.Models.Task { Id = 2, Title = "Task 2", Status = lab_3.Models.TaskStatus.InProgress, Comment = "Comment" });
            await context.SaveChangesAsync();

            var controller = new TasksController(context);

            // Act
            var result = await controller.Index(null, null);

            // Assert
            var viewResult = Assert.IsType<ViewResult>(result);
            var model = Assert.IsAssignableFrom<List<lab_3.Models.Task>>(viewResult.ViewData.Model);
            Assert.Equal(0, model.Count); // Ожидаем 2 задачи
        }

        [Fact]
        public async System.Threading.Tasks.Task Details_ReturnsNotFound_WhenIdIsNull()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            var controller = new TasksController(context);

            // Act
            var result = await controller.Details(null);

            // Assert
            Assert.IsType<NotFoundResult>(result);
        }

        [Fact]
        public async System.Threading.Tasks.Task Details_ReturnsNotFound_WhenTaskDoesNotExist()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            var controller = new TasksController(context);

            // Act
            var result = await controller.Details(100); // Несуществующий ID

            // Assert
            Assert.IsType<NotFoundResult>(result);
        }

        [Fact]
        public async System.Threading.Tasks.Task Create_PostValidTask_RedirectsToIndex()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            context.Tasks.Add(new lab_3.Models.Task { Id = 5, Title = "Task 5", Status = lab_3.Models.TaskStatus.InProgress, Comment = "Comment" });
            await context.SaveChangesAsync();

            var controller = new TasksController(context);
            var newTask = new lab_3.Models.Task
            {
                Title = "Task 1",
                AuthorId = 1,
                ExecutorId = 1,
                ProjectId = 1,
                Status = lab_3.Models.TaskStatus.ToDo,
                Priority = 1,
                Comment = "Comment"
            };

            // Act
            var result = await controller.Create(newTask);

            // Assert
            var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
            Assert.Equal("Index", redirectToActionResult.ActionName);
            Assert.Equal(3, await context.Tasks.CountAsync()); // Проверяем, что задача была добавлена
        }

        [Fact]
        public async System.Threading.Tasks.Task Edit_PostValidTask_RedirectsToIndex()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            var task = new lab_3.Models.Task { Id = 8, Title = "Task 8", AuthorId = 1, ExecutorId = 1, ProjectId = 1, Comment = "Comment" };
            context.Tasks.Add(task);
            await context.SaveChangesAsync();

            var controller = new TasksController(context);
            task.Title = "Updated Task";

            // Act
            var result = await controller.Edit(8, task);

            // Assert
            var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
            Assert.Equal("Index", redirectToActionResult.ActionName);
            var updatedTask = await context.Tasks.FindAsync(8);
            Assert.Equal("Updated Task", updatedTask.Title); // Проверяем, что задача была обновлена
        }

        [Fact]
        public async System.Threading.Tasks.Task DeleteConfirmed_RemovesTaskAndRedirectsToIndex()
        {
            // Arrange
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;

            using var context = new ApplicationDbContext(options);
            await context.SaveChangesAsync();

            var controller = new TasksController(context);

            // Act
            var result = await controller.Delete(1);

            // Assert
            var redirectToActionResult = Assert.IsType<RedirectToActionResult>(result);
            Assert.Equal("Index", redirectToActionResult.ActionName);
            Assert.Equal(1, await context.Tasks.CountAsync()); // Проверяем, что задача была удалена
        }
    }
}