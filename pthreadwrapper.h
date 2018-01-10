
///////////////////////////////////////
//pthreadwrapper.h
//Comp 3430
//A2 Frogger
//Elizabeth Kenyon
//7739830
// Thread wrapper methods for error checking
////////////////////////////////////////

#ifndef PTHREADWRAPPER_H
#define PTHREADWRAPPER_H

/////////////////////////////////////////

void create_pthread(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

void join_pthread(pthread_t thread);

/////////////////////////////////////////

#endif 