#include <iostream>

// this two laibraries are for vilidation 
#include <limits>
#include <sstream>
using namespace std;


template <class T>
class Queue {
private:
    T* arr;    
    int maxSize; // Maximum size of the queue
    int front; 
    int rear;  
    int currentSize; // Current size of the queue

public:

    Queue(int s) {
        maxSize = s;
        arr = new T[maxSize];
        front = -1;
        rear = -1;
        currentSize = 0;
    }

    bool isFull() {
        return currentSize == maxSize;
    }

   
    bool isEmpty() {
        return currentSize == 0;
    }

    void enQueue(T value) {
        if (isFull()) {
            cout << "\t*** Queue is full ***" << endl;
            return;
        }

        if (isEmpty()) { // If queue is empty initlize it f, r with 0
            front = 0;
            rear = 0;
        }
        else { // increment rear and add value
            rear = (rear + 1) % maxSize;
        }

        //add value to the queue
        arr[rear] = value;
        currentSize++;
        cout << "\t*** " << value << " enqueued successfully ***" << endl;
    }

   
    void deQueue() {
        if (isEmpty()) {
            cout << "\t*** Queue is empty, cannot dequeue ***" << endl;
            return;
        }

        cout << "\t*** " << arr[front] << " dequeued successfully ***" << endl;

        if (front == rear) { // If only one element is left, reset the queue
            front = -1;
            rear = -1;
        }
        else { // increment front
            front = (front + 1) % maxSize;
        }

        currentSize--;
    }

    // Peek Function
    void peek() {
        if (isEmpty()) {
            cout << "\t*** Queue is empty, nothing to peek ***" << endl;
        }
        else {
            cout << "\t*** Front element: " << arr[front] << " ***" << endl;
        }
    }

    // Display current size
    void displaySize() {
        cout << "\t*** Current size of the queue: " << currentSize << " ***" << endl;
    }

   
    ~Queue() {
        delete[] arr;
    }

    // Input validation function
    int getValidatedInput() {
        string input;
        int result;

        while (true) {
            getline(cin, input); 

            // Check if input is empty or just whitespace
            if (input.empty() || input.find_first_not_of(" \t\n\r") == string::npos) {
                cout << "\n\tEmpty input. Please enter a valid number: ";
                continue;
            }
            //it convert strings to input
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


void displayMenu() {
    cout << "\n\t\t\t*** Queue Operations Menu ***" << endl;
    cout << "\t1. Enqueue an element" << endl;
    cout << "\t2. Dequeue an element" << endl;
    cout << "\t3. Peek at the front element" << endl;
    cout << "\t4. Display the size of the queue" << endl;
    cout << "\t5. Exit" << endl;
    cout << "\n\tEnter your choice: ";
}

int main() {
    int queueSize;

    
    cout << "\n\t\t\t*** Welcome to the Queue Program ***" << endl;
    cout << "\n\tEnter the size of the queue: ";

    Queue<int> q(0);  // we creat an object of q with 0 size for deafult
   
    queueSize = q.getValidatedInput(); // get valid input
    q = Queue<int>(queueSize); // initlizing queue with user defined size

    int choice;
    do {
        displayMenu();
        choice = q.getValidatedInput(); // get validated input 

        switch (choice) {
        case 1: { 
            int value;
            cout << "\n\tEnter an integer to enqueue: ";
            value = q.getValidatedInput(); 
            q.enQueue(value);
            break;
        }
        case 2: 
            q.deQueue();
            break;
        case 3: 
            q.peek();
            break;
        case 4: 
            q.displaySize();
            system("cls");
            break;
        case 5: 
            cout << "\n\t*** Exiting the program... ***" << endl;
            break;
        default: 
            cout << "\n\tInvalid choice, please try again." << endl;
        }
    } while (choice != 5); 

    return 0;
}
