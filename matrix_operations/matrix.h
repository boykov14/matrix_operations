#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <initializer_list>


class matrix {

private:

	std::vector<int> dimentions;
	std::vector<std::vector<float>> mat;

public:

	matrix();
	matrix(int x, int y);
	matrix(int x, int y, float t);
	matrix(std::vector<std::vector<float>> data);
	matrix(const std::initializer_list<std::initializer_list<float>> &parameters);

	~matrix();

	matrix operator * (const matrix &m);
	matrix operator * (float x);
	matrix dot(const matrix &m);

	matrix operator / (float x);
	matrix dotDivide(const matrix &m);

	matrix operator - (const matrix &m);
	matrix operator - (float x);

	matrix operator + (const matrix &m);
	matrix operator + (float x);

	std::string display();

	std::vector<int> getSize();

	//float& matrix::operator[](int n);
	std::vector<float>& matrix::operator[](int n);

	matrix sum();
	matrix sumP();

	matrix natLog();

	matrix power(int n);

	matrix transpose();

	matrix addColumn(matrix n);

	matrix addColumn(matrix n, int i);

	matrix getColumn(int c);

	matrix getColumn(int c1, int c2);
};

#endif