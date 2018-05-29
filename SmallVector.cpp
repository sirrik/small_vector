/* Sýrrý Kýrýmlýoðlu*/

#include <iostream>
#include "SmallVector.h"

SmallVector::SmallVector(int temp[], int vector_size) {
	if (vector_size > 32) {
		for (int i = 0; i < 32; i++)
			StaticBuffer[i] = temp[i];
		DynamicBuffer = new int[vector_size - 32]; // more than 32 we need new memory space
		for (int i = 0; i < vector_size - 32; i++)
			DynamicBuffer[i] = temp[i + 32]; //initializing
		capacity = vector_size;
	}
	else if (vector_size <= 32) {
		for (int i = 0; i < vector_size; i++) // if less than 32 no need to allocate
			StaticBuffer[i] = temp[i];
		capacity = 32;
	}
	size = vector_size;
}
SmallVector::SmallVector(const SmallVector &object_in) {
	size = object_in.size;
	if (object_in.size <= 32) {
		for (int i = 0; i < size; i++)
			StaticBuffer[i] = object_in.StaticBuffer[i]; //no need for allocation static array is enough
		capacity = 32;
	}
	else if (object_in.size > 32) {
		for (int i = 0; i < 32; i++)
			StaticBuffer[i] = object_in.StaticBuffer[i]; //first 32 copied
		DynamicBuffer = new int[object_in.size - 32]; // for rest of the data requires new memory space
		for (int i = 0; i < object_in.size - 32; i++)
			DynamicBuffer[i] = object_in.DynamicBuffer[i];
		capacity = object_in.size;
	}
}

SmallVector::~SmallVector() {
delete[] DynamicBuffer;
}

int SmallVector::pop_back() {
	int result;
	if (size <= 32) {
		result = StaticBuffer[size - 1];//last element
		size--; //size is updated
	}
	else if (size == 33) {
		result = DynamicBuffer[0]; // only one element in DynamicBuffer
		delete[] DynamicBuffer; //no need for extra memory capacity is enough for our static array
		size--;  //size is updated
		capacity--; //capacity is 32 again
	}
	else if (size > 33) {
		result = DynamicBuffer[size - 33]; //last element is in the DynamicBuffer
		int *temp;
		temp = new int[size - 32];
		for (int i = 0; i < size - 32; i++)
			temp[i] = DynamicBuffer[i];
		int *ptr = DynamicBuffer; //to hold address of dynamic memory
		delete[] DynamicBuffer;
		DynamicBuffer = new int[size - 33]; //reallocated with the new size
		for (int i = 0; i < size - 33; i++)
			DynamicBuffer[i] = temp[i];
		delete[] temp;
		DynamicBuffer = ptr;
		size--; //size is updated
		capacity--; //capacity is updated
	}
	return result;
}

void SmallVector::push_back(int new_last) {
	if (size < 32) {
		StaticBuffer[size] = new_last; //adding last of static
		size++;
	}
	if (size == 32) {
		DynamicBuffer = new int[1]; //static is full first allocated space is filled with new_last
		DynamicBuffer[0] = new_last;
		size++;
		capacity++;
	}
	if (size > 32) { // we need to adjust allocated space
		int *temp;
		temp = new int[size - 31];
		for (int i = 0; i < size - 32; i++)
			temp[i] = DynamicBuffer[i];
		temp[size - 32] = new_last;
		int *ptr = DynamicBuffer; //holding address of memory space
		delete[] DynamicBuffer; //free memory
		DynamicBuffer = new int[size - 31]; //to adjust in here
		for (int i = 0; i < size - 31; i++)
			DynamicBuffer[i] = temp[i];
		delete[] temp;
		DynamicBuffer = ptr;
		size++;
		capacity++;
	}
}
void SmallVector::push_back(int new_lasts[], int new_size) {
	if (size + new_size <= 32) { //if less than 32 no need to search for dynamic
		for (int i = 0; i < new_size; i++)
			StaticBuffer[size + i] = new_lasts[i]; //pushing array to back 
		size = size + new_size;
	}
	else if (size + new_size > 32) {
		if (size > 32) { //we need to 
			int *temp;
			temp = new int[size + new_size - 32];
			for (int i = 0; i < size - 32; i++)
				temp[i] = DynamicBuffer[i];
			for (int i = 0; i < new_size; i++)
				temp[size - 32 + i] = new_lasts[i];
			int *ptr = DynamicBuffer;  //holding address of memory space
			delete[] DynamicBuffer; // free memory
			DynamicBuffer = new int[size + new_size - 32]; //to adjust in here
			for (int i = 0; i < size - 32; i++)
				DynamicBuffer[i] = temp[i];
			delete[] temp;
			DynamicBuffer = ptr;
		}
		if (size <= 32) {
			DynamicBuffer = new int[size + new_size - 32]; // new memory space
			for (int i = 0; i < 32 - size; i++) // because static part is now full
				StaticBuffer[size + i] = new_lasts[i];
			for (int i = 0; i < size + new_size - 32; i++)
				DynamicBuffer[i] = new_lasts[32 - size + i];
		}
		size = size + new_size;
		capacity = size + new_size;
	}
}

SmallVector SmallVector::reverse() {
	int *temp = new int[size]; //allocation
	if (size <= 32) {
		for (int i = 0; i < size; i++)
			temp[i] = StaticBuffer[size - 1 - i]; //initializing reverse of object to new allocated space
		//SmallVector reversed(temp,size);
	}
	if (size > 32) {
		for (int i = 0; i < size - 32; i++)
			temp[i] = DynamicBuffer[size - 33 - i]; // copying allocated memory
		for (int i = 0; i < 32; i++)
			temp[i + size - 32] = StaticBuffer[31 - i];
		//SmallVector reversed(temp,size);
	}
	SmallVector reversed(temp, size);
	delete[] temp; //free memory
	return reversed;
}

SmallVector SmallVector::operator+(const SmallVector& a) const {
	int *temp = new int[size + a.size]; //new array to help concatenate object
	int i;
	if (size <= 32 && a.size <= 32) { //first condition both just static
		for (i = 0; i<size; i++)
			temp[i] = StaticBuffer[i];
		for (i = 0; i < a.size; i++)
			temp[i + size] = a.StaticBuffer[i];
	}
	else if (size <= 32 && a.size > 32) { //second condition one static and other has allocated memory too
		for (i = 0; i<size; i++)
			temp[i] = StaticBuffer[i];
		for (i = 0; i<32; i++)
			temp[i + size] = a.StaticBuffer[i];
		for (i = 0; i< a.size - 32; i++)
			temp[size + 32 + i] = a.DynamicBuffer[i]; //copying allocated memory space
	}
	else if (size > 32 && a.size <= 32) { //second condition one static and other has allocated memory too 
		for (i = 0; i<32; i++)
			temp[i] = StaticBuffer[i];
		for (i = 0; i<size - 32; i++)
			temp[i + 32] = DynamicBuffer[i];
		for (i = 0; i<a.size; i++)
			temp[size + i] = a.StaticBuffer[i];
	}
	else if (size > 32 && a.size > 32) { //final condition both has allocated space 
		for (i = 0; i<32; i++)
			temp[i] = StaticBuffer[i];
		for (i = 0; i<size - 32; i++)
			temp[i + 32] = DynamicBuffer[i]; //dyanmic part copied
		for (i = 0; i<32; i++)
			temp[size + i] = a.StaticBuffer[i]; //statics copied
		for (i = 0; i<a.size - 32; i++)
			temp[size + 32 + i] = a.DynamicBuffer[i]; //dynamic part copied
	}
	int new_size = size + a.size;
	SmallVector added(temp, new_size);
	delete[] temp;
	return added;
}

const SmallVector& SmallVector::operator=(const SmallVector &object) {
	for (int i = 0; i < 32; i++)
		StaticBuffer[i] = 0; // deleting static array 
	if (size > 32)
		delete[] DynamicBuffer; // free allocated data because now we need more
	if (object.size <= 32) {
		for (int i = 0; i < object.size; i++)
			StaticBuffer[i] = object.StaticBuffer[i]; // copying static
	}
	if (object.size > 32) {
		for (int i = 0; i < 32; i++)
			StaticBuffer[i] = object.StaticBuffer[i]; //copying static
		DynamicBuffer = new int[object.size - 32]; //allocate new memory
		for (int i = 0; i < object.size - 32; i++)
			DynamicBuffer[i] = object.DynamicBuffer[i]; // copying new mmory space
	}
	size = object.size;
	capacity = object.capacity;
	return *this;
}

int & SmallVector::operator[](int x) {
	if (x >= 0) {
		if (size <= 32)
			return StaticBuffer[x]; // less than 32 means just static
		if (size > 32) {
			if (x > 31)
				return DynamicBuffer[x - 32]; // accesing allocated memory
			else return StaticBuffer[x];
		}
	}
	if (x < 0) {
		if (size < 32)
			return StaticBuffer[x + size]; //reverse of static array
		if (size > 32) {
			if (abs(x) - 1 <= size - 32)
				return StaticBuffer[x + size]; // reverese of dynamic memory
			else
				return DynamicBuffer[x + size - 32];
		}
	}
}

int SmallVector::operator[](int x) const {
	if (x >= 0) {
		if (size <= 32)
			return StaticBuffer[x];
		if (size > 32) {
			if (x > 31)
				return DynamicBuffer[x - 32];
			else return StaticBuffer[x];
		}
	}
	if (x < 0) {
		if (size < 32)
			return StaticBuffer[x + size];
		if (size > 32) {
			if (abs(x) - 1 <= size - 32)
				return StaticBuffer[x + size];
			else
				return DynamicBuffer[x + size - 32];
		}
	}
}

SmallVector SmallVector::operator*(int replicate) {
	int *temp = new int[size*replicate]; //new array for replicating old one 
	if (size * replicate < 32) {
		int i, j;
		for (i = 0; i < replicate; i++) {
			for (j = 0; j < size; j++)
				temp[i*size + j] = StaticBuffer[j]; //writing object datas as replicate times
		}
	}
	else if (size * replicate > 32) {
		int i, j;
		if (size < 32) {
			for (i = 0; i < replicate; i++) {
				for (j = 0; j < size; j++)
					temp[i*size + j] = StaticBuffer[j]; // just static array needed
			}
		}
		else if (size > 32) {
			int i, j;
			for (i = 0; i<32; i++)
				temp[i] = StaticBuffer[i];
			for (j = 0; j < size - 32; j++)
				temp[j + 32] = DynamicBuffer[j]; // taking allocated memory
			for (i = 1; i < replicate; i++) {
				for (j = 0; j < size; j++)
					temp[i*size + j] = temp[j]; //replicating
			}
		}
	}
	size = size * replicate;
	capacity = size *replicate;
	SmallVector replicated(temp, size);
	delete[] temp; //free the memory
	return replicated;
}

int SmallVector::getSize() const
{
	return size;
}
