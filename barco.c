#include "barco.h"
#include <stdio.h>

void imprimirBarco(struct Barco b) {
    printf("Tipo de barco: ");
    
    switch(b.tipo) {
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
    
    printf("Velocidad: %i\n", b.velocidad);
}
