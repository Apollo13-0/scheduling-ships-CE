#include "thread_test.h"
#include <stdio.h>

#include <unistd.h> 

void* thread_function(void* arg) {
    sleep(*(int*)arg);
    printf("Hilo ejecutándose con argumento: %d\n", *(int*)arg);
    int result = *(int*)arg + 10;  // Simular algún trabajo
    return (void*)(long)result;    // Retornar el resultado
}

int hiloTest() {

    thread_t my_thread;
    thread_t my_thread2;
    thread_t my_thread3;

    int arg = 4;
    int arg2 = 1;
    int arg3 = 2;

    void* retval;
    void* retval2;

    // Crear el hilo
    if (CEthread_create(&my_thread, thread_function, &arg) != 0) {
        printf("Error al crear el hilo\n");
        return 1;
    }

    if (CEthread_create(&my_thread2, thread_function, &arg2) != 0) {
        printf("Error al crear el hilo\n");
        return 1;
    }

    if (CEthread_create(&my_thread3, thread_function, &arg3) != 0) {
        printf("Error al crear el hilo\n");
        return 1;
    }

    // Esperar a que el hilo termine
    CEthread_join(&my_thread, &retval);
    CEthread_join(&my_thread2, &retval2);
    CEthread_join(&my_thread3, &retval2);

    // Mostrar el valor de retorno del hilo
    printf("El hilo 1 retornó: %ld\n", (long)retval);
    printf("El hilo 2 retornó: %ld\n", (long)retval2);

    // Liberar la memoria de la pila y el contexto
    free(my_thread.stack);
    //free(my_thread.ucp);
    free(my_thread2.stack);
    //free(my_thread2.ucp);
    free(my_thread3.stack);
    //free(my_thread3.ucp);


    return 0;
}
