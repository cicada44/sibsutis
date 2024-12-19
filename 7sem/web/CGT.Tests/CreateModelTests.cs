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
    public class CreateModelTests
    {
        private ApplicationDbContext GetTestDbContext()
        {
            var options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase("TestDatabase")
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

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("admin@example.com");

            var createModel = new CreateModel(dbContext, userManager.Object, adminSettings);

            // Act
            var result = createModel.OnGet();

            // Assert
            Assert.IsType<PageResult>(result);
        }

        [Fact]
        public void OnGet_NonAdminUser_ReturnsForbid()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("user@example.com");

            var createModel = new CreateModel(dbContext, userManager.Object, adminSettings);

            // Act
            var result = createModel.OnGet();

            // Assert
            Assert.IsType<ForbidResult>(result);
        }

        [Fact]
        public void OnPost_ValidAdminUser_AddsPostAndRedirects()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("admin@example.com");

            var createModel = new CreateModel(dbContext, userManager.Object, adminSettings)
            {
                Post = new Post { Title = "Test Post", Content = "This is a test post." }
            };

            // Act
            var result = createModel.OnPost();

            // Assert
            Assert.IsType<RedirectToPageResult>(result);
            Assert.Equal(1, dbContext.Posts.CountAsync().Result); // Проверяем, что пост был добавлен
        }

        [Fact]
        public void OnPost_InvalidModel_ReturnsPage()
        {
            // Arrange
            var dbContext = GetTestDbContext();
            var userManager = GetMockUserManager();
            var adminSettings = Options.Create(new AdminSettings { AdminEmail = "admin@example.com" });

            userManager.Setup(um => um.GetUserName(It.IsAny<ClaimsPrincipal>())).Returns("admin@example.com");

            var createModel = new CreateModel(dbContext, userManager.Object, adminSettings);
            createModel.ModelState.AddModelError("Title", "The Title field is required."); // Добавляем ошибку модели

            // Act
            var result = createModel.OnPost();

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

            var createModel = new CreateModel(dbContext, userManager.Object, adminSettings)
            {
                Post = new Post { Title = "Test Post", Content = "This is a test post." }
            };

            // Act
            var result = createModel.OnPost();

            // Assert
            Assert.IsType<ForbidResult>(result);
        }
    }
}
