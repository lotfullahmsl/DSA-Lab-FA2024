//open ended task
//task is to manage a list of cricket players and their match records
//using a program that supports adding, updating, removing,
//and displaying players.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct PlayerNode {
    string name;
    int testSeries = 0;
    int odi = 0;
    int t20 = 0;
    PlayerNode* next = nullptr;
    PlayerNode* previous = nullptr;

    PlayerNode(string playerName, int test, int odiCount, int t20Count)
        : name(playerName), testSeries(test), odi(odiCount), t20(t20Count), next(nullptr), previous(nullptr) {}
};

class PlayerList {
private:
    PlayerNode* head = nullptr;
    PlayerNode* tail = nullptr;
    int playerCount = 0;

public:
    void addPlayer(string playerName, int testSeries, int odi, int t20, bool saveToFile = true);
    void removePlayer(string playerName);
    void updatePlayer(string playerName);
    void displayPlayers() const;
    bool isEmpty() const;
    int getPlayerCount() const;
    void loadFromFiles();

    ~PlayerList();
};

void printMenu() {
    cout << "\n***************************************\n";
    cout << "*          Player Management          *\n";
    cout << "***************************************\n";
    cout << "1. Add Player\n";
    cout << "2. Remove Player\n";
    cout << "3. Update Player\n";
    cout << "4. Display All Players\n";
    cout << "5. Exit\n";
    cout << "***************************************\n";
}

// valid integer input
int getValidIntInput() {
    int input;
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) {
            cout << "Invalid input. Please enter a valid integer: ";
            continue;
        }
        stringstream ss(line);
        if (ss >> input && input >= 0 && ss.eof()) {
            break;
        }
        else {
            cout << "Invalid input. Please enter a valid integer: ";
        }
    }
    return input;
}

// Function to get a valid menu choice
int getValidMenuChoice() {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        choice = getValidIntInput();
        if (choice >= 1 && choice <= 5) {
            break;
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
    return choice;
}

// Adds a player to the list
void PlayerList::addPlayer(string playerName, int testSeries, int odi, int t20, bool saveToFile) {
    PlayerNode* newNode = new PlayerNode(playerName, testSeries, odi, t20);

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }

    playerCount++;

    if (saveToFile) {
        string fileName = playerName + "_Data.txt";
        //open a file for a user one for each user
        ofstream outFile(fileName);
        if (outFile.is_open()) {
            outFile << playerName << " " << testSeries << " " << odi << " " << t20;
            outFile.close();
        }
        // list of all players in one file
        ofstream playerListFile("players_list.txt", ios::app);
        if (playerListFile.is_open()) {
            playerListFile << playerName << "\n";
            playerListFile.close();
        }
    }
}

// removes a player from the list
void PlayerList::removePlayer(string playerName) {
    if (isEmpty()) {
        cout << "The list is empty.\n";
        return;
    }

    PlayerNode* current = head;
    while (current != nullptr) {
        if (current->name == playerName) {
            // if player is in the head
            if (current == head) {
                head = current->next;
                if (head) head->previous = nullptr;
            }
            // if player is in the tail
            else if (current == tail) {
                tail = current->previous;
                if (tail) tail->next = nullptr;
            }
            else {
                current->previous->next = current->next;
                current->next->previous = current->previous;
            }

            delete current;
            playerCount--;

            string fileName = playerName + "_Data.txt";
            // this will convert the file name to the compiler to understand
            remove(fileName.c_str());

            ifstream inFile("players_list.txt"); // players_list.txt in input mode for reading.
            ofstream outFile("temp_players_list.txt"); //temp_players_list.txt in output mode for writing.

            if (!inFile.is_open() || !outFile.is_open()) {
                cout << "Error opening file.\n";
                return;
            }

            // read line by line 
            string line;
            while (getline(inFile, line)) {
                if (line != playerName) {
                    outFile << line << "\n";
                }
            }

            inFile.close(); 
            outFile.close(); 

            remove("players_list.txt");
            rename("temp_players_list.txt", "players_list.txt");

            cout << "Player " << playerName << " removed successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Player " << playerName << " not found in the list.\n";
}

// Updates player information
void PlayerList::updatePlayer(string playerName) {
    if (isEmpty()) {
        cout << "The list is empty. No players to update.\n";
        return;
    }

    PlayerNode* current = head;
    while (current != nullptr) {
        if (current->name == playerName) {
            cout << "Updating information for " << playerName << ":\n";
            cout << "Enter new number of ODI: ";
            current->odi = getValidIntInput();
            cout << "Enter new number of Test Series: ";
            current->testSeries = getValidIntInput();
            cout << "Enter new number of T20: ";
            current->t20 = getValidIntInput();

            // make a new file for the player 
            string fileName = playerName + "_Data.txt";
            ofstream outFile(fileName);
            if (outFile.is_open()) {
                outFile << playerName << " " << current->testSeries << " " << current->odi << " " << current->t20;
                outFile.close();
                cout << "Player data updated successfully in file.\n";
            }
            return;
        }
        current = current->next;
    }
    cout << "Player " << playerName << " not found in the list.\n";
}

void PlayerList::displayPlayers() const {
    if (isEmpty()) {
        cout << "No players in the list.\n";
        return;
    }

    PlayerNode* current = head;
    while (current != nullptr) {
        cout << "\n***************************************\n";
        cout << "Player Name: " << current->name << "\n";
        cout << "Test Series: " << current->testSeries << "\n";
        cout << "ODI: " << current->odi << "\n";
        cout << "T20: " << current->t20 << "\n";
        cout << "***************************************\n";
        current = current->next;
    }
}

// if the list is empty
bool PlayerList::isEmpty() const {
    return head == nullptr;
}

// number of players
int PlayerList::getPlayerCount() const {
    return playerCount;
}

// Loads players from files
void PlayerList::loadFromFiles() {
    // open file
    ifstream playersFile("players_list.txt");
    if (!playersFile.is_open()) {
        cout << "No previous data found. Starting with an empty list.\n";
        return;
    }

    string playerName;
    while (getline(playersFile, playerName)) { // open file player 
        string fileName = playerName + "_Data.txt";
        ifstream inFile(fileName); // open file data

        if (inFile.is_open()) {
            string name;
            int testSeries, odi, t20;
            inFile >> name >> testSeries >> odi >> t20;
            addPlayer(name, testSeries, odi, t20, false);
            inFile.close();
        }
    }
    playersFile.close();
}

// clean data
PlayerList::~PlayerList() {
    while (!isEmpty()) {
        removePlayer(head->name);
    }
}

int main() {
    PlayerList players;
    players.loadFromFiles();

    int choice, testSeries, odi, t20;
    string name;

    while (true) {
        printMenu();
        choice = getValidMenuChoice();

        switch (choice) {
        case 1:
            if (players.getPlayerCount() >= 20) {
                cout << "Cannot add more players. Maximum limit reached.\n";
                break;
            }
            cout << "Enter player name: ";
            getline(cin, name);

            cout << "Enter number of Test Series: ";
            testSeries = getValidIntInput();
            cout << "Enter number of ODI: ";
            odi = getValidIntInput();
            cout << "Enter number of T20: ";
            t20 = getValidIntInput();

            players.addPlayer(name, testSeries, odi, t20);
            cout << "Player added successfully.\n";
            break;

        case 2:
            cout << "Enter player name to remove: ";
            getline(cin, name);
            players.removePlayer(name);
            break;

        case 3:
            cout << "Enter player name to update: ";
            getline(cin, name);
            players.updatePlayer(name);
            break;

        case 4:
            players.displayPlayers();
            break;

        case 5:
            cout << "Exiting the program. Goodbye!\n";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
