//mid term
// Write a C++ program to manage a doubly linked list representing a 
// cricket team's performance in multiple matches. Each node in the 
// list should store the runs scored in a particular match. The program
// should allow the user to perform the following operations:

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Match {
    int score;
    Match* prev;
    Match* next;

    Match(int runs) : score(runs), prev(nullptr), next(nullptr) {}
};

class CricketRecord {
private:
    Match* firstMatch;
    Match* lastMatch;

public:
    CricketRecord() : firstMatch(nullptr), lastMatch(nullptr) {}

    void insertScoreAtStart(int runs) {
        if (runs < 0) {
            cout << "Invalid score. Score must be a non-negative integer.\n";
            return;
        }
        Match* newMatch = new Match(runs);
        // if node is empty it become both first and last node
        if (!firstMatch) {
            firstMatch = lastMatch = newMatch;
        }
        else {
            // shift the start
            newMatch->next = firstMatch;
            firstMatch->prev = newMatch;
            firstMatch = newMatch;
        }
        cout << "Score " << runs << " recorded at the beginning.\n";
    }

    void insertScoreAtEnd(int runs) {
        if (runs < 0) {
            cout << "Invalid score. Score must be a non-negative integer.\n";
            return;
        }
        Match* newMatch = new Match(runs);
        // same like inserting at start 
        if (!lastMatch) {
            firstMatch = lastMatch = newMatch;
        }
        else {
            // shift last node back
            lastMatch->next = newMatch;
            newMatch->prev = lastMatch;
            lastMatch = newMatch;
        }
        cout << "Score " << runs << " recorded at the end.\n";
    }

    void removeScoreInstances(int runs) {
        if (runs < 0) {
            cout << "Invalid score. Score must be a non-negative integer.\n";
            return;
        }
        if (!firstMatch) {
            cout << "No scores recorded.\n";
            return;
        }
        // start from the current to ittrate the list 
        Match* current = firstMatch;
        bool scoreFound = false;
        //loop continue until the current is not empty 
        while (current) {
            if (current->score == runs) {//If the score of the current node matches runs, it means this node needs to be removed.
                scoreFound = true;
                if (current == firstMatch) { // current is head 
                    firstMatch = current->next;
                    if (firstMatch) firstMatch->prev = nullptr;
                }
                else if (current == lastMatch) { // current is last node
                    lastMatch = current->prev;
                    if (lastMatch) lastMatch->next = nullptr;
                }
                else {
                    // cut the connection from the prev and front
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                // deleting the nodes
                Match* toDelete = current;
                current = current->next;
                delete toDelete;
            }
            else {
                current = current->next;
            }
        }

        if (scoreFound)
            cout << "Removed all entries of score " << runs << ".\n";
        else
            cout << "Score " << runs << " not found in any match.\n";
    }

    void listScores() const {
        if (!firstMatch) {
            cout << "No scores recorded.\n";
            return;
        }
        Match* current = firstMatch;
        cout << "Scores from first to last: ";
        while (current) {
            cout << current->score << " ";
            current = current->next;
        }
        cout << endl;
    }

    void listScoresReverse() const {
        if (!lastMatch) {
            cout << "No scores recorded.\n";
            return;
        }
        Match* current = lastMatch;
        cout << "Scores from last to first: ";
        while (current) {
            cout << current->score << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void displayHighestAndLowest() const {
        if (!firstMatch) {
            cout << "No scores recorded.\n";
            return;
        }

        int maxScore = firstMatch->score;
        int minScore = firstMatch->score;
        Match* current = firstMatch->next;

        while (current) {
            if (current->score > maxScore) maxScore = current->score;
            if (current->score < minScore) minScore = current->score;
            current = current->next;
        }

        cout << "Highest score: " << maxScore << "\n";
        cout << "Lowest score: " << minScore << "\n";
    }


    ~CricketRecord() {
        Match* current = firstMatch;
        while (current) {
            Match* nextMatch = current->next;
            delete current;
            current = nextMatch;
        }
    }
};

// valid integer input (including check for empty input)
int getValidIntInput() {
    int input;
    string line;
    while (true) {
        getline(cin, line);  // Read the entire line of input
        if (line.empty()) {  // Check if the input is empty (user pressed Enter without entering anything)
            cout << "Invalid input. Please enter a non-negative integer: ";
            continue;  // Prompt for input again
        }

        stringstream ss(line);  // Use stringstream to try converting the input to an integer
        if (ss >> input && input >= 0 && ss.eof()) {
            break;  // Valid input, break out of the loop
        }
        else {
            cout << "Invalid input. Please enter a non-negative integer: ";
        }
    }
    return input;
}


//  valid menu choice (1-7)
int getValidMenuChoice() {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        choice = getValidIntInput();
        if (choice >= 1 && choice <= 7) {
            break; // Valid choice
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    }
    return choice;
}

int main() {
    CricketRecord team;
    int choice, score;

    while (true) {
        cout << "*      Cricket Record Menu   \n";
        cout << "* 1. Record Score at Start    \n";
        cout << "* 2. Record Score at End      \n";
        cout << "* 3. Remove All Instances     \n";
        cout << "* 4. List Scores in Order     \n";
        cout << "* 5. List Scores in Reverse   \n";
        cout << "* 6. Show Highest and Lowest  \n";
        cout << "* 7. Exit                     \n";

        choice = getValidMenuChoice();  

        switch (choice) {
        case 1:
            cout << "Enter score to record at start: ";
            score = getValidIntInput();
            team.insertScoreAtStart(score);
            break;
        case 2:
            cout << "Enter score to record at end: ";
            score = getValidIntInput();
            team.insertScoreAtEnd(score);
            break;
        case 3:
            cout << "Enter score to remove all instances: ";
            score = getValidIntInput();
            team.removeScoreInstances(score);
            break;
        case 4:
            team.listScores();
            break;
        case 5:
            team.listScoresReverse();
            break;
        case 6:
            team.displayHighestAndLowest();
            break;
        case 7:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
}
