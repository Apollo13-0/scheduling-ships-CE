#include "ship.h"
#include <stdio.h>

void printShip(struct Ship b) {
    printf("Tipo de barco: ");
    
    switch(b.type) {
        case NORMAL:
            printf("Normal\n");
            break;
        case PESQUERO:
            printf("Pesquero\n");
            break;
        case PATRULLA:
            printf("Patrulla\n");
            break;
    }
    
    printf("Velocidad: %i\n", b.speed);
    printf("Prioridad: %i\n", b.priority);
}
