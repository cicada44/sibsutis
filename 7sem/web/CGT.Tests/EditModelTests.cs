using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Options;
using Moq;
using f1news.Data;
using f1news.Models;
using f1news.Pages.Posts;
using System.Collections.Generic;
using System.Security.Claims;
using Xunit;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;

namespace f1news.Tests
{
    public class EditModelTests
    {
        private ApplicationDbContext GetTestDbContext()
        {
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase("TestDatabase_Edit")
                .Options;
            return new ApplicationDbContext(options);
        }

        private Mock<UserManager<IdentityUser>> GetMockUserManager()
        {
            var store = new Mock<IUserStore<IdentityUser>>();
            return new Mock<UserManager<IdentityUser>>(
                store.Object, null, null, null, null, null, null, null, null);
        }

        [Fact]
        public void OnGet_AdminUser_ReturnsPage()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            // Добавляем тестовый пост
            var testPost = new Post { Id = 3, Title = "Test Post", Content = "Test Content" };
            dbContext.Posts.Add(testPost);
            dbContext.SaveChanges();

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("admin@example.com");

            var editModel = new EditModel(dbContext, userManager.Object, adminSettings);

            // Act
            var result = editModel.OnGet(3);

            // Assert
            Assert.IsType<PageResult>(result);
            Assert.Equal(testPost.Title, editModel.Post.Title); // Проверяем, что пост загружен
        }

        [Fact]
        public void OnGet_NonAdminUser_ReturnsForbid()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("user@example.com");

            var editModel = new EditModel(dbContext, userManager.Object, adminSettings);

            // Act
            var result = editModel.OnGet(1);

            // Assert
            Assert.IsType<ForbidResult>(result);
        }

        [Fact]
        public void OnGet_PostNotFound_ReturnsNotFound()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("admin@example.com");

            var editModel = new EditModel(dbContext, userManager.Object, adminSettings);

            // Act
            var result = editModel.OnGet(99); // Невалидный ID

            // Assert
            Assert.IsType<NotFoundResult>(result);
        }

        [Fact]
        public void OnPost_ValidAdminUser_UpdatesPostAndRedirects()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            // Добавляем тестовый пост
            var testPost = new Post { Id = 22, Title = "Old Title", Content = "Old Content" };
            dbContext.Posts.Add(testPost);
            dbContext.SaveChanges();

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("admin@example.com");

            // Используем объект, который уже отслеживается в DbContext
            var editModel = new EditModel(dbContext, userManager.Object, adminSettings)
            {
                Post = dbContext.Posts.Find(22) // Получаем отслеживаемый объект из контекста
            };

            // Обновляем данные поста
            editModel.Post.Title = "New Title";
            editModel.Post.Content = "New Content";

            // Act
            var result = editModel.OnPost();

            // Assert
            Assert.IsType<RedirectToPageResult>(result);

            var updatedPost = dbContext.Posts.Find(22);
            Assert.Equal("New Title", updatedPost.Title); // Проверяем, что пост обновился
            Assert.Equal("New Content", updatedPost.Content);
        }

        [Fact]
        public void OnPost_InvalidModel_ReturnsPage()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("admin@example.com");

            var editModel = new EditModel(dbContext, userManager.Object, adminSettings)
            {
                Post = new Post { Id = 1, Title = "", Content = "New Content" } // Пустой заголовок
            };
            editModel.ModelState.AddModelError("Title", "The Title field is required."); // Добавляем ошибку модели

            // Act
            var result = editModel.OnPost();

            // Assert
            Assert.IsType<PageResult>(result);
        }

        [Fact]
        public void OnPost_NonAdminUser_ReturnsForbid()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("user@example.com");

            var editModel = new EditModel(dbContext, userManager.Object, adminSettings)
            {
                Post = new Post { Id = 1, Title = "New Title", Content = "New Content" }
            };

            // Act
            var result = editModel.OnPost();

            // Assert
            Assert.IsType<ForbidResult>(result);
        }
    }
}
