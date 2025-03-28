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
		
		// Parametrized constructor
		Matrix(const int n_row, const int n_column);
		
		// Member operators
		double& operator () (const int n_row, const int n_column);
		Matrix& operator + (Matrix&m);
		Matrix& operator - (Matrix&m);
		Matrix& operator * (Matrix &m);
		
		// Non-member operators
		friend ostream& operator << (ostream &o, Matrix&m);
	
};
// Operator overloading
ostream& operator << (ostream &o, Matrix&m);

// Methods
Matrix& zeros(const int n_row, const int n_column);

#endif
