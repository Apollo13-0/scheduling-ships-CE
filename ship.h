#ifndef BARCO_H
#define BARCO_H

typedef enum {
    NORMAL,
    PESQUERO,
    PATRULLA
} ShipType;

struct Ship {
    ShipType type;
    int speed;
    int priority;
};

void printShip(struct Ship b);

#endif // BARCO_H
