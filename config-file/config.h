#ifndef CONFIG_H
#define CONFIG_H

// sudo apt install libcjson1 libcjson-dev

typedef struct userData {
    char* controlMethod;    // Método de control de flujo
    char* scheduler;        // Calendarizador para oceanos
    int canalLength;        // Largo del canal en metros
    int shipSpeed;          // Velocidad del barco en m/s
    int amountShipsInQ;     // Cantidad de barcos en la cola
    int controlSignTime;    // Tiempo en segundos
    int W;                  // Parámetro W
} UserData;

UserData* initUserData(); // Cambiado para retornar un puntero
void printUserData(); // Cambiado para recibir un puntero
void freeUserData(); // Función para liberar la memoria

#endif
