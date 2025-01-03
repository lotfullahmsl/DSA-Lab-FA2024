#include <iostream>
#include <stack>
#include <string>
using namespace std;


bool isAlphabetic(string word) {
    for (char c : word) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

// Function to check if the input is a palindrome
bool palindromeCheck(string word) {
    stack<char> s;
    string str1 = "";

    // Push characters onto the stack
    for (int i = 0; i < word.length(); i++) {
        s.push(word[i]);
    }

    // Pop characters from the stack to reverse the word
    for (int i = 0; i < word.length(); i++) {
        char topChar = s.top();
        s.pop();
        str1 += topChar;
    }

    // Compare the reversed word with the original
    return (str1 == word);
}

int main() {
    string word;

    // Input validation loop
    while (true) {
        cout << "Enter a word: ";
        getline(cin, word);

        if (word.empty()) {
            cout << "Error: You entered an empty input. Please enter a valid word.\n";
            continue;
        }

        if (!isAlphabetic(word)) {
            cout << "Error: Invalid input. Please enter alphabetic characters only.\n";
            continue;
        }

        // If input is valid, check if it's a palindrome
        if (palindromeCheck(word)) {
            cout << "The word is a palindrome." << endl;
        }
        else {
            cout << "The word is not a palindrome." << endl;
        }
        break;
    }

    return 0;
}
