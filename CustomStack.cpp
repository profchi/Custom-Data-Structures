
/*
Implementation of a Generic Stack class with pointers 

Author: Chinedu Isaiah
*/

//header files
#include "stdafx.h"
#include <iostream>
#include <cstdlib>

using namespace std;


// class declaration with template 
template<class T>
class Stack {

	// Represents an element in the stack
	struct Element {
		T value;						// value stored
		struct Element *nextElement;	// pointer to the next element
	};

	public:
		Stack(){
			count = 0;
		}

		//Adds element to the top of the stack
		void Push( T element) {
			
			//set the element to the top element if stack was empty
			if (count == 0) {
				topElement = (struct Element*) malloc(sizeof(struct Element));
				topElement->value = element;
			}

			//Otherwise set the new element to the topelement and point to the previous top element
			else {
				struct Element *elementToAdd = (struct Element*) malloc(sizeof(struct Element));
				elementToAdd->value = element;
				elementToAdd->nextElement = topElement;
				topElement = elementToAdd;
			}
			++count;
		}
		//Removes and returns the value of the element at the top of the Stack
		T Pop() {
			T result;					// value returned
			
			//Returns null if stack is empty
			// otherwise set the result to the top element
			// dealloacate memory used for the remove element
			if (count == 0)
				return NULL;			
			else {
				result = topElement->value;
				if (count == 1)
					free(topElement);
				else {
					struct Element *top = topElement;
					topElement = top->nextElement;
					free(top);
				}
				--count;
			}
			return result;
		}

		// Returns the value of the element at the top of the Stack 
		T Peek() {
			return topElement->value;
		}

		//Returns a pointer to an array of all the elements on the stack
		//The first array element would be the alue of the element on top of the stack
		T* ToArray() {
			if (count == 0)
				return NULL;
			T *result = new T [count];
			struct Element *currentElement = topElement;

			//set the values in the array to that of the elements on the stack
			for (int i = 0; i < count; ++i) {
				result[i] = currentElement->value;
				currentElement = currentElement->nextElement;
			}
			return result;
		}

		//Returns the number of element on the Stack
		int Size() {
			return count;
		}

		// Returns true if Stack is empty, otherwise false
		bool IsEmpty() {
			if (count == 0)
				return true;
			else
				return false;
		}
	private:
		int count;
		struct Element *topElement;
};

int main()
{
	Stack<int> Test;

	// Adding elemets to the stack
	Test.Push(5);
	Test.Push(4);
	Test.Push(35);
	Test.Push(6);
	Test.Push(7);



	Test.Push(1);
	Test.Push(2);
	Test.Push(3);
	Test.Push(4);

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

