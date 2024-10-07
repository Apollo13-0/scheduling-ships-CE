// C Program to Implement Doubly Linkede List
#include <stdio.h>
#include <stdlib.h>

// defining a node
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node with given value as data
Node* createNode(int data);

// Function to insert a node at the beginning
void insertAtBeginning(Node** head, int data);


// Function to insert a node at the end
void insertAtEnd(Node** head, int data);


// Function to insert a node at a specified position
void insertAtPosition(Node** head, int data, int position);
// Function to delete a node from the beginning
void deleteAtBeginning(Node** head);

// Function to delete a node from the end
void deleteAtEnd(Node** head);

// Function to delete a node from a specified position
void deleteAtPosition(Node** head, int position);

// Function to print the list in forward direction
void printListForward(Node* head);

// Function to print the list in reverse direction
void printListReverse(Node* head);

int getValue(Node** head, int position);
