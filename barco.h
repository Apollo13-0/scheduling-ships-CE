#ifndef BARCO_H
#define BARCO_H

typedef enum {
    NORMAL,
    PESQUERO,
    PATRULLA
} TipoBarco;

struct Barco {
    TipoBarco tipo;
    int velocidad;
};

void imprimirBarco(struct Barco b);

#endif // BARCO_H
