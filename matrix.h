#ifndef MATRIX_H
#define MATRIX_H

// include the declarations
#include "matrix_utils.h"

// from the standard library
#include <vector>
#include <memory>
#include <cassert>


/**
 * @brief Basic matrix. Contains all the basic operations. Will be decorated later.
 * `basic_matrix` is the default type
 * @tparam T the type of data contained in the matrix
*/
template<typename T>
class matrix<T, basic_matrix> {
protected:
    unsigned int n_rows; // height of the matrix
    unsigned int n_cols; // width of the matrix
    typename std::shared_ptr<std::vector<T>> matrix_content;


public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    typedef column_iterator<T, basic_matrix> col_iterator;
    typedef const_column_iterator<T, basic_matrix> const_col_iterator;

    /**
       @brief Begin iterator for traversing the matrix by column
       @return col_iterator starting from (0, i = 0)
    */
    col_iterator column_begin(unsigned int i = 0) {
        assert((i < n_cols) && "Out of bounds!");
        return col_iterator(*this, 0, i);
    }

    /**
        @brief End col_iterator for traversing the matrix by column
        @return col_iterator that points to (0, i + 1) "end of column"
    */
    col_iterator column_end(unsigned int i) {
        assert((i < n_cols) && "Out of bounds!");
        return col_iterator(*this, 0, i + 1);
    }

    /**
    @brief End col_iterator for traversing the matrix by column
    @return col_iterator that points to end of matrix
    */
    col_iterator column_end() {
        return col_iterator(*this, 0, n_cols);
    }


    /**
       @brief Begin const_iterator for traversing the matrix by column
       @return const_col_iterator starting from (0, i = 0)
    */
    const_col_iterator column_begin(unsigned int i = 0) const {
        assert((i < n_cols) && "Out of bounds!");
        return const_col_iterator(*this, 0, i);
    }

    /**
        @brief End const_iterator for traversing the matrix by column
        @return const_col_iterator that points to (0, i + 1) "end of column"
    */
    const_col_iterator column_end(unsigned int i) const {
        assert((i < n_cols) && "Out of bounds!");
        return const_col_iterator(*this, 0, i + 1);
    }

    /**
        @brief End const_iterator for traversing the matrix by column
        @return const_col_iterator that points to "end of matrix"
    */
    const_col_iterator column_end() const {
        return const_col_iterator(*this, 0, n_cols);
    }

    /**
       @brief Begin iterator for traversing the matrix by row
       @return iterator starting from the first element of line i
    */
    iterator begin(unsigned int i = 0) {
        assert((i == 0 || i < n_rows) && "Out of bounds!");
        return matrix_content->begin() + i * n_cols;
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the "end" of last line
    */
    iterator end() {
        return matrix_content->begin() + n_rows * n_cols;
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the "end" of line i
    */
    iterator end(unsigned int i) {
        return matrix_content->begin() + (i + 1) * n_cols;
    }

    /**
       @brief Const begin iterator for traversing the matrix by row
       @return const_iterator starting from the first element of line i
    */
    const_iterator begin(unsigned int i = 0) const {
        assert((i == 0 || i < n_rows) && "Out of bounds!");
        return matrix_content->begin() + i * n_cols;
    }

    /**
       @brief Const end iterator for traversing the matrix by row
       @return const_iterator pointing to the "end" of line i
    */
    const_iterator end() const {
        return matrix_content->begin() + n_rows * n_cols;
    }

    /**
       @brief Const end iterator for traversing the matrix by row
       @return const_iterator pointing to the "end" of line i
    */
    const_iterator end(unsigned int i) const {
        return matrix_content->begin() + (i + 1) * n_cols;
    }

    /**
       @brief Default constructor
       Initialize an empty matrix with 0 rows and 0 columns
    */
    matrix() :
            n_rows(0),
            n_cols(0),
            matrix_content(std::make_shared<std::vector<T> >(0)) {}

    /**
       @brief Constructor given the numbers of rows and columns
       Initialize a matrix of `rows` rows and `cols` columns
       @param rows number of rows
       @param cols number of columns
    */
    matrix(unsigned int rows, unsigned int cols) :
            n_rows(rows),
            n_cols(cols),
            matrix_content(std::make_shared<std::vector<T> >(rows * cols)) {}


    /**
    @brief Copy constructor
    Create a matrix by deep copy of another one. No sharing of information!
    @param matrix_to_copy matrix to be used to create the new one
    */
    template <typename type>
    matrix(const matrix<T, type> &matrix_to_copy) {
        n_rows = matrix_to_copy.get_rows();
        n_cols = matrix_to_copy.get_cols();
        matrix_content = std::make_shared<std::vector<T>>(this->n_cols * this->n_rows);
        for (unsigned int i = 0; i < n_rows; ++i) {
            auto ii = matrix_to_copy.begin(i);
            auto ie = matrix_to_copy.end(i);
            auto i_this = this->begin(i);
            while (ii != ie) {
                *i_this = *ii;
                ++i_this;
                ++ii;
            }

        }
    }


    /**
        Assignment operator
        @param other matrix to copy
        @return reference to this
    */
    matrix &operator=(const matrix &other) {
        if (this != &other) {
            matrix tmp(other);
            std::swap(tmp.n_cols, n_cols);
            std::swap(tmp.n_rows, n_rows);
            std::swap(tmp.matrix_content, matrix_content);
        }
        return *this;
    }


    /**
       @brief Operator()
       Useful for direct access to element in the matrix.
       r * n_cols --> select correct line of the matrix
       +c --> select the correct cell of the line
       @param r number of row (0-based)
       @param c number of column (0-based)
       @return T& to requested element of the matrix
    */
    T& operator()(unsigned int r, unsigned int c) {
        assert((r < this->get_rows() && c < this->get_cols()) && "Out of bounds!");
        return matrix_content->operator[](r * n_cols + c);
    }

    /**
       @brief Operator() const
       Useful for direct access to element in the matrix
       @param r number of row (0-based)
       @param c number of column (0-based)
       @return const T& to requested element of the matrix
    */
    const T& operator()(unsigned int r, unsigned int c) const {
        assert((r < this->get_rows() && c < this->get_cols()) && "Out of bounds!");
        return matrix_content->operator[](r * n_cols + c);
    }

    /**
       @brief Get number of rows
        Doesn't modify state of the matrix
       @return unsigned int corresponding to number of rows
    */
    unsigned int get_rows() const {
        return n_rows;
    }

    /**
       @brief Get number of columns
       Doesn't modify state of the matrix
       @return unsigned int corresponding to number of columns
    */
    unsigned int get_cols() const {
        return n_cols;
    }

    /**
        @brief create the transpose of the current matrix
        Needs a constructor that, given a basic matrix, creates a transpose_matrix from it
        @return trasposed matrix
    */
    matrix<T, transpose_matrix<basic_matrix>> get_transpose() const {
        // RVO
        return matrix<T, transpose_matrix<basic_matrix>>(*this);
    }

    /**
     * @brief get a submatrix of the current matrix
     * @param begin_row row to begin from
     * @param end_row row to end to (EXCLUDED)
     * @param begin_column column to begin from
     * @param end_column column to end to (EXCLUDED)
     * @return required submatrix
     */
    matrix<T, submatrix<basic_matrix>> get_submatrix (
            unsigned int begin_row, unsigned int end_row,
            unsigned int begin_column, unsigned int end_column) const {
        // RVO
        return matrix<T, submatrix<basic_matrix>>
                (*this, begin_row, end_row, begin_column, end_column);
    }

    /**
     * @brief get a vector containing the diagonal elements of this matrix
     * @return diagonal a vector containing the diagonal elements of this matrix
     */
    matrix<T, diagonal<basic_matrix>> get_diagonal() const {
        // RVO
        return matrix<T, diagonal<basic_matrix>>(*this);
    }

    /**
     * @brief get a diagonal matrix from this matrix (iff it is a vector)
     * @return diagonalmatrix whose diagonal elements are those of this vector
     */
    const matrix<T, diagonalmatrix<basic_matrix>> get_diagonalmatrix() const {
        // RVO
        return matrix<T, diagonalmatrix<basic_matrix>>(*this);
    }
};


/**
 * @brief Transpose of a matrix
 * @tparam T the type of data contained in the matrix
 * @tparam decorator_matrix the matrix this one is built from
 */
template<typename T, typename decorator_matrix>
class matrix<T, transpose_matrix<decorator_matrix>> : protected matrix<T, decorator_matrix> {

public:
    friend class matrix<T, decorator_matrix>;
    typedef typename matrix<T, decorator_matrix>::iterator col_iterator;
    typedef typename matrix<T, decorator_matrix>::const_iterator const_col_iterator;
    typedef typename matrix<T, decorator_matrix>::col_iterator iterator;
    typedef typename matrix<T, decorator_matrix>::const_col_iterator const_iterator;

    /**
       @brief Copy constructor
       Create a matrix by deep copy of another one. No sharing of information!
       @param other matrix to be used to create the new one
   */
    matrix(const matrix<T, decorator_matrix> &other) :
            matrix<T, decorator_matrix>(other) {}

    /**
     * @brief operator()
     * @param r row of the element to be accessed
     * @param c column of the element to be accessed
     * @return reference to element in that cell of the matrix
     */
    T& operator()(unsigned int r, unsigned int c) {
        assert((r < this->get_rows() && c < this->get_cols()) && "Out of bounds!");
        return matrix<T, decorator_matrix>::operator()(c, r);
    }

    /**
     * @brief operator() const
     * @param r row of the element to be accessed
     * @param c column of the element to be accessed
     * @return const reference to element in that cell of the matrix
     */
    const T& operator()(unsigned int r, unsigned int c) const {
        assert((r < this->get_rows() && c < this->get_cols()) && "Out of bounds!");
        return matrix<T, decorator_matrix>::operator()(c, r);
    }

    /**
       @brief col_iterator begin() for column i
       @param i column (default = 0)
       @return iterator to beginning of column i
     */
    col_iterator column_begin(unsigned int i = 0) {
        return matrix<T, decorator_matrix>::begin(i);
    }

    /**
       @brief col_iterator end() for column i
       @param i column (default = 0)
       @return iterator to end of column i
     */
    col_iterator column_end(unsigned int i) {
        return matrix<T, decorator_matrix>::end(i);
    }

    /**
       @brief col_iterator end()
       @return iterator to end of the matrix
     */
    col_iterator column_end() {
        return matrix<T, decorator_matrix>::end();
    }

    /**
       @brief const_col_iterator begin() for column i
       @param i column (default = 0)
       @return const_iterator to beginning of column i
     */
    const_col_iterator column_begin(unsigned int i = 0) const {
        return matrix<T, decorator_matrix>::begin(i);
    }

    /**
       @brief const_col_iterator end() for column i
       @param i column (default = 0)
       @return const_iterator to end of column i
     */
    const_col_iterator column_end(unsigned int i) const {
        return matrix<T, decorator_matrix>::end(i);
    }


    /**
       @brief const_col_iterator end()
       @return const_iterator to end
     */
    const_col_iterator column_end() const {
        return matrix<T, decorator_matrix>::end();
    }

    /**
     * @brief iterator begin() for row i
     * @param i row (default = 0)
     * @return iterator to the beginning of row i
     */
    iterator begin(unsigned int i = 0) {
        return matrix<T, decorator_matrix>::column_begin(i);
    }

    /**
     * @brief iterator end() for row i
     * @param i row (default = 0)
     * @return iterator to the end of row i
     */
    iterator end(unsigned int i) {
        return matrix<T, decorator_matrix>::column_end(i);
    }

    /**
     * @brief iterator end()
     * @return iterator to the end of matrix
     */
    iterator end() {
        return matrix<T, decorator_matrix>::column_end();
    }

    /**
     * @brief const_iterator begin() for row i
     * @param i row (default = 0)
     * @return const_iterator to the beginning of row i
     */
    const_iterator begin(unsigned int i = 0) const {
        return matrix<T, decorator_matrix>::column_begin(i);
    }

    /**
     * @brief const_iterator end() for row i
     * @param i row (default = 0)
     * @return const_iterator to the end of row i
     */
    const_iterator end(unsigned int i) const {
        return matrix<T, decorator_matrix>::column_end(i);
    }

    /**
     * @brief const_iterator end() for matrix
     * @return const_iterator to the end of matrix
     */
    const_iterator end() const {
        return matrix<T, decorator_matrix>::column_end();
    }



    /**
       @brief Get number of rows
        Doesn't modify state of the matrix
       @return unsigned int corresponding to number of rows
    */
    unsigned int get_rows() const {
        return matrix<T, decorator_matrix>::get_cols();
    }

    /**
       @brief Get number of columns
       Doesn't modify state of the matrix
       @return unsigned int corresponding to number of columns
    */
    unsigned int get_cols() const {
        return matrix<T, decorator_matrix>::get_rows();
    }

    /**
     * @brief compute the transpose of a transpose matrix
     * @return transpose of the transpose (i.e. the original matrix)
     */
    matrix<T, decorator_matrix> get_transpose() const {
        return *this;
    }

    /**
     * @brief get a submatrix of the current matrix
     * @param begin_row row to begin from
     * @param end_row row to end to (EXCLUDED)
     * @param begin_column column to begin from
     * @param end_column column to end to (EXCLUDED)
     * @return required submatrix
     */
    matrix<T, submatrix<transpose_matrix<decorator_matrix>>> get_submatrix
        (unsigned int begin_row, unsigned int end_row,
         unsigned int begin_column, unsigned int end_column) const {
            // RVO
            return matrix<T, submatrix<transpose_matrix<decorator_matrix>>>
                         (*this, begin_row, end_row, begin_column, end_column);
    }

    /**
     * @brief get a vector containing the diagonal elements of this matrix
     * @return diagonal a vector containing the diagonal elements of this matrix
     */
    matrix<T, diagonal<transpose_matrix<decorator_matrix>>> get_diagonal() const {
        // RVO
         return matrix<T, diagonal<transpose_matrix<decorator_matrix>>>(*this);
    }

    /**
     * @brief get a diagonal matrix from this matrix (iff it is a vector)
     * @return diagonalmatrix whose diagonal elements are those of this vector
     */
    const matrix<T, diagonalmatrix<transpose_matrix<decorator_matrix>>> get_diagonalmatrix() const {
        // RVO
         return matrix<T, diagonalmatrix<transpose_matrix<decorator_matrix>>>(*this);
    }

};

/**
 * @brief Take a submatrix of a matrix. Note: the last row/column is excluded, i.e.
 * we intervals like [i, j)
 *
 * @tparam T the type of data contained in the matrix
 * @tparam decorator_matrix the matrix this one is built from
 */
template<typename T, typename decorator_matrix>
class matrix<T, submatrix<decorator_matrix>> : protected matrix<T, decorator_matrix> {
protected:
    unsigned int first_row, last_row, first_col, last_col;
public:
    friend class matrix<T, decorator_matrix>;
    typedef iterator_limited<T, submatrix<decorator_matrix>> iterator;
    typedef const_iterator_limited<T, submatrix<decorator_matrix>> const_iterator;
    typedef column_iterator<T, submatrix<decorator_matrix>> col_iterator;
    typedef const_column_iterator<T, submatrix<decorator_matrix>> const_col_iterator;

    /**
        @brief Copy constructor
        Create a matrix by deep copy of another one. No sharing of information!
        @param other matrix to be used to create the new one
        @param fr first row
        @param lr last row (excluded)
        @param fc first column
        @param lc last column (excluded)
        @return matrix
    */
    matrix(const matrix<T, decorator_matrix> &other,
           unsigned int fr, unsigned int lr,
           unsigned int fc, unsigned int lc) :
            matrix<T, decorator_matrix>(other), first_row(fr),
            last_row(lr), first_col(fc), last_col(lc) {
        assert((lr <= other.get_rows() && lc <= other.get_cols()) && "Out of bound!");
    }

    /**
     * @brief take the submatrix of a submatrix
     * @param begin_row row to begin from
     * @param end_row row to end to (EXCLUDED)
     * @param begin_column column to begin from
     * @param end_column column to end to (EXCLUDED)
     * @return required submatrix
     */
    matrix<T, submatrix<decorator_matrix>> get_submatrix (
            unsigned int begin_row, unsigned int end_row,
            unsigned int begin_column, unsigned int end_column) const {
        // RVO
        return matrix<T, submatrix<decorator_matrix>>
                (*this, begin_row + first_row,
                 end_row + first_row,
                 begin_column + first_col,
                 end_column + first_col);
    }

    /**
     * @brief get the transpose of this submatrix
     * @return required transpose
     */
    matrix<T, transpose_matrix<submatrix<decorator_matrix>>> get_transpose() const {
        // RVO
        return matrix<T, transpose_matrix<submatrix<decorator_matrix>>>(*this);
    }

    /**
     * @brief get a vector containing the diagonal elements of this matrix
     * @return diagonal a vector containing the diagonal elements of this matrix
     */
    matrix<T, diagonal<submatrix<decorator_matrix>>> get_diagonal() const {
        // RVO
        return matrix<T, diagonal<submatrix<decorator_matrix>>>(*this);
    }

    /**
     *
     * @brief get a diagonal matrix from this matrix (iff it is a vector)
     * @return diagonalmatrix whose diagonal elements are those of this vector
     */
    const matrix<T, diagonalmatrix<submatrix<decorator_matrix>>> get_diagonalmatrix() const {
        // RVO
        return matrix<T, diagonalmatrix<submatrix<decorator_matrix>>>(*this);
    }

    /**
     * @brief operator()
     * @param r row of the element to be accessed
     * @param c column of the element to be accessed
     * @return reference to element in that cell of the matrix
     */
    T& operator()(unsigned int r, unsigned int c) {
        assert((r <= this->get_rows() && r < last_row &&
                c <= this->get_cols() && c < last_col) && "Out of bounds!");
        return matrix<T, decorator_matrix>::operator()(r + first_row, c + first_col);
    }

    /**
     * @brief operator() const
     * @param r row of the element to be accessed
     * @param c column of the element to be accessed
     * @return const reference to element in that cell of the matrix
     */
    const T& operator()(unsigned int r, unsigned int c) const {
        assert((r <= this->get_rows() && r < last_row &&
                c <= this->get_cols() && c < last_col) && "Out of bounds!");
        return matrix<T, decorator_matrix>::operator()(r + first_row, c + first_col);
    }

    /**
       @brief Begin col_iterator for traversing the matrix by column starting from i
       @return col_iterator starting from (0, i)
    */
    col_iterator column_begin(unsigned int i = 0) {
        assert((i < last_col) && "Out of bounds!");
        return col_iterator(*this, 0, i);
    }

    /**
        @brief End iterator for traversing the matrix by column
        @return col_iterator that points to end of matrix
    */
    col_iterator column_end() {
        return col_iterator(*this, 0, this->get_cols());
    }


    /**
        @brief End iterator for traversing the matrix by column starting from i
        @return col_iterator that points to (0, i + 1)
    */
    col_iterator column_end(unsigned int i) {
        assert((i < last_col) && "Out of bounds!");
        return col_iterator(*this, 0, i + 1);
    }

    /**
       @brief Begin const_iterator for traversing the matrix by column starting from i
       @return const_col_iterator starting from (0, i)
    */
    const_col_iterator column_begin(unsigned int i = 0) const {
        assert((i < last_col) && "Out of bounds!");
        return const_col_iterator(*this, 0, i);
    }

    /**
        @brief End const_iterator for traversing the matrix by column
        @return const_col_iterator that points to end of matrix
    */
    const_col_iterator column_end() const {
        return const_col_iterator(*this, 0, this->get_cols());
    }

    /**
        @brief End const_iterator for traversing the matrix by column starting from i
        @return const_col_iterator that points to (0, i + 1)
    */
    const_col_iterator column_end(unsigned int i) const {
        assert((i < last_col) && "Out of bounds!");
        return const_col_iterator(*this, 0, i + 1);
    }

    /**
       @brief Begin iterator for traversing the matrix by row starting from i
       @return iterator starting from the first element of row i
    */
    iterator begin(unsigned int i = 0) {
        assert(((i == 0 && first_row == 0) || i < last_row) && "Out of bounds!");
        return iterator(*this, i, 0);
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the end of the matrix
    */
    iterator end() {
        return iterator(*this, this->get_rows(), 0);
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the end of row i
    */
    iterator end(unsigned int i) {
        assert(((i == 0 && first_row == 0) || i < last_row) && "Out of bounds!");
        return iterator(*this, i + 1, 0);
    }

    /**
       @brief Const begin iterator for traversing the matrix by row
       @return const_iterator starting from the first element of row i
    */
    const_iterator begin(unsigned int i = 0) const {
        assert(((i == 0 && first_row == 0) || i < last_row) && "Out of bounds!");
        return const_iterator(*this, i, 0);
    }

    /**
       @brief Const end iterator for traversing the matrix by row
       @return const_iterator pointing to the end of row i
    */
    const_iterator end(unsigned int i) const {
        assert(((i == 0 && first_row == 0) || i < last_row) && "Out of bounds!");
        return const_iterator(*this, i + 1, 0);
    }

    /**
       @brief Const end iterator for traversing the matrix by row
       @return const_iterator pointing to the end of the matrix
    */
    const_iterator end() const {
        return const_iterator(*this, this->get_rows(), 0);
    }

    /**
       @brief Get number of rows
        Doesn't modify state of the matrix
       @return unsigned int corresponding to number of rows
    */
    unsigned int get_rows() const {
        return last_row - first_row;
    }

    /**
       @brief Get number of columns
       Doesn't modify state of the matrix
       @return unsigned int corresponding to number of columns
    */
    unsigned int get_cols() const {
        return last_col - first_col;
    }

};


template<typename T, typename decorator_matrix>
class matrix<T, diagonalmatrix<decorator_matrix>> : protected matrix<T, decorator_matrix> {
private:
    const T null_element;

public:
    friend class matrix<T, decorator_matrix>;
    typedef const_iterator_limited<T, diagonalmatrix<decorator_matrix>> const_iterator;
    typedef const_column_iterator<T, diagonalmatrix<decorator_matrix>> const_col_iterator;

    /**
        @brief Copy constructor
        Create a matrix by deep copy of another one. No sharing of information!
        @param other matrix to be used to create the new one
    */
    matrix(const matrix<T, decorator_matrix> &other) :
            matrix<T, decorator_matrix>(other), null_element(0) {
        assert((other.get_cols() == 1) && "Invalid matrix!");
    }

    /**
       @brief Get number of rows
        Doesn't modify state of the matrix
       @return unsigned int corresponding to number of rows
    */
    unsigned int get_rows() const {
        return matrix<T, decorator_matrix>::get_rows();
    }

    /**
       @brief Get number of columns
       Doesn't modify state of the matrix
       @return unsigned int corresponding to number of columns
    */
    unsigned int get_cols() const {
        return matrix<T, decorator_matrix>::get_rows();
    }

    /**
       @brief Operator() const
       Useful for direct access to element in the matrix
       @param r number of row (0-based)
       @param c number of column (0-based)
       @return const T& to requested element of the matrix
    */
    const T &operator()(unsigned int r, unsigned int c) const {
        if (r != c)
            return null_element;
        return matrix<T, decorator_matrix>::operator()(r, 0);
    }


    /**
       @brief Begin iterator for traversing the matrix by row
       @return iterator starting from the first element of line i
    */
    const_iterator begin(unsigned int i = 0) const {
        return const_iterator(*this, i, 0);
    }

    /**
       @brief End const_iterator for traversing the matrix by row
       @return const_iterator pointing to the end of the matrix
    */
    const_iterator end() const {
        return const_iterator(*this, this->get_rows(), this->get_cols());
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the end of the i-th line
    */
    const_iterator end(unsigned int i) const {
        return const_iterator(*this, i + 1, 0);
    }

    /**
       @brief iterator begin() for column i
       @param i column
       @return iterator to beginning of column i
     */
    const_col_iterator column_begin(unsigned i = 0) const {
        return const_col_iterator(*this, 0, i);
    }

    /**
        @brief End col_iterator for traversing the matrix by column
        @return col_iterator that points to (0, i + 1) "end of column"
    */
    const_col_iterator column_end(unsigned i) const {
        return const_col_iterator(*this, 0, i + 1);
    }

    /**
        @brief End col_iterator for traversing the matrix by column
        @return col_iterator that points to "end of matrix"
    */
    const_col_iterator column_end() const {
        return const_col_iterator(*this, 0, this->get_rows());
    }

    /**
     * @brief get a submatrix of the current matrix
     * @param begin_row row to begin from
     * @param end_row row to end to (EXCLUDED)
     * @param begin_column column to begin from
     * @param end_column column to end to (EXCLUDED)
     * @return required submatrix
     */
    matrix<T, submatrix<diagonalmatrix<decorator_matrix>>> get_submatrix
            (unsigned int begin_row, unsigned int end_row,
             unsigned int begin_column, unsigned int end_column) const {
        // RVO
        return matrix<T, submatrix<diagonalmatrix<decorator_matrix>>>
                (*this, begin_row, end_row, begin_column, end_column);
    }

    /**
     * @brief get a vector containing the diagonal elements of this matrix
     * @return diagonal a vector containing the diagonal elements of this matrix
     */
    matrix<T, diagonal<diagonalmatrix<decorator_matrix>>> get_diagonal() const {
        // RVO
        return matrix<T, diagonal<diagonalmatrix<decorator_matrix>>>(*this);
    }

    /**
        @brief create the transpose of the current matrix
        Needs a constructor that, given a basic matrix, creates a transpose_matrix from it
        @return trasposed matrix
    */
    matrix<T, transpose_matrix<diagonalmatrix<decorator_matrix>>> get_transpose() const {
        // RVO
        return matrix<T, transpose_matrix<diagonalmatrix<decorator_matrix>>>(*this);
    }
};


template<typename T, typename decorator_matrix>
class matrix<T, diagonal<decorator_matrix>> : protected matrix<T, decorator_matrix> {

public:
    friend class matrix<T, decorator_matrix>;
    typedef iterator_limited<T, diagonal<decorator_matrix>> iterator;
    typedef const_iterator_limited<T, diagonal<decorator_matrix>> const_iterator;
    typedef column_iterator<T, diagonal<decorator_matrix>> col_iterator;
    typedef const_column_iterator<T, diagonal<decorator_matrix>> const_col_iterator;

    /**
        @brief Copy constructor
        Create a matrix by deep copy of another one. No sharing of information!
        @param other matrix to be used to create the new one
    */
    matrix(const matrix<T, decorator_matrix> &other) :
            matrix<T, decorator_matrix>(other) {
    }

    /**
       @brief Get number of rows
        Doesn't modify state of the matrix
       @return unsigned int corresponding to number of rows
    */
    unsigned int get_rows() const {
        return (matrix<T, decorator_matrix>::get_rows() < matrix<T, decorator_matrix>::get_cols()
                ? matrix<T, decorator_matrix>::get_rows()
                : matrix<T, decorator_matrix>::get_cols());
    }

    /**
       @brief Get number of columns
       Doesn't modify state of the matrix
       @return unsigned int corresponding to number of columns
    */
    unsigned int get_cols() const {
        return 1;
    }

    /**
       @brief Operator()
       Useful for direct access to element in the matrix
       @param r number of row (0-based)
       @param c number of column (0-based)
       @return T& to requested element of the matrix
    */
    T& operator()(unsigned int r, unsigned int c = 0) {
        assert((c == 0) && "A vector is a 1xn matrix and you are accessing a non-existing column!");
        return matrix<T, decorator_matrix>::operator()(r, r);
    }

    /**
       @brief Operator() const
       Useful for direct access to element in the matrix
       @param r number of row (0-based)
       @param c number of column (0-based)
       @return const T& to requested element of the matrix
    */
    const T& operator()(unsigned int r, unsigned int c = 0) const {
        assert((c == 0) && "A vector is a 1xn matrix and you are accessing a non-existing column!");
        return matrix<T, decorator_matrix>::operator()(r, r);
    }

    /**
       @brief Begin iterator for traversing the matrix by row
       @return iterator starting from the first element of line i
    */
    iterator begin(unsigned int i = 0) {
        return iterator(*this, i, 0);
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the end of the matrix
    */
    iterator end() {
        return iterator(*this, this->get_rows(), 0);
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the end of the i-th row
    */
    iterator end(unsigned int i) {
        return iterator(*this, i + 1, 0);
    }

    /**
       @brief Begin const_iterator for traversing the matrix by row
       @return const_iterator starting from the first element of line i
    */
    const_iterator begin(unsigned int i = 0) const {
        return const_iterator(*this, i, 0);
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the end of the matrix
    */
    const_iterator end() const{
        return const_iterator(*this, this->get_rows(), 0);
    }

    /**
       @brief End iterator for traversing the matrix by row
       @return iterator pointing to the end of the i-th row
    */
    const_iterator end(unsigned int i) const {
        return const_iterator(*this, i + 1, 0);
    }

    /**
       @brief Begin col_iterator for traversing the matrix by column starting from i
       @return col_iterator starting from (0, i)
    */
    col_iterator column_begin(unsigned int i = 0) {
        return col_iterator(*this, 0, i);
    }

    /**
        @brief End col_iterator for traversing the matrix by column
        @return col_iterator that points to (0, i + 1) "end of column"
    */
    col_iterator column_end(unsigned int i) {
        return col_iterator(*this, 0, i + 1);
    }

    /**
        @brief End col_iterator for traversing the matrix by column
        @return col_iterator that points to "end of matrix"
    */
    col_iterator column_end() {
        return col_iterator(*this, 0, this->get_cols());
    }

    /**
       @brief Begin const_col_iterator for traversing the matrix by column starting from i
       @return const_col_iterator starting from (0, i)
    */
    const_col_iterator column_begin(unsigned int i = 0) const {
        return const_col_iterator(*this, 0, i);
    }

    /**
        @brief End const_col_iterator for traversing the matrix by column
        @return const_col_iterator that points to (0, i + 1) "end of column"
    */
    const_col_iterator column_end(unsigned int i) const {
        return const_col_iterator(*this, 0, i + 1);
    }

    /**
        @brief End const_col_iterator for traversing the matrix by column
        @return const_col_iterator that points to (0, i + 1) "end of column"
    */
    const_col_iterator column_end() const {
        return const_col_iterator(*this, 0, this->get_cols());
    }


    /**
        @brief create the transpose of the current matrix
        Needs a constructor that, given a basic matrix, creates a transpose_matrix from it
        @return trasposed matrix
    */
    matrix<T, transpose_matrix<diagonal<decorator_matrix>>> get_transpose() const {
        return matrix<T, transpose_matrix<diagonal<decorator_matrix>>>(*this);
    }

    /**
     * @brief get a submatrix of the current matrix
     * @param begin_row row to begin from
     * @param end_row row to end to (EXCLUDED)
     * @param begin_column column to begin from
     * @param end_column column to end to (EXCLUDED)
     * @return required submatrix
     */
    matrix<T, submatrix<diagonal<decorator_matrix>>> get_submatrix
            (unsigned int begin_row, unsigned int end_row,
             unsigned int begin_column, unsigned int end_column) const {
        // RVO
        return matrix<T, submatrix<diagonal<decorator_matrix>>>
                (*this, begin_row, end_row, begin_column, end_column);
    }

    /**
     * @brief get a vector containing the diagonal elements of this matrix
     * @return diagonal a vector containing the diagonal elements of this matrix
     */
    matrix<T, diagonal<diagonal<decorator_matrix>>> get_diagonal() const {
        // RVO
        return matrix<T, diagonal<diagonal<decorator_matrix>>>(*this);
    }

    /**
     * @brief get a diagonal matrix from this matrix (iff it is a vector)
     * @return diagonalmatrix whose diagonal elements are those of this vector
     */
    const matrix<T, diagonalmatrix<diagonal<decorator_matrix>>> get_diagonalmatrix() const {
        // RVO
        return matrix<T, diagonalmatrix<diagonal<decorator_matrix>>>(*this);
    }

};


#endif