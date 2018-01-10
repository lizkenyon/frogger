///////////////////////////////////////////////////////////////
/* GAME GLOBALS
/ gameGlobals.h
/Comp 3430 
/A2
/Elizaeth Kenyon
/ A file to keep track of all globals needed for the game.
// As well as to handle error checking.
*/////////////////////////////////////////////////////////////

#ifndef GLOBALS_H
#define GLOBALS_H

#include "Player.h"

#define MUTEX_NORMAL PTHREAD_MUTEX_NORMAL

static pthread_mutexattr_t attribute_norm;
static pthread_mutex_t draw_lock;
static pthread_mutex_t refresh_lock;
static pthread_mutex_t game_on_lock;
static pthread_mutex_t list_lock;
static pthread_cond_t game_on_cv;

//////////////////////////////
Player* getPlayer();

void mallocPlayer();

void updatePlayer(Player *this_player);

void freePlayer();
//////////////////////////////

void loseLife();

int getLives();

/////////////////////////////

void initializeDrawLock();

void lockDrawLock();

void unlockDrawLock();

void destroyDrawLock();

/////////////////////////////


void initializeFrogLock();

void lockFrogLock();

void unlockFrogLock();

void destroyFrogLock();

//////////////////////////

void initializeGameOnCV();

void destroyGameOnCV();

void signalGameOnCV();

void waitGameOnCV();

/////////////////////////

void initializeGameOnLock();

void lockGameOnLock();

void unlockGameOnLock();

void destroyGameOnLock();

/////////////////////////////

void initializeListLock();

void lockListLock();

void unlockListLock();

void destroyListLock();

////////////////////////////////


void initializeLogCountLock();

void lockLogCountLock();

void unlockLogCountLock();

void destroyLogCountLock();

////////////////////////////////
 
 void initializePlayerLivesLock();

void lockPlayerLivesLock();

void unlockPlayerLivesLock();

void destroyPlayerLivesLock();

////////////////////////////////

int isGameOn();

void gameOff();

////////////////////////////////

void quickSleep(int num);

///////////////////////////////

void addLogCount();


#endif 
