#include <iostream>
#include "SmallVector.h"

void printSmallVector(const char* const message, const SmallVector& in_vector)
{
	std::cout << message << ": ";
	for (int i = 0; i < in_vector.getSize(); i++)
	{
		std::cout << in_vector[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	int temp[35];
	for (int i = 0; i < 35; i++)
		temp[i] = i;
	SmallVector test(temp, 10);				// creating SmallVector with 10 elements
	SmallVector test2(temp, 35);			// creating SmallVector with 35 elements
											// print test in reverse order
	printSmallVector("Printing test in reverse", test.reverse());
	SmallVector test3;						// empty SmallVector
	test3 = test2 + test;					// concatenate two SmallVectors
	printSmallVector("Printing test3", test3);
	SmallVector test4(test);				// copy SmallVector
	SmallVector test5(temp, 2);
	test5 = test5 * 5;						// replicate elements
	test5.push_back(12);					// add 12 at the end
	test5[0] = 4;							// modify the first element of test5
	std::cout << "Printing test5 in reverse: ";
	for (int i = 1; i < test5.getSize() + 1; i++)
	{
		// testing negative numbers as indices
		std::cout << test5[-i] << "  ";
	}
	getchar();
	return 0;
}
