#include "mutex_test.h"
#include <stdio.h>
#include <unistd.h>

mutex_t mutex;
int shared = 0;

void* threadFunction(void* arg) {
    CEmutex_lock(&mutex);  // Bloquear el mutex

    // Simular algún trabajo
    for(int i = 0; i < 1000000; i++) {
        shared++;
    }

    int result = shared;
    printf("Hilo ejecutándose con argumento: %d y con resultado: %d\n", *(int*)arg, shared);
    CEmutex_unlock(&mutex);  // Desbloquear el mutex
    return (void*)(long)result;    // Retornar el resultado
}

int mutexTest() {

    thread_t my_thread;
    thread_t my_thread2;
    thread_t my_thread3;

    int arg1 = 1;
    int arg2 = 2;
    int arg3 = 3;

    CEmutex_init(&mutex);  // Inicializar el mutex

    CEthread_create(&my_thread, threadFunction, &arg1);
    CEthread_create(&my_thread2, threadFunction, &arg2);
    CEthread_create(&my_thread3, threadFunction, &arg3);

    CEthread_join(&my_thread, NULL);
    CEthread_join(&my_thread2, NULL);
    CEthread_join(&my_thread3, NULL);

    free(my_thread.stack);
    free(my_thread2.stack);
    free(my_thread3.stack);

    return 0;
}
