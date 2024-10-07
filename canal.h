#ifndef CANAL_H
#define CANAL_H
#include "linkedList.h"



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
    Node* left_queue;
    Node* right_queue;

};

void print_canal(struct canal c);
void init_canal();

#endif

