#include "canal.h"
#include <stdio.h>
#include "ship.h"


/*

===================LISTA ENLAZADA TRABAJA CON INDICE A PARTIR DE 1===================


*/

void init_canal(){

    struct canal c;
    c.canal_length= 5;
    c.canal_list=NULL;
    c.right_queue=NULL;
    c.left_queue=NULL;
    c.max_ships_queue=3;
    
    /*int canal_list[c.canal_length];
    
    int left_queue[c.max_ships_queue];
    int right_queue[c.max_ships_queue];

    c.canal_list=canal_list;
    c.right_queue=right_queue;
    c.left_queue=left_queue;*/
    


    for(int i=0; i<c.canal_length;i++){
        insertAtBeginning(&c.canal_list,0);
    }
    
    
    for(int i=0;i<c.max_ships_queue;i++){
        insertAtBeginning(&c.right_queue,1);
        insertAtBeginning(&c.left_queue,1);
    }

    c.canal_flow_control= EQUIDAD;
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
    /*c.canal_scheduler= user_canal_scheduler;
    
    
    */
    
}


void equidad (struct canal c){
    printf("EQUIDAD\n");
    int w=5;
    int whi=0;
    //======================= 1er for izq der, der izq 
    while(whi<1){//while que mantiene vivo el canal

        //==============================  LEFT------RIGHT=========================
        for(int i=0; i<w;i++){
           //VERIFICA SI EL ULTIMO ES 1
            if(getValue(&c.canal_list,c.canal_length)==1){
                setValue(&c.canal_list, 0, c.canal_length);
            } 

            for(int k=c.canal_length; k>1;k--){//MOVER LOS BARCOS DEL CANAL
                
                //VERIFICA SI LA POSICION K ESTA VACIA PARA AVANZAR
                if(getValue(&c.canal_list,k)==0){
                    int data=getValue(&c.canal_list,k-1);//BARCO ANTERIOR
                    
                    setValue(&c.canal_list, data, k);//METER BARCO ANTERIOR EN POS ACTUAL
                    
                    setValue(&c.canal_list,0 , k-1);//DEJAR VACIA LA POSICION ANTERIOR
                    
                }
                
                else{
                    continue;
                }
            }
            //METER BARCO AL CANAL
            if(getValue(&c.canal_list,1)==0 && c.left_queue!=NULL){
                int data=getValue(&c.left_queue,0);
                
                //insertAtBeginning(&c.canal_list,data);
                setValue(&c.canal_list,data , 1);
                
                deleteAtBeginning(&c.left_queue);
            
            }
            
            
            for(int o = 1; o < c.canal_length+1; o++){
                printf("i: %d, CANAL[%d]: %d\n",i, o,getValue(&c.canal_list,o) );
            } 
            printf("==============================================\n");
            
        }
        //VACIAR EL CANAL SI TODAVÍA HAY BARCOS
        while(getValue(&c.canal_list,c.canal_length)==1){
                setValue(&c.canal_list, 0, c.canal_length);

                for(int k=c.canal_length; k>1;k--){//MOVER LOS BARCOS DEL CANAL
                    //VERIFICA SI LA POSICION K ESTA VACIA PARA AVANZAR
                    if(getValue(&c.canal_list,k)==0){
                        int data=getValue(&c.canal_list,k-1);//BARCO ANTERIOR
                        
                        setValue(&c.canal_list, data, k);//METER BARCO ANTERIOR EN POS ACTUAL
                        
                        setValue(&c.canal_list,0 , k-1);//DEJAR VACIA LA POSICION ANTERIOR
                        
                    }
                    
                    else{
                        continue;
                    }
                }

                for(int o = 1; o < c.canal_length+1; o++){
                printf("i: +w, CANAL[%d]: %d\n", o,getValue(&c.canal_list,o) );
            } 
            printf("==============================================\n");

            } 

        //==============================  RIGHT------LEFT=========================
        printf("\n==================== CAMBIA DE DIRECCION ================\n");
        for(int i=0; i<w;i++){
           //VERIFICA SI EL ULTIMO ES 1
            if(getValue(&c.canal_list,1)==1){
                setValue(&c.canal_list, 0, 1);
            } 

            for(int k=1; k<c.canal_length;k++){//MOVER LOS BARCOS DEL CANAL
                
                //VERIFICA SI LA POSICION K ESTA VACIA PARA AVANZAR
                if(getValue(&c.canal_list,k)==0){
                    int data=getValue(&c.canal_list,k+1);//BARCO ANTERIOR
                    
                    setValue(&c.canal_list, data, k);//METER BARCO ANTERIOR EN POS ACTUAL
                    
                    setValue(&c.canal_list,0 , k+1);//DEJAR VACIA LA POSICION ANTERIOR
                    
                }
                
                else{
                    continue;
                }
            }
            //METER BARCO AL CANAL
            if(getValue(&c.canal_list,c.canal_length)==0 && c.right_queue!=NULL){
                int data=getValue(&c.right_queue,0);
                
                //insertAtBeginning(&c.canal_list,data);
                setValue(&c.canal_list,data , c.canal_length);
                
                deleteAtBeginning(&c.right_queue);
            
            }
            
            
            for(int o = 1; o < c.canal_length+1; o++){
                printf("i: %d, CANAL[%d]: %d\n",i, o,getValue(&c.canal_list,o) );
            } 
            printf("==============================================\n");
            
        }

        //VACIAR EL CANAL SI TODAVÍA HAY BARCOS
        while(getValue(&c.canal_list,1)==1){
                setValue(&c.canal_list, 0, 1);

                for(int k=1; k<c.canal_length;k++){//MOVER LOS BARCOS DEL CANAL
                
                //VERIFICA SI LA POSICION K ESTA VACIA PARA AVANZAR
                if(getValue(&c.canal_list,k)==0){
                    int data=getValue(&c.canal_list,k+1);//BARCO ANTERIOR
                    
                    setValue(&c.canal_list, data, k);//METER BARCO ANTERIOR EN POS ACTUAL
                    
                    setValue(&c.canal_list,0 , k+1);//DEJAR VACIA LA POSICION ANTERIOR
                    
                }
                
                else{
                    continue;
                }
            }

                for(int o = 1; o < c.canal_length+1; o++){
                printf("i: +w, CANAL[%d]: %d\n", o,getValue(&c.canal_list,o) );
            } 
            printf("==============================================\n");

            }





        whi++;
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