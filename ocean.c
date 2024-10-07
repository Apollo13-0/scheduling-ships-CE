#include "ocean.h"
#include <stdio.h>
#include <stdlib.h>

//Añadir barco
void addShip(struct Ocean *ocean, struct Ship ship) {
    ocean->numShips++;
    ocean->ships = realloc(ocean->ships, ocean->numShips * sizeof(struct Ship));
    ocean->ships[ocean->numShips - 1] = ship;
}

//Quitar barco
void removeShip(struct Ocean *ocean) {
    if (ocean->numShips > 0) {
        ocean->numShips--;
        ocean->ships = realloc(ocean->ships, ocean->numShips * sizeof(struct Ship));
    }
}

//Imprimir los barcos que hay en cada oceano
void printOcean(struct Ocean ocean) {
    const char *sideStr = (ocean.side == 0) ? "Left" : "Right";
    printf("Ocean Side: %s\n", sideStr);
    for (int i = 0; i < ocean.numShips; i++) {
        printShip(ocean.ships[i]);
    }
}
