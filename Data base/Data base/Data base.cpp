#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct User {
    string username;
    string password;
};

// Function prototypes
bool registerUser(const string& username, const string& password);
bool loginUser(const string& username, const string& password);
void displayMenu();
vector<User> readUsersFromFile();
void writeUsersToFile(const vector<User>& users);

int main() {
    vector<User> users = readUsersFromFile();
    int choice;
    bool flag = false;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (registerUser(username, password)) {
                cout << "Registration successful!\n";
                users.push_back({ username, password });
                writeUsersToFile(users);
            }
            else {
                cout << "Username already exists. Please choose a different username.\n";
            }
            break;
        }
        case 2: {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (loginUser(username, password)) {
                cout << "Login successful!\n";
                return 0;
            }
            else {
                cout << "Invalid username or password. Please try again.\n";
            }
            break;
        }
        case 3:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            flag = true;
        }
        if (flag)
        {
            break;
        }
    } while (choice != 3);

    return 0;
}

bool registerUser(const string& username, const string& password) {
    vector<User> users = readUsersFromFile();

    for (const User& user : users) {
        if (user.username == username) {
            return false;  // Username already exists
        }
    }

    return true;  // Username is available
}

bool loginUser(const string& username, const string& password) {
    vector<User> users = readUsersFromFile();

    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;  // Login successful
        }
    }

    return false;  // Invalid username or password
}

void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Register\n";
    cout << "2. Log in\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

vector<User> readUsersFromFile() {
    vector<User> users;
    ifstream inputFile("users.txt");

    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            User user;
            inputFile >> user.username >> user.password;
            if (!user.username.empty() && !user.password.empty()) {
                users.push_back(user);
            }
        }

        inputFile.close();
    }

    return users;
}

void writeUsersToFile(const vector<User>& users) {
    ofstream outputFile("users.txt");

    if (outputFile.is_open()) {
        for (const User& user : users) {
            outputFile << user.username << " " << user.password << endl;
        }

        outputFile.close();
    }
}
