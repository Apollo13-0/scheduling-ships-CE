#include "canal.h"
#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include <time.h>
#include "config-file/config.h"
#include "schedulers.h"


/*

===================LISTA ENLAZADA TRABAJA CON INDICE A PARTIR DE 1===================


*/

void init_canal(struct canal *c){
    UserData* userData =  initUserData();

    //Comparar char* de userData->controlMethod para asignar el valor de canal_flow_control
    if (strcmp(userData->controlMethod, "EQUIDAD") == 0) {
        c->canal_flow_control= EQUIDAD;
    } else if (strcmp(userData->controlMethod, "LETRERO") == 0) {
        c->canal_flow_control= LETRERO;
    }else if (strcmp(userData->controlMethod, "TICO") == 0) {
        c->canal_flow_control= TICO;
    }else{
        printf("NO VALID CONTROL METHOD \n");
    }

    c->canal_length=userData->canalLength;//c.canal_length= 5;
    c->max_ships_queue=userData->amountShipsInQ;//c.max_ships_queue=3;
    c->canal_list=NULL;

    struct Ocean leftO;
    leftO.ships=NULL;
    leftO.side=0;
    c->left_ocean=leftO;

    struct Ocean rightO;
    rightO.ships=NULL;
    rightO.side=1;
    c->right_ocean=rightO;


    for(int i=0; i<c->canal_length;i++){
        struct Ship s ;
        insertAtBeginning(&c->canal_list,s,0);
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
}


void equidad (struct canal *c, int w){
    printf("EQUIDAD W: %d\n",w);
    //int w=5;
    int whi=0;
    //======================= 1er for izq der, der izq 
    while(whi<2){//while que mantiene vivo el canal

        //==============================  LEFT------RIGHT=========================
        for(int i=0; i<w;i++){
           //VERIFICA SI EL ULTIMO ES 1
            moveToRight(c,0);
            
        }
        emptyRight(c);

        //==============================  RIGHT------LEFT=========================
        printf("\n==================== CAMBIA DE DIRECCION ================\n");
        for(int i=0; i<w;i++){
           moveToLeft(c,0);
            
        }
        emptyLeft(c);
        


        whi++;
    }
    return;   
}


int letrero (struct canal *c,int sign_time){
    printf("LETRERO TIME: %d\n",sign_time);
    //float sign_time=0.00009;//user_sign_time;
    int whi=0;
    time_t before,after,difference;
    float elapsedTime=0;
    while(whi<1){//MANTIENE EL CANAL ACTIVO
        
        before=time(NULL);

        while(sign_time>elapsedTime){//MOVE RIGHT
            
            moveToRight(c,0);
            after=time(NULL);
            
            difference=after-before;
            
            elapsedTime=((float)(difference));
            
        }
        
        emptyRight(c);
        before=0;
        after=0;
        elapsedTime=0;
        before=time(NULL);
        while(sign_time>elapsedTime){//MOVE LEFT
            moveToLeft(c,0);
            after=time(NULL);
            
            difference=after-before;

            
            elapsedTime=((double)(difference));


        }
        emptyLeft(c);
        before=0;
        after=0;
        elapsedTime=0;



        
        whi++;
    }


    return 0;   
}

int tico (struct canal *c){
    srand(time(NULL));
    printf("TICO\n");
    int dir = rand() % 2;
    int data=-1;
    
    if(dir==0){//EMPTY RIGHT QUEUE (MOVE ALL TO LEFT), FIRST LEFT<<-------RIGHT
        printf("PRIMERO HACIA IZQ\n");
        while(1){
            for (int s=1;s<=c->max_ships_queue;s++){
                if(getValue(&c->right_ocean,s)==1 ){
                    data=getValue(&c->right_ocean,s);
                    break;
                }else{
                    data=-1;
                }
            }

            if(data==-1){
                printf("VACIANDO CANAL\n");
                emptyLeft(c);
                break;
            }
            moveToLeft(c,0);
            

        }

        while(1){
            for (int s=1;s<=c->max_ships_queue;s++){
                if(getValue(&c->left_ocean,s)==1 ){
                    data=getValue(&c->left_ocean,s);
                    break;
                }else{
                    data=-1;
                }
            }

            if(data==-1){
                printf("VACIANDO CANAL\n");
                emptyRight(c);
                break;
            }
            moveToRight(c,0);
            

        }
        



    }else{//EMPTY RIGHT QUEUE, FIRST LEFT------->>RIGHT
        printf("PRIMERO HACIA DERECHA\n");
        while(1){
            printf("test\n");
            for (int s=1;s<=c->max_ships_queue;s++){
                if(getValue(&c->left_ocean,s)==1 ){
                    data=getValue(&c->left_ocean,s);
                    break;
                }else{
                    data=-1;
                }
            }

            if(data==-1){
                printf("VACIANDO CANAL\n");
                emptyRight(c);
                break;
            }
            moveToRight(c,0);
        }

        while(1){
            for (int s=1;s<=c->max_ships_queue;s++){
                if(getValue(&c->right_ocean,s)==1 ){
                    data=getValue(&c->right_ocean,s);
                    break;
                }else{
                    data=-1;
                }
            }

            if(data==-1){
                printf("VACIANDO CANAL\n");
                emptyLeft(c);
                break;
            }
            moveToLeft(c,0);
            

        }

    }

    return 0;   
}


void moveToLeft(struct canal *c, int vaciando){
    //VERIFICA SI EL ULTIMO ES 1
    if(getValue(&c->canal_list,1)==1){
        setValue(&c->canal_list, 0, 1);
        struct Ship emptyShip;
        emptyShip.priority=-1;
        emptyShip.speed=-1;

        setShip(&c->canal_list, emptyShip, 1);
    } 

    for(int k=1; k<c->canal_length;k++){//MOVER LOS BARCOS DEL CANAL
        
        //VERIFICA SI LA POSICION K ESTA VACIA PARA AVANZAR
        if(getValue(&c->canal_list,k)==0){
            int data=getValue(&c->canal_list,k+1);//ESPACIO ANTERIOR
            struct Ship s =getShip(&c->canal_list,k+1);
            
            setValue(&c->canal_list, data, k);//METER BARCO ANTERIOR EN POS ACTUAL
            setShip(&c->canal_list, s, k);

            setValue(&c->canal_list,0 , k+1);//DEJAR VACIA LA POSICION ANTERIOR
            struct Ship emptyShip;
            emptyShip.priority=0;
            emptyShip.speed=0;

            setShip(&c->canal_list, emptyShip, k+1);
        }
        
        else{
            continue;
        }
    }
    //METER BARCO AL CANAL
    if(getValue(&c->canal_list,c->canal_length)==0 && c->right_ocean.ships!=NULL && vaciando!=1){
        int data=-1;
        struct Ship sh;
        for (int s=1;s<=c->max_ships_queue;s++){
            if(getValue(&c->right_ocean,s)==1 ){
                data=getValue(&c->right_ocean,s);
                sh=getShip(&c->right_ocean,s);
                setValue(&c->right_ocean,0,s);
                break;
            }else{
                data=-1;
            }
        }
        if(data!=-1){
            printf("METE BARCO\n");
            setValue(&c->canal_list,data ,  c->canal_length);
            setShip(&c->canal_list,sh,  c->canal_length);
            
        }
    
    }
    
    printf("test\n");
    printListForward(c->canal_list);/*
    for(int o = 1; o < c->canal_length+1; o++){
        printf("CANAL[%d]: %d --> ", o,getValue(&c->canal_list,o) );
        printf("TIPO: %s  PRIORIDAD: %d\n",getShip(&c->canal_list,o).type, getShip(&c->canal_list,o).priority);
        //printShip(getShip(&c->canal_list,o));
    } */
    printf("==============================================\n");


}
void moveToRight(struct canal *c,int vaciando){
    if(getValue(&c->canal_list,c->canal_length)==1){
        struct Ship emptyShip;
        emptyShip.priority=-1;
        emptyShip.speed=-1;

        setShip(&c->canal_list, emptyShip, c->canal_length);
        setValue(&c->canal_list, 0, c->canal_length);
    } 

    for(int k=c->canal_length; k>1;k--){//MOVER LOS BARCOS DEL CANAL
        
        //VERIFICA SI LA POSICION K ESTA VACIA PARA AVANZAR
        if(getValue(&c->canal_list,k)==0){
            int data=getValue(&c->canal_list,k-1);//BARCO ANTERIOR
            struct Ship s =getShip(&c->canal_list,k-1);
            
            setValue(&c->canal_list, data, k);//METER BARCO ANTERIOR EN POS ACTUAL
            setShip(&c->canal_list, s, k);
            setValue(&c->canal_list,0 , k-1);//DEJAR VACIA LA POSICION ANTERIOR
            struct Ship emptyShip;
            emptyShip.priority=0;
            emptyShip.speed=0;

            setShip(&c->canal_list, emptyShip, k-1);
        }
        
        else{
            continue;
        }
    }
    
    //METER BARCO AL CANAL
    if(getValue(&c->canal_list,1)==0 && c->left_ocean.ships!=NULL && vaciando!=1){
        int data=-1;
        struct Ship sh;
        for (int s=1;s<=c->max_ships_queue;s++){
            if(getValue(&c->left_ocean,s)==1 ){
                data=getValue(&c->left_ocean,s);
                sh=getShip(&c->left_ocean,s);
                setValue(&c->left_ocean,0,s);
                break;
            }else{
                data=-1;
            }
        }
        if(data!=-1){
            printf("METE BARCO\n");
            setValue(&c->canal_list,data , 1);
            setShip(&c->canal_list,sh,  1);
        }
    
    }
    
    printf("test\n");
    printListForward(c->canal_list);
    
    /*for(int o = 1; o < c->canal_length+1; o++){
        printf("CANAL[%d]: %d --> ",o,getValue(&c->canal_list,o));
        printf("TIPO: %s  PRIORIDAD: %d\n",getShip(&c->canal_list,o).type, getShip(&c->canal_list,o).priority);
        //printShip(getShip(&c->canal_list,o));
    } */
    printf("==============================================\n");


}

void emptyLeft(struct canal *c){
    printf("VACIANDO IZQ\n");
    int data=-1;
    while(1){
            for (int s=1;s<=c->canal_length;s++){
                if(getValue(&c->canal_list,s)==1 ){
                    data=getValue(&c->canal_list,s);
                    break;
                }else{
                    data=-1;
                }
            }

            if(data==-1){
                break;
            }
            moveToLeft(c,1);

        }
}

void emptyRight(struct canal *c){
    printf("VACIANDO DER\n");
    int data=-1;
    while(1){
            for (int s=1;s<=c->canal_length;s++){
                if(getValue(&c->canal_list,s)==1 ){
                    data=getValue(&c->canal_list,s);
                    break;
                }else{
                    data=-1;
                }
            }

            if(data==-1){
                break;
            }
            moveToRight(c,1);

        }
}

void print_canal(struct canal *c){
     printf("Canal info: \n");
     printf("Scheduler: \n");
    

    switch(c->canal_flow_control) {
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

    
    printf("Canal lenght: %i\n", c->canal_length);
    printf("Canal max queue: %i\n", c->max_ships_queue);
}