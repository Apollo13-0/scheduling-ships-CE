#include "config_test.h"

void configTest() {
    UserData* test = initUserData(); // Cambia para recibir un puntero
    test = initUserData(); // Probar Singleton
    printUserData();
    freeUserData(); // Liberar la memoria
}
