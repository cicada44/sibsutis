using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using lab_4.Data;
using lab_4.Models;
using System.Threading.Tasks;

namespace lab_4.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class BooksController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public BooksController(ApplicationDbContext context)
        {
            _context = context;
        }

        [HttpPost]
        public async Task<IActionResult> AddBook(Book book)
        {
            _context.Books.Add(book);
            await _context.SaveChangesAsync();
            return CreatedAtAction(nameof(GetBookById), new { id = book.Id }, book);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> UpdateBook(int id, Book updatedBook)
        {
            var book = await _context.Books.FindAsync(id);
            if (book == null) return NotFound();

            book.Title = updatedBook.Title;
            book.Author = updatedBook.Author;
            book.ISBN = updatedBook.ISBN;
            book.Year = updatedBook.Year;
            book.Copies = updatedBook.Copies;

            await _context.SaveChangesAsync();
            return NoContent();
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteBook(int id)
        {
            var book = await _context.Books.FindAsync(id);
            if (book == null) return NotFound();

            _context.Books.Remove(book);
            await _context.SaveChangesAsync();
            return NoContent();
        }

        [HttpGet("{id}")]
        public async Task<IActionResult> GetBookById(int id)
        {
            var book = await _context.Books.FindAsync(id);
            if (book == null) return NotFound();
            return Ok(book);
        }

        [HttpGet("available")]
        public async Task<IActionResult> GetAvailableBooks()
        {
            var availableBooks = await _context.Books
                .Where(b => b.Copies > 0)
                .ToListAsync();
            return Ok(availableBooks);
        }

        [HttpGet("borrowed")]
        public async Task<IActionResult> GetBorrowedBooks()
        {
            var borrowedBooks = await _context.Books.Where(b => !b.IsAvailable).ToListAsync();
            return Ok(borrowedBooks);
        }

        [HttpGet("search")]
        public async Task<IActionResult> SearchBooks(string titlePart)
        {
            var books = await _context.Books.Where(b => b.Title.Contains(titlePart)).ToListAsync();
            return Ok(books);
        }
    }
}
