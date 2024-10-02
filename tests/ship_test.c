#include "ship_test.h"
#include <stdio.h>

void shipTest() {

    struct Ship ship1 = {NORMAL, 10};
    struct Ship ship2 = {PESQUERO, 15};
    struct Ship ship3 = {PATRULLA, 20};

    printShip(ship1);
    printShip(ship2);
    printShip(ship3);
}
