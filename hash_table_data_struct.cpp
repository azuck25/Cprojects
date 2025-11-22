#include <iostream>
#include <random>
#include <cstdlib>

#define size 16

using namespace std;

struct hashT {
    int value;
    int key;
    hashT* previous;
    hashT* next;

    // constructor method to build nodes of hashtable
    hashT(int x, int y) : value(y), key(x), previous(nullptr), next(nullptr) {}
};

class hashTable {
public:
    hashT* table[size];

public:
    void constructTable() {
        for (int i = 0; i <= size - 1; i++) {
            // initializing hashtable with null values
            table[i] = new hashT(NULL, NULL);
        }
    }

    hashT* createNode(int key, int value) {
        // creating new node with constructor
        hashT* newNode = new hashT(key, value);
        return newNode;
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key, int value) {
        int hash = hashFunction(key);

        // If the key position in the hashtable has an entry then we will create
        // a linked list to avoid collisions
        // We then implement the separate chaining technique
        if (table[hash]->value != NULL) {
            hashT* address = table[hash];
            while (table[hash]->next != NULL) {
                table[hash] = table[hash]->next;
            }
            table[hash]->next = createNode(key, value);
            table[hash] = address;
        }
        // Node created at key position without collision
        else {
            table[hash] = createNode(key, value);
        }
    }

    void del(int key, int value) {
        int index = hashFunction(key);
        hashT* head = table[index];

        cout << endl
             << "Searching for element in key position : " << index << endl;

        // Here we reuse our search function to return the address of the found
        // value.
        hashT* t = search(value, key);

        cout << endl
             << "Attempting to delete element, key : " << index
             << " value : " << value << endl;

        table[index] = t;

        // If the next node is NULL and the previous link in the chain is not
        // NULL then it is the last position in the linked list
        // Deletes by setting pointer of previous node to null to separate the
        // node from the list.
        if (table[index]->next == NULL && table[index]->previous != NULL) {
            table[index] = table[index]->previous;
            table[index]->next = nullptr;
            table[index] = head;
        }
        // If the value is not equal to the head value then it is in the middle
        // of the list.
        // Deletes by setting the pointer to the next next node. If 2 is to be
        // deleted then 1,2,3 then 1's pointer is set to 3
        else if (value != head->value) {
            table[index] = table[index]->previous;
            table[index]->next = table[index]->next->next;
            table[index] = head;
        }
        // If the value is equal to the value at the head node and the next
        // link is NULL
        // Uses the method above
        else if (table[index]->next != NULL && value == head->value) {
            table[index]->value = table[index]->next->value;
            table[index]->next = table[index]->next->next;
        }
        else {
            table[index] = new hashT(NULL, NULL);
        }
    }

    hashT* search(int searchVal, int key) {
        bool check = false;
        int index = hashFunction(key);
        hashT* t = table[index];
        hashT* prev = t;

        if (t->next != NULL) {
            while (t) {
                if (t->value == searchVal) {
                    cout << "Value Found!";
                    // If the value is found the previous link's address is saved
                    // to be used for deletion
                    t->previous = prev;
                    return t;
                }
                else {
                    // Captures the previous link's address
                    prev = t;
                    // Traverses to next node
                    t = t->next;
                }
            }
        }
        // If there isn't a linked list traversal isn't necessary and checks for
        // node's value
        else {
            if (t->value == searchVal) {
                cout << "Value Found!";
                return t;
            }
            else {
                cout << "Value Not Found!\n\n";
            }
        }

        return nullptr;
    }

    void printTable() {
        bool check = false;
        cout << "\n\n";

        for (int i = 0; i <= size - 1; i++) {
            // If a linked list exists at the key's position we then traverse
            // the list
            if (table[i]->next != NULL) {
                // The address of the head node is saved to reset the cursor to
                // the head position of the hashtable so the next linked list is
                // able to be traversed as we iterate through the structure
                hashT* returnAddress = table[i];

                cout << table[i]->key << " : ";
                while (!check) {
                    cout << table[i]->value;
                    cout << " : ";
                    check = (table[i]->next == NULL) ? true : false;
                    table[i] = table[i]->next;
                }

                // After iterating through the check flag is reset for the next
                // traversal and the address is set back to the head address
                cout << endl;
                check = false;
                table[i] = returnAddress;
            }
            // No traversal needed: print key-value pair
            else {
                cout << table[i]->key << " : ";
                cout << table[i]->value;
                cout << endl;
            }
        }
    }
};

int main() {
    hashTable hashTble;

    // Initialize table
    hashTble.constructTable();

    // Allocate memory on the heap for an array of ints of size 16
    int* key = (int*)calloc(size, sizeof(int));
    int* value = (int*)calloc(size, sizeof(int));

    // Seeding the random number generator with the current time generates
    // diverse number array. Commented out for consistency
    // srand(time(0));

    cout << endl
         << "Generating 16 random numbers between 0 and 5000" << endl;

    for (int i = 0; i <= size - 1; i++) {
        value[i] = (int)rand() % 5000;
        cout << value[i] << "\n";
    }

    cout << endl
         << "Key pair calculated by taking modulo 16 of elements in value "
            "array."
         << endl;

    for (int i = 0; i <= size - 1; i++) {
        key[i] = hashTble.hashFunction(value[i]);
        cout << key[i] << "\n";
    }

    cout << endl
         << "Inserting elements into their position in the hashtable by key."
         << endl;

    for (int i = 0; i <= size - 1; i++) {
        hashTble.insert(key[i], value[i]);
    }

    hashTble.printTable();
    cout << endl;

    hashTble.search(4358, 6);
    cout << endl;

    hashTble.search(725, hashTble.hashFunction(724));

    hashTble.del(hashTble.hashFunction(3281), 3281);
    hashTble.del(hashTble.hashFunction(41), 41);

    hashTble.printTable();

    return 0;
}
