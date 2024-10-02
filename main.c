#include "barco.h"

void pruebaBarco() {

    Barco barco1 = {NORMAL, 10.0};
    Barco barco2 = {PESQUERO, 15.0};
    Barco barco3 = {PATRULLA, 20.0};

    imprimirBarco(barco1);
    imprimirBarco(barco2);
    imprimirBarco(barco3);
}


int main() {
    //Si quieren realizar pruebas en el main, crear una función aparte y llamarlas aquí
    pruebaBarco();

    return 0;
}
