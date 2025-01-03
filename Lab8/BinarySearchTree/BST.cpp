//BST tree task 1
//implement a BST in which we are Able to search
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    // Function that find node and its parent
    // if value is less go to left other wise go to right
    TreeNode* findNode(TreeNode* node, int value, TreeNode*& parent) {
        while (node != nullptr && node->data != value) {
            parent = node;
            if (value < node->data) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return node;
    }

    // Function that find anncestors
    // traverse until the node with the respective value are found
    bool printAncestors(TreeNode* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (node->data == value)
        {
            return true;
        }

        if (printAncestors(node->left, value) || printAncestors(node->right, value)) {
            cout << node->data << " ";
            return true;
        }

        return false;
    }

    // Function that find its sibling
    void printSibling(TreeNode* parent, int value) {
        if (!parent) {
            cout << "No sibling (Root node has no sibling).\n";
            return;
        }

       /* parent->left ensures the parent has a left child.
          parent->left->data == value checks if the left child is the node in question.
          parent->right ensures the parent also has a right child(i.e., a sibling exists).*/

        if (parent->left && parent->left->data == value && parent->right) {
            cout << "Sibling: " << parent->right->data << endl;
        }
        else if (parent->right && parent->right->data == value && parent->left) {
            cout << "Sibling: " << parent->left->data << endl;
        }
        else {
            cout << "No sibling.\n";
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void buildTree() {
        root = new TreeNode(50);
        root->left = new TreeNode(30);
        root->right = new TreeNode(70);
        root->left->left = new TreeNode(20);
        root->left->right = new TreeNode(40);
        root->right->left = new TreeNode(60);
        root->right->right = new TreeNode(80);
        cout << "Predefined BST created successfully.\n";
    }

    // vilidate int input
    int getValidInteger(string prompt) {
        int value;
        string input;

        while (true) {
            cout << prompt;
            getline(cin, input);

            if (input.empty()) {
                cout << "Input cannot be empty! Please enter a valid integer.\n";
                continue;
            }

            stringstream ss(input);
            if (ss >> value) {
                return value;
            }
            else {
                cout << "Invalid input! Please enter a valid integer.\n";
            }
        }
    }

    // Search and display information about the node
    void searchNode() {
        if (root == nullptr) {
            cout << "Tree is empty. Initialize the tree first.\n";
            return;
        }

        int value = getValidInteger("Enter the value to search: ");
        TreeNode* parent = nullptr;
        TreeNode* node = findNode(root, value, parent);

        if (node == nullptr) {
            cout << "Value " << value << " not found in the BST.\n";
            return;
        }
        else {
            cout << "Value " << value << " found in the BST.\n";
        }

        int choice;
        do {
            cout << "\n--- Node Information Menu ---\n";
            cout << "1. Print Parent\n";
            cout << "2. Print Ancestors\n";
            cout << "3. Print Sibling\n";
            cout << "4. Back to Main Menu\n";
            cout << "Enter your choice: ";
            choice = getValidInteger("");

            switch (choice) {
            case 1:
                if (parent) {
                    cout << "Parent: " << parent->data << endl;
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
        } while (choice != 4);
    }
};

int main() {
    BinarySearchTree bst;
    bst.buildTree();

    int choice;
    do {
        cout << "\n--- Binary Tree Management ---\n";
        cout << "1. Search in Binary Tree\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        choice = bst.getValidInteger("");

        switch (choice) {
        case 1:
            bst.searchNode();
            break;
        case 2:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 2);

    return 0;
}
