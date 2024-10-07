#ifndef OCEAN_H
#define OCEAN_H

#include "ship.h"

struct Ocean {
    struct Ship *ships;  // List of ships
    int numShips;        // Number of ships waiting
    int canalLength;     // Length of the canal
    int canalCapacity;   // Capacity of the canal
    int side;            // 0 = Left ocean, 1 = Right ocean
};

void addShip(struct Ocean *ocean, struct Ship ship);
void removeShip(struct Ocean *ocean);
void printOcean(struct Ocean ocean);

#endif // OCEAN_H
