// $Source$
// --------------------------------------------------------------------------------------------------------
// matrix.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/03/19
//
/** @file matrix.cpp
 *  @brief Matrix and vector class implementation with basic operations.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------


#include "../include/matrix.hpp"

Matrix::Matrix(const int n_row, const int n_column){
	
	if(n_row <= 0 || n_column <= 0){
		cout << "Matrix: Error in n_row/n_column\n";
		exit(EXIT_FAILURE);
	}
	
	this-> n_row = n_row;
	this-> n_column = n_column;
	
	this->data = (double**)malloc(n_row*sizeof(double*));
	
	if(this->data == NULL){
		cout << "Matrix: Error in data\n";
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n_row; i++)
		this->data[i] = (double*)malloc(n_column*sizeof(double));
	
}

Matrix::Matrix(const int n) : Matrix(1,n){
	
}

// ------------------- Member operators ------------------- //
// ------------------- Matrix ------------------- //

double& Matrix::operator () (const int n_row, const int n_column){
	if(n_row <= 0 || n_column <= 0 || n_row > this->n_row || n_column > this->n_column){
		cout << "Matrix get: Error in n_row/n_column\n";
		exit(EXIT_FAILURE);
	}
	
	return this->data[n_row-1][n_column-1];
}

Matrix& Matrix::operator + (Matrix&m){
	if(this->n_row != m.n_row || this->n_column != m.n_column){
		cout << "Matrix sum: Error in n_row/n_column\n";
		exit(EXIT_FAILURE);
	}

	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= m.n_row; i++){
		for(int j = 1; j <= m.n_column; j++){
			(*m_aux)(i,j) = (*this)(i,j)+m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator - (Matrix&m){
        if(this->n_row != m.n_row || this->n_column != m.n_column){
		cout << "Matrix sub: Error in n_row/n_column\n";
		exit(EXIT_FAILURE);
	}

	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= m.n_row; i++){
		for(int j = 1; j <= m.n_column; j++){
			(*m_aux)(i,j) = (*this)(i,j)-m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator * (Matrix &m) {
    if (this->n_column != m.n_row) { 
        cout << "Matrix: Error in matrix multiplication\n";
        exit(EXIT_FAILURE);
    }

    Matrix *m_aux = new Matrix(this->n_row, m.n_column);

    for (int i = 1; i <= this->n_row; i++) {
        for (int j = 1; j <= m.n_column; j++) {
            (*m_aux)(i, j) = 0; 
            for (int k = 1; k <= this->n_column; k++) {
                (*m_aux)(i, j) += (*this)(i, k) * m(k, j);
            }
        }
    }

    return *m_aux;
}

Matrix& Matrix::operator / (Matrix &m) {
	if (m.n_row != m.n_column) {
		cout << "Matrix division: Error, divisor must be square\n";
		exit(EXIT_FAILURE);
	}

	Matrix& m_inv = inv(m);      // inversa de la matriz m
	Matrix& result = (*this) * m_inv;  // producto con la matriz actual

	return result;
}

Matrix& Matrix::operator = (Matrix &m) {
	if (this == &m) return *this; // Evita autoasignación

	this->n_row = m.n_row;
	this->n_column = m.n_column;

	delete[] this->data; // Liberamos memoria

	this->data = (double**)malloc(n_row*sizeof(double*));
	
	if(this->data == NULL){
		cout << "Matrix: Error in data\n";
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n_row; i++)
		this->data[i] = (double*)malloc(n_column*sizeof(double));

	for (int i = 1; i <= n_row; i++) {
		for (int j = 1; j <= n_column; j++) {
			(*this)(i, j) = m(i, j);
		}
	}

	return *this;
}

// ------------------- Member operators ------------------- //
// ------------------- Matrix and double ------------------- //

Matrix& Matrix::operator + (double val) {
	Matrix* m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= this->n_row; i++) {
		for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) + val;
		}
	}
	return *m_aux;
}

Matrix& Matrix::operator - (double val) {
	Matrix* m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= this->n_row; i++) {
		for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) - val;
		}
	}
	return *m_aux;
}

Matrix& Matrix::operator * (double val) {
	Matrix* m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= this->n_row; i++) {
		for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) * val;
		}
	}
	return *m_aux;
}

Matrix& Matrix::operator / (double val) {
	if(val == 0) {
		cout << "Matrix division: Division by zero error\n";
		exit(EXIT_FAILURE);
	}

	Matrix* m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= this->n_row; i++) {
		for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) / val;
		}
	}
	return *m_aux;
}

// ------------------- Member operators ------------------- //
// ------------------- Vector ------------------- //

double& Matrix::operator () (const int i) {
	if (n_row != 1) {
		cout << "Vector operator(): Not a row vector\n";
		exit(EXIT_FAILURE);
	}
	if (i <= 0 || i > n_column) {
		cout << "Vector operator(): Index out of bounds\n";
		exit(EXIT_FAILURE);
	}
	return this->data[0][i - 1];
}

// ------------------- Non-member operators ------------------- //

ostream& operator << (ostream &o, Matrix&m){
	for(int i = 1; i <= m.n_row; i++){
		o << "[ ";
		for(int j = 1; j <= m.n_column; j++){
			printf("%5.20lf ", m(i,j));
		}
		o << " ]\n";
	}
	
	return o;
}

// ------------------- Methods ------------------- //
// ------------------- Matrix ------------------- //
Matrix& zeros(const int n_row, const int n_column) {
	Matrix *m_aux = new Matrix(n_row, n_column);
	
	for(int i = 1; i <= n_row; i++) {
		for(int j = 1; j <= n_column; j++) {
			(*m_aux)(i,j) = 0;
		}
	}
	
	return (*m_aux);
}

Matrix& eye(const int n) {
	if (n <= 0) {
		cout << "eye: Error, n must be positive\n";
		exit(EXIT_FAILURE);
	}

	Matrix* m_aux = new Matrix(n, n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			(*m_aux)(i, j) = (i == j) ? 1.0 : 0.0;
		}
	}

	return *m_aux;
}

Matrix& transpose(Matrix &m) {
	Matrix* m_aux = new Matrix(m.n_column, m.n_row);

	for (int i = 1; i <= m.n_row; i++) {
		for (int j = 1; j <= m.n_column; j++) {
			(*m_aux)(j, i) = m(i, j);
		}
	}

	return *m_aux;
}

Matrix& inv(Matrix &m) {
	if (m.n_row != m.n_column) {
		cout << "inv: Error, matrix is not square\n";
		exit(EXIT_FAILURE);
	}

	int n = m.n_row;
	Matrix* a = new Matrix(n, 2 * n); // extendida: [m | I]

	// Copiar m y la identidad en la matriz extendida
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			(*a)(i, j) = m(i, j);
			(*a)(i, j + n) = (i == j) ? 1.0 : 0.0;
		}
	}

	// Método de Gauss-Jordan
	for (int i = 1; i <= n; i++) {
		// Pivote nulo
		if ((*a)(i, i) == 0) {
			cout << "inv: Error, singular matrix\n";
			exit(EXIT_FAILURE);
		}

		// Normalizar fila i
		double pivot = (*a)(i, i);
		for (int j = 1; j <= 2 * n; j++) {
			(*a)(i, j) = (*a)(i, j) / pivot;
		}

		// Eliminar columna i de otras filas
		for (int k = 1; k <= n; k++) {
			if (k == i) continue;
			double factor = (*a)(k, i);
			for (int j = 1; j <= 2 * n; j++) {
				(*a)(k, j) -= factor * (*a)(i, j);
			}
		}
	}

	// Extraer la parte derecha como inversa
	Matrix* m_inv = new Matrix(n, n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			(*m_inv)(i, j) = (*a)(i, j + n);
		}
	}

	delete a; 

	return *m_inv;
}

// assign_column
void assign_column(Matrix &m, int col, Matrix &v) {
	if (col <= 0 || col > m.n_column || v.n_row != 1 || v.n_column != m.n_row) {
		cout << "assign_column: Dimension mismatch or invalid column\n";
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= m.n_row; i++) {
		m(i, col) = v(1, i);
	}
}

// assign_row
void assign_row(Matrix &m, int row, Matrix &v) {
	if (row <= 0 || row > m.n_row || v.n_row != 1 || v.n_column != m.n_column) {
		cout << "assign_row: Dimension mismatch or invalid row\n";
		exit(EXIT_FAILURE);
	}
	for (int j = 1; j <= m.n_column; j++) {
		m(row, j) = v(1, j);
	}
}

// extract_column
Matrix& extract_column(Matrix &m, int col) {
	if (col <= 0 || col > m.n_column) {
		cout << "extract_column: Invalid column\n";
		exit(EXIT_FAILURE);
	}
	Matrix* result = new Matrix(1, m.n_row);
	for (int i = 1; i <= m.n_row; i++) {
		(*result)(1, i) = m(i, col);
	}
	return *result;
}

// extract_row
Matrix& extract_row(Matrix &m, int row) {
	if (row <= 0 || row > m.n_row) {
		cout << "extract_row: Invalid row\n";
		exit(EXIT_FAILURE);
	}
	Matrix* result = new Matrix(1, m.n_column);
	for (int j = 1; j <= m.n_column; j++) {
		(*result)(1, j) = m(row, j);
	}
	return *result;
}

// equals
bool equals(Matrix m1, Matrix m2) {
    // Verificar que las matrices tengan el mismo tamaño
    if (m1.n_row != m2.n_row || m1.n_column != m2.n_column) {
        return false;
    }

    for (int i = 1; i <= m1.n_row; i++) {
		for (int j = 1; j <= m1.n_column; j++) {
			double a = m1(i, j);
			double b = m2(i, j);
			double diff = std::abs(a - b);
			double maxAbs = std::max(std::abs(a), std::abs(b));
			if (diff > 1e-6 && diff / (maxAbs + 1e-10) > 1e-6) {
				return false;
			}
		}
	}	

    // Si no hay diferencias, las matrices son iguales dentro de la tolerancia
    return true;
}

// ------------------- Methods ------------------- //
// ------------------- Vector ------------------- //

// zeros(n): vector fila de n ceros
Matrix& zeros(const int n) {
	Matrix* m_aux = new Matrix(1, n);
	for (int j = 1; j <= n; j++) {
		(*m_aux)(1, j) = 0;
	}
	return *m_aux;
}

// norm: norma euclídea del vector
double norm(Matrix &v) {
	if (v.n_row != 1) {
		cout << "norm: Not a row vector\n";
		exit(EXIT_FAILURE);
	}
	double sum = 0;
	for (int i = 1; i <= v.n_column; i++) {
		sum += v(1, i) * v(1, i);
	}
	return sqrt(sum);
}

// dot: producto escalar
double dot(Matrix &v, Matrix &w) {
	if (v.n_row != 1 || w.n_row != 1 || v.n_column != w.n_column) {
		cout << "dot: Dimension mismatch or not row vectors\n";
		exit(EXIT_FAILURE);
	}
	double result = 0;
	for (int i = 1; i <= v.n_column; i++) {
		result += v(1, i) * w(1, i);
	}
	return result;
}

// cross: producto vectorial 3D
Matrix& cross(Matrix &v, Matrix &w) {
	if (v.n_row != 1 || w.n_row != 1 || v.n_column != 3 || w.n_column != 3) {
		cout << "cross: Must be 3D row vectors\n";
		exit(EXIT_FAILURE);
	}

	Matrix* result = new Matrix(1, 3);
	(*result)(1, 1) = v(1, 2) * w(1, 3) - v(1, 3) * w(1, 2);
	(*result)(1, 2) = v(1, 3) * w(1, 1) - v(1, 1) * w(1, 3);
	(*result)(1, 3) = v(1, 1) * w(1, 2) - v(1, 2) * w(1, 1);
	return *result;
}

// extract_vector(start, end): extrae un subvector
Matrix& extract_vector(Matrix &v, const int start, const int end) {
	if (v.n_row != 1 || start <= 0 || end > v.n_column || start > end) {
		cout << "extract_vector: Invalid range or not a row vector\n";
		exit(EXIT_FAILURE);
	}
	Matrix* result = new Matrix(1, end - start + 1);
	for (int i = 0; i < end - start + 1; i++) {
		(*result)(1, i + 1) = v(1, start + i);
	}
	return *result;
}

// union_vector(v, w): concatena dos vectores
Matrix& union_vector(Matrix &v, Matrix &w) {
	if (v.n_row != 1 || w.n_row != 1) {
		cout << "union_vector: Both must be row vectors\n";
		exit(EXIT_FAILURE);
	}
	int n = v.n_column + w.n_column;
	Matrix* result = new Matrix(1, n);
	for (int i = 1; i <= v.n_column; i++) (*result)(1, i) = v(1, i);
	for (int i = 1; i <= w.n_column; i++) (*result)(1, v.n_column + i) = w(1, i);
	return *result;
}