/*
This program implements and compares the performance of two data structures: a Stack and a Queue, both using doubly-linked lists. It measures
the time taken to perform insert and delete operations on these data structures for different numbers of elements (100, 1000, and 10000). The 
results are displayed in a formatted table, allowing for easy comparison of the performance characteristics of Stack and Queue operations.
*/ 

#include <iostream> // This is a header file library that lets us work with input and output objects, such as cout (used in line 12).
#include <chrono> // This is a header file library that lets us work with time, measuring time intervals.
#include <random> // This is a header file library that lets us work with random numbers.
#include <iomanip> // This is a header file library that lets us work with parametric manipulators.
#include <vector> // This is a header file library that lets us work with arrays and vectors.
#include <string> // This is a header file library that lets us work with strings.

using namespace std; // using standard namespace to avoid writing std:: before standard library functions
using namespace chrono; // using chrono namespace to avoid writing chrono:: before time measurement functions

class Node { // This is a class that defines a node.
public: // This is a public access specifier.
	int data; // This is a variable that stores the data.
	Node* next; // This is a pointer that points to the next node.
	Node* prev; // This is a pointer that points to the previous node.

	Node(int value) : data(value), next(nullptr), prev(nullptr) {} // This is a constructor that initializes the data with the value, and the next and previous pointers with nullptr.
};

class Stack { // This is a class that defines a stack.
private: // This is a private access specifier.
	Node* head; // This is a pointer that points to the head of the stack.

public: // This is a public access specifier.
	Stack() : head(nullptr) {} // This is a constructor that initializes the head with nullptr.  nullptr is a constant that is defined in the C++ standard library.

	void insert(int data) { // This is a function that inserts a node with the data at the head of the stack.
		Node* newNode = new Node(data); // This is a pointer that points to a new node with the data.
		if (head == nullptr) { // This is a condition that checks if the head is nullptr.
			head = newNode; // This assigns the head to the new node.
        }
		else { // This is a condition that runs if the head is not nullptr.
			newNode->prev = head; // This assigns the previous pointer of the new node to the head.
			head->next = newNode; // This assigns the next pointer of the head to the new node.
			head = newNode; // This assigns the head to the new node.
        }
    }

	void remove(int data) { // This is a function that removes a node with the data from the stack.
		Node* current = head; // This is a pointer that points to the head.
		while (current) { // This is a loop that runs while the current pointer is not nullptr.
			if (current->data == data) { // This is a condition that checks if the data of the current node is equal to the data.
				if (current->prev) { // This is a condition that checks if the previous pointer of the current node is not nullptr.
					current->prev->next = current->next; // This assigns the next pointer of the previous node of the current node to the next pointer of the current node.
                }
				if (current->next) { // This is a condition that checks if the next pointer of the current node is not nullptr.
					current->next->prev = current->prev; // This assigns the previous pointer of the next node of the current node to the previous pointer of the current node.
                }
				if (current == head) { // This is a condition that checks if the current node is the head.
					head = current->prev; // This assigns the head to the previous node of the current node.
                }
				delete current; // This deletes the current node.
				return; // This exits the function.
            }
			current = current->prev; // This assigns the current pointer to the previous pointer of the current pointer.
        }
    }

	void print() { // This is a function that prints the stack.
		Node* current = head; // This is a pointer that points to the head.
		cout << "Stack: "; // This prints "Stack: ".
		while (current) { // This is a loop that runs while the current pointer is not nullptr.
			cout << current->data << " -> "; // This prints the data of the current node followed by " -> ".
			current = current->prev; // This assigns the current pointer to the previous pointer of the current pointer.
        }
		cout << "nullptr" << endl; // This prints "nullptr".
    }
};

class Queue { // This is a class that defines a queue.
private: // This is a private access specifier.
	Node* head; // This is a pointer that points to the head of the queue.
	Node* tail; // This is a pointer that points to the tail of the queue.

public: // This is a public access specifier.
	Queue() : head(nullptr), tail(nullptr) {} // This is a constructor that initializes the head and tail with nullptr.

	void insert(int data) { // This is a function that inserts a node with the data at the tail of the queue.
		Node* newNode = new Node(data); // This is a pointer that points to a new node with the data.
		if (tail == nullptr) { // This is a condition that checks if the tail is nullptr.
			head = tail = newNode; // This assigns the head and tail to the new node.
        }
		else { // This is a condition that runs if the tail is not nullptr.
			newNode->prev = tail; // This assigns the previous pointer of the new node to the tail.
			tail->next = newNode; // This assigns the next pointer of the tail to the new node.
			tail = newNode; // This assigns the tail to the new node.
        }
    }

	void remove(int data) { // This is a function that removes a node with the data from the queue.
		Node* current = head; // This is a pointer that points to the head.
		while (current) { // This is a loop that runs while the current pointer is not nullptr.
			if (current->data == data) { // This is a condition that checks if the data of the current node is equal to the data.
				if (current->prev) { // This is a condition that checks if the previous pointer of the current node is not nullptr.
					current->prev->next = current->next; // This assigns the next pointer of the previous node of the current node to the next pointer of the current node.
                }
				if (current->next) { // This is a condition that checks if the next pointer of the current node is not nullptr.
					current->next->prev = current->prev;// This assigns the previous pointer of the next node of the current node to the previous pointer of the current node.
                }
				if (current == head) { // This is a condition that checks if the current node is the head.
					head = current->next; // This assigns the head to the next node of the current node.
                }
				if (current == tail) { // This is a condition that checks if the current node is the tail.
					tail = current->prev; // This assigns the tail to the previous node of the current node.
                }
				delete current; // This deletes the current node.
				return; // This exits the function.
            }
			current = current->next; // This assigns the current pointer to the next pointer of the current pointer.
        }
    }

	void print() { // This is a function that prints the queue.
		Node* current = head; // This is a pointer that points to the head.
		cout << "Queue: "; // This prints "Queue: ".
		while (current) { // This is a loop that runs while the current pointer is not nullptr.
			cout << current->data << " -> "; // This prints the data of the current node followed by " -> ".
			current = current->next; // This assigns the current pointer to the next pointer of the current pointer.
        }
		cout << "nullptr" << endl; // This prints "nullptr".
    }
};

template <typename DataStructure> // This is a template that defines a data structure.
double measureTime(DataStructure& dataStructure, const string& operation, int count) { // This is a function that measures the time taken to perform an operation on a data structure.
	random_device rd; // This is a random device that generates random numbers.
	mt19937 gen(rd()); // This is a random number generator that generates random numbers.
	uniform_int_distribution<> dis(1, 10000); // This is a uniform integer distribution that generates random numbers between 1 and 10000.

	auto start = high_resolution_clock::now(); // This is a time point that represents the start time.
	for (int i = 0; i < count; ++i) { // This is a loop that runs count times.
		if (operation == "insert") { // This is a condition that checks if the operation is insert.
			dataStructure.insert(dis(gen)); // This inserts a random number into the data structure.
        }
		else if (operation == "delete") { // This is a condition that checks if the operation is delete.
			dataStructure.remove(dis(gen)); // This removes a random number from the data structure.
        }
    }
	auto end = high_resolution_clock::now(); // This is a time point that represents the end time.

	duration<double> diff = end - start; // This is a duration that represents the difference between the end and start times.
	return diff.count(); // This returns the count of the duration.	
}

int main() { // This is the main function.
	Stack stack; // This is a stack.
	Queue queue; // This is a queue.

	vector<int> counts = { 100, 1000, 10000 }; // This is a vector that stores the counts.
	vector<string> operations = { "insert", "delete" }; // This is a vector that stores the operations.
	vector<string> dataStructures = { "Stack", "Queue" }; // This is a vector that stores the data structures.

	cout << fixed << setprecision(5); // This sets the fixed and precision flags of the cout object.
	cout << "| Operation | Data Structure | 100 items | 1000 items | 10000 items |" << endl; // This prints the table header.
	cout << "|-----------|----------------|-----------|------------|-------------|" << endl; // This prints the table header.

	for (const auto& operation : operations) { // This is a loop that iterates over the operations.
		for (const auto& ds : dataStructures) { // This is a loop that iterates over the data structures.
			cout << "| " << setw(9) << operation << " | " << setw(14) << ds << " |"; // This prints the operation and data structure.
			for (const auto& count : counts) { // This is a loop that iterates over the counts.
				double time; // This is a variable that stores the time.
				if (ds == "Stack") { // This is a condition that checks if the data structure is a stack.
					time = measureTime(stack, operation, count); // This measures the time taken to perform the operation on the stack.
                }
				else { // This is a condition that runs if the data structure is not a stack.
					time = measureTime(queue, operation, count); // This measures the time taken to perform the operation on the queue.
                }
				cout << " " << setw(9) << time << "s |"; // This prints the time.
            }
			cout << endl; // This prints a new line.
        }
    }

	return 0; // This returns 0, which means the program has run successfully.
}
