
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// C Program to Implement Doubly Linkede List
#include <stdio.h>
#include <stdlib.h>
#include "ship.h"

// defining a node
typedef struct Node {
    struct Ship data; 
    int booked;
    struct Node* next;
    struct Node* prev;
} Node;


// Function to create a new node with given value as data
Node* createNode(struct Ship data, int type);

// Function to insert a node at the beginning
void insertAtBeginning(Node** head, struct Ship data, int type);


// Function to insert a node at the end
void insertAtEnd(Node** head, struct Ship data, int type);


// Function to insert a node at a specified position
void insertAtPosition(Node** head, struct Ship data, int position, int type);
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
void setValue(Node** head, int data_in, int position);
struct Ship getShip(Node** head, int position);
#endif  // LINKEDLIST_H
