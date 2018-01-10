///////////////////////////////////////
//pthreadwrapper.c
//Comp 3430
//A2 Frogger
//Elizabeth Kenyon
// Thread wrapper methods for error checking
////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "pthread.h"

///////////////////////////////////////////

void create_pthread(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg){
	int rc;
	rc = pthread_create(thread, attr, start_routine, arg);
	if(rc){
	   printf("ERROR-return code from pthread_create() is %d\n", rc);
       exit(EXIT_FAILURE);
	}
}

void join_pthread(pthread_t thread){
	int rc;
	rc = pthread_join(thread, NULL);
	if(rc != 0){
		perror("Error in pthread join");
		exit(EXIT_FAILURE);
	}
}
