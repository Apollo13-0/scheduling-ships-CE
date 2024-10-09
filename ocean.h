#ifndef OCEAN_H
#define OCEAN_H

#include "ship.h"
#include "linkedList.h"  // Incluir el archivo de la lista enlazada

struct Ocean {
    Node* ships;    // Lista enlazada de barcos
    int numShips;   // Número de barcos esperando
    int side;       // 0 = Left ocean, 1 = Right ocean
};

// Funciones para manipular barcos
void addShip(struct Ocean *ocean, struct Ship ship);
void removeShip(struct Ocean *ocean);
void printOcean(struct Ocean ocean);

#endif // OCEAN_H
