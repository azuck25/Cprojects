#include <iostream>
#include <random>
#include <cstdlib>

#define maxSize 8

using namespace std;

struct vertex {
    int weight;
    bool visted;
    vertex* path1;
    vertex* path2;
    vertex* path3;

    vertex(int w)
        : weight(w), visted(false), path1(nullptr), path2(nullptr), path3(nullptr) {}
};

class StackOps {
    // Here I changed the stack type to accommodate the vertex structure
private:
    int front;
    int back;
    int size = 0;
    vertex* arr = (vertex*)calloc(0, sizeof(vertex));

public:
    void push(vertex* input) {
        size++;
        arr = (vertex*)realloc(arr, size * sizeof(vertex));

        arr[size - 1].path1 = input->path1;
        arr[size - 1].path2 = input->path2;
        arr[size - 1].path3 = input->path3;
        arr[size - 1].visted = input->visted;
        arr[size - 1].weight = input->weight;
    }

    void pop() {
        if (size != 0) {
            --size;
            arr = (vertex*)realloc(arr, size * sizeof(vertex));
        } else {
            cout << "Stack underflow\n";
        }
    }

    vertex* peek() {
        // cout << "Returning top element...\n";
        // cout << arr[size - 1].weight << endl;
        return &arr[size - 1];
    }

    bool isEmpty() {
        if (size != 0) {
            return false;
        } else {
            return true;
        }
    }

    void printStack() {
        cout << "Printing stack..." << endl;
        for (int i = 0; i <= size - 1; i++) {
            cout << arr[i].weight << endl;
        }
    }
};

class graph {
public:
    vertex* vertexStruct[maxSize];
    StackOps stack;

public:
    void constructGraph(int arr[]) {
        for (int i = 0; i < maxSize; i++) {
            vertexStruct[i] = new vertex(arr[i]);
        }
    }

    void createConnections() {
        int offset = 3, staticOffset = 3;
        int count = 0;
        int count1 = 0;

        while (count != maxSize) {
            // In an ordered array the minimum value is the first
            // We will create an undirected hexagonal graph where the smallest
            // node and largest node have 3 connections
            // The rest will only have two edges

            if (count == (maxSize - maxSize)) {
                for (int i = 1; i <= 3; i++) {
                    // left
                    if (i == 1)
                        vertexStruct[count]->path1 = vertexStruct[i];
                    // middle
                    else if (i == 2)
                        vertexStruct[count]->path2 = vertexStruct[i];
                    // right
                    else if (i == 3)
                        vertexStruct[count]->path3 = vertexStruct[i];
                }
            }

            if (count < maxSize - 1 && count > 0) {
                if (count <= 3) {
                    // previous
                    vertexStruct[count]->path2 = vertexStruct[count - count];
                    // next
                    vertexStruct[count]->path1 = vertexStruct[count + staticOffset];
                } else if (count > 3 && count < maxSize - 4) {
                    // previous
                    vertexStruct[count]->path2 = vertexStruct[count - staticOffset];
                    // next
                    vertexStruct[count]->path1 = vertexStruct[count + staticOffset];
                } else if (count >= maxSize - 4 && count < maxSize - 1) {
                    // previous
                    vertexStruct[count]->path2 = vertexStruct[count - staticOffset];
                    // next
                    vertexStruct[count]->path1 = vertexStruct[count + offset];
                    --offset;
                }
            }

            if (count == maxSize - 1) {
                for (int i = count - 1; i >= maxSize - 4; i--) {
                    if (i == maxSize - 4)
                        vertexStruct[count]->path3 = vertexStruct[i];
                    else if (i == maxSize - 3)
                        vertexStruct[count]->path2 = vertexStruct[i];
                    else if (i == maxSize - 2)
                        vertexStruct[count]->path1 = vertexStruct[i];
                }
            }
            ++count;
        }
    }

    void printVertex(vertex* v) {
        if (v->path3 != nullptr) {
            cout << "(w: " << v->weight;
            cout << " -> p1: " << v->path1->weight;
            cout << " -> p2: " << v->path2->weight;
            cout << " -> p3: " << v->path3->weight;
            cout << ")\n";
        } else {
            cout << "(w: " << v->weight;
            cout << " -> p1: " << v->path1->weight;
            cout << " -> p2: " << v->path2->weight;
            cout << ")\n";
        }
    }

    int checkPath(vertex* v) {
        // If path is unvisited take the path else return 0
        if (v->path1->visted == false) {
            return 1;
        } else if (v->path2->visted == false) {
            return 2;
        }
        // Only the largest or smallest node can take this path when it is
        // unvisited
        else if (v->path3 != nullptr && v->path3->visted == false) {
            return 3;
        } else {
            return 0;
        }
    }

    void depthFirstSearch(vertex* v) {
        cout << "Implementing DFS traversal algorithm\n";
        int direction;

        stack.push(v);
        v->visted = true;

        while (!stack.isEmpty()) {
            direction = checkPath(stack.peek());

            if (direction == 1) {
                cout << "direction 1\n";
                v->visted = true;
                printVertex(v);
                v = v->path1;
                stack.push(v);
            } else if (direction == 2) {
                cout << "direction 2\n";
                v->visted = true;
                printVertex(v);
                v = v->path2;
                stack.push(v);
            } else if (direction == 3) {
                cout << "direction 3\n";
                v->visted = true;
                printVertex(v);
                v = v->path3;
                stack.push(v);
            } else {
                cout << "Popping element from stack...\n";
                stack.pop();
            }
        }
        cout << "Stack empty, exiting...";
    }
};

int main() {
    graph g;

    // int arr1[maxSize] = { 9,10,15,25,30,45,50,70};
    int* arr1 = (int*)calloc(maxSize, sizeof(int));

    // srand(time(0));
    for (int i = 0; i < maxSize; i++) {
        arr1[i] = rand() % 100;
    }

    g.constructGraph(arr1);
    g.createConnections();
    g.depthFirstSearch(g.vertexStruct[0]);

    free(arr1);

    return 0;
}
