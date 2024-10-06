#ifndef CETHREADS_H
#define CETHREADS_H

#include <ucontext.h>

#define STACK_SIZE 8192  // Tamaño de la pila para el hilo
#define THREAD_READY  0  // Hilo listo para ejecutarse
#define THREAD_RUNNING 1  // Hilo en ejecución
#define THREAD_FINISHED 2  // Hilo terminado

typedef unsigned long int cethread_t;

typedef struct Thread_t
{
    cethread_t tid; 		// thread id
	void * stack;			// stack of the thread
    cethread_t joining; 	// thread id of the thread that is joining this thread
    int state;				// state of the thread
    void* (*proc)(void*);	// function to be executed by the thread
    void* arg;				// argument to be passed to the function
    void* retval;			// return value of the thread
    ucontext_t* ucp; 		// context of the thread
} thread_t;  

typedef struct Mutex_t
{
    int locked; // 0: unlocked, 1: locked
} mutex_t;

/*
	CEthread_t: thread identifier
	start_routine: function to be executed by the thread
	arg: argument to be passed to the function
*/

int CEthread_create(thread_t * thread,void *(*start_routine) (void *), void *arg);

// retval: return value of the thread
void CEthread_end(thread_t* thread);

// thread: thread to be joined
// retval: return value of the thread
int CEthread_join(thread_t* thread, void **retval);

// mutex: mutex to be initialized
// mutexattr: mutex attributes
void CEmutex_init(mutex_t *mutex);

//mutex: mutex to be locked
void CEmutex_lock(mutex_t *mutex);

// mutex: mutex to be destroyed
void CEmutex_destroy(mutex_t *mutex);

// mutex: mutex to be unlocked
void CEmutex_unlock(mutex_t *mutex);

#endif // CETHREADS_H