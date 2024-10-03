// CEthreads.c
#include "CEthreads.h"
#include <ucontext.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ucontext_t main_context;  // Contexto principal

// Función que ejecuta la rutina del hilo
void thread_start(thread_t *thread) {
    // Ejecutar la función del hilo
    thread->retval = thread->proc(thread->arg);
    // Marcar el hilo como finalizado
    thread->state = THREAD_FINISHED;
    // Cambiar de vuelta al contexto principal
    setcontext(&main_context);
}

int CEthread_create(thread_t* thread, void* (*start_routine)(void*), void* arg) {
    // Inicializar el identificador del hilo
    static cethread_t tid_counter = 1;
    thread->tid = tid_counter++;
    thread->state = THREAD_READY;  // El hilo está listo para ejecutarse
    thread->proc = start_routine;  // Asignar la función del hilo
    thread->arg = arg;             // Asignar el argumento

    // Asignar una pila al hilo
    thread->stack = malloc(STACK_SIZE);
    if (thread->stack == NULL) {
        return -1;  // Error al asignar la pila
    }

    // Asignar memoria para el contexto del hilo
    thread->ucp = (ucontext_t *) malloc(sizeof(ucontext_t));
    if (thread->ucp == NULL) {
        free(thread->stack);
        return -1;  // Error al asignar el contexto
    }

    // Obtener el contexto actual y guardarlo en el nuevo hilo
    if (getcontext(thread->ucp) == -1) {
        free(thread->stack);
        free(thread->ucp);
        return -1;  // Error al obtener el contexto
    }

    // Configurar el contexto del hilo para que use la nueva pila
    thread->ucp->uc_stack.ss_sp = thread->stack;
    thread->ucp->uc_stack.ss_size = STACK_SIZE;
    thread->ucp->uc_link = &main_context;  // Volver al contexto principal cuando termine

    // Configurar el contexto del hilo para que ejecute la función `thread_start`
    makecontext(thread->ucp, (void (*)(void))thread_start, 1, thread);

    return 0;  // Hilo creado con éxito
}

void CEthread_end(){
    printf("CEthread_end\n");
}

int CEthread_join(thread_t* thread, void** retval) {
    // Cambiar al contexto del hilo para que se ejecute
    swapcontext(&main_context, thread->ucp);

    // Al volver aquí, el hilo debe haber terminado
    if (thread->state == THREAD_FINISHED && retval != NULL) {
        *retval = thread->retval;  // Retornar el valor de retorno del hilo
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