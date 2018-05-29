/* Sýrrý Kýrýmlýoðlu  */
#include <cmath>
#include <cstdio>
#include <iostream>

class SmallVector {
	int StaticBuffer[32];
	int *DynamicBuffer;
	int size, capacity;
public:
	SmallVector() {};
	SmallVector(int[], int);
	SmallVector(const SmallVector &);
	~SmallVector();
	int pop_back();
	void push_back(int);
	void push_back(int[], int);
	SmallVector reverse();
	SmallVector operator+(const SmallVector&) const;
	const SmallVector& operator=(const SmallVector &);
	int & operator[](int);
	SmallVector operator*(int);
	int getSize() const;
	int operator[](int) const;
};
