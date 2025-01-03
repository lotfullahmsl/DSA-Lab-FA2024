// implement a BST 
// we should be able to add, remove ...

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Node {
public:
    int Data;
    Node* Left;
    Node* Right;

    Node(int Val) : Data(Val), Left(nullptr), Right(nullptr) {}
};


Node* insertBST(Node* root, int val) {
    if (root == NULL) {
        return new Node(val);
    }
    if (val < root->Data) {
        root->Left = insertBST(root->Left, val);
    }
    else if (val > root->Data) {
        root->Right = insertBST(root->Right, val);
    }
    return root;
}

void Pre_Order(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->Data << "->";
    Pre_Order(root->Left);
    Pre_Order(root->Right);
}

void in_Order(Node* root) {
    if (root == NULL) {
        return;
    }
    in_Order(root->Left);
    cout << root->Data << "->";
    in_Order(root->Right);
}


void Post_Order(Node* root) {
    if (root == NULL) {
        return;
    }
    Post_Order(root->Left);
    Post_Order(root->Right);
    cout << root->Data << "->";
}


int getValidInteger(string prompt) {
    int value;
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value) {
            return value;
        }
        else {
            cout << "Invalid input! Please enter a valid integer.\n";
        }
    }
}

Node* findNode(Node* root, int value, Node*& parent) {
    while (root != nullptr && root->Data != value) {
        parent = root;
        if (value < root->Data) {
            root = root->Left;
        }
        else {
            root = root->Right;
        }
    }
    return root;
}

bool printAncestors(Node* root, int value) {
    if (root == nullptr) {
        return false;
    }
    if (root->Data == value) {
        return true;
    }
    if (printAncestors(root->Left, value) || printAncestors(root->Right, value)) {
        cout << root->Data << " ";
        return true;
    }
    return false;
}


void printSibling(Node* parent, int value) {
    if (!parent) {
        cout << "No sibling (Root node has no sibling).\n";
        return;
    }
    if (parent->Left && parent->Left->Data == value && parent->Right) {
        cout << "Sibling: " << parent->Right->Data << endl;
    }
    else if (parent->Right && parent->Right->Data == value && parent->Left) {
        cout << "Sibling: " << parent->Left->Data << endl;
    }
    else {
        cout << "No sibling.\n";
    }
}

int main() {
    Node* root = nullptr;
    int choice;

    do {
        cout << "\n--- Binary Tree Implemention ---\n";
        cout << "1. Insert Node into Tree\n";
        cout << "2. Display Pre-Order Traversal\n";
        cout << "3. Display In-Order Traversal\n";
        cout << "4. Display Post-Order Traversal\n";
        cout << "5. Search and Display Node Info\n";
        cout << "6. Exit\n";
        choice = getValidInteger("Enter your choice: ");

        switch (choice) {
        case 1: {
            int value = getValidInteger("Enter value to insert: ");
            root = insertBST(root, value);
            cout << "Value " << value << " inserted into the BST.\n";
            break;
        }
        case 2:
            cout << "Pre-Order Traversal: ";
            Pre_Order(root);
            cout << "NULL\n";
            break;
        case 3:
            cout << "In-Order Traversal: ";
            in_Order(root);
            cout << "NULL\n";
            break;
        case 4:
            cout << "Post-Order Traversal: ";
            Post_Order(root);
            cout << "NULL\n";
            break;
        case 5: {
            if (!root) {
                cout << "Tree is empty. Insert nodes first.\n";
                break;
            }
            int value = getValidInteger("Enter value to search: ");
            Node* parent = nullptr;
            Node* node = findNode(root, value, parent);

            if (node == nullptr) {
                cout << "Value " << value << " not found in the BST.\n";
            }
            else {
                cout << "Value " << value << " found in the BST.\n";
                int subChoice;
                do {
                    cout << "\n--- Node Information Menu ---\n";
                    cout << "1. Print Parent\n";
                    cout << "2. Print Ancestors\n";
                    cout << "3. Print Sibling\n";
                    cout << "4. Back to Main Menu\n";
                    subChoice = getValidInteger("Enter your choice: ");

                    switch (subChoice) {
                    case 1:
                        if (parent) {
                            cout << "Parent: " << parent->Data << endl;
                        }
                        else {
                            cout << "Parent: None (This is the root node).\n";
                        }
                        break;
                    case 2:
                        cout << "Ancestors: ";
                        if (!printAncestors(root, value)) {
                            cout << "None (This is the root node).\n";
                        }
                        cout << endl;
                        break;
                    case 3:
                        printSibling(parent, value);
                        break;
                    case 4:
                        cout << "Returning to Main Menu...\n";
                        break;
                    default:
                        cout << "Invalid choice! Try again.\n";
                    }
                } while (subChoice != 4);
            }
            break;
        }
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
