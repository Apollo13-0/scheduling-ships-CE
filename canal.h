#ifndef CANAL_H
#define CANAL_H
#include "linkedList.h"
#include "ocean.h"



typedef enum {
    EQUIDAD,
    LETRERO,
    TICO
} canal_flow_control;


struct canal {
    canal_flow_control canal_flow_control;
    int canal_length;
    int max_ships_queue;
    Node* canal_list;
    struct Ocean left_ocean;
    struct Ocean right_ocean;

};

void equidad (struct canal *c, int w);
void print_canal(struct canal *c);
void init_canal(struct canal *c);

#endif

