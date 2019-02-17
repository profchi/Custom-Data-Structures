/*
Implementation of a Generic Queue class with pointers

Author: Chinedu Isaiah
*/

#include "stdafx.h"
#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Queue {

	// Represents an element in the queue
	struct Element {
		T value;						// value stored
		struct Element *nextElement;	// pointer to the next element
	};

	public:
		Queue() {
			count = 0;
		}

		//Adds element to the top of the queue
		void Push(T element) {

			//set the element to the first and last element if queue was empty
			if (count == 0) {
				firstElement = (struct Element*) malloc(sizeof(struct Element));
				firstElement->value = element;
				lastElement = firstElement;
			}

			//Otherwise set the new element to the last element and point to previous last element to the added element
			else {
				struct Element *elementToAdd = (struct Element*) malloc(sizeof(struct Element));
				elementToAdd->value = element;
				lastElement->nextElement = elementToAdd;
				lastElement = elementToAdd;
			}
			++count;
		}
		//Removes and returns the value of the element at the top of the queue
		T Pop() {
			T result;					// value returned

			//Returns null if queue is empty
			// otherwise set the result to the first element
			// dealloacate memory used for the remove element
			if (count == 0)
				return NULL;
			else {
				result = firstElement->value;
				if (count == 1)
					free(firstElement);
				else {
					struct Element *top = firstElement;
					firstElement = top->nextElement;
					free(top);
				}
				--count;
			}
			return result;
		}

		// Returns the value of the element at the top of the queue 
		T Peek() {
			return firstElement->value;
		}

		//Returns a pointer to an array of all the elements on the queue
		//The first array element would be the value of the element first on the queue
		T* ToArray() {
			if (count == 0)
				return NULL;
			T *result = new T[count];
			struct Element *currentElement = firstElement;

			//set the values in the array to that of the elements on the queue
			for (int i = 0; i < count; ++i) {
				result[i] = currentElement->value;
				currentElement = currentElement->nextElement;
			}
			return result;
		}

		//Returns the number of element on the queue
		int Size() {
			return count;
		}

		// Returns true if queue is empty, otherwise false
		bool IsEmpty() {
			if (count == 0)
				return true;
			else
				return false;
		}
	private:
		int count;
		struct Element *firstElement;
		struct Element *lastElement;
};


int main()
{
	Queue<int> Test;
	
	//Adding elements to the queue
	Test.Push(1);
	Test.Push(2);
	Test.Push(3);
	Test.Push(4);
	Test.Push(5);



	Test.Push(6);
	Test.Push(7);
	Test.Push(8);
	Test.Push(9);

	int *myArray = Test.ToArray();

	for (int i = 0; i < Test.Size(); ++i) {
		cout << myArray[i] << endl;
	}

	cout << "" << endl;
	cout << "" << endl;


	cout << Test.Peek() << endl;	//prints the first element without deleting it
	cout << Test.Pop() << endl;		//prints the first element entered and deletes it
	cout << Test.Pop() << endl;		//prints the second element entered and deletes it
	cout << Test.Pop() << endl;		//prints the third element entered an deletes it

	cout << Test.Size() << endl;	//prints the current size

	return 0;
}

