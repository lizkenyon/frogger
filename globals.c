///////////////////////////////////////////////////////////////
/* GAME GLOBALS
/ globals.c
/Comp 3430 
/A2
/Elizaeth Kenyon
/ A file to keep track of all globals needed for the game.
// As well as to handle error checking.
*/////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "console.h"
#include "Player.h"

#define MUTEX_NORMAL PTHREAD_MUTEX_NORMAL

static pthread_mutexattr_t attribute_norm;
static pthread_mutex_t draw_lock;
static pthread_mutex_t refresh_lock;
static pthread_mutex_t game_on_lock;
static pthread_mutex_t list_lock;
static pthread_mutex_t log_count_lock;
static pthread_mutex_t player_live_lock;
static pthread_cond_t game_on_cv;

static int game_on = 1;
static int player_lives = 4;

Player *player;

int ret;

/////////////////////////////////////////////////////////////
Player* getPlayer(){
	return player;
}

void updatePlayer(Player *this_player){
	player->x = this_player->x;
	player->y = this_player->y;
	player->tile = this_player->tile;
}

void mallocPlayer(){
	player = malloc(sizeof(Player));
}

void freePlayer(){
	free(player);
}
//////////////////////////////////////////////////////////

void initializePlayerLivesLock(){
	int ret;
	ret = pthread_mutexattr_init(&attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex attribute");
	}
	ret = pthread_mutexattr_settype(&attribute_norm, MUTEX_NORMAL);
	if(ret != 0){
		perror("Error setting mutex");
	}
	ret = pthread_mutex_init(&player_live_lock, &attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex");
	}
}

void lockPlayerLivesLock(){
	int ret;
	ret = pthread_mutex_lock(&player_live_lock);
	if(ret != 0){
		perror("Error locking");
	}
}

void unlockPlayerLivesLock(){
	int ret;
	ret = pthread_mutex_unlock(&player_live_lock);
	if(ret != 0){
		perror("error unlocking mutex");
	}
}

void destroyPlayerLivesLock(){
	int ret;
	ret = pthread_mutex_destroy(&player_live_lock);
	if(ret != 0){
		perror("error destroying mutex");
	}
}

/////////////////////////////////////////////////////////////

void loseLife(){
	lockPlayerLivesLock();
	player_lives--;
	unlockPlayerLivesLock();
}

int getLives(){
	return player_lives;
}

//////////////////////////////////////////////////////////////

void initializeDrawLock(){
	int ret;
	ret = pthread_mutexattr_init(&attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex attribute");
	}
	ret = pthread_mutexattr_settype(&attribute_norm, MUTEX_NORMAL);
	if(ret != 0){
		perror("Error setting mutex");
	}
	ret = pthread_mutex_init(&draw_lock, &attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex");
	}
}

void lockDrawLock(){
	int ret;
	ret = pthread_mutex_lock(&draw_lock);
	if(ret != 0){
		perror("Error locking");
	}
}

void unlockDrawLock(){
	int ret;
	ret = pthread_mutex_unlock(&draw_lock);
	if(ret != 0){
		perror("error unlocking mutex");
	}
}

void destroyDrawLock(){
	int ret;
	ret = pthread_mutex_destroy(&draw_lock);
	if(ret != 0){
		perror("error destroying mutex");
	}
}

////////////////////////////////////////////////////

void initializeFrogLock(){
	int ret; 
	ret = pthread_mutexattr_init(&attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex attribute");
	}
	ret = pthread_mutexattr_settype(&attribute_norm, MUTEX_NORMAL);
	if(ret != 0){
		perror("Error setting mutex");
	}
	ret = pthread_mutex_init(&refresh_lock, &attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex");
	}
}

void lockFrogLock(){
	int ret;
	ret = pthread_mutex_lock(&refresh_lock);
	if(ret != 0){
		perror("Error locking");
	}
}

void unlockFrogLock(){
	int ret;
	ret = pthread_mutex_unlock(&refresh_lock);
	if(ret != 0){
		perror("error unlocking mutex");
	}
}

void destroyFrogLock(){
	int ret;
	ret = pthread_mutex_destroy(&refresh_lock);
	if(ret != 0){
		perror("error destroying mutex");
	}
}

////////////////////////////////////////////////////////

void initializeGameOnCV()
{
	ret = pthread_cond_init(&game_on_cv, NULL);
	if(ret != 0){
		perror("Error initializing game_on");
		exit(EXIT_FAILURE);
	}
}

void destroyGameOnCV(){
	ret = pthread_cond_destroy(&game_on_cv);
	if(ret != 0){
		perror("Error destroying game_on");
		exit(EXIT_FAILURE);
	}
}

void signalGameOnCV(){
	pthread_cond_signal(&game_on_cv);
}

void waitGameOnCV(){
	pthread_cond_wait(&game_on_cv, &game_on_lock);
}

////////////////////////////////////////////////////////
void initializeGameOnLock(){
	int ret;
	ret = pthread_mutexattr_init(&attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex attribute");
	}
	ret = pthread_mutexattr_settype(&attribute_norm, MUTEX_NORMAL);
	if(ret != 0){
		perror("Error setting mutex");
	}
	ret = pthread_mutex_init(&game_on_lock, &attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex");
	}
}

void lockGameOnLock(){
	int ret;
	ret = pthread_mutex_lock(&game_on_lock);
	if(ret != 0){
		perror("Error locking");
	}
}

void unlockGameOnLock(){
	int ret;
	ret = pthread_mutex_unlock(&game_on_lock);
	if(ret != 0){
		perror("error unlocking mutex");
	}
}

void destroyGameOnLock(){
	int ret;
	ret = pthread_mutex_destroy(&game_on_lock);
	if(ret != 0){
		perror("error destroying mutex");
	}
}

//////////////////////////////////////////////////////////

void initializeListLock(){
	int ret;
	ret = pthread_mutexattr_init(&attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex attribute");
	}
	ret = pthread_mutexattr_settype(&attribute_norm, MUTEX_NORMAL);
	if(ret != 0){
		perror("Error setting mutex");
	}
	ret = pthread_mutex_init(&list_lock, &attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex");
	}
}

void lockListLock(){
	int ret;
	ret = pthread_mutex_lock(&list_lock);
	if(ret != 0){
		perror("Error locking");
	}
} 

void unlockListLock(){
	int ret;
	ret = pthread_mutex_unlock(&list_lock);
	if(ret != 0){
		perror("error unlocking mutex");
	}
}

void destroyListLock(){
	int ret;
	ret = pthread_mutex_destroy(&list_lock);
	if(ret != 0){
		perror("error destroying mutex");
	}
}

/////////////////////////////////////////////////////

void initializeLogCountLock(){
	int ret;
	ret = pthread_mutexattr_init(&attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex attribute");
	}
	ret = pthread_mutexattr_settype(&attribute_norm, MUTEX_NORMAL);
	if(ret != 0){
		perror("Error setting mutex");
	}
	ret = pthread_mutex_init(&log_count_lock, &attribute_norm);
	if(ret != 0){
		perror("Error initializing mutex");
	}
}

void lockLogCountLock(){
	int ret;
	ret = pthread_mutex_lock(&log_count_lock);
	if(ret != 0){
		perror("Error locking");
	}
}

void unlockLogCountLock(){
	int ret;
	ret = pthread_mutex_unlock(&log_count_lock);
	if(ret != 0){
		perror("error unlocking mutex");
	}
}

void destroyLogCountLock(){
	int ret;
	ret = pthread_mutex_destroy(&log_count_lock);
	if(ret != 0){
		perror("error destroying mutex");
	}
}

////////////////////////////////////////////////////////

int isGameOn(){
	return game_on;
}

void gameOff(){
	game_on = 0; 
}

/////////////////////////////////////////////////////

void quickSleep(int num){
	int i;
	for(i = 0;i <= num && isGameOn(); i++){
		sleepTicks(1);
	}
}
