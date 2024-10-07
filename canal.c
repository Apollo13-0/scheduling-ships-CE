#include "canal.h"
#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include <time.h>
#include "config-file/config.h"


/*

===================LISTA ENLAZADA TRABAJA CON INDICE A PARTIR DE 1===================


*/

void init_canal(){
     UserData* userData = NULL;
    userData=initUserData();
    struct canal c;
    c.canal_length=userData->canalLength;//c.canal_length= 5;
    c.canal_list=NULL;
    c.right_queue=NULL;
    c.left_queue=NULL;
    c.max_ships_queue=userData->amountShipsInQ;//c.max_ships_queue=3;
    

    for(int i=0; i<c.canal_length;i++){
        struct Ship s ;
        insertAtBeginning(&c.canal_list,s,0);
    }
    
    
    for(int i=0;i<c.max_ships_queue;i++){
        struct Ship s;
        insertAtBeginning(&c.right_queue,s,1);
        insertAtBeginning(&c.left_queue,s,1);
    }
    //strcpy(userData->controlMethod, controlMethod->valuestring);
    //c.canal_flow_control=userData->controlMethod;//
    
    if (strcmp(userData->controlMethod, "EQUIDAD") == 0) {
        c.canal_flow_control= EQUIDAD;
        equidad(c,userData->W);
    } else if (strcmp(userData->controlMethod, "LETRERO") == 0) {
        c.canal_flow_control= LETRERO;
        letrero(c,userData->controlSignTime);
    }else if (strcmp(userData->controlMethod, "TICO") == 0) {
        c.canal_flow_control= TICO;
        tico(c);
        
    }else{
        printf("NO VALID CONTROL METHOD \n");
    }
    
}


void equidad (struct canal c, int w){
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
    



    
    return 0;   
}

int letrero (struct canal c,int sign_time){
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

int tico (struct canal c){
    srand(time(NULL));
    printf("TICO\n");
    int dir = rand() % 2;
    int data=-1;
    
    if(dir==0){//EMPTY RIGHT QUEUE (MOVE ALL TO LEFT), FIRST LEFT<<-------RIGHT
        printf("PRIMERO HACIA IZQ\n");
        while(1){
            for (int s=1;s<=c.max_ships_queue;s++){
                if(getValue(&c.right_queue,s)==1 ){
                    data=getValue(&c.right_queue,s);
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
            for (int s=1;s<=c.max_ships_queue;s++){
                if(getValue(&c.left_queue,s)==1 ){
                    data=getValue(&c.left_queue,s);
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
            for (int s=1;s<=c.max_ships_queue;s++){
                if(getValue(&c.left_queue,s)==1 ){
                    data=getValue(&c.left_queue,s);
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
            for (int s=1;s<=c.max_ships_queue;s++){
                if(getValue(&c.right_queue,s)==1 ){
                    data=getValue(&c.right_queue,s);
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


void moveToLeft(struct canal c, int vaciando){
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
    if(getValue(&c.canal_list,c.canal_length)==0 && c.right_queue!=NULL && vaciando!=1){
        int data=-1;
        for (int s=1;s<=c.max_ships_queue;s++){
            if(getValue(&c.right_queue,s)==1 ){
                data=getValue(&c.right_queue,s);
                setValue(&c.right_queue,0,s);
                break;
            }else{
                data=-1;
            }
        }
        if(data!=-1){
            printf("METE BARCO\n");
            setValue(&c.canal_list,data ,  c.canal_length);
        }
    
    }
    
    
    for(int o = 1; o < c.canal_length+1; o++){
        printf("CANAL[%d]: %d\n", o,getValue(&c.canal_list,o) );
    } 
    printf("==============================================\n");


}
void moveToRight(struct canal c,int vaciando){
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
    if(getValue(&c.canal_list,1)==0 && c.left_queue!=NULL && vaciando!=1){
        int data=-1;
        for (int s=0;s<=c.max_ships_queue;s++){
            if(getValue(&c.left_queue,s)==1 ){
                data=getValue(&c.left_queue,s);
                setValue(&c.left_queue,0,s);
                break;
            }else{
                data=-1;
            }
        }
        if(data!=-1){
            printf("METE BARCO\n");
            setValue(&c.canal_list,data , 1);
        }
    
    }
    
    
    for(int o = 1; o < c.canal_length+1; o++){
        printf("CANAL[%d]: %d\n",o,getValue(&c.canal_list,o) );
    } 
    printf("==============================================\n");


}

void emptyLeft(struct canal c){
    printf("VACIANDO IZQ\n");
    int data=-1;
    while(1){
            for (int s=1;s<=c.canal_length;s++){
                if(getValue(&c.canal_list,s)==1 ){
                    data=getValue(&c.canal_list,s);
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

void emptyRight(struct canal c){
    printf("VACIANDO DER\n");
    int data=-1;
    while(1){
            for (int s=1;s<=c.canal_length;s++){
                if(getValue(&c.canal_list,s)==1 ){
                    data=getValue(&c.canal_list,s);
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

void print_canal(struct canal c){
     printf("Canal info: \n");
     printf("Scheduler: \n");
    

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