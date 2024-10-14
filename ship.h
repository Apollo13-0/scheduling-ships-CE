#ifndef BARCO_H
#define BARCO_H

#include "CEthreads.h"

typedef enum {
    NORMAL,
    PESQUERO,
    PATRULLA
} ShipType;

struct Ship {
    ShipType type;
    int speed;
    int priority;
    thread_t thread;
};

void printShip(struct Ship b);

#endif // BARCO_H
