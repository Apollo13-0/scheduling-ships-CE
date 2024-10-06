#include "thread_test.h"
#include <stdio.h>
#include <unistd.h> 

// Función del hilo que utiliza CEthread_end al finalizar
void* thread_function(void* arg) {
    sleep(*(int*)arg);
    printf("Hilo ejecutándose con argumento: %d\n", *(int*)arg);

    int result = *(int*)arg + 10;  // Simular algún trabajo

    // Finalizar el hilo y retornar el resultado usando CEthread_end
    CEthread_end((void*)(long)result);  // Retorna el resultado de esta manera
}

int hiloTest() {
    thread_t my_thread;
    thread_t my_thread2;

    int arg = 4;
    int arg2 = 1;

    void* retval;
    void* retval2;

    // Crear el primer hilo
    if (CEthread_create(&my_thread, thread_function, &arg) != 0) {
        printf("Error al crear el hilo\n");
        return 1;
    }

    // Crear el segundo hilo
    if (CEthread_create(&my_thread2, thread_function, &arg2) != 0) {
        printf("Error al crear el hilo\n");
        return 1;
    }

    // Esperar a que los hilos terminen
    CEthread_join(&my_thread, &retval);
    CEthread_join(&my_thread2, &retval2);

    // Mostrar los valores de retorno de los hilos
    printf("El hilo 1 retornó: %ld\n", (long)retval);
    printf("El hilo 2 retornó: %ld\n", (long)retval2);

    return 0;
}
