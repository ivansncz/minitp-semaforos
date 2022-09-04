#include <stdio.h>
#include <stdlib.h>    
#include <string.h>

#include <pthread.h>
#include <semaphore.h>


#include <unistd.h>     // para hacer sleep

sem_t D;
sem_t A;
sem_t B;
sem_t C;
int a=0;
int b=0;
int c=0;
char equipoA []="equipo a";
char equipoB []="equipo b";
char equipoC []="equipo c";
char ganador [];

void* funcionGanador(){
sem_wait(&D);
if (ganador[0]=='\0' && a==2){
    
        strcpy (ganador,equipoA);
        printf("elganadores , %s  ",ganador);   
}
if(ganador[0]=='\0' && b==2){

        strcpy (ganador,equipoB);
        printf("elganadores , %s",ganador); 
}
if(ganador[0]=='\0' && c==2){

        strcpy (ganador,equipoC);
        printf("elganadores , %s",ganador); 
}

sem_post(&D);
}


void* funcionB ()
{ 
   int i;
   sem_wait(&B);
   for(i=0; i < 214748300 ; i++ ){    

   }      
   b += 1;
   funcionGanador();
   sem_post(&B); 
   pthread_exit(NULL);
}


void* funcionA ()
{ 
   int k;
   sem_wait(&A);
   for(k=0; k < 214748300 ; k++ ){    

   }      
a += 1;
   funcionGanador();
   sem_post(&A);
   pthread_exit(NULL);
}



void* funcionC ()
{ 
   int j;
   sem_wait(&C);
   for(j=0; j < 214748300 ; j++ ){    

   }      
   c +=1;
   funcionGanador();
   sem_post(&C); 
   pthread_exit(NULL);
} 




  int main(int argc , char *argv []) {
   pthread_t threadA;
   pthread_t threadB;
   pthread_t threadC;
   pthread_t threadA2;
   pthread_t threadC2;
   pthread_t threadB2; 

   sem_init(&D,0,1);
   sem_init(&A,0,1);
   sem_init(&B,0,1);      //inicializo semaforos
   sem_init(&C,0,1);


   pthread_create(&threadA,NULL,funcionA,NULL);
   pthread_create(&threadB,NULL,funcionB,NULL);  // lanzo los threads que simbolizarian 1er participante de equipo
   pthread_create(&threadC,NULL,funcionC,NULL);
   pthread_create(&threadA2,NULL,funcionA,NULL);
   pthread_create(&threadB2,NULL,funcionB,NULL);  // lanzo los threads que simbolizarian 2do participante de equipo     
   pthread_create(&threadC2,NULL,funcionC,NULL);


   pthread_join(threadA , NULL);
   pthread_join(threadB , NULL);
   pthread_join(threadC , NULL);
  
   pthread_join(threadA2,NULL);
   pthread_join(threadB2,NULL);
   pthread_join(threadC2,NULL);


   //destruir los semaforos
   sem_destroy(&A);
   sem_destroy(&B);
   sem_destroy(&C);
   sem_destroy(&D);



   pthread_exit(NULL);
}