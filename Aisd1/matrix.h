#include <stdlib.h>
#include <iostream>

using namespace std;

class Matrix {
private:
	int rows, columns;
	double** matrix;
public:
	double epsilon;
	Matrix();
	Matrix(int rows, int columns);
	~Matrix();
	Matrix(const Matrix& obj);
	void EnterMatrix();
	double& operator () (int i, int j);
	Matrix operator + (const Matrix& rhs);
	Matrix operator - (const Matrix& rhs);
	Matrix operator * (const Matrix& rhs);
	Matrix operator * (const double h);
	Matrix operator / (const double h);
	Matrix& operator = (const Matrix& a);
	bool operator == (const Matrix& rhs);
	friend Matrix operator / (double h, Matrix matrix);
	friend Matrix operator * (double h, Matrix matrix);
	friend std::ostream& operator << (std::ostream& out, const Matrix& matrix);
	int GetRows() const;
	int GetCols() const;
	double tr();
	Matrix Solution_of_the_equation(const Matrix& vector);
};