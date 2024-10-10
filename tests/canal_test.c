#include "canal_test.h"
#include <stdio.h>

void canalTest() {

    struct canal canal1;
    
    init_canal(&canal1);

    print_canal(&canal1);
    printf("==============================================\n");
    
    struct Ship ship1 = {NORMAL, 10, 1};
    struct Ship ship2 = {PESQUERO, 5, 2};
    struct Ship ship3 = {PATRULLA, 15, 3};

    printf("Adding ships to left ocean\n");
    addShip(&canal1.left_ocean, ship1);
    addShip(&canal1.left_ocean, ship2);
    addShip(&canal1.left_ocean, ship3);

    struct Ship ship4 = {NORMAL, 6, 1};
    struct Ship ship5 = {PESQUERO, 12, 2};
    struct Ship ship6 = {PATRULLA, 18, 3};

    printf("Adding ships to right ocean\n");
    addShip(&canal1.right_ocean, ship4);
    addShip(&canal1.right_ocean, ship5);
    addShip(&canal1.right_ocean, ship6);

    //printf("===========INICIANDO EQUIDAD===============\n");
    //equidad(&canal1, 3);
    tico(&canal1);
}    


// if (strcmp(userData->scheduler, "FCFS") == 0) {
    //     c.right_ocean=fcfs(&rightO);
    //     c.left_ocean=fcfs(&leftO);
    // } else if (strcmp(userData->scheduler, "RR") == 0) {
    //     c.right_ocean=roundRobin(&rightO,10);
    //     c.left_ocean=roundRobin(&leftO,10);
    // }else if (strcmp(userData->scheduler, "SJF") == 0) {
    //     printf("SJF\n");
    //     c.right_ocean=sjf(&rightO);
    //     c.left_ocean=sjf(&leftO);
        
    // }else if (strcmp(userData->scheduler, "PRIORITY") == 0) {
    //     c.right_ocean=priorityScheduler(&rightO);
    //     c.left_ocean=priorityScheduler(&leftO);
        
    // }else if (strcmp(userData->scheduler, "RT") == 0) {
    //     c.right_ocean=realTime(&rightO,5);
    //     c.left_ocean=realTime(&leftO,5);
        
    // }
    // else{
    //     printf("NO VALID SHEDULER \n");
    // }




    // for(int i=0;i<c.max_ships_queue;i++){
        
    //     struct Ship s;
    //     insertAtBeginning(&c.right_ocean,s,1);
    //     insertAtBeginning(&c.left_ocean,s,1);
    // }
    // //strcpy(userData->controlMethod, controlMethod->valuestring);
    // //c.canal_flow_control=userData->controlMethod;//
    
    // if (strcmp(userData->controlMethod, "EQUIDAD") == 0) {
    //     c.canal_flow_control= EQUIDAD;
    //     equidad(c,userData->W);
    // } else if (strcmp(userData->controlMethod, "LETRERO") == 0) {
    //     c.canal_flow_control= LETRERO;
    //     letrero(c,userData->controlSignTime);
    // }else if (strcmp(userData->controlMethod, "TICO") == 0) {
    //     c.canal_flow_control= TICO;
    //     tico(c);
        
    // }else{
    //     printf("NO VALID CONTROL METHOD \n");
    // }