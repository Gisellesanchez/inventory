#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Base class
class Product {
public:
    virtual void display() = 0;
    virtual string toFile() = 0;
    virtual ~Product() {} // good practice
};

// Derived class
class Item : public Product {
public:
    string name;
    int quantity;
    double price;

    void display() override {
        cout << name << " | Qty: " << quantity << " | Price: $" << price << endl;
    }

    string toFile() override {
        return name + " " + to_string(quantity) + " " + to_string(price);
    }
};

// Show inventory with index
void showInventory(vector<Product*>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    for (int i = 0; i < inventory.size(); i++) {
        cout << i << ": ";
        inventory[i]->display();
    }
}

// Add item
void addItem(vector<Product*>& inventory) {
    Item* newItem = new Item();

    cout << "Enter name: ";
    cin >> newItem->name;
    cout << "Enter quantity: ";
    cin >> newItem->quantity;
    cout << "Enter price: ";
    cin >> newItem->price;

    inventory.push_back(newItem);
}

// Delete item
void deleteItem(vector<Product*>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    showInventory(inventory);

    int index;
    cout << "Enter index to delete: ";
    cin >> index;

    if (index >= 0 && index < inventory.size()) {
        delete inventory[index]; // free memory
        inventory.erase(inventory.begin() + index); // remove from vector
        cout << "Item deleted.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

// Save to file
void saveToFile(vector<Product*>& inventory) {
    ofstream file("inventory.txt");

    for (Product* item : inventory) {
        file << item->toFile() << endl;
    }

    file.close();
}

// Load from file
void loadFromFile(vector<Product*>& inventory) {
    ifstream file("inventory.txt");

    string name;
    int quantity;
    double price;

    while (file >> name >> quantity >> price) {
        Item* item = new Item();
        item->name = name;
        item->quantity = quantity;
        item->price = price;
        inventory.push_back(item);
    }

    file.close();
}

int main() {
    vector<Product*> inventory;
    int choice;

    loadFromFile(inventory);

    do {
        cout << "\n=== Inventory Menu ===\n";
        cout << "1. Add Item\n";
        cout << "2. View Inventory\n";
        cout << "3. Delete Item\n";
        cout << "4. Save & Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            addItem(inventory);
        }
        else if (choice == 2) {
            showInventory(inventory);
        }
        else if (choice == 3) {
            deleteItem(inventory);
        }

    } while (choice != 4);

    saveToFile(inventory);

    // Clean up memory
    for (Product* item : inventory) {
        delete item;
    }

    return 0;
}
