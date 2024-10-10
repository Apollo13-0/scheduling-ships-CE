#include "ocean.h"
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

// Agregar un barco a la lista enlazada del océano
void addShip(struct Ocean *ocean, struct Ship ship) {
    // Insertar al final de la lista enlazada y marcar el nodo como "booked" (1)
    insertAtEnd(&(ocean->ships), ship, 1);  
    ocean->numShips++;
}

// Eliminar un barco desde el inicio de la lista enlazada
void removeShip(struct Ocean *ocean) {
    if (ocean->numShips > 0) {
        deleteAtBeginning(&(ocean->ships));  // Eliminar el primer barco de la lista enlazada
        ocean->numShips--;
    }
}

// Imprimir los barcos del océano usando la lista enlazada
void printOcean(struct Ocean ocean) {
    const char *sideStr = (ocean.side == 0) ? "Left" : "Right";
    printf("Ocean Side: %s\n", sideStr);
    printListForward(ocean.ships);  // Usar la función para imprimir la lista enlazada
}
