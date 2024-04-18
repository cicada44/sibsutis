#pragma once

#include <iostream>

#include <cassert>
#include <cstring>
#include <utility>

namespace matrix_t {

template <typename T, typename Allocator = std::allocator<T>>
class matrix {
public:
    explicit matrix(size_t rows = 0, size_t cols = 0, std::allocator<T> allocator = std::allocator<T>())
        : m_Rows(rows), m_Cols(cols), m_Capacity(rows * 2 * cols), m_Allocator(allocator) {
        if (rows == 0 || cols == 0) throw std::runtime_error("Matrix can't contain zero rows or columns");
        m_Data = m_Allocator.allocate(m_Capacity);
    }

    matrix(const std::initializer_list<std::initializer_list<T>>& il) : matrix(il.size(), il.begin()->size()) {
        size_t j = 0, stable_cols = il.begin()->size();
        for (const auto& il_i : il) {
            if (il_i.size() != stable_cols)
                throw std::runtime_error("Matrix must contain same number of elements in each column");
            for (const auto& il_j : il_i) m_Data[j++] = il_j;
        }
    }

    matrix(const matrix<T>& other) : matrix(other.m_Rows, other.m_Cols) {
        std::memcpy(m_Data, other.m_Data, m_Rows * m_Cols * sizeof(T));
    }

    matrix(matrix<T>&& other) noexcept { swap(other); }

    matrix<T>& operator=(const matrix<T>& other) noexcept {
        if (this != &other) {
            m_Allocator.deallocate(m_Data, m_Capacity);
            m_Capacity = other.m_Capacity;
            m_Rows = other.m_Rows;
            m_Cols = other.m_Cols;
            m_Data = m_Allocator.allocate(m_Capacity);
            std::memcpy(m_Data, other.m_Data, m_Rows * m_Cols * sizeof(T));
        }
        return *this;
    }

    matrix<T>& operator=(matrix<T>&& other) noexcept {
        if (this != &other) {
            m_Allocator.deallocate(m_Data, m_Capacity);
            swap(other);
        }
        return *this;
    }

    // C++23
    // inline T operator[](size_t i, size_t j) noexcept { return m_Data[getIdx(i, j)]; }

    inline const T& at(size_t i, size_t j) const {
        if (i >= m_Rows || j >= m_Cols) throw std::out_of_range("Indexes is out of range");
        return m_Data[getIdx(i, j)];
    }

    inline T& at(size_t i, size_t j) {
        if (i >= m_Rows || j >= m_Cols) throw std::out_of_range("Indexes is out of range");
        return m_Data[getIdx(i, j)];
    }

    inline void shrink_to_fit() & {
        const size_t new_capa = m_Rows * m_Cols;
        m_Data = reallocData(new_capa);
        m_Capacity = size();
    }

    inline void reserve(size_t new_capa) & {
        if (new_capa <= m_Capacity) return;
        m_Data = reallocData(new_capa);
        m_Capacity = new_capa;
    }

    inline void resize_row(size_t count, const T& defaultValue = T{}) {
        if (count == m_Rows || count == 0) return;
        if (count > m_Rows) {
            if (count * m_Cols > m_Capacity) reserve(m_Capacity + count * m_Cols);
            for (size_t i = m_Rows; i != count; ++i)
                for (size_t j = 0; j != m_Cols; ++j) m_Data[getIdx(i, j)] = defaultValue;
        }
        m_Rows = count;
    }

    inline void resize_col(size_t count, const T& defaultValue = T{}) {
        if (count == m_Cols || count == 0) return;
        T* newStorage = m_Allocator.allocate(m_Rows * count);
        if (count * m_Rows > m_Capacity) reserve(m_Capacity + count * m_Rows);
        for (size_t i = 0; i < m_Rows; ++i) {
            for (size_t j = 0; j < std::min(m_Cols, count); ++j) newStorage[getIdx(i, j, count)] = m_Data[getIdx(i, j)];
            for (size_t j = m_Cols; j < count; ++j) newStorage[getIdx(i, j, count)] = defaultValue;
        }
        if (std::is_trivially_copyable<T>())
            std::memcpy(m_Data, newStorage, count * m_Rows * sizeof(T));
        else
            for (size_t i = 0; i != count * m_Rows; ++i) m_Data[i] = newStorage[i];
        m_Allocator.deallocate(newStorage, m_Rows * count);
        m_Cols = count;
    }

    inline void resize(size_t row, size_t col, const T& defaultValue = T{}) {
        resize_row(row, defaultValue);
        resize_col(col, defaultValue);
    }

    inline void insert_row(size_t pos, const std::initializer_list<T>& il) {
        if (il.size() != m_Cols) throw std::runtime_error("The size of inserted row don't fit matrix");
        if (pos > m_Rows) throw std::out_of_range("Can't insert row after matrix end");
        if (m_Capacity < (m_Rows + 1) * m_Cols) reserve((m_Capacity + m_Cols) * 2);
        for (long i = m_Rows + 1; i >= static_cast<long>(pos) + 1; --i) {
            for (long j = m_Cols; j >= 0; --j) {
                m_Data[i * m_Cols + j] = m_Data[(i - 1) * m_Cols + j];
            }
        }
        size_t i = 0;
        for (const auto& c : il) m_Data[pos * m_Cols + i++] = c;
        ++m_Rows;
    }

    inline void insert_col(size_t pos, const std::initializer_list<T>& il) {
        if (il.size() != m_Rows) throw std::runtime_error("The size of inserted column don't fit matrix");
        if (pos > m_Cols) throw std::out_of_range("Can't insert column after matrix end");
        if (m_Capacity < m_Rows * (m_Cols + 1)) reserve((m_Capacity + m_Rows) * 2);
        matrix<T> temp(m_Rows, m_Cols + 1);  // Evgeny Sergeevich, I HATE THIS, but i was forsed!!!
        for (size_t i = 0; i < m_Rows; ++i)
            for (size_t j = 0; j < m_Cols; ++j) temp.at(i, j + ((j >= pos) ? 1 : 0)) = m_Data[getIdx(i, j)];
        for (size_t i = 0; i < m_Rows; ++i) temp.at(i, pos) = *(il.begin() + i);
        for (size_t i = 0; i < m_Rows; ++i)
            for (size_t j = 0; j < m_Cols + 1; ++j) m_Data[i * (m_Cols + 1) + j] = temp.at(i, j);
        ++m_Cols;
    }

    inline void push_back_row(const std::initializer_list<T>& il) { insert_row(m_Rows, il); }

    inline void push_back_col(const std::initializer_list<T>& il) { insert_col(m_Cols, il); }

    void erase_row(size_t idx) {
        if (idx >= m_Rows) throw std::out_of_range("Index is out of range");
        for (size_t i = idx; i < m_Rows - 1; ++i)
            for (size_t j = 0; j < m_Cols; ++j) m_Data[getIdx(i, j)] = m_Data[(i + 1) * m_Cols + j];
        m_Rows--;
    }

    void erase_col(size_t idx) {
        if (idx > m_Cols) throw std::out_of_range("Can't delete column after matrix end");
        for (size_t i = 0; i != m_Rows * m_Cols; ++i)
            if ((idx == m_Cols - 1 && i % idx == 0 && i != 0) || (idx != m_Cols - 1 && i % (m_Cols - 1) == idx))
                for (size_t j = i; j != m_Rows * m_Cols; ++j) m_Data[j] = m_Data[j + 1];
        --m_Cols;
    }

    void erase(size_t row, size_t col) {
        erase_row(row);
        erase_col(col);
    }

    inline size_t rows() const { return m_Rows; }
    inline size_t cols() const { return m_Cols; }
    inline size_t size() const { return m_Rows * m_Cols; }
    inline size_t capacity() const { return m_Capacity; }

    inline bool empty() const { return (m_Rows == 0 || m_Cols == 0); }

    virtual ~matrix() { m_Allocator.deallocate(m_Data, m_Capacity); };

    using value_type = T;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    template <typename U, bool R = false>
    class matrix_iter {
    private:
        friend class matrix_t;

    public:
        explicit matrix_iter(T* n) noexcept : current_(n) {}

        // using value_type = matrix_t::value_type;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::bidirectional_iterator_tag;

        reference operator*() const noexcept {
            assert(current_ != nullptr);
            return *current_;
        }

        matrix_iter& operator++() noexcept {
            assert(current_ != nullptr);
            (!R) ? ++current_ : --current_;
            return *this;
        }

        matrix_iter& operator--() noexcept {
            assert(current_ != nullptr);
            (!R) ? --current_ : ++current_;
            return *this;
        }

        matrix_iter operator++(int) noexcept {
            assert(current_ != nullptr);
            auto prev = *this;
            (!R) ? current_ += sizeof(T) : current_ -= sizeof(T);
            return prev;
        }

        matrix_iter operator--(int) noexcept {
            assert(current_ != nullptr);
            auto next = *this;
            (!R) ? current_ -= sizeof(T) : current_ += sizeof(T);
            return next;
        }

        bool operator==(matrix_iter iter) noexcept { return iter.current_ == current_; }

        bool operator!=(matrix_iter iter) noexcept { return !(*this == iter); }

    private:
        const T* Get() const noexcept { return current_; }
        T* current_;
    };

    using base_iterator = matrix_iter<T>;
    using const_iterator = matrix_iter<const T>;
    using reverse_iterator = matrix_iter<T, true>;
    using const_reverse_iterator = matrix_iter<const T, true>;

    const_iterator cbegin() const { return const_iterator{m_Data}; }
    const_iterator cend() const { return const_iterator{m_Data + size()}; }
    base_iterator begin() const { return base_iterator{m_Data}; }
    base_iterator end() const { return base_iterator{m_Data + size()}; }
    reverse_iterator rbegin() const { return reverse_iterator{m_Data + size() - 1}; }
    reverse_iterator rend() const { return reverse_iterator{m_Data - 1}; }
    const_reverse_iterator crbegin() const { return const_reverse_iterator{m_Data + size() - 1}; }
    const_reverse_iterator crend() const { return const_reverse_iterator{m_Data - 1}; }

private:
    T* m_Data = nullptr;
    size_t m_Rows = 0;
    size_t m_Cols = 0;
    size_t m_Capacity = 0;

    std::allocator<T> m_Allocator;

protected:
    inline size_t getIdx(size_t i, size_t j) const noexcept { return (i * m_Cols + j); }

    inline size_t getIdx(size_t i, size_t j, size_t cols) const noexcept { return (i * cols + j); }

    inline T* reallocData(size_t new_capa) noexcept {
        T* newStorage = m_Allocator.allocate(new_capa);
        std::memcpy(newStorage, m_Data, m_Rows * m_Cols * sizeof(T));
        m_Allocator.deallocate(m_Data, m_Capacity);
        m_Data = m_Allocator.allocate(new_capa);
        std::memcpy(m_Data, newStorage, m_Rows * m_Cols * sizeof(T));
        m_Allocator.deallocate(newStorage, m_Capacity);
        return m_Data;
    }

    inline void swap(matrix<T> other) noexcept {
        std::swap(m_Data, other.m_Data);
        std::swap(m_Capacity, other.m_Capacity);
        std::swap(m_Rows, other.m_Rows);
        std::swap(m_Cols, other.m_Cols);
        other.m_Data = nullptr;
    }
};

template <typename T>
bool operator==(const matrix<T>& m1, const matrix<T>& m2) {
    if (m1.size() != m2.size() || m1.rows() != m2.rows() || m1.cols() != m2.cols()) return false;
    for (size_t i = 0; i != m1.rows(); ++i)
        for (size_t j = 0; j != m1.cols(); ++j)
            if (m1.at(i, j) != m2.at(i, j)) return false;
    return true;
}

}  // namespace matrix_t
