#ifndef BARCO_H
#define BARCO_H

typedef enum {
    NORMAL,
    PESQUERO,
    PATRULLA
} TipoBarco;

typedef struct {
    TipoBarco tipo;
    float velocidad;
} Barco;

void imprimirBarco(Barco b);

#endif // BARCO_H
