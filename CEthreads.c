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

    // Marcar el hilo como en ejecucion
    thread->state = THREAD_RUNNING;
    //printf("Hilo %lu está corriendo. Estado: %d (THREAD_RUNNING)\n", thread->tid, thread->state);
    // Ejecutar la función asignada al hilo
    thread->retval = thread->proc(thread->arg);
    // Marcar el hilo como terminado
    thread->state = THREAD_FINISHED;
    //printf("Hilo %lu ha terminado. Estado: %d (THREAD_FINISHED)\n", thread->tid, thread->state);

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

    //printf("Hilo %lu ha sido creado. Estado: %d (THREAD_READY)\n", thread->tid, thread->state);

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

void CEmutex_init(mutex_t *mutex){
    mutex->locked = 0;
}

void CEmutex_lock(mutex_t *mutex) {
    while (__sync_lock_test_and_set(&mutex->locked, 1)) {
        // Busy waiting
    }
}

void CEmutex_unlock(mutex_t *mutex) {
    __sync_lock_release(&mutex->locked);
}

void CEmutex_destroy(mutex_t *mutex) {
    free(mutex);
}
