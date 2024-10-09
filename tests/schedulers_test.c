#include "schedulers_test.h"
#include <stdio.h>

// Función para imprimir la lista de barcos
void printShipList(Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* current = head;
    while (current != NULL) {
        if (current->booked == 1) {  // Si el nodo está ocupado, imprimimos el barco
            printShip(current->data);
        }
        current = current->next;
    }
}

// Función para probar los algoritmos de calendarización
void test_schedulers() {   
    // Crear un océano para la prueba
    struct Ocean ocean;
    ocean.numShips = 0;
    ocean.side = 0;  // Lado izquierdo (0)

    // Crear algunos barcos para las pruebas
    struct Ship ship1 = {NORMAL, 10, 1};    // Barco normal, velocidad 10, prioridad 1
    struct Ship ship2 = {PESQUERO, 20, 2};   // Barco pesquero, velocidad 20, prioridad 2
    struct Ship ship3 = {PATRULLA, 30, 3};    // Barco patrulla, velocidad 30, prioridad 3

    // Agregar los barcos al océano (usa la lista enlazada)
    addShip(&ocean, ship1);
    addShip(&ocean, ship2);
    addShip(&ocean, ship3);

    // Probar el algoritmo FCFS
    printf("Testing FCFS:\n");
    Node* fcfsResult = fcfs(&ocean);
    printShipList(fcfsResult);

    // Probar el algoritmo Round Robin con quantum = 2
    printf("\nTesting Round Robin (quantum = 2):\n");
    Node* rrResult = roundRobin(&ocean, 2);
    printShipList(rrResult);

    // Probar el algoritmo SJF (Shortest Job First)
    printf("\nTesting SJF:\n");
    Node* sjfResult = sjf(&ocean);
    printShipList(sjfResult);

    // Probar el algoritmo de Prioridad
    printf("\nTesting Priority:\n");
    Node* priorityResult = priorityScheduler(&ocean);
    printShipList(priorityResult);

    // Probar el algoritmo Tiempo Real (Real-Time) con maxTime = 5
    printf("\nTesting Real-Time (maxTime = 5):\n");
    Node* realTimeResult = realTime(&ocean, 5);
    printShipList(realTimeResult);
}