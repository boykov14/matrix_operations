#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <string>
#include <initializer_list>

#include "matrix.h"

/*Default constructor initializing a matrix of size 0
*/
matrix::matrix() {
	dimentions.push_back(0);
	dimentions.push_back(0);
}

/**Constructor that initializes a X by Y matrix filled with zeroes
*@param dimentions X and Y of the matrix;
*/
matrix::matrix(int x, int y) {
	dimentions.push_back(x);
	dimentions.push_back(y);

	for (int i = 0; i < x; i++) {
		std::vector<float> newV(y, 0);

		mat.push_back(newV);
	}
}

/**Constructor that initializes a X by Y matrix filled with floats t
*@param dimentions X and Y of the matrixand the value with which to fill the matrix;
*/
matrix::matrix(int x, int y, float t) {
	dimentions.push_back(x);
	dimentions.push_back(y);

	for (int i = 0; i < x; i++) {
		std::vector<float> newV(y, t);

		mat.push_back(newV);
	}
}

/**Constructor that initializes matrix equivalent to a provided 2 dimentional float vector
*@param 2d float vector
*/
matrix::matrix(std::vector<std::vector<float>> data) {
	//if 2d vector is empty
	if (data.size() == 0) {
		dimentions.push_back(0);
		dimentions.push_back(0);
	}
	//if 2d vector is not empty
	else {
		//retrieve dimentions of provided 2d vect
		dimentions.push_back(data.size());
		dimentions.push_back(data[0].size());

		//copy data from 2d vect into matrix
		for (int i = 0; i < dimentions[0]; i++) {
			std::vector<float> newV(dimentions[1]);

			for (int j = 0; j < dimentions[1]; j++) {
				newV[j] = data[i][j];
			}
			mat.push_back(newV);
		}
	}
}

/*constructor which allows to build a matrix from an initializer list
@param a 2 dimentional initializer list
*/
matrix::matrix(const std::initializer_list<std::initializer_list<float>> &parameters) {
	dimentions.push_back(parameters.size());
	dimentions.push_back((*(parameters.begin())).size());


	for (auto itm1 : parameters) {
		std::vector<float> newV;
		for (auto itm2 : itm1) {
			newV.push_back(itm2);
		}
		mat.push_back(newV);
		if (newV.size() != dimentions[1]) {
			std::cerr << "The provided initializer list is invalid, it must have the same ammount of numbers in each row" << std::endl;
			exit(1);
		}
	}
}

/**Destructor
*/
matrix::~matrix() {
	dimentions.clear();
	mat.clear();
}

/**multiplication operator of a matrix by a matrix
*@param the matrix by which to multiply this matrix
*@return the resulting matrix
*/
matrix matrix::operator * (const matrix &m) {
	//determining the dimentions of the new matrix;
	int x = dimentions[0];
	int y = m.dimentions[1];

	//checking that the operation is valid
	if (dimentions[1] != m.dimentions[0]) {
		std::cerr << "unable to perform such multiplication as the matrix dimentions are not valid" << std::endl;
		exit(1);
	}

	std::vector<std::vector<float>> newM;

	for (int i = 0; i < x; i++) {
		std::vector<float> newV(y);

		for (int j = 0; j < y; j++) {
			float mult = 0;

			for (int k = 0; k < dimentions[1]; k++) {
				mult += mat[i][k] * m.mat[k][j];
			}
			newV[j] = mult;
		}

		newM.push_back(newV);
	}

	matrix finalM(newM);

	return finalM;

}

/**multiplication operator of a matrix by a float
*@param the float by which to multiply this matrix
*@return the resulting matrix
*/
matrix matrix::operator * (float x) {
	matrix newM(dimentions[0], dimentions[1]);
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			newM.mat[i][j] = mat[i][j] * x;
		}
	}
	return newM;
}

/**multiplication of a matrix by a matrix element wise
*@param the matrix by which to multiply this matrix
*@return the resulting matrix
*/
matrix matrix::dot(const matrix &m) {
	//making sure that the operation is feasible based on the dimentions
	if (m.dimentions[1] != 1 || m.dimentions[0] != dimentions[0]) {
		std::cerr << "Invalid indexes used in dot multiplication" << std::endl;
		exit(1);
	}

	matrix newM(dimentions[0], dimentions[1]);
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			newM.mat[i][j] = m.mat[i][0] * mat[i][j];
		}
	}
	return newM;
}


/**overloading division operator so matrix can be divided by a floating point value
*@param the float by which to divide every element in the matrix
*@return the resulting matrix
*/
matrix matrix::operator / (float x) {
	matrix newM(dimentions[0], dimentions[1]);
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			newM.mat[i][j] = mat[i][j] / x;
		}
	}
	return newM;
}

/**Function allowing every element in matrix to be divided by the appropriate element of another
*@param the matrix by which to divide the matrix
*@return the resulting matrix
*/
matrix matrix::dotDivide(const matrix &m) {
	//making sure that the operation is feasible based on the dimentions
	if (m.dimentions[1] == 1 && m.dimentions[0] == dimentions[0]) {

		matrix newM(dimentions[0], dimentions[1]);
		for (int i = 0; i < dimentions[0]; i++) {
			for (int j = 0; j < dimentions[1]; j++) {
				newM.mat[i][j] = mat[i][j] / m.mat[i][0];
			}
		}
		return newM;
	}
	else if (m.dimentions[0] == 1 && m.dimentions[1] == dimentions[1]) {
		matrix newM(dimentions[0], dimentions[1]);
		for (int i = 0; i < dimentions[0]; i++) {
			for (int j = 0; j < dimentions[1]; j++) {
				newM.mat[i][j] = mat[i][j] / m.mat[0][j];
			}
		}
		return newM;
	}
	else {
		std::cerr << "Invalid indexes used in dot multiplication" << std::endl;
		exit(1);
	}
}

/*overloading the - operator so that one matrix can be subtracted from another element wise
@param a matrix to be subtracted from this matrix
@return the resulting matrix
*/
matrix matrix::operator - (const matrix &m) {
	//making sure that the operation is feasible based on the dimentions
	if (m.dimentions[1] == 1 && m.dimentions[0] == dimentions[0]) {


		matrix newM(dimentions[0], dimentions[1]);
		for (int i = 0; i < dimentions[0]; i++) {
			for (int j = 0; j < dimentions[1]; j++) {
				newM.mat[i][j] = mat[i][j] - m.mat[i][0];
			}
		}
		return newM;
	}
	else if (m.dimentions[0] == 1 && m.dimentions[1] == dimentions[1]) {
		matrix newM(dimentions[0], dimentions[1]);
		for (int i = 0; i < dimentions[0]; i++) {
			for (int j = 0; j < dimentions[1]; j++) {
				newM.mat[i][j] = mat[i][j] - m.mat[0][j];
			}
		}
		return newM;
	}
	else {
		std::cerr << "Invalid indexes used in dot multiplication" << std::endl;
		exit(1);
	}
}

/**overloading the - operator so a number can be subtracted from the matrix
*@param the float which is to be subtrcted from every term
*@return the resulting matrix
*/
matrix matrix::operator - (float x) {
	matrix newM(dimentions[0], dimentions[1]);
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			newM[i][j] = mat[i][j] - x;
		}
	}
	return newM;
}

/*overloading the + operator so that one matrix can be added to another element wise
@param the matrix to be added to the current matrix
@return the resulting matrix
*/
matrix matrix::operator + (const matrix &m) {
	//making sure that the operation is feasible based on the dimentions
	if (m.dimentions[1] != 1 || m.dimentions[0] != dimentions[0]) {
		std::cerr << "Invalid indexes used in dot multiplication" << std::endl;
		exit(1);
	}

	matrix newM(dimentions[0], dimentions[1]);
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			newM.mat[i][j] = mat[i][j] + m.mat[i][0];
		}
	}
	return newM;
}

/**overloading the + operator so a number can be added to the matrix
*@param the float which is to be added to every term
*@return the resulting matrix
*/
matrix matrix::operator + (float x) {
	matrix newM(dimentions[0], dimentions[1]);
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			newM.mat[i][j] = mat[i][j] + x;
		}
	}
	return newM;
}


/**outputs the content of the matrix to the command prompt
*@return a string identical to what was outputed to the command prompt
*/
std::string matrix::display() {
	std::string disp = "";

	//going through the matrix adding the elements to the output string
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			disp += std::to_string(mat[i][j]);
			disp += ' ';
		}
		disp += '\n';
	}

	std::cout << disp << "\n";

	return disp;
}

/**Getter method which retrieves the dimentions of the matrix
*@return vector which contains the dimentions of the matrix
*/
std::vector<int> matrix::getSize() {
	return dimentions;
}

/*method that overwrites the [] operator
*@param integer n which is the index of the number to be retrieved from the matrix if the matrix were stretched into a vector
*/
std::vector<float>& matrix::operator[](int n) {
	//checking that the index is valid
	if (n < 0 || n >= dimentions[0]) {
		std::cerr << "invalid index" << std::endl;
		exit(1);
	}
	return mat[n];
}

/**operator that returns a different matrix depending on the char provided
*@param a char
*@return a matrix which will vary depending on the char provided, otherwise if an invalid char is provided the program will exit
*/
matrix matrix::operator[](char c) {
	//checking the char provided and returning appropriate response
	//provide : to return a vector matrix of all the values in the matrix
	if (c == ':') {
		int total = dimentions[0] * dimentions[1];
		return this->reshape(0, total-1, total, 1);
	}
	else {
		std::cerr << "invalid char provided" << std::endl;
		exit(1);
	}
}

/**method that returns a value at a specific index in the matrix
*@param the index in the matrix
*@return the val at the specified index in the matrix
*/
float& matrix::getValAt(int n) {
	int x = int(n / dimentions[1]);
	int y = n%dimentions[1];

	return mat[x][y];
}

/*function that determines the sum of the values in each column
@return the matrix of the sums
*/
matrix matrix::sum() {
	matrix returnVal(1, dimentions[1], 0);

	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			returnVal[0][j] += mat[i][j];
		}
	}

	return returnVal;
}

matrix matrix::sumP() {
	matrix returnVal(1, dimentions[1], 0);

	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			returnVal[0][j] += mat[i][j];
			std::cout << returnVal[0][j] << std::endl;
		}
	}

	return returnVal;
}

/**Function that takes the log base e of every term in the matrix
*@return the resulting matrix
*/
matrix matrix::natLog() {
	matrix newM(dimentions[0], dimentions[1]);
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			if (mat[i][j] >(pow(10, -15))) {
				newM.mat[i][j] = log(mat[i][j]);
			}
			else {
				newM.mat[i][j] = log(pow(10, -15));
			}
		}
	}
	return newM;
}

/*Function that takes the power of n of every element in the matrix
@param the power to which exponentiate every element of the matrix
@return the resulting matrix
*/
matrix matrix::power(int n) {
	matrix newM(dimentions[0], dimentions[1]);
	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			newM.mat[i][j] = pow(mat[i][j], n);
		}
	}
	return newM;
}

/*transpose function
@return the transpose of the original matrix
*/
matrix matrix::transpose() {
	matrix nM(dimentions[1], dimentions[0]);

	for (int i = 0; i < dimentions[0]; i++) {
		for (int j = 0; j < dimentions[1]; j++) {
			nM.mat[j][i] = mat[i][j];
		}
	}
	return nM;
}

/**function that adds a column to the matrix
*@param a matrix of the same first dimention as the matrix to which it will be added
*/
matrix matrix::addColumn(matrix n) {
	//making sure that the vect is of the right length
	if (n.dimentions[0] != dimentions[0] && n.dimentions[1] != 1) {
		std::cerr << "Dimentions of matricies dont match properly, cant add new column" << std::endl;
		exit(1);
	}

	for (int i = 0; i < dimentions[0]; i++) {
		mat[i].push_back(n[i][0]);
	}

	dimentions[1] += 1;

	return *this;
}

/*function that adds a column to the matrix at a certain index
@param a matrix of the same first dimention as the matrix to which it is added and the index to which it should be added
*/
matrix matrix::addColumn(matrix n, int p) {
	//making sure that the vect is of the right length
	if (n.dimentions[0] != dimentions[0] && n.dimentions[1] != 1) {
		std::cerr << "Dimentions of matricies dont match properly, cant add new column" << std::endl;
		exit(1);
	}

	if (p < 0 || p > dimentions[1]) {
		std::cerr << "Cannot add column at the index provided" << std::endl;
		exit(1);
	}

	for (int i = 0; i < dimentions[0]; i++) {
		std::vector<float>::iterator pos = mat[i].begin();
		mat[i].insert(pos + p, n[i][0]);
	}

	dimentions[1] += 1;

	return *this;
}

/**getter method which returns a column from a matrix
*@param the index of the column to be returned
*@return the resulting matrix
*/
matrix matrix::getColumn(int c) {
	//checking that a valid index was given
	if (c >= 0 && c < dimentions[1]) {
		matrix nM(dimentions[0], 1);

		for (int i = 0; i < dimentions[0]; i++) {
			nM[i][0] = mat[i][c];
		}

		return nM;
	}
}

/**getter method which returns columns in the provided range (from c1 to c2)
*@param the column range to be returned
*@return the resulting matrix
*/
matrix matrix::getColumn(int c1, int c2) {
	if (c1 >= 0 && c2 >= 0 && c2 > c1 && c2 < dimentions[1]) {
		matrix nM(dimentions[0], 0);

		for (int i = c1; i <= c2; i++) {
			nM.addColumn(this->getColumn(i));
		}

		return nM;
	}
}

/**method which creates a new x by y matrix from the i1 to i2 element of the existing matrix
@param i1 i2 giving the range of elements to be used, and x y as dimentions for the new matrix
@return the resulting matrix
*/
matrix matrix::reshape(int i1, int i2, int x, int y) {
	//checking that the operation is feasible
	if (x * y != i2 - i1 + 1) {
		std::cerr << "reshape dimentions and range do not match" << std::endl;
		exit(1);
	}
	else if (i1 > i2 || (i1 < 0 || i2 >= dimentions[0] * dimentions[1])) {
		std::cerr << "invalid range" << std::endl;
		exit(1);
	}

	matrix nM(x, y);

	for (int i = i1; i <= i2; i++) {
		nM.getValAt(i - i1) = this->getValAt(i);
	}

	return nM;
	
}