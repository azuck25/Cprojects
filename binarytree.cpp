// binarytree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <cstdlib>

#define size 7
#define range 256

using namespace std;

int bubbleSort(int arr[], int n) {
    int count = n;
    int j = 1;
    int mid = 0;

    for (int i = 0; i < count - 1; i++) {
        // cout << "comparing : " << arr[i] << " " << arr[j] << "\n";
        if (arr[i] > arr[j]) {
            // cout << "swapping" << "\n";
            // cout << arr[j] << " " << arr[i] << "\n";
            swap(arr[i], arr[j]);
        }
        j++;
    }

    j = 1;

    if (n == 1) {
        mid = arr[size / 2];
        return mid;
    } else {
        return bubbleSort(arr, n - 1);
    }
}

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

class binaryTree {
private:
    Node* root;

public:
    binaryTree() {
        root = NULL;
    }

    Node* createNewNode(int newData) {
        Node* newNode = new Node(newData);
        return newNode;
    }

    void inOrder(Node* node) {
        if (node == NULL) {
            return;
        }
        inOrder(node->left);
        cout << node->data << ", ";
        inOrder(node->right);
    }

    void preOrder(Node* node) {
        if (node == NULL) {
            return;
        }
        cout << node->data << ", ";
        inOrder(node->left);
        inOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == NULL) {
            return;
        }
        inOrder(node->left);
        inOrder(node->right);
        cout << node->data << ", ";
    }

    void insert(Node* node, int newData) {
        if (root == NULL) {
            root = new Node(newData);
            return;
        }

        if (newData < node->data && newData != root->data) {
            if (node->left == NULL) {
                node->left = createNewNode(newData);
            } else {
                insert(node->left, newData);
            }
        } else if (newData > node->data && newData != root->data) {
            if (node->right == NULL) {
                node->right = createNewNode(newData);
            } else {
                insert(node->right, newData);
            }
        }
    }

    void deleteNode(Node* node, int num) {
        while (node != NULL) {
            if (num < node->data) {
                node = node->left;

                if (node->right != NULL && node->right->data == num) {
                    // cout << "node found ! : " << num << " = " << node->data;
                    if (node->right->data == num) {
                        if (node->right->right == NULL) {
                            free(node->right);
                            node->right = NULL;
                            return;
                        } else {
                            node->right->data = node->right->right->data;
                            free(node->right->right);
                            node->right->right = NULL;
                            return;
                        }
                    }
                } else if (node->left != NULL && node->left->data == num) {
                    if (node->left->left == NULL) {
                        delete node->left;
                        node->left = NULL;
                        return;
                    } else {
                        node->left->data = node->left->left->data;
                        delete node->left->left;
                        node->left->left = NULL;
                        return;
                    }
                } else if (node != NULL && node->data == num) {
                    if (node->right != NULL) {
                        node->data = node->right->data;
                        free(node->right);
                        node->right = NULL;
                        return;
                    } else if (node->left != NULL && node->right == NULL) {
                        node->data = node->left->data;
                        free(node->left);
                        node->left = NULL;
                        return;
                    } else {
                        free(node);
                        node = NULL;
                        return;
                    }
                }
            } else if (num > node->data) {
                node = node->right;

                if (node->right != NULL && node->right->data == num) {
                    // cout << "node found ! : " << num << " = " << node->data;
                    if (node->right->data == num) {
                        if (node->right->right == NULL) {
                            free(node->right);
                            node->right = NULL;
                            return;
                        } else {
                            node->right->data = node->right->right->data;
                            free(node->right->right);
                            node->right->right = NULL;
                            return;
                        }
                    }
                } else if (node->left != NULL && node->left->data == num) {
                    if (node->left->left == NULL) {
                        delete node->left;
                        node->left = NULL;
                        return;
                    } else {
                        node->left->data = node->left->left->data;
                        delete node->left->left;
                        node->left->left = NULL;
                        return;
                    }
                } else if (node != NULL && node->data == num) {
                    if (node->right != NULL) {
                        node->data = node->right->data;
                        free(node->right);
                        node->right = NULL;
                        return;
                    } else if (node->left != NULL && node->right == NULL) {
                        node->data = node->left->data;
                        free(node->left);
                        node->left = NULL;
                        return;
                    }
                }
            }
        }
    }

    Node* getRoot() {
        return root;
    }
};

int main() {
    binaryTree btree;

    int randomData[size] = {56, 53, 24, 55, 208, 176, 231};
    // int* randomData;
    int* copy;
    // randomData = (int*)calloc(size, sizeof(int));
    copy = (int*)calloc(size, sizeof(int));

    int sum = 0;
    int midPoint = 0;

    srand(time(0));

    for (int i = 0; i <= size - 1; i++) {
        // randomData[i] = (int)rand() % range;
        copy[i] = randomData[i];
        cout << randomData[i] << "\n";
    }

    cout << "\n\n\n\n";

    midPoint = bubbleSort(copy, size);
    free(copy);

    cout << "midpoint : " << midPoint << "\n";

    btree.insert(btree.getRoot(), midPoint);
    cout << btree.getRoot() << endl;

    for (int i = 0; i <= size - 1; i++) {
        btree.insert(btree.getRoot(), randomData[i]);
    }

    // cout << btree.getRoot() << endl;
    btree.inOrder(btree.getRoot());

    int selection;

    cout << "\n\n"
         << "Enter a number to insert : ";
    cin >> selection;

    btree.insert(btree.getRoot(), selection);
    cout << endl;

    btree.inOrder(btree.getRoot());
    cout << endl;

    cout << "Select a number to delete : ";
    cin >> selection;
    cout << endl;

    btree.deleteNode(btree.getRoot(), selection);
    cout << "\n\n";

    btree.inOrder(btree.getRoot());
    cout << endl;

    cout << "Select a number to delete : ";
    cin >> selection;

    btree.deleteNode(btree.getRoot(), selection);
    cout << endl;

    btree.inOrder(btree.getRoot());

    return 0;
}
