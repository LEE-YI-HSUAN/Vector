#include "Vector.h" // include definition of class vector 
#include<iostream>
using namespace std;


// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
	myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector(const size_type count)
{
	//by self
	myFirst = new value_type[count];
	myEnd = myFirst + count;
	myLast = myEnd;
	//將element全部預設為0
	for (unsigned int i = 0; i < count; i++)
		myFirst[i] = 0;
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector(const vector& right)
{
	//by self
	//right中的element數量
	int size = right.myLast - right.myFirst;
	int* temp = new int[size];

	myFirst = temp;
	myEnd = temp + size;
	myLast = temp + size;

	//將right的值copy給myFirst
	for (int i = 0; i < size; i++)
		temp[i] = *(right.myFirst + i);
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
	//不是空的
	if (myFirst != nullptr)
		delete[] myFirst;
}

// Adds a new element at the end of the vector, after its current last element.
// The content of val is copied to the new element.
// This effectively increases the vector size by one,
// which causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
void vector::push_back(const value_type& val)
{
	size_type originalSize = size();
	resize(originalSize + 1);
	myFirst[originalSize] = val;
	//cout << myFirst[originalSize] << endl;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign(const vector& right)
{
	//by self
	if (this != &right) // avoid self-assignment
	{
		int right_Capacity = right.myEnd - right.myFirst;
		int right_Size = right.myLast - right.myFirst;

		//vector為空
		if (myFirst == nullptr) {
			int* temp = new int[right_Size];

			myFirst = temp;
			myEnd = myFirst + right_Size;
			myLast = myFirst + right_Size;

			for (int i = 0; i < right_Size; i++)
				temp[i] = *(right.myFirst + i);
		}
		else {
			int Capacity = myEnd - myFirst;
			int Size = myLast - myFirst;

			//新需要的空間(right_Size)小於等於原有空間(Capacity)的話，capacity照舊，size更改為新空間大小。
			if (right_Size <= Capacity) {
				myLast = myFirst + right_Size;

				for (int i = 0; i < right_Size; i++)
					*(myFirst + i) = *(right.myFirst + i);
			}
			else {
				//就是規則
				int newCapacity = Capacity * 1.5;

				//newCapacity < 新需要空間的話，capacity、size更改為新空間大小。
				if (newCapacity < right_Size) {
					int* temp = new int[right_Size];

					myFirst = temp;
					myEnd = temp + right_Size;
					myLast = temp + right_Size;

					for (int i = 0; i < right_Size; i++)
						*(myFirst + i) = *(right.myFirst + i);
				}
				//newCapacity >= 新需要空間的話，capacity更改為原空間大小*1.5、size更改為新空間大小。
				else {
					int* temp = new int[newCapacity];

					myFirst = temp;
					myLast = temp + right_Size;
					myEnd = temp + newCapacity;

					for (int i = 0; i < right_Size; i++)
						temp[i] = *(right.myFirst + i);
				}
			}
		}
	}

	return *this; // enables x = y = z, for example
}

// Resizes the vector so that it contains newSize elements.
// If newSize is smaller than the current vector size,
// the content is reduced to its first newSize elements, removing those beyond.
// If newSize is greater than the current vector size,
// the content is expanded by inserting at the end
// as many elements as needed to reach a size of newSize.
// The new elements are initialized as 0.
// If newSize is also greater than the current vector capacity,
// an automatic reallocation of the allocated storage space takes place.
void vector::resize(const size_type newSize)
{
	//新需要的空間(newSize) <= 原有空間(capacity())的話，capacity照舊，size更改為新空間大小。
	if (newSize <= capacity()) {
		myLast = myFirst + newSize;
		for (int a = newSize; a < capacity(); a++)
			*(myFirst + a) = 0;
	}
	else {
		int newCapacity = capacity() * 1.5;

		//newCapacity <= 新需要空間的話，capacity、size更改為新空間大小
		if (newCapacity <= newSize) {
			int* temp = new int[newSize];
			//先將element全設成0
			for (int i = 0; i < newSize; i++)
				temp[i] = 0;

			myEnd = temp + newSize;
			//原本的值要保留
			for (int i = 0; i < size(); i++)
				temp[i] = *(myFirst + i);

			myFirst = temp;
			myLast = myFirst + newSize;
		}
		//newCapacity > 新需要空間的話，capacity更改為原空間大小*1.5、size更改為新空間大小。
		else {
			int* temp = new int[newCapacity];
			//先將element全設成0
			for (int i = 0; i < newCapacity; i++)
				temp[i] = 0;

			myEnd = temp + newCapacity;
			//原本的值要保留
			for (int i = 0; i < size(); i++)
				temp[i] = *(myFirst + i);

			myFirst = temp;
			myLast = myFirst + newSize;
		}
	}
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
	if (size() > 0)
		--myLast;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
	myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::pointer vector::begin()
{
	return myFirst;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
	return (myLast - myFirst);
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
	return (myEnd - myFirst);
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::element(const size_type pos)
{
	//cout << myFirst[pos] << endl;
	return myFirst[pos];
}