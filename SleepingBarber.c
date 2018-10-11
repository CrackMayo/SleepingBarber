#include<stdio.h>     
#include<stdlib.h>    
#include<unistd.h>    
#include<pthread.h>   
#include<semaphore.h> 
#include<sys/ipc.h>
#include<errno.h>



sem_t clientes;
sem_t barberos;
sem_t mutex;


int clientesEspera=0; 	
int numSillas; 	


void P(sem_t *s);
void V(sem_t *s);


void P(sem_t *s){

	if(sem_wait(s)<0){
		printf("sem_wait error \n");
		exit(0);
	}
}

void V(sem_t *s){

	if(sem_post(s)<0){
		printf("sem_post error \n");
		exit(0);
	}
}



void barbero(void *args){
	while(1){
		P(&clientes); 
		P(&mutex); 	
		clientesEspera--; 	
		V(&barberos); 	
		V(&mutex); 	
		printf("Barbero afeitando, (clientes en espera: %d)\n",clientesEspera);
		sleep(3);		

	}
}


