#include <iostream>

// this two libraries are added for vilidation

#include <limits> // for cleaning input buffer (store) data for temporary time)
#include <sstream> // for conversion of strings to integers

using namespace std;

class CircularQueue {
private:
    int* queue;    
    int front, rear;
    int capacity;  
    int size;      

public:

    CircularQueue(int MaximumCapacity) {
        capacity = MaximumCapacity;
        queue = new int[capacity];
        front = -1;
        rear = -1;
        size = 0;
    }

    bool isFull() {
        return size == capacity;
    }

    bool isEmpty() {
        return size == 0;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "\n\tQUEUE IS FULL. CANNOT ENQUEUE " << value << ".\n";
            return;
        }
        if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % capacity; // for positioning the rear index  eg (2+1) % 4 = 3 
        queue[rear] = value;
        size++;
        cout << "\n\tENQUEUED " << value << " SUCCESSFULLY.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "\n\tQUEUE IS EMPTY. NOTHING TO DEQUEUE.\n";
            return;
        }
        cout << "\n\tDEQUEUED " << queue[front] << " SUCCESSFULLY.\n";
        front = (front + 1) % capacity; // for allocating the front index 
        size--;
        if (isEmpty()) {
            front = -1;
            rear = -1;
        }
    }

    int getFront() {
        if (isEmpty()) {
            cout << "\n\tQUEUE IS EMPTY.\n";
            return -1;
        }
        return queue[front];
    }

    int getRear() {
        if (isEmpty()) {
            cout << "\n\tQUEUE IS EMPTY.\n";
            return -1;
        }
        return queue[rear];
    }

    ~CircularQueue() {
        delete[] queue;
    }

    // Function to get validated input from the user
    int getValidatedInput() {
        string input;
        int result;

        while (true) {
            getline(cin, input);

            if (input.empty() || input.find_first_not_of(" \t\n\r") == string::npos) { // Check if input is empty or only whitespace
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

void DisplayMenu() {
    cout << "\n\t\t*** DYNAMIC IMPLEMENTATION OF QUEUE ***\n\n";
    cout << "\t1. Enqueue\n";
    cout << "\t2. Dequeue\n";
    cout << "\t3. Peek (Front Element)\n";
    cout << "\t4. Get Queue rear\n";
    cout << "\t5. EXIT\n";
    cout << "\n\tEnter your choice: ";
}

int main() {
    int capacity;
    cout << "\n\t\t*** DYNAMIC IMPLEMENTATION OF QUEUE ***\n\n";
    cout << "\tEnter the capacity of the circular queue: ";

    CircularQueue q(0);  // Declare the queue with default capacity
    string input;
    while (true) {
        getline(cin, input);

        if (input.empty() || input.find_first_not_of(" \t\n\r") == string::npos) {
            cout << "\n\tPlease enter a valid positive integer for the capacity: ";
            continue;
        }

        stringstream ss(input);
        if (ss >> capacity && capacity > 0) {
            q = CircularQueue(capacity);  // Initialize the queue after getting valid input
            break;
        }
        else {
            cout << "\n\tPlease enter a valid positive integer for the capacity: ";
        }
    }

    system("cls"); // This is for clearing the screen; you can remove it if not required

    int choice, value;
    do {
        DisplayMenu();
        choice = q.getValidatedInput(); // Validate the choice

        switch (choice) {
        case 1:
            cout << "\n\tEnter value to enqueue: ";
            value = q.getValidatedInput(); // Validate the value for enqueue
            q.enqueue(value);
            break;
        case 2:
            q.dequeue();
            break;
        case 3:
            cout << "\n\tFRONT ELEMENT IS: " << q.getFront() << endl;
            break;
        case 4:
            cout << "\n\tREAR ELEMENT IS: " << q.getRear() << endl;
            break;
        case 5:
            cout << "\n\tEXITING PROGRAM.\n";
            break;
        default:
            cout << "\n\tINVALID CHOICE. PLEASE TRY AGAIN.\n";
        }
    } while (choice != 5);

    return 0;
}
