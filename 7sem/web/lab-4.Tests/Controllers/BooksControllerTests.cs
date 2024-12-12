using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Xunit;
using lab_4.Controllers;
using lab_4.Data;
using lab_4.Models;

namespace lab_4.Tests.Controllers
{
    public class BooksControllerTests
    {
        private readonly DbContextOptions<ApplicationDbContext> _options;

        public BooksControllerTests()
        {
            _options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabase")
                .Options;
        }

        [Fact]
        public async Task AddBook_ReturnsCreatedAtActionResult()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new BooksController(context);

            var newBook = new Book { Title = "Book Title 1", Author = "Author1", ISBN = "1", Year = 2020, Copies = 5 };
            var result = await controller.AddBook(newBook);

            var createdAtActionResult = Assert.IsType<CreatedAtActionResult>(result);
            var book = Assert.IsType<Book>(createdAtActionResult.Value);
            Assert.Equal("Book Title 1", book.Title);
        }

        [Fact]
        public async Task UpdateBook_ReturnsNoContentResult()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new BooksController(context);

            var book = new Book { Id = 22, Title = "Title 2", Author = "Author2", ISBN = "2", Year = 2020, Copies = 5 };
            context.Books.Add(book);
            await context.SaveChangesAsync();

            var updatedBook = new Book { Title = "Updated Title2", Author = "Updated Author2", ISBN = "2", Year = 2021, Copies = 3 };
            var result = await controller.UpdateBook(book.Id, updatedBook);

            Assert.IsType<NoContentResult>(result);
            var dbBook = await context.Books.FindAsync(book.Id);
            Assert.Equal("Updated Title2", dbBook.Title);
            Assert.Equal("Updated Author2", dbBook.Author);
        }

        [Fact]
        public async Task DeleteBook_ReturnsNoContentResult()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new BooksController(context);

            var book = new Book { Id = 44, Title = "Book Title 3", Author = "Author3", ISBN = "3", Year = 2020, Copies = 5 };
            context.Books.Add(book);
            await context.SaveChangesAsync();

            var result = await controller.DeleteBook(book.Id);

            Assert.IsType<NoContentResult>(result);
            Assert.Null(await context.Books.FindAsync(book.Id));
        }

        [Fact]
        public async Task GetBookById_ReturnsBook()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new BooksController(context);

            var book = new Book { Id = 55, Title = "Book Title 4", Author = "Author4", ISBN = "4", Year = 2020, Copies = 5 };
            context.Books.Add(book);
            await context.SaveChangesAsync();

            var result = await controller.GetBookById(book.Id);
            var okResult = Assert.IsType<OkObjectResult>(result);
            var returnedBook = Assert.IsType<Book>(okResult.Value);
            Assert.Equal("Book Title 4", returnedBook.Title);
        }

        [Fact]
        public async Task GetAvailableBooks_ReturnsAvailableBooks()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new BooksController(context);

            context.Books.AddRange(
                new Book { Title = "Available Book", Author = "Author", ISBN = "12345", Year = 2020, Copies = 5 },
                new Book { Title = "Unavailable Book", Author = "Author", ISBN = "67890", Year = 2021, Copies = 0 }
            );
            await context.SaveChangesAsync();
            await controller.DeleteBook(1);

            var result = await controller.GetAvailableBooks();
            var okResult = Assert.IsType<OkObjectResult>(result);
            var books = Assert.IsAssignableFrom<List<Book>>(okResult.Value);

            Assert.Single(books);
            Assert.Equal("Available Book", books[0].Title);
        }

        [Fact]
        public async Task SearchBooks_ReturnsMatchingBooks()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new BooksController(context);

            context.Books.AddRange(
                new Book { Title = "Programming in C#", Author = "Author1", ISBN = "12345", Year = 2020, Copies = 5 },
                new Book { Title = "Learning Python", Author = "Author2", ISBN = "67890", Year = 2021, Copies = 3 }
            );
            await context.SaveChangesAsync();

            var result = await controller.SearchBooks("Programming");
            var okResult = Assert.IsType<OkObjectResult>(result);
            var books = Assert.IsAssignableFrom<List<Book>>(okResult.Value);

            Assert.Single(books);
            Assert.Equal("Programming in C#", books[0].Title);
        }
    }
}
