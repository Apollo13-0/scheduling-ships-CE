#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include "ocean.h"

// First Come First Serve
void fcfs(struct Ocean *ocean);

// Round Robin
void roundRobin(struct Ocean *ocean, int quantum);

// Shortest Job First
void sjf(struct Ocean *ocean);

// Priority
void priorityScheduler(struct Ocean *ocean);

// Real-Time (Para patrullas)
void realTime(struct Ocean *ocean, int maxTime);

#endif // SCHEDULERS_H
