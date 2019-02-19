/*
Implementation of a Generic Queue class with pointers

Author: Chinedu Isaiah
*/

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>

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


int main(int argc, char* argv[])
{

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}

TEST(Queue, PushPopPeek) {
	Queue<int> myQueue;

	myQueue.Push(5);
	myQueue.Push(6);
	myQueue.Push(7);
	myQueue.Push(8);

	EXPECT_EQ(myQueue.Peek(), 5);
	EXPECT_EQ(myQueue.Pop(), 5);
	EXPECT_EQ(myQueue.Pop(), 6);


}

TEST(Queue, IsEmpty) {
	Queue<int> myQueue;


	EXPECT_TRUE(myQueue.IsEmpty());

	myQueue.Push(1);
	myQueue.Push(2);


	EXPECT_FALSE(myQueue.IsEmpty());

	myQueue.Pop();
	myQueue.Pop();

	EXPECT_TRUE(myQueue.IsEmpty());
}

TEST(Queue, Size) {
	Queue<int> myQueue;

	EXPECT_EQ(myQueue.Size(), 0);

	myQueue.Push(5);
	myQueue.Push(6);
	myQueue.Push(7);
	myQueue.Push(8);

	EXPECT_EQ(myQueue.Size(), 4);

	myQueue.Pop();
	myQueue.Pop();
	myQueue.Pop();
	myQueue.Pop();

	EXPECT_EQ(myQueue.Size(), 0);

	myQueue.Push(5);
	myQueue.Push(6);


	EXPECT_EQ(myQueue.Size(), 2);
}

TEST(Queue, ToArray) {
	Queue<int> myQueue;
	int *myArray;

	myQueue.Push(5);
	myQueue.Push(6);
	myQueue.Push(7);
	myQueue.Push(8);

	myArray = myQueue.ToArray();

	EXPECT_EQ(myArray[0], 5);
	EXPECT_EQ(myArray[3], 8);

	free(myArray);

	myQueue.Pop();

	myArray = myQueue.ToArray();
	EXPECT_EQ(myArray[0], 6);
	EXPECT_EQ(myArray[2], 8);

	free(myArray);

}

