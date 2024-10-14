#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include "CEthreads.h"
#include "ship.h"
#include "canal.h"
#include "config-file/config.h"


struct canal mainCanal;
UserData* userConfig;
int exitFlag = 0;
mutex_t queueMutex;

void *shipThread(){
    printf("Se ejecula el hilo de barco\n");
}

void addShipToQueue(int side, char *type) {
    CEmutex_lock(&queueMutex);
    //printf("Aqui tengo que agregar logica para meter barcos a cola\n");
    struct Ship newShip;
    if (strcmp(type, "Normal") == 0) {
        newShip.type = NORMAL;
        newShip.speed = 10;
        newShip.priority = 1;
    } else if (strcmp(type, "Pesquero") == 0) {
        newShip.type = PESQUERO;
        newShip.speed = 5;
        newShip.priority = 2;
    } else if (strcmp(type, "Patrulla") == 0) {
        newShip.type = PATRULLA;
        newShip.speed = 15;
        newShip.priority = 3;
    }

    thread_t newThread;
    CEthread_create(&newThread, shipThread, NULL);

    newShip.thread = newThread;

    if (side == 0) {
        addShip(&mainCanal.left_ocean, newShip);
    } else {
        addShip(&mainCanal.right_ocean, newShip);
    }

    CEmutex_unlock(&queueMutex);
    return;
}

// Función para generar barcos manualmente con teclas
void *keyboardInputHandler(void *arg) {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch;
    while (!exitFlag) {
        ch = getchar();
        if (ch == 'y') { // Tecla 'l' para agregar un barco al lado izquierdo
            addShipToQueue(0, "Normal");
            printf("Barco normal agregado al lado izquierdo\n");
        } else if (ch == 'u') { // Tecla 'r' para agregar un barco al lado derecho
            addShipToQueue(1, "Normal");
            printf("Barco normal agregado al lado derecho\n");
        } else if (ch == 'h') {
            addShipToQueue(0, "Pesquero");
            printf("Barco pesquero agregado al lado izquierdo\n");
        } else if (ch == 'j') {
            addShipToQueue(1, "Pesquero");
            printf("Barco pesquero agregado al lado derecho\n");
        } else if (ch == 'n') {
            addShipToQueue(0, "Patrulla");
            printf("Barco patrulla agregado al lado izquierdo\n");
        } else if (ch == 'm') {
            addShipToQueue(1, "Patrulla");
            printf("Barco patrulla agregado al lado derecho\n");
        } else if (ch == 'w') { // Tecla 'w' para terminar el programa
            printf("Finalizando simulación...\n");
            exitFlag = 1;
        }
    }


    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return NULL;
}

// Simulación del cruce de barcos (placeholder)
void *crossingSimulation(void *arg) {
    while (!exitFlag) {
        sleep(1); // Simular el paso del tiempo
        CEmutex_lock(&queueMutex);
        printf("Simulando el cruce de barcos...\n");
        CEmutex_unlock(&queueMutex);
    }
    return NULL;
}

int main() {
    thread_t keyboardThread, simulationThread;

    CEmutex_init(&queueMutex);

    init_canal(&mainCanal);

    userConfig = initUserData();
    printUserData();

    // Modo 1: Generación de barcos predefinidos
    int predefShips;
    printf("¿Desea ingresar barcos predefinidos? (1: Sí, 0: No): ");
    scanf("%d", &predefShips);

    if (predefShips) {
        int shipCount, side;
        char type[10];
        printf("Ingrese el número de barcos predefinidos: ");
        scanf("%d", &shipCount);

        for (int i = 0; (i < shipCount); i++) {
            printf("Ingrese el tipo de barco (Normal/Pesquero/Patrulla): ");
            scanf("%s", type);
            printf("Ingrese el lado del canal (0: Izquierdo, 1: Derecho): ");
            scanf("%d", &side);
            addShipToQueue(side, type);
        }
    } else{
        // Crear hilos para manejar la entrada por teclado y la simulación
        CEthread_create(&keyboardThread, keyboardInputHandler, NULL);
    }

    CEthread_create(&simulationThread, crossingSimulation, NULL);

    // Esperar que finalicen los hilos
    CEthread_join(&keyboardThread, NULL);
    CEthread_join(&simulationThread, NULL);

    printf("Simulación terminada.\n");
    return 0;
}
