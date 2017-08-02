#include <stdio.h>
#include <iostream>

#include "matrix.h"

int main() {

	matrix X = { {1,2,3}, {4,5,6}, {7,8,9} };

	X.display();
	getchar();

	matrix Y = X.reshape(1, 8, 2, 4);

	Y.display();
	X.display();

	getchar();
}