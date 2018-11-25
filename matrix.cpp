#include <iostream>
#include <string>
#include "matrix.h" 



void basic_test_basic_matrix() {
    std::cout << "BASIC TEST" << std::endl;
    matrix<int> a;
    assert((a.get_rows() == 0 && a.get_cols() == 0) && "This is not an empty matrix!");
    matrix<int> b(2, 5);
    assert((b.get_rows() == 2 && b.get_cols() == 5) && "This is not a 2x5 matrix!");
    for (unsigned int i = 0; i < 2; ++i)
        for (unsigned int j = 0; j < 5; ++j)
            b(i, j) = i + j;
    std::cout << "a (empty)" << std::endl << a << std::endl;
    std::cout << "b" << std::endl << b << std::endl;
    assert(*(b.begin() + 3) == 3 && "Problem with begin()");
    a = b;
    assert((a.get_rows() == 2 && a.get_cols() == 5) && "This is not a 2x5 matrix!");
    std::cout << "a = b" << std::endl << a << std::endl;
    std::cout << "b by single column" << std::endl;
    for (unsigned int i = 0; i < b.get_cols(); i++) {
        auto col_begin = b.column_begin(i);
        auto col_end = b.column_end(i);
        for (; col_begin != col_end; ++col_begin) {
            std::cout << *col_begin << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl <<  "b by column" << std::endl;
    auto col_begin = b.column_begin();
    auto col_end = b.column_end();
    unsigned int k = 0;
    for (; col_begin != col_end; ++col_begin) {
        k++;
        std::cout << *col_begin << " ";
        if (k == b.get_rows()) {
            k = 0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl << "3rd column of b" << std::endl;
    for (auto i = b.column_begin(2), ie = b.column_end(2); i != ie; ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;
    assert(*(++(b.column_begin(2))) == 3 && "Problem with column_begin");
    std::cout << "**************************" << std::endl << std::endl;
}


void basic_test_transpose_matrix() {
    std::cout << "BASIC TEST TRANSPOSE" << std::endl;
    matrix<int> b(2, 5);
    for (unsigned int i = 0; i < 2; i++)
        for (unsigned int j = 0; j < 5; j++)
            b(i, j) = i + j;
    auto c = b.get_transpose();
    assert((c.get_cols() == 2 && c.get_rows() == 5) && "You call this thing a transpose?");
    std::cout << "b" << std::endl << b << std::endl;
    std::cout << "c = b.get_transpose()" << std::endl << c << std::endl;
    std::cout << "c by single column" << std::endl;
    for (unsigned int i = 0; i < c.get_cols(); i++) {
        auto col_begin = c.column_begin(i);
        auto col_end = c.column_end(i);
        for (; col_begin != col_end; ++col_begin) {
            std::cout << *col_begin << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl <<  "c by column" << std::endl;
    auto col_begin = c.column_begin();
    auto col_end = c.column_end();
    unsigned int k = 0;
    for (; col_begin != col_end; ++col_begin) {
        k++;
        std::cout << *col_begin << " ";
        if (k == c.get_rows()) {
            k = 0;
            std::cout << std::endl;
        }
    }
    std::cout << "**************************" << std::endl << std::endl;
}


void basic_test_submatrix() {
    std::cout << "BASIC TEST SUBMATRIX" << std::endl;
    matrix<int> b(4, 5);
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 5; j++)
            b(i, j) = i + j;
    matrix<int, submatrix<basic_matrix>> c = b.get_submatrix(1, 3, 1, 4);
    assert((c.get_cols() == 3 && c.get_rows() == 2) && "You call this thing a submatrix?");
    std::cout << "b" << std::endl << b << std::endl;
    std::cout << "c = b.get_submatrix()" << std::endl << c << std::endl;
    std::cout << "stampa con il for " << std::endl;
    for (unsigned int i = 0; i < 2; i++) {
        for (unsigned int j = 0; j < 3; j++)
            std::cout << c(i, j) << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl << "c by single column" << std::endl;
    for (unsigned int i = 0; i < c.get_cols(); i++) {
        auto col_begin = c.column_begin(i);
        auto col_end = c.column_end(i);
        for (; col_begin != col_end; ++col_begin)
            std::cout << *col_begin << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl << "c by column" << std::endl;
    auto col_begin = c.column_begin();
    auto col_end = c.column_end();
    unsigned int k = 0;
    for (; col_begin != col_end; ++col_begin) {
        k++;
        std::cout << *col_begin << " ";
        if (k == c.get_rows()) {
            k = 0;
            std::cout << std::endl;
        }
    }
    std::cout << "**************************" << std::endl << std::endl;
}


void basic_test_diagonalmatrix() {
    std::cout << "BASIC TEST DIAGONALMATRIX" << std::endl;
    matrix<int> b(5, 1);
    for (unsigned int i = 0; i < b.get_rows(); i++)
        for (unsigned int j = 0; j < b.get_cols(); j++)
            b(i, j) = i + j + 2;
    std::cout << "b" << std::endl << b << std::endl;
    auto c = b.get_diagonalmatrix();
    assert((c.get_cols() == c.get_rows() && c.get_cols() == 5) && "Something wrong with diagonalmatrix");
    std::cout << "c = b.get_diagonalmatrix()" << std::endl << c;
    std::cout << std::endl << "c by single column" << std::endl;
    for (unsigned int i = 0; i < c.get_cols(); i++) {
        auto col_begin = c.column_begin(i);
        auto col_end = c.column_end(i);
        for (; col_begin != col_end; ++col_begin)
            std::cout << *col_begin << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl << "c by column" << std::endl;
    auto col_begin = c.column_begin();
    auto col_end = c.column_end();
    unsigned int j = 0;
    for (; col_begin != col_end; ++col_begin) {
        j++;
        std::cout << *col_begin << " ";
        if (j == c.get_rows()) {
            j = 0;
            std::cout << std::endl;
        }
    }
    matrix<std::string> k(8, 1);
    for (unsigned int i = 0; i < k.get_rows(); i++)
        for (unsigned int j = 0; j < k.get_cols(); j++)
            k(i, j) = std::to_string(i + j);
    std::cout << std::endl << "k.get_diagonalmatrix()" << std::endl << k.get_diagonalmatrix() << std::endl;
    std::cout << "**************************" << std::endl;

}


void basic_test_diagonal() {
    std::cout << std::endl << "BASIC TEST DIAGONAL" << std::endl;
    matrix<int> b(4, 5);
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 5; j++)
            b(i, j) = i + j;
    auto c = b.get_diagonal();
    std::cout << "b" << std::endl << b << std::endl;
    std::cout << "c = b.get_diagonal()" << std::endl << c << std::endl;
    std::cout << std::endl << "c by column" << std::endl;
    // print using general column_begin() and column_end()
    auto ic = c.column_begin();
    auto ec = c.column_end();
    for (; ic != ec; ic++) {
        std::cout << *ic << std::endl;
    }
    std::cout << std::endl;
    // print using column_begin(0) and column_end(0)
    std::cout << "c by column 0" << std::endl;
    auto ic0 = c.column_begin(0);
    auto ec0 = c.column_end(0);
    for (; ic0 != ec0; ic0++) {
        std::cout << *ic0 << std::endl;
    }

    std::cout << "**************************" << std::endl << std::endl;

}


void test_transpose_of_transpose() {
    std::cout << "TEST TRANSPOSE OF TRANSPOSE" << std::endl;
    matrix<int> b(4, 5);
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 5; j++)
            b(i, j) = i + j;
    auto c = b.get_transpose();
    assert(c.get_cols() == 4 && c.get_rows() == 5 && "This is not a transpose!");
    std::cout << "b" << std::endl << b << std::endl;
    std::cout << "c = b.get_transpose()" << std::endl << c << std::endl;
    b(2, 2) = 100;
    std::cout << "b" << std::endl << b << std::endl;
    std::cout << "b.get_transpose()" << std::endl << b.get_transpose();
    std::cout << "**************************" << std::endl;
}


void hard_test_1() {
    std::cout << std::endl << "HARD TEST #1" << std::endl;
    matrix<int> b(8, 10);
    for (unsigned int i = 0; i < b.get_rows(); i++)
        for (unsigned int j = 0; j < b.get_cols(); j++)
            b(i, j) = i + j;
    b.get_transpose().operator()(2, 2) = 100;
    assert(b(2, 2) == 100 && "You are not sharing memory at all...");
    auto d = b.get_transpose().get_submatrix(2, 6, 1, 8);
    auto e = b.get_transpose().get_submatrix(2, 6, 1, 8).get_transpose();
    std::cout << "b" << std::endl << b << std::endl;
    std::cout << "d" << std::endl << d << std::endl;
    std::cout << "e" << std::endl << e << std::endl;
    auto f = e.get_transpose();
    std::cout << "f = e.get_transpose()" << std::endl << f << std::endl;
    std::cout << "e by column" << std::endl;
    for (unsigned int i = 0; i < e.get_cols(); i++) {
        auto col_begin = e.column_begin(i);
        auto col_end = e.column_end(i);
        for (; col_begin != col_end; ++col_begin)
            std::cout << *col_begin << " ";
        std::cout << std::endl;
    }
    auto g = f.get_diagonal();
    assert((g.get_cols() == 1) && "This is not a vector!");
    std::cout << std::endl << "g = f.get_diagonal()" << std::endl << g;
    std::cout << "**************************" << std::endl;
}


void hard_test_2() {
    std::cout << std::endl << "HARD TEST #2" << std::endl;
    matrix<int> b(8, 10);
    for (unsigned int i = 0; i < b.get_rows(); i++)
        for (unsigned int j = 0; j < b.get_cols(); j++)
            b(i, j) = i + j;
    // auto c = b.get_submatrix(0, 8, 0, 8);
    auto c = b.get_submatrix(0, 5, 1, 4);
    auto d = c.get_diagonal();
    c(3, 0) = 80;
    auto f = d.get_diagonalmatrix();
    auto l = f.get_transpose();
    // l(0, 0) = 50; // fails because l is a "descendant" of a diagonalmatrix
    std::cout << "c" << std::endl << c << std::endl;
    std::cout << "d = c.get_diagonal();" << std::endl << d << std::endl;
    std::cout << "f = d.get_diagonalmatrix();" << std::endl << f << std::endl;
    std::cout << "l = f.get_transpose(); " << std::endl << l << std::endl;
    matrix<int> k = f;
    std::cout << "k: basic matrix created from f (diagonalmatrix) using operator=" << std::endl << k << std::endl;
    matrix<int> p = d;
    std::cout << "p: basic matrix created from d (diagonal) using operator=" << std::endl << d;    
    std::cout << "**************************" << std::endl;
}

void hard_test_3() {
    std::cout << std::endl << "HARD TEST #3" << std::endl;
    matrix<int> b(8, 10);
    for (unsigned int i = 0; i < b.get_rows(); i++)
        for (unsigned int j = 0; j < b.get_cols(); j++)
            b(i, j) = i + j;
    auto d = b.get_diagonal();
    auto f = d.get_diagonalmatrix();
    auto l = f.get_transpose();
    // l(0, 0) = 50; // fails because l is a "descendant" of a diagonalmatrix
    std::cout << "d = c.get_diagonal();" << std::endl << d << std::endl;
    std::cout << "f = d.get_diagonalmatrix();" << std::endl << f;
    matrix<int> k = f;
    std::cout << std::endl << "k: basic matrix created from f (diagonalmatrix) using operator=" << std::endl << k << std::endl;
    matrix<int> p = d;
    std::cout << "p: basic matrix created from d (diagonal) using operator=" << std::endl << d;
    std::cout << "**************************" << std::endl;
}


void test_copy_iterators() {
    std::cout << std::endl << "TEST COPY ITERATORS" << std::endl;
    matrix<int> a(5, 6), b(5, 6);
    for (unsigned int i = 0; i < a.get_rows(); ++i) {
        for (unsigned int j = 0; j < a.get_cols(); ++j) {
            a(i, j) = i + j;
        }
    }
    auto ia = a.begin();
    auto ea = a.end();
    auto ib = b.begin();
    auto eb = b.end();
    for (; ia != ea && ib != eb; ia++, ib++) {
        *ib = *ia;
    }
    std::cout << "b created from a using iterators" << std::endl;
    std::cout << b << std::endl;
    auto c = a.get_transpose();
    matrix<int> g(6, 5);
    auto ic = c.begin();
    auto ec = c.end();
    auto ig = g.begin();
    auto eg = g.end();
    for (; ic != ec && ig != eg; ic++, ig++) {
        *ig = *ic;
    }
    std::cout << "c = a.get_transpose()" << std::endl;
    std::cout << c << std::endl;
    std::cout << "g created from a c iterators" << std::endl;
    std::cout << g << std::endl; 
    auto col_begin = c.column_begin();
    auto col_end = c.column_end();
    unsigned int k = 0;
    std::cout << "c printed by column" << std::endl;
    for (; col_begin != col_end; ++col_begin) {
        k++;
        std::cout << *col_begin << " ";
        if (k == c.get_rows()) {
            k = 0;
            std::cout << std::endl;
        }
    }
    std::cout << "**************************" << std::endl << std::endl << std::endl;
}


int main() {
    basic_test_basic_matrix();
    basic_test_transpose_matrix();
    basic_test_submatrix();
    basic_test_diagonalmatrix();
    basic_test_diagonal();
    test_transpose_of_transpose();
    hard_test_1();
    hard_test_2();
    hard_test_3();
    test_copy_iterators();
}