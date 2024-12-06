#include <iostream>
#include <string>

using namespace std;

struct Item {
    string name;
    int quantity;
};

const int max_users = 10;  // max users
const int max_items = 54;  // max items sa double chest

struct UserInventory {
    Item items[max_items];
    int itemCount;

    UserInventory() : itemCount(0) {}  // all item will start at 0
};

UserInventory inventories[max_users];
string usernames[max_users];  // holds usernames
int numUsers = 0;           // number or registered users

int findUserIndex(const string& username) {
    for (int i = 0; i < numUsers; i++) {
        if (usernames[i] == username) {
            return i;  // will return the user if username matches
        }
    }
    return -1;  // if user is not found, will return "user not found"
}

void createUser(const string& username) {
    if (numUsers >= max_users) {
        cout << "Maximum user limit reached." << endl;
        return;
    }
    usernames[numUsers] = username;
    numUsers++;
    cout << "User created successfully!" << endl;
}

void createItem(const string& username) {
    int usernameIndex = findUserIndex(username);
    if (usernameIndex == -1) {
        cout << "Invalid username." << endl;
        return;
    }

    UserInventory& inventory = inventories[usernameIndex];
    if (inventory.itemCount >= max_items) {
        cout << username << ", your inventory is full. Please remove an item if you wish to add this item." << endl;
        return;
    }

    string name;
    int quantity;

    cin.ignore();
    cout << "Enter the item name: ";
    getline(cin, name);
    cout << "Enter the quantity: ";
    cin >> quantity;

    inventory.items[inventory.itemCount] = {name, quantity};
    inventory.itemCount++;
    cout << "Item created successfully!" << endl;
}

void readItems(const string& username) {
    int usernameIndex = findUserIndex(username);
    if (usernameIndex == -1) {
        cout << "Invalid username." << endl;
        return;
    }

    UserInventory& inventory = inventories[usernameIndex];
    cout << "Your Inventory:" << endl;
    for (int i = 0; i < inventory.itemCount; i++) {
        cout << i + 1 << ". " << inventory.items[i].name << " - " << inventory.items[i].quantity << endl;
    }
}

void updateItem(const string& username) {
    int usernameIndex = findUserIndex(username);
    if (usernameIndex == -1) {
        cout << "Invalid username." << endl;
        return;
    }

    UserInventory& inventory = inventories[usernameIndex];
    int index;
    int newQuantity;

    cout << "Enter the number of the item to update (1 to " << inventory.itemCount << "): ";
    cin >> index;

    if (index < 1 || index > inventory.itemCount) {
        cout << "Invalid information." << endl;
        return;
    }

    cout << "Enter the new quantity: ";
    cin >> newQuantity;
    inventory.items[index - 1].quantity = newQuantity;
    cout << "Item updated successfully!" << endl;
}

void deleteItem(const string& username) {
    int usernameIndex = findUserIndex(username);
    if (usernameIndex == -1) {
        cout << "Invalid username." << endl;
        return;
    }

    UserInventory& inventory = inventories[usernameIndex];
    int index;

    cout << "Enter the number of the item to delete (1 to " << inventory.itemCount << "): ";
    cin >> index;

    if (index < 1 || index > inventory.itemCount) {
        cout << "Invalid, please enter the correct information required." << endl;
        return;
    }

    for (int i = index - 1; i < inventory.itemCount - 1; i++) {
        inventory.items[i] = inventory.items[i + 1];
    }
    inventory.itemCount--;
    cout << "Item deleted successfully!" << endl;
}

void mainMenu() {
    string username;
    int choice;

    while (true) {
        cout << "\nHello User! Welcome to the Inventory Management System.\nPlease fill out the form to get your items sorted!" << endl;
        cout << "1. Input Username" << endl;
        cout << "2. Input items in storage" << endl;
        cout << "3. Read items in storage" << endl;
        cout << "4. Update an item in storage" << endl;
        cout << "5. Delete an item in storage" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 6) {
            cout << "Exiting..." << endl;
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter your user ID: ";
                cin >> username;
                createUser(username);
                break;
            case 2:
                cout << "Enter your user ID: ";
                cin >> username;
                createItem(username);
                break;
            case 3:
                cout << "Enter your user ID: ";
                cin >> username;
                readItems(username);
                break;
            case 4:
                cout << "Enter your user ID: ";
                cin >> username;
                updateItem(username);
                break;
            case 5:
                cout << "Enter your user ID: ";
                cin >> username;
                deleteItem(username);
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}