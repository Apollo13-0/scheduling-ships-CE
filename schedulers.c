#include "schedulers.h"
#include <stdio.h>
#include <stdlib.h>

void fcfs(struct Ocean *ocean) {
    const char *sideStr = (ocean->side == 0) ? "Left" : "Right";
    printf("FCFS order from the %s ocean:\n", sideStr);
    for (int i = 0; i < ocean->numShips; i++) {
        printShip(ocean->ships[i]);
    }
}

void roundRobin(struct Ocean *ocean, int quantum) {
    printf("Round Robin order (quantum = %d):\n", quantum);
    
    int remainingShips = ocean->numShips;           // Número de barcos pendientes por cruzar
    int *remainingTime = malloc(ocean->numShips * sizeof(int));  // Tiempo restante de cada barco

    // Inicializar el tiempo restante para cada barco (igual a la velocidad, que sería el "trabajo total")
    for (int i = 0; i < ocean->numShips; i++) {
        remainingTime[i] = ocean->ships[i].speed;  // Usamos "speed" como el tiempo que toma cruzar el canal
    }

    // Mientras haya barcos que necesiten cruzar
    while (remainingShips > 0) {
        //Recorremos todos los barcos
        for (int i = 0; i < ocean->numShips; i++) {
            if (remainingTime[i] > 0) {  //Si el barco aún tiene tiempo pendiente (aún no ha terminado de cruzar)
                
                // Se decide cuánto tiempo le vamos a dar al barco, puede ser el quantum completo o el tiempo restante
                int timeToUse = (remainingTime[i] > quantum) ? quantum : remainingTime[i];

                //El barco "utiliza" su tiempo para cruzar el canal
                printf("Ship #%d crosses for %d time units\n", i + 1, timeToUse);
                
                //Reducimos el tiempo restante de ese barco
                remainingTime[i] -= timeToUse;

                // **Cambio de contexto:** Aquí es donde se hace el cambio, porque después de este punto,
                // otro barco puede empezar a cruzar, ya que hemos "pausado" el cruce de este barco.
                // Si no ha terminado, tendrá que esperar a su siguiente turno.
                
                if (remainingTime[i] == 0) {  // Si el barco terminó de cruzar
                    remainingShips--;  // Decrementamos el número de barcos restantes
                    printf("Ship #%d has finished crossing\n", i + 1);
                }
                
                // **Cambio de contexto:** Después de esta iteración, se pasa al siguiente barco
                // en la lista (i.e., el siguiente proceso en ejecución).
            }
        }
    }

    // Liberamos la memoria usada para el tiempo restante
    free(remainingTime);
}

int compareBySpeed(const void *a, const void *b) {
    struct Ship *shipA = (struct Ship *)a;
    struct Ship *shipB = (struct Ship *)b;
    return shipA->speed - shipB->speed;
}

void sjf(struct Ocean *ocean) {
    const char *sideStr = (ocean->side == 0) ? "Left" : "Right";
    printf("SJF order from the %s ocean (Shortest Job First):\n", sideStr);
    qsort(ocean->ships, ocean->numShips, sizeof(struct Ship), compareBySpeed);
    for (int i = 0; i < ocean->numShips; i++) {
        printShip(ocean->ships[i]);
    }
}

int compareByPriority(const void *a, const void *b) {
    struct Ship *shipA = (struct Ship *)a;
    struct Ship *shipB = (struct Ship *)b;
    return shipB->priority - shipA->priority;
}

void priorityScheduler(struct Ocean *ocean) {
    const char *sideStr = (ocean->side == 0) ? "Left" : "Right";
    printf("Priority order from the %s ocean:\n", sideStr);
    qsort(ocean->ships, ocean->numShips, sizeof(struct Ship), compareByPriority);
    for (int i = 0; i < ocean->numShips; i++) {
        printShip(ocean->ships[i]);
    }
}

void realTime(struct Ocean *ocean, int maxTime) {
    const char *sideStr = (ocean->side == 0) ? "Left" : "Right";
    printf("Real-Time order from the %s ocean (maxTime = %d):\n", sideStr, maxTime);
    for (int i = 0; i < ocean->numShips; i++) {
        if (ocean->ships[i].type == PATRULLA) {
            if (ocean->ships[i].speed <= maxTime) {
                printf("Patrol ship #%d from the %s ocean crosses in %d time units\n", i + 1, sideStr, ocean->ships[i].speed);
            } else {
                printf("Warning: Patrol ship #%d from the %s ocean cannot cross within the maximum time\n", i + 1, sideStr);
            }
        } else {
            printf("Ship #%d from the %s ocean is not a patrol ship, ignored by real-time scheduler\n", i + 1, sideStr);
        }
    }
}
