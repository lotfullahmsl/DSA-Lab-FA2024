#include <iostream>
#include <string>
// these two laibraries are for vilidation
#include <limits> // for cleaning input buffer this (store) data or input for temporray time
#include <sstream> // for conversion of strings to iintegers
using namespace std;

class Queue {
private:
    int* arr;       // Dynamic memory allocation
    int capacity;   // total capcity
    int front;      
    int rear;       
    int size;       // Index Location

public:
    // Constructor that takes capacity from the main function
    Queue(int cap) {
        capacity = cap;
        arr = new int[capacity]; 
        front = -1;
        rear = -1;
        size = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    
    void enqueue(int value) {
        if (size == capacity) {
            cout << "\tQueue is full, cannot enqueue" << endl;
            return;
        }
        rear++;             
        arr[rear] = value;  
        size++;            
        cout << "\tEnqueued " << value << " successfully." << endl;
    }

   
    void dequeue() {
        if (isEmpty()) {
            cout << "\tQueue is empty, cannot dequeue" << endl;
            return;
        }

        // Shift elements to the left after dequeue
        for (int i = 0; i < rear; i++) {
            arr[i] = arr[i + 1];  // Move elements to the left
        }

        rear--;  
        size--;  
        cout << "\tDequeued successfully." << endl;
    }

   
    bool isEmpty() {
        return size == 0;
    }

    
    int peek() {
        if (!isEmpty())
            return arr[front]; //top of element
        else
            return -1;
    }

    
    int getSize() {
        return size; //return the size of what we added before as size++
    }

    // Function that vilidate input take helped from google 
    int getValidatedInput() {
        string input;
        int result;

        while (true) {
            getline(cin, input); 

            if (input.empty() || input.find_first_not_of(" \t\n\r") == string::npos) { //This checks if the input contains only spaces, tabs, or newline characters (whitespace).
                cout << "\n\tEmpty input. Please enter a valid number: ";
                continue;
            }
            stringstream ss(input);
                        if (ss >> result) {
                            return result; // return an valid int
                        }
                        else {
                            cout << "\n\tInvalid input. Please enter a valid number: ";
                        }
            
        }
    }
};

int main() {
    cout << "\n\n\n\t\t\t*** Dynamic Implementation of Queue ***";
    int capacity;
    cout << "\n\n\tEnter the capacity of the queue: ";
    while (true) {
        string input;
        getline(cin, input); 

        
        if (input.empty() || input.find_first_not_of(" \t\n\r") == string::npos) { //This checks if the input contains only spaces, tabs, or newline characters (whitespace).
            cout << "\tPlease enter a valid positive integer for the capacity: ";
            continue;
        }

        
        stringstream ss(input);
        if (ss >> capacity && capacity > 0) {
            break; // If the input is a valid positive integer, break out of the loop
        }
        else {
            cout << "\tPlease enter a valid positive integer for the capacity: ";
        }
    }

    Queue q(capacity);

    int choice;
    do {
        cout << "\n\n\t1. Enqueue";
        cout << "\n\t2. Dequeue";
        cout << "\n\t3. Peek (Front Element)";
        cout << "\n\t4. Get Queue Size";
        cout << "\n\t5. Exit";
        cout << "\n\n\tEnter your choice: ";

        choice = q.getValidatedInput(); // Validate the choice

        switch (choice) {
        case 1: {
            int value;
            cout << "\n\tEnter value to enqueue: ";
            value = q.getValidatedInput(); // Validate the value for enqueue
            q.enqueue(value);
            break;
        }
        case 2:
            q.dequeue();
            break;
        case 3:
            if (q.isEmpty()) {
                cout << "\n\tQueue is empty." << endl;
            }
            else {
                cout << "\n\tFront element is: " << q.peek() << endl;
            }
            break;
        case 4:
            cout << "\n\tCurrent size of the queue: " << q.getSize() << endl;
            break;
        case 5:
            cout << "\n\tExiting program." << endl;
            break;
        default:
            cout << "\n\tInvalid choice, please try again!" << endl;
        }
    } while (choice != 5);

    return 0;
}
