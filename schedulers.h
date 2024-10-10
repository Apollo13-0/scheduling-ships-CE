#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include "ocean.h"
//#include "linkedList.h"

// Declaración de los algoritmos de calendarización
Node* fcfs(struct Ocean *ocean);
Node* roundRobin(struct Ocean *ocean, int quantum);
Node* sjf(struct Ocean *ocean);
Node* priorityScheduler(struct Ocean *ocean);
Node* realTime(struct Ocean *ocean, int maxTime);

#endif // SCHEDULERS_H
