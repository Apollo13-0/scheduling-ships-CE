#include "ship.h"
#include <stdio.h>

void printShip(struct Ship b) {
    printf("Tipo de barco: ");
    
    switch(b.type) {
        case NORMAL:
            printf("Normal------>");
            break;
        case PESQUERO:
            printf("Pesquero------>");
            break;
        case PATRULLA:
            printf("Patrulla");
            break;
    }
    
    printf("Velocidad: %i------>", b.speed);
    printf("Prioridad: %i", b.priority);
}
