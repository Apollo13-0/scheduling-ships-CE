#include "canal.h"
#include <stdio.h>
#include "ship.h"



void init_canal(){

    struct canal c;
    /*c.canal_scheduler= user_canal_scheduler;
    c.canal_flow_control= user_canal_flow_control;
    c.canal_lenght= user_canal_lenght;
    int canal[c.canal_lenght];
    c.max_ships_queue=user_max_ships_queue;
    int left_queue[max_ships_queue];
    int right_queue[max_ships_queue];

    switch(c.canal_flow_control) {
        case EQUIDAD:
            equidad(c);
            break;
        case LETRERO:
            letrero(c);
            break;
        case TICO:
            tico(c);
            break;
    }

    */
    
}



int equidad (struct canal c){
    printf("EQUIDAD\n");
    //int w=user_w;
    //======================= 1er for izq der, der izq 
    while(true){

        for(int i=0; i<w;i++){
            if (){

            }
        }

        for(int o=0; o<w;o++){
            if (){

            }
        }
    }
    



    
    return 0;   
}

int letrero (struct canal c){
    printf("LETRERO\n");
    //int sign_time=user_sign_time;
    return 0;   
}

int tico (struct canal c){
    printf("TICO\n");
    //inventarme el tico
    return 0;   
}


void letPass(ship ship, int direction){
    //DIRECTION =0 : LEFT--->RIGHT
    //DIRECTION =1 : RIGHT--->LEFT
    if(direction==1){

    }else{

    }


}


void print_canal(struct canal c){
     printf("Canal info: \n");
     printf("Scheduler: \n");
    
    switch(c.canal_scheduler) {
        case RR:
            printf("RR\n");
            break;
        case PRIORITY:
            printf("PRIORITY\n");
            break;
        case SJF:
            printf("SJF\n");
            break;
        case FCFS:
            printf("FCFS\n");
            break;
        case REAL_TIME:
            printf("REAL_TIME\n");
            break;
    }

    switch(c.canal_flow_control) {
        case EQUIDAD:
            printf("EQUIDAD\n");
            break;
        case LETRERO:
            printf("LETRERO\n");
            break;
        case TICO:
            printf("TICO\n");
            break;
    }

    
    printf("Canal lenght: %i\n", c.canal_length);
    printf("Canal max queue: %i\n", c.max_ships_queue);
}