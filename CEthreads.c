// CEthreads.c
#define _GNU_SOURCE
#include "CEthreads.h"
#include <ucontext.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>


// Función que ejecuta la rutina del hilo
int thread_start(void* arg) {
    thread_t *thread = (thread_t*) arg;
    // Ejecutar la función asignada al hilo
    thread->retval = thread->proc(thread->arg);
    // Marcar el hilo como terminado
    thread->state = THREAD_FINISHED;
    // Finalizar el proceso del hilo
    _exit(0);
}

int CEthread_create(thread_t* thread, void* (*start_routine)(void*), void* arg) {
    // Inicializar el identificador del hilo
    static cethread_t tid_counter = 1;
    thread->tid = tid_counter++;
    thread->state = THREAD_READY;  // El hilo está listo para ejecutarse
    thread->proc = start_routine;  // Asignar la función del hilo
    thread->arg = arg;             // Asignar el argumento

    // Asignar memoria para la pila del hilo
    thread->stack = malloc(STACK_SIZE);
    if (thread->stack == NULL) {
        return -1;  // Error al asignar la pila
    }

    // Crear el hilo utilizando clone
    thread->tid = clone(thread_start, thread->stack + STACK_SIZE, CLONE_VM | CLONE_FS | CLONE_FILES | SIGCHLD, thread);
    if (thread->tid == -1) {
        free(thread->stack);  // Liberar la memoria si falla
        return -1;            // Error al crear el hilo
    }

    return 0;  // Hilo creado con éxito
}

void CEthread_end(thread_t* thread) {
    // liberar recursos
    free(thread->stack);
}

int CEthread_join(thread_t* thread, void** retval) {
    // Esperar a que el hilo hijo termine
    waitpid(thread->tid, NULL, 0);

    // Si se espera un valor de retorno, asignarlo
    if (thread->state == THREAD_FINISHED && retval != NULL) {
        *retval = thread->retval;
    }

    return 0;
}
void CEmutex_init(){
    printf("CEmutex_init\n");
}

void CEmutex_destroy(){
    printf("CEmutex_destroy\n");
}

void CEmutex_unlock(){
    printf("CEmutex_unlock\n");
}