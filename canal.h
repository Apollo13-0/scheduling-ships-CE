#ifndef CANAL_H
#define CANAL_H



typedef enum {
    RR,
    PRIORITY,
    SJF,
    FCFS,
    REAL_TIME
} canal_scheduler;

typedef enum {
    EQUIDAD,
    LETRERO,
    TICO
} canal_flow_control;


struct canal {
    canal_scheduler canal_scheduler;
    canal_flow_control canal_flow_control;
    int canal_length;
    int max_ships_queue;

};

void print_canal(struct canal c);
void init_canal(struct canal c);

#endif

