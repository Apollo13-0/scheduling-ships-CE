#include "schedulers.h"
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>





/////////////////////////////////////////////////////////////
// First Come First Serve (FCFS)
/////////////////////////////////////////////////////////////
Node* fcfs(struct Ocean *ocean) {
    printf("FCFS order:\n");

    // Dado que no se altera el orden, retornamos la lista tal como está
    return ocean->ships;
}

/////////////////////////////////////////////////////////////
// Round Robin
/////////////////////////////////////////////////////////////
Node* roundRobin(struct Ocean *ocean, int quantum) {
    printf("Round Robin order (quantum = %d):\n", quantum);
    
    Node* current = ocean->ships;
    Node* orderedList = NULL;  // Nueva lista para los barcos en el orden de cruce
    
    while (current != NULL) {
        if (current->booked == 1) {
            int timeToUse = (current->data.speed > quantum) ? quantum : current->data.speed;
            printf("Ship crosses for %d time units\n", timeToUse);
            current->data.speed -= timeToUse;

            // Insertar barco en la lista de salida ordenada
            insertAtEnd(&orderedList, current->data, 1);

            if (current->data.speed <= 0) {
                printf("Ship has finished crossing\n");
            }
        }
        current = current->next;
    }

    return orderedList;  // Retornar la lista ordenada
}

/////////////////////////////////////////////////////////////
// Shortest Job First (SJF)
/////////////////////////////////////////////////////////////

// Función auxiliar para insertar barcos en orden de velocidad
void insertInOrder(Node* head, struct Ship ship) {
    Node* current;
    Node* newNode = createNode(ship, 1);
    

    // Si la lista está vacía o el nuevo nodo es menor que el primero
    if (head == NULL || (head)->data.speed >= ship.speed) {
        newNode->next = head;
        head = newNode;
    } else {
        current = head;
        while (current->next != NULL && current->next->data.speed < ship.speed) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Node* sjf(struct Ocean *ocean) {
    printf("SJF order (Shortest Job First):\n");

    Node* current = ocean->ships;
    Node* orderedList;  // Nueva lista enlazada para almacenar el orden SJF

    // Insertar cada barco en la lista ordenada por velocidad
    while (current != NULL) {
        insertInOrder(orderedList, current->data);
        current = current->next;
    }

    return orderedList;  // Retornar la lista enlazada ordenada por SJF
}

/////////////////////////////////////////////////////////////
// Prioridad
/////////////////////////////////////////////////////////////

// Función auxiliar para insertar barcos en orden de prioridad
void insertByPriority(Node** head, struct Ship ship) {
    Node* current;
    Node* newNode = createNode(ship, 1);

    // Si la lista está vacía o el nuevo nodo tiene mayor prioridad
    if (*head == NULL || (*head)->data.priority <= ship.priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        current = *head;
        while (current->next != NULL && current->next->data.priority > ship.priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Node* priorityScheduler(struct Ocean *ocean) {
    printf("Priority order:\n");

    Node* current = ocean->ships;
    Node* orderedList = NULL;  // Nueva lista enlazada para almacenar el orden por prioridad

    // Insertar cada barco en la lista según su prioridad
    while (current != NULL) {
        insertByPriority(&orderedList, current->data);
        current = current->next;
    }

    return orderedList;  // Retornar la lista enlazada ordenada por prioridad
}

/////////////////////////////////////////////////////////////
// Tiempo Real (Real-Time Scheduler)
/////////////////////////////////////////////////////////////
Node* realTime(struct Ocean *ocean, int maxTime) {
    printf("Real-Time order (maxTime = %d):\n", maxTime);

    Node* current = ocean->ships;
    Node* orderedList = NULL;  // Lista para barcos de tiempo real

    // Recorrer todos los barcos y filtrar los de patrulla
    while (current != NULL) {
        if (current->data.type == PATRULLA && current->booked == 1) {
            if (current->data.speed <= maxTime) {
                printf("Patrol ship crosses in %d time units\n", current->data.speed);
                insertAtEnd(&orderedList, current->data, 1);
            } else {
                printf("Warning: Patrol ship cannot cross within the maximum time\n");
            }
        }
        current = current->next;
    }

    return orderedList;  // Retornar la lista enlazada con los barcos que cumplieron
}
