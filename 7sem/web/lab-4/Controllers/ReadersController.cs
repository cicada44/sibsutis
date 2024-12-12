using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using lab_4.Data;
using lab_4.Models;
using System.Threading.Tasks;

namespace lab_4.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ReadersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public ReadersController(ApplicationDbContext context)
        {
            _context = context;
        }

        [HttpPost]
        public async Task<IActionResult> AddReader(Reader reader)
        {
            _context.Readers.Add(reader);
            await _context.SaveChangesAsync();
            return CreatedAtAction(nameof(GetReaderById), new { id = reader.Id }, reader);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> UpdateReader(int id, Reader updatedReader)
        {
            var reader = await _context.Readers.FindAsync(id);
            if (reader == null) return NotFound();

            reader.FullName = updatedReader.FullName;
            reader.BirthDate = updatedReader.BirthDate;

            await _context.SaveChangesAsync();
            return NoContent();
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteReader(int id)
        {
            var reader = await _context.Readers.FindAsync(id);
            if (reader == null) return NotFound();

            _context.Readers.Remove(reader);
            await _context.SaveChangesAsync();
            return NoContent();
        }

        [HttpPost("{readerId}/borrow/{bookId}")]
        public async Task<IActionResult> BorrowBook(int readerId, int bookId)
        {
            var reader = await _context.Readers.Include(r => r.BorrowedBooks).FirstOrDefaultAsync(r => r.Id == readerId);
            var book = await _context.Books.FindAsync(bookId);

            if (reader == null || book == null || book.Copies <= 0) return BadRequest("Invalid request");

            book.Copies--;
            reader.BorrowedBooks.Add(book);

            await _context.SaveChangesAsync();
            return Ok();
        }

        [HttpPost("{readerId}/return/{bookId}")]
        public async Task<IActionResult> ReturnBook(int readerId, int bookId)
        {
            var reader = await _context.Readers.Include(r => r.BorrowedBooks).FirstOrDefaultAsync(r => r.Id == readerId);
            var book = await _context.Books.FindAsync(bookId);

            if (reader == null || book == null || !reader.BorrowedBooks.Contains(book)) return BadRequest("Invalid request");

            book.Copies++;
            reader.BorrowedBooks.Remove(book);

            await _context.SaveChangesAsync();
            return Ok();
        }

        [HttpGet("{id}")]
        public async Task<IActionResult> GetReaderById(int id)
        {
            var reader = await _context.Readers.Include(r => r.BorrowedBooks).FirstOrDefaultAsync(r => r.Id == id);
            if (reader == null) return NotFound();
            return Ok(reader);
        }

        [HttpGet("search")]
        public async Task<IActionResult> SearchReaders(string namePart)
        {
            var readers = await _context.Readers.Where(r => r.FullName.Contains(namePart)).ToListAsync();
            return Ok(readers);
        }
    }
}
