#include "barco.h"

void pruebaBarco() {

    struct Barco barco1 = {NORMAL, 10};
    struct Barco barco2 = {PESQUERO, 15};
    struct Barco barco3 = {PATRULLA, 20};

    imprimirBarco(barco1);
    imprimirBarco(barco2);
    imprimirBarco(barco3);
}


int main() {
    //Si quieren realizar pruebas en el main, crear una función aparte y llamarlas aquí
    pruebaBarco();

    return 0;
}
