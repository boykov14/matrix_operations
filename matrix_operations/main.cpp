#include <stdio.h>
#include <iostream>

#include "matrix.h"

int main() {

	matrix X = { {1,2,3}, {4,5,6}, {7,8,9} ,{100,200,456} };

	X.display();
	getchar();

	matrix Y = X[':'];


	Y.display();
	X.display();

	getchar();
}