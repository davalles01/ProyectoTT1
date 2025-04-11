// $Source$
// --------------------------------------------------------------------------------------------------------
// matrix_tests.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file matrix_tests.cpp
 *  @brief Contains tests for all methods defined in matrix.hpp.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include <assert.h>
#include <iostream>

using namespace std;

/** @brief Tests the constructor and element assignment */
void test_constructor_and_operator_parentheses() {
    Matrix m(2, 2);
    m(1, 1) = 1.0;
    m(1, 2) = 2.0;
    m(2, 1) = 3.0;
    m(2, 2) = 4.0;

    assert(m(1, 1) == 1.0);
    assert(m(1, 2) == 2.0);
    assert(m(2, 1) == 3.0);
    assert(m(2, 2) == 4.0);
}

/** @brief Tests the Matrix '+' Matrix operation */
void test_addition() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(1, 1) = 1; a(1, 2) = 2; a(2, 1) = 3; a(2, 2) = 4;
    b(1, 1) = 5; b(1, 2) = 6; b(2, 1) = 7; b(2, 2) = 8;
    Matrix& result = a + b;

    assert(result(1, 1) == 6);
    assert(result(2, 2) == 12);
}

/** @brief Tests the Matrix '-' Matrix operation */
void test_subtraction() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(1, 1) = 5; a(1, 2) = 6; a(2, 1) = 7; a(2, 2) = 8;
    b(1, 1) = 1; b(1, 2) = 2; b(2, 1) = 3; b(2, 2) = 4;
    Matrix& result = a - b;

    assert(result(1, 1) == 4);
    assert(result(2, 2) == 4);
}

/** @brief Tests the Matrix '*' Matrix operation */
void test_multiplication_matrix() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(1, 1) = 1; a(1, 2) = 2;
    a(2, 1) = 3; a(2, 2) = 4;
    b(1, 1) = 2; b(1, 2) = 0;
    b(2, 1) = 1; b(2, 2) = 2;
    Matrix& result = a * b;

    assert(result(1, 1) == 4);
    assert(result(2, 2) == 8);
}

/** @brief Tests the Matrix '/' Matrix operation */
void test_division_matrix() {
    Matrix a = eye(2);
    Matrix b = eye(2);
    Matrix& result = a / b;

    assert(result(1, 1) == 1);
    assert(result(2, 2) == 1);
}

/** @brief Tests the Matrix '=' Matrix assignment */
void test_assignment() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(1, 1) = 5; a(2, 2) = 10;
    b = a;

    assert(b(1, 1) == 5);
    assert(b(2, 2) == 10);
}

/** @brief Tests matrix with scalar operations */
void test_scalar_operations() {
    Matrix a(2, 2);
    a(1, 1) = 2; a(2, 2) = 4;

    Matrix& add = a + 1;
    Matrix& sub = a - 1;
    Matrix& mul = a * 2;
    Matrix& div = a / 2;

    assert(add(1, 1) == 3);
    assert(sub(2, 2) == 3);
    assert(mul(1, 1) == 4);
    assert(div(2, 2) == 2);
}

/** @brief Tests the vector access operator */
void test_vector_access() {
    Matrix v(3);
    v(1) = 10; v(2) = 20; v(3) = 30;
    assert(v(2) == 20);
}

/** @brief Tests the eye function */
void test_eye() {
    Matrix& I = eye(3);
    assert(I(1, 1) == 1);
    assert(I(1, 2) == 0);
    assert(I(3, 3) == 1);
}

/** @brief Tests the transpose function */
void test_transpose() {
    Matrix m(2, 3);
    m(1, 1) = 1; m(1, 2) = 2; m(1, 3) = 3;
    m(2, 1) = 4; m(2, 2) = 5; m(2, 3) = 6;
    Matrix& t = transpose(m);
    assert(t(1, 2) == 4);
    assert(t(3, 2) == 6);
}

/** @brief Tests the inv function */
void test_inverse() {
    Matrix m(2, 2);
    m(1, 1) = 4; m(1, 2) = 7;
    m(2, 1) = 2; m(2, 2) = 6;
    Matrix& inv_m = inv(m);
    Matrix& identity = m * inv_m;
    assert(identity(1, 1) - 1 < 1e-10);
    assert(identity(2, 2) - 1 < 1e-10);
}

/** @brief Tests assign_column */
void test_assign_column() {
    Matrix m(2, 2);
    Matrix v(1, 2);
    v(1, 1) = 9; v(1, 2) = 8;
    assign_column(m, 2, v);
    assert(m(1, 2) == 9);
    assert(m(2, 2) == 8);
}

/** @brief Tests assign_row */
void test_assign_row() {
    Matrix m(2, 2);
    Matrix v(1, 2);
    v(1, 1) = 9; v(1, 2) = 8;
    assign_row(m, 1, v);
    assert(m(1, 1) == 9);
    assert(m(1, 2) == 8);
}

/** @brief Tests extract_column */
void test_extract_column() {
    Matrix m(2, 2);
    m(1, 1) = 1; m(2, 1) = 2;
    Matrix& c = extract_column(m, 1);
    assert(c(1, 1) == 1);
    assert(c(1, 2) == 2);
}

/** @brief Tests extract_row */
void test_extract_row() {
    Matrix m(2, 2);
    m(1, 1) = 3; m(1, 2) = 4;
    Matrix& r = extract_row(m, 1);
    assert(r(1, 1) == 3);
    assert(r(1, 2) == 4);
}

/** @brief Tests norm function */
void test_norm() {
    Matrix v(3);
    v(1) = 3; v(2) = 4; v(3) = 0;
    double n = norm(v);
    assert(n == 5);
}

/** @brief Tests dot function */
void test_dot() {
    Matrix v(3), w(3);
    v(1) = 1; v(2) = 2; v(3) = 3;
    w(1) = 4; w(2) = 5; w(3) = 6;
    assert(dot(v, w) == 32);
}

/** @brief Tests cross product */
void test_cross() {
    Matrix v(3), w(3);
    v(1) = 1; v(2) = 0; v(3) = 0;
    w(1) = 0; w(2) = 1; w(3) = 0;
    Matrix& r = cross(v, w);
    assert(r(1) == 0 && r(2) == 0 && r(3) == 1);
}

/** @brief Tests extract_vector */
void test_extract_vector() {
    Matrix v(5);
    for (int i = 1; i <= 5; i++) v(i) = i;
    Matrix& s = extract_vector(v, 2, 4);
    assert(s(1) == 2);
    assert(s(3) == 4);
}

/** @brief Tests union_vector */
void test_union_vector() {
    Matrix a(2), b(3);
    a(1) = 1; a(2) = 2;
    b(1) = 3; b(2) = 4; b(3) = 5;
    Matrix& r = union_vector(a, b);
    assert(r(5) == 5);
}

int main() {
    test_constructor_and_operator_parentheses();
    test_addition();
    test_subtraction();
    test_multiplication_matrix();
    test_division_matrix();
    test_assignment();
    test_scalar_operations();
    test_vector_access();
    test_eye();
    test_transpose();
    test_inverse();
    test_assign_column();
    test_assign_row();
    test_extract_column();
    test_extract_row();
    test_norm();
    test_dot();
    test_cross();
    test_extract_vector();
    test_union_vector();

    cout << "All tests passed successfully.\n";
    return 0;
}
