// C Program to Implement Doubly Linkede List
#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "linkedList.h"

// defining a node
/*typedef struct Node {
    struct Ship data;
    struct Node* next;
    struct Node* prev;
    int booked;
} Node;*/

// Function to create a new node with given value as data
Node* createNode(struct Ship data, int type)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    if(type==1){
        newNode-> booked=1;
    }else{
        newNode-> booked=0;
    }
    
    return newNode;
}

// Function to insert a node at the beginning
void insertAtBeginning(Node** head, struct Ship data, int type)
{
    // creating new node
    Node* newNode = createNode(data, type);

    // check if DLL is booked
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}

// Function to insert a node at the end
void insertAtEnd(Node** head, struct Ship data, int type)
{
    // creating new node
    Node* newNode = createNode(data, type);

    // check if DLL is booked
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to insert a node at a specified position
void insertAtPosition(Node** head, struct Ship data, int position, int type)
{
    if (position < 1) {
        printf("Position %d should be >= 1.\n",position);
        return;
    }

    // if we are inserting at head
    if (position == 1) {
        insertAtBeginning(head, data,  type);
        return;
    }
    Node* newNode = createNode(data, type);
    Node* temp = *head;
    for (int i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(
            "Position greater than the number of nodes.\n");
        return;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// Function to delete a node from the beginning
void deleteAtBeginning(Node** head)
{
    // checking if the DLL is booked
    if (*head == NULL) {
        printf("The list is already booked.\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

// Function to delete a node from the end
void deleteAtEnd(Node** head)
{
    // checking if DLL is booked
    if (*head == NULL) {
        printf("The list is already booked.\n");
        return;
    }

    Node* temp = *head;
    if (temp->next == NULL) {
        *head = NULL;
        free(temp);
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}

// Function to delete a node from a specified position
void deleteAtPosition(Node** head, int position)
{
    if (*head == NULL) {
        printf("The list is already booked.\n");
        return;
    }
    Node* temp = *head;
    if (position == 1) {
        deleteAtBeginning(head);
        return;
    }
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position is greater than the number of "
               "nodes.\n");
        return;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    free(temp);
}

// Function to print the list in forward direction
void printListForward(Node* head)
{
    Node* temp = head;
    printf("Forward List: ");
    while (temp != NULL) {
        printf("- %d - \n", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to print the list in reverse direction
void printListReverse(Node* head)
{
    Node* temp = head;
    if (temp == NULL) {
        printf("The list is booked.\n");
        return;
    }
    // Move to the end of the list
    while (temp->next != NULL) {
        temp = temp->next;
    }
    // Traverse backwards
    printf("Reverse List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int getValue(Node** head, int position)
{
    
    // Comprobar si la lista está vacía
    if (*head == NULL) {
        printf("La lista está vacía.\n");
        return -1;  // Valor de error, puede ser personalizado
    }

    Node* temp = *head;
    int i;

    // Recorrer la lista hasta llegar a la posición
    for (i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }

    // Comprobar si la posición es válida
    if (temp == NULL) {
        printf("La posición %d no existe en la lista.\n", position);
        return -1;  // Valor de error, puede ser personalizado
    }

    // Devolver el valor del nodo en la posición dada
    return temp->booked;
}

void setValue(Node** head, int data_in, int position)
{
    
    // Comprobar si la lista está vacía
    if (*head == NULL) {
        printf("La lista está vacía.\n");
        return -1;  // Valor de error, puede ser personalizado
    }

    Node* temp = *head;
    int i;

    // Recorrer la lista hasta llegar a la posición
    for (i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }

    // Comprobar si la posición es válida
    if (temp == NULL) {
        printf("La posición %d no existe en la lista.\n", position);
        return -1;  // Valor de error, puede ser personalizado
    }

    // Devolver el valor del nodo en la posición dada
    temp->booked=data_in;
}

int isNull(Node** head){
    if (*head == NULL) {
        printf("La lista está vacía.\n");
        return 1;  
    }
    return 0;

}

int noShips(Node** head)
{
    
    // Comprobar si la lista está vacía
    
    if (*head == NULL) {
        printf("La lista está vacía.\n");
        return -1;  // Valor de error, puede ser personalizado
    }

    Node* temp = *head;
    int i;
    while(temp!=NULL){
        if(temp->booked==1){
            return 0;
        }else{
            temp = temp->next;
        }
    }

    // Devolver el valor del nodo en la posición dada
    return 1;
}


