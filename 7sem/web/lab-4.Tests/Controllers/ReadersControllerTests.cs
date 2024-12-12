using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Xunit;
using lab_4.Controllers;
using lab_4.Data;
using lab_4.Models;

namespace lab_4.Tests.Controllers
{
    public class ReadersControllerTests
    {
        private readonly DbContextOptions<ApplicationDbContext> _options;

        public ReadersControllerTests()
        {
            _options = new DbContextOptionsBuilder<ApplicationDbContext>()
                .UseInMemoryDatabase(databaseName: "TestDatabaseReaders")
                .Options;
        }

        [Fact]
        public async Task AddReader_ReturnsCreatedAtActionResult()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new ReadersController(context);

            var newReader = new Reader { FullName = "John Doe", BirthDate = new DateTime(1990, 1, 1) };
            var result = await controller.AddReader(newReader);

            var createdAtActionResult = Assert.IsType<CreatedAtActionResult>(result);
            var reader = Assert.IsType<Reader>(createdAtActionResult.Value);
            Assert.Equal("John Doe", reader.FullName);
        }

        [Fact]
        public async Task UpdateReader_ReturnsNoContentResult()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new ReadersController(context);

            var reader = new Reader { Id = 2, FullName = "John Doe", BirthDate = new DateTime(1990, 1, 1) };
            context.Readers.Add(reader);
            await context.SaveChangesAsync();

            var updatedReader = new Reader { FullName = "Jane Doe", BirthDate = new DateTime(1992, 5, 5) };
            var result = await controller.UpdateReader(reader.Id, updatedReader);

            Assert.IsType<NoContentResult>(result);
            var dbReader = await context.Readers.FindAsync(reader.Id);
            Assert.Equal("Jane Doe", dbReader.FullName);
            Assert.Equal(new DateTime(1992, 5, 5), dbReader.BirthDate);
        }

        [Fact]
        public async Task DeleteReader_ReturnsNoContentResult()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new ReadersController(context);

            var reader = new Reader { Id = 4, FullName = "John Doe", BirthDate = new DateTime(1990, 1, 1) };
            context.Readers.Add(reader);
            await context.SaveChangesAsync();

            var result = await controller.DeleteReader(reader.Id);

            Assert.IsType<NoContentResult>(result);
            Assert.Null(await context.Readers.FindAsync(reader.Id));
        }

        [Fact]
        public async Task GetReaderById_ReturnsReaderWithBooks()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new ReadersController(context);

            var reader = new Reader { Id = 5, FullName = "John Doe", BirthDate = new DateTime(1990, 1, 1) };
            context.Readers.Add(reader);
            await context.SaveChangesAsync();

            var result = await controller.GetReaderById(reader.Id);
            var okResult = Assert.IsType<OkObjectResult>(result);
            var returnedReader = Assert.IsType<Reader>(okResult.Value);

            Assert.Equal("John Doe", returnedReader.FullName);
        }

        [Fact]
        public async Task BorrowBook_AddsBookToReaderAndUpdatesCopies()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new ReadersController(context);

            var reader = new Reader { Id = 6, FullName = "John Doe" };
            var book = new Book { Id = 1, Title = "Test Book", Author = "Author", ISBN = "12345", Year = 2020, Copies = 5 };

            context.Readers.Add(reader);
            context.Books.Add(book);
            await context.SaveChangesAsync();

            var result = await controller.BorrowBook(reader.Id, book.Id);
            Assert.IsType<OkResult>(result);

            var updatedBook = await context.Books.FindAsync(book.Id);
            Assert.Equal(4, updatedBook.Copies);
            Assert.Contains(book, context.Readers.Include(r => r.BorrowedBooks).FirstOrDefault(r => r.Id == reader.Id)?.BorrowedBooks);
        }

        [Fact]
        public async Task ReturnBook_RemovesBookFromReaderAndIncreasesCopies()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new ReadersController(context);

            var reader = new Reader { Id = 7, FullName = "John Doe" };
            var book = new Book { Id = 2, Title = "Test Book", Author = "Author", ISBN = "12345", Year = 2020, Copies = 0 };

            reader.BorrowedBooks.Add(book);
            context.Readers.Add(reader);
            context.Books.Add(book);
            await context.SaveChangesAsync();

            var result = await controller.ReturnBook(reader.Id, book.Id);
            Assert.IsType<OkResult>(result);

            var updatedBook = await context.Books.FindAsync(book.Id);
            Assert.Equal(1, updatedBook.Copies);
            Assert.DoesNotContain(book, context.Readers.Include(r => r.BorrowedBooks).FirstOrDefault(r => r.Id == reader.Id)?.BorrowedBooks);
        }

        [Fact]
        public async Task SearchReaders_ReturnsMatchingReaders()
        {
            using var context = new ApplicationDbContext(_options);
            var controller = new ReadersController(context);

            var result = await controller.SearchReaders("John");
            var okResult = Assert.IsType<OkObjectResult>(result);
            var readers = Assert.IsAssignableFrom<List<Reader>>(okResult.Value);

            Assert.Equal("John Doe", readers[0].FullName);
        }
    }
}
