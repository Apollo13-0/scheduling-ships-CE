#include "schedulers_test.h"
#include <stdio.h>

int test_schedulers() {
    // Ocean on the left side
    struct Ocean leftOcean;
    leftOcean.numShips = 0;
    leftOcean.canalLength = 100;
    leftOcean.canalCapacity = 5;
    leftOcean.side = 0;  // Left ocean (0)

    // Ocean on the right side
    struct Ocean rightOcean;
    rightOcean.numShips = 0;
    rightOcean.canalLength = 100;
    rightOcean.canalCapacity = 5;
    rightOcean.side = 1;  // Right ocean (1)

    struct Ship ship1 = {NORMAL, 10, 1};
    struct Ship ship2 = {PESQUERO, 20, 2};
    struct Ship ship3 = {PATRULLA, 30, 3};
    struct Ship ship4 = {PATRULLA, 30, 3};


    // Adding ships to the left ocean
    addShip(&leftOcean, ship1);
    addShip(&leftOcean, ship2);
    addShip(&leftOcean, ship3);

    // Adding ships to the right ocean
    addShip(&rightOcean, ship1);
    addShip(&rightOcean, ship2);
    addShip(&rightOcean, ship3);
    addShip(&rightOcean, ship4);



    //Se escoge que usar en que oceano
    //printf("FCFS:\n");
    //fcfs(&leftOcean);
    //fcfs(&rightOcean);

    printf("\nRound Robin (quantum = 10):\n");
    roundRobin(&rightOcean, 10);

    //printf("\nSJF:\n");
    //sjf(&leftOcean);
    //sjf(&rightOcean);

    //printf("\nPriority:\n");
    //priorityScheduler(&rightOcean);
    //priorityScheduler(&leftOcean);


    //printf("\nReal-Time (maxTime = 5):\n");
    //realTime(&leftOcean, 5);
    //realTime(&rightOcean, 5);


    return 0;
}