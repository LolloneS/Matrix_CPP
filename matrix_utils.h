#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H
#include <iostream>


/** 
 * https://en.wikipedia.org/wiki/Decorator_pattern
 * "In object-oriented programming, the decorator pattern is a design pattern that 
 * allows behavior to be added to an individual object, dynamically, 
 * without affecting the behavior of other objects from the same class"
 * 
 * We want to specify some specific behaviour of our "Standard" Matrix, reusing the base
 * class as much as possible.
 * This means we will have a component_matrix and many decorator_matrix's
 */


/**
 * Here some classs will be used. These are just "flags" useful to understand
 * which kind of decorated matrix we are dealing with
 */ 


// useful to avoid specifying anything when we don't want to decorate a matrix
struct basic_matrix;

// decoration that takes a submatrix of a matrix
template <typename decorator_matrix> 
class submatrix;

// decoration that takes the diagonal vector of a matrix
template <typename decorator_matrix> 
class diagonal;

// decoration that creates a diagonal matrix starting from a vector
template <typename decorator_matrix> 
class diagonalmatrix;

// decoration that consists in the transpose of a basic matrix
template <typename decorator_matrix> 
class transpose_matrix;

// matrix base class, will be decorated for the rest of things
template <typename T, typename type = basic_matrix>
class matrix;

template <typename T, typename type>
class column_iterator;

template <typename T, typename type>
class const_column_iterator;

template <typename T, typename type>
class iterator_limited;

template <typename T, typename type>
class const_iterator_limited;


/**
    @brief Output stream operator

    Easily print a matrix on stdout (by rows)

    @param os output stream
    @param m matrix we want to print

    @return reference to output stream
**/
template <typename T, typename type>
std::ostream& operator<<(std::ostream &os, const matrix<T, type> &m) {
    unsigned int columns = m.get_cols();
    for (unsigned int j = 0; j < m.get_rows(); j++) {
        auto i = m.begin(j);
        auto ie = m.end(j);
        unsigned int k = 0;
        for (; i != ie; ++i) {
            ++k;
            os << *i << " ";
            if (columns == k) {
                os << std::endl;
                k = 0;
            }
        }
    }
    return os;
}


template <typename T, typename type>
class column_iterator {
    friend class matrix<T, type>;
    friend class const_column_iterator<T, type>;
    matrix<T, type> &m;
    unsigned int current_row;
    unsigned int current_column;

public:
    column_iterator(matrix<T, type> &mm, unsigned int r, unsigned int c) :
            m(mm), current_row(r), current_column(c) {}

    column_iterator &operator++() {
        if (current_row == m.get_rows() - 1) {
            current_column++;
            current_row = 0;
        }
        else {
            current_row++;
        }
        return *this;
    }

    column_iterator &operator++(int) {
        if (current_row == m.get_rows() - 1) {
            current_column++;
            current_row = 0;
        }
        else {
            current_row++;
        }
        return *this;
    }

    T &operator*() {
        return m(current_row, current_column);
    }

    const T &operator*() const {
        return m(current_row, current_column);
    }

    bool operator==(const column_iterator &other) const {
        return (this->current_row == other.current_row &&
                this->current_column == other.current_column);
    }

    bool operator!=(const column_iterator &other) const {
        return !(*this == other);
    }

    bool operator==(const const_column_iterator<T, type> &other) const {
        return (this->current_row == other.current_row &&
                this->current_column == other.current_column);
    }

    bool operator!=(const const_column_iterator<T, type> &other) const {
        return !(*this == other);
    }
};

template <typename T, typename type>
class const_column_iterator {
    friend class matrix<T, type>;
    friend class column_iterator<T, type>;
    const matrix<T, type> &m;
    unsigned int current_row;
    unsigned int current_column;

public:
    const_column_iterator(const matrix<T, type> &mm, unsigned int r, unsigned int c) :
            m(mm), current_row(r), current_column(c) {}

    const_column_iterator& operator++() {
        if (current_row == m.get_rows() - 1) {
            current_column++;
            current_row = 0;
        }
        else {
            current_row++;
        }
        return *this;
    }

    const_column_iterator& operator++(int) {
        if (current_row == m.get_rows() - 1) {
            current_column++;
            current_row = 0;
        }
        else {
            current_row++;
        }
        return *this;
    }

    const T &operator*() const {
        return m(current_row, current_column);
    }

    bool operator==(const const_column_iterator &other) const {
        return (this->current_row == other.current_row && this->current_column == other.current_column);
    }

    bool operator!=(const const_column_iterator &other) const {
        return !(*this == other);
    }

    bool operator==(const column_iterator<T, type> &other) const {
        return (this->current_row == other.current_row && this->current_column == other.current_column);
    }

    bool operator!=(const column_iterator<T, type> &other) const {
        return !(*this == other);
    }
};


template <typename T, typename type>
class iterator_limited {
    matrix<T, type> &m;
    unsigned int row;
    unsigned int column;

public:
    iterator_limited(matrix<T, type> &mm, unsigned int r, unsigned int c) :
            m(mm), row(r), column(c) {}

    iterator_limited &operator++() {
        ++column;
        if (column == m.get_cols()) {
            column = 0;
            row++;
        }
        return *this;
    }

    iterator_limited &operator++(int) {
        ++column;
        if (column == m.get_cols()) {
            column = 0;
            row++;
        }
        return *this;
    }


    T& operator*() {
        return m(row, column);
    }

    friend class const_iterator_limited<T, type>;

    bool operator==(const iterator_limited &i) const {
        return (row == i.row) && (column == i.column);
    }

    bool operator==(const const_iterator_limited<T, type> &i) const {
        return (row == i.row) && (column == i.column);
    }

    bool operator!=(const iterator_limited &i) const {
        return (row != i.row) || (column != i.column);
    }

    bool operator!=(const const_iterator_limited<T, type> &i) const {
        return (row != i.row) || (column != i.column);
    }
};


template <typename T, typename type>
class const_iterator_limited {
    const matrix<T, type> &m;
    unsigned int row;
    unsigned int column;

public:
    const_iterator_limited(const matrix<T, type> &mm, unsigned int r, unsigned int c) :
            m(mm), row(r), column(c) {}

    const_iterator_limited &operator++() {
        ++column;
        if (column == m.get_cols()) {
            column = 0;
            row++;
        }
        return *this;
    }

    const_iterator_limited &operator++(int) {
        ++column;
        if (column == m.get_cols()) {
            column = 0;
            row++;
        }
        return *this;
    }

    const T& operator*() const {
        return m(row, column);
    }

    friend class iterator_limited<T, type>;

    bool operator==(const_iterator_limited &i) const {
        return (row == i.row) && (column == i.column);
    }

    bool operator==(const iterator_limited<T, type> &i) const {
        return (row == i.row) && (column == i.column);
    }

    bool operator!=(const_iterator_limited &i) const {
        return (row != i.row) || (column != i.column);
    }

    bool operator!=(const iterator_limited<T, type> &i) const {
        return (row != i.row) || (column != i.column);
    }
};


#endif