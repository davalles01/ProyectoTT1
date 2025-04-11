
// $Header$
// --------------------------------------------------------------------------------------------------------
// matrix.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/03/19
//
/** @file matrix.hpp
 *  @brief Matrix and vector class implementation with basic operations.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _MATRIX_
#define _MATRIX_

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

class Matrix{
	private: 
		double **data; 
		
	public:
		int n_row, n_column;
		
		// --------------------------------------------------------------------------------
		// Parametrized constructors
		// --------------------------------------------------------------------------------
		
		/**
		 * @brief Constructor for creating a matrix with the given number of rows and columns.
		 * @param n_row Number of rows.
		 * @param n_column Number of columns.
		 */
		Matrix(const int n_row, const int n_column);

		/**
		 * @brief Constructor for creating a vector of size n (1 row, n columns).
		 * @param n Size of the vector.
		 */
		Matrix(const int n);

		// --------------------------------------------------------------------------------
		// Member operators - Matrix
		// --------------------------------------------------------------------------------
		
		/**
		 * @brief Access or modify the element at a given row and column.
		 * @param n_row Row index (1-based).
		 * @param n_column Column index (1-based).
		 * @return Reference to the element.
		 */
		double& operator () (const int n_row, const int n_column);

		/**
		 * @brief Adds two matrices.
		 * @param m Matrix to add.
		 * @return Reference to the resulting matrix.
		 */
		Matrix& operator + (Matrix &m);

		/**
		 * @brief Subtracts one matrix from another.
		 * @param m Matrix to subtract.
		 * @return Reference to the resulting matrix.
		 */
		Matrix& operator - (Matrix &m);

		/**
		 * @brief Multiplies two matrices.
		 * @param m Matrix to multiply by.
		 * @return Reference to the resulting matrix.
		 */
		Matrix& operator * (Matrix &m);

		/**
		 * @brief Divides one matrix by another (i.e., multiplies by the inverse).
		 * @param m Matrix to divide by.
		 * @return Reference to the resulting matrix.
		 */
		Matrix& operator / (Matrix &m);

		/**
		 * @brief Assigns the values of one matrix to another.
		 * @param m Matrix to assign from.
		 * @return Reference to the current matrix.
		 */
		Matrix& operator = (Matrix &m);

		// --------------------------------------------------------------------------------
		// Member operators - Matrix and double
		// --------------------------------------------------------------------------------

		/**
		 * @brief Adds a scalar value to all elements in the matrix.
		 * @param val Scalar value.
		 * @return Reference to the resulting matrix.
		 */
		Matrix& operator + (double val);

		/**
		 * @brief Subtracts a scalar value from all elements in the matrix.
		 * @param val Scalar value.
		 * @return Reference to the resulting matrix.
		 */
		Matrix& operator - (double val);

		/**
		 * @brief Multiplies all elements in the matrix by a scalar value.
		 * @param val Scalar value.
		 * @return Reference to the resulting matrix.
		 */
		Matrix& operator * (double val);

		/**
		 * @brief Divides all elements in the matrix by a scalar value.
		 * @param val Scalar value.
		 * @return Reference to the resulting matrix.
		 */
		Matrix& operator / (double val);

		// --------------------------------------------------------------------------------
		// Member operators - Vector
		// --------------------------------------------------------------------------------

		/**
		 * @brief Access or modify the i-th element of the vector.
		 * @param i Index (1-based).
		 * @return Reference to the element.
		 */
		double& operator () (const int i);

		// --------------------------------------------------------------------------------
		// Non-member operators
		// --------------------------------------------------------------------------------

		/**
		 * @brief Prints the matrix to the output stream.
		 * @param o Output stream.
		 * @param m Matrix to print.
		 * @return Reference to the output stream.
		 */
		friend ostream& operator << (ostream &o, Matrix&m);
};

// --------------------------------------------------------------------------------
// Non-member operator
// --------------------------------------------------------------------------------

/**
 * @brief Prints the matrix to the output stream.
 * @param o Output stream.
 * @param m Matrix to print.
 * @return Reference to the output stream.
 */
ostream& operator << (ostream &o, Matrix&m);

// --------------------------------------------------------------------------------
// Methods - Matrix
// --------------------------------------------------------------------------------

/**
 * @brief Creates a matrix of given dimensions filled with zeros.
 * @param n_row Number of rows.
 * @param n_column Number of columns.
 * @return Reference to the new zero matrix.
 */
Matrix& zeros(const int n_row, const int n_column);

/**
 * @brief Creates an identity matrix of size n x n.
 * @param n Size of the identity matrix.
 * @return Reference to the new identity matrix.
 */
Matrix& eye(const int n);

/**
 * @brief Returns the transpose of a matrix.
 * @param m Matrix to transpose.
 * @return Reference to the transposed matrix.
 */
Matrix& transpose(Matrix &m);

/**
 * @brief Returns the inverse of a matrix.
 * @param m Matrix to invert.
 * @return Reference to the inverted matrix.
 */
Matrix& inv(Matrix &m);

/**
 * @brief Assigns a vector to a specific column of the matrix.
 * @param m Matrix to assign the column to
 * @param col Column index (1-based).
 * @param v Vector to assign.
 */
void assign_column(Matrix &m, int col, Matrix &v);

/**
 * @brief Assigns a vector to a specific row of the matrix.
 * @param m Matrix to assign the row to
 * @param row Row index (1-based).
 * @param v Vector to assign.
 */
void assign_row(Matrix &m, int row, Matrix &v);

/**
 * @brief Extracts a specific column from the matrix as a vector.
 * @param m Matrix to extract the column from
 * @param col Column index (1-based).
 * @return Reference to the extracted column vector.
 */
Matrix& extract_column(Matrix &m, int col);

/**
 * @brief Extracts a specific row from the matrix as a vector.
 * @param m Matrix to extract the row from
 * @param row Row index (1-based).
 * @return Reference to the extracted row vector.
 */
Matrix& extract_row(Matrix &m, int row);

// --------------------------------------------------------------------------------
// Methods - Vector
// --------------------------------------------------------------------------------

/**
 * @brief Creates a vector of given size filled with zeros.
 * @param n Size of the vector.
 * @return Reference to the new zero vector.
 */
Matrix& zeros(const int n);

/**
 * @brief Computes the norm of the vector.
 * @param v Vector to compute the norm of
 * @return Norm of the vector.
 */
double norm(Matrix &v);

/**
 * @brief Computes the dot product with another vector.
 * @param v First vector to compute dot product with.
 * @param w Second vector to compute dot product with.
 * @return Scalar dot product.
 */
double dot(Matrix &v, Matrix &w);

/**
 * @brief Computes the cross product between 2 vectors (only valid for size 3).
 * @param v First vector to compute cross product with.
 * @param w Second vector to compute cross product with.
 * @return Reference to the resulting vector.
 */
Matrix& cross(Matrix &v, Matrix &w);

/**
 * @brief Extracts a subvector between given indices (inclusive).
 * @param v Vector to extract from 
 * @param start Start index (1-based).
 * @param end End index (1-based).
 * @return Reference to the resulting subvector.
 */
Matrix& extract_vector(Matrix &v, const int start, const int end);

/**
 * @brief Concatenates two vectors into one.
 * @param v First vector.
 * @param w Second vector.
 * @return Reference to the resulting vector.
 */
Matrix& union_vector(Matrix &v, Matrix &w);

#endif
