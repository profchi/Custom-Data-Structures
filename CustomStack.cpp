
/*
Implementation of a Generic Stack class with pointers 

Author: Chinedu Isaiah
*/

//header files
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>

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

int main(int argc, char* argv[])
{
	
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}

TEST(Stack, PushPopPeek) {
	Stack<int> myStack;
	
	myStack.Push(5); 
	myStack.Push(6);
	myStack.Push(7);
	myStack.Push(8);

	EXPECT_EQ(myStack.Peek(), 8);
	EXPECT_EQ(myStack.Pop(), 8);
	EXPECT_EQ(myStack.Pop(), 7);


}

TEST(Stack, IsEmpty) {
	Stack<int> myStack;
	
	
	EXPECT_TRUE(myStack.IsEmpty());
	
	myStack.Push(1);
	myStack.Push(2);


	EXPECT_FALSE(myStack.IsEmpty());

	myStack.Pop();
	myStack.Pop();

	EXPECT_TRUE(myStack.IsEmpty());
}

TEST(Stack, Size) {
	Stack<int> myStack;

	EXPECT_EQ(myStack.Size(), 0);

	myStack.Push(5);
	myStack.Push(6);
	myStack.Push(7);
	myStack.Push(8);

	EXPECT_EQ(myStack.Size(), 4);

	myStack.Pop();
	myStack.Pop();
	myStack.Pop();
	myStack.Pop();

	EXPECT_EQ(myStack.Size(), 0);

	myStack.Push(5);
	myStack.Push(6);


	EXPECT_EQ(myStack.Size(), 2);
}

TEST(Stack, ToArray) {
	Stack<int> myStack;
	int *myArray;

	myStack.Push(5);
	myStack.Push(6);
	myStack.Push(7);
	myStack.Push(8);

	myArray = myStack.ToArray();

	EXPECT_EQ(myArray[0], 8);
	EXPECT_EQ(myArray[3], 5);

	free(myArray);
	
	myStack.Pop();

	myArray = myStack.ToArray();
	EXPECT_EQ(myArray[0], 7);
	EXPECT_EQ(myArray[2], 5);

}

