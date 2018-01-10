//***************************************
// Comp 3430
// Assignment 2
// Frogger
// Elizabeth Kenyon
//***************************************

#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>

#include "Player.h"
#include "console.h"
#include "pthreadwrapper.h"
#include "globals.h"
#include "log.h"

/////////////////////////////////////////////

#define GAME_ROWS 24
#define GAME_COLS 80
#define NUM_THREADS 100

/**** DIMENSIONS MUST MATCH the ROWS/COLS */

char *GAME_BOARD[] = {
"                                   Lives:",
"/------\\          /------\\          /------\\          /------\\          /------\\",
"|      |          |      |          |      |          |      |          |      |",
"+      +----------+      +----------+      +----------+      +----------+      +",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"",
"",
"",
"" };

#define PLAYER_ANIM_TILES 2
#define PLAYER_HEIGHT 2
#define LOG_ANIM_TILES 2
#define LOG_HEIGHT 4

static char* quit = "Ya quitter... :(";
int thread_count = 0;
pthread_t threads[NUM_THREADS]; 
pthread_t log_threads[NUM_THREADS];
int game_on = 1;

//Player *player; 

///////////////////////////////Start up and Clean up/////////////////////////////

void initializeLocks()
{
	initializeDrawLock();
	initializeFrogLock();
	initializeGameOnLock();
	initializeListLock();
	initializeLogCountLock();
	initializePlayerLivesLock();

}

void destroyLocks()
{
	destroyDrawLock();
	destroyFrogLock();
	destroyGameOnLock();
	destroyListLock();
	destroyLogCountLock();
	destroyPlayerLivesLock();
}

void JoinThreads(){
	for(int i = 0; i < thread_count; i++){
		join_pthread(threads[i]);
	}
}
////////////////////////////////Keyboard////////////////////////////

void processCommand(char c){
	if(c == 'w'){
		clearFrogger(getPlayer());
		movePlayerUp(getPlayer());
	}
	else if(c == 'a'){
		clearFrogger(getPlayer());
		movePlayerLeft(getPlayer());
	}
	else if(c == 's'){
		clearFrogger(getPlayer());
		movePlayerDown(getPlayer());

	}
	else if(c == 'd'){
		clearFrogger(getPlayer());
		movePlayerRight(getPlayer());

	}
	else if(c == 'q'){
		lockDrawLock();
		putBanner(quit);
		unlockDrawLock();
		disableConsole(1);
		gameOff(); 
		pthread_exit(NULL);

	}
}

void *getKeyboard(){

	fd_set set;
	char command;
	while(isGameOn()){
		FD_ZERO(&set);
		FD_SET(STDIN_FILENO, &set);
		struct timespec timeout = getTimeout(1);
		int ret = pselect(FD_SETSIZE, &set, NULL, NULL, &timeout, NULL);
		if(ret == -1){
			perror("Error in get keyboard");
			exit(EXIT_FAILURE);
		}
		else if(ret > 0){
			command = getchar();

			processCommand(command);
			quickSleep(5);

		}
	}
	pthread_exit(NULL);
}
//////////////////////////Screen////////////////////////////////

void *refresh_screen()
{ 
	while(isGameOn()){
	lockDrawLock();
	consoleRefresh();
	unlockDrawLock();
	quickSleep(5);
   }
   pthread_exit(NULL);
}

void *player_animation()
{
	while(isGameOn()){
		Player *player = getPlayer();
		animateFrog(player);
		quickSleep(25);

	}
		pthread_exit(NULL);
} 

////////////////////Spawn Log Rows///////////////////////////////

void *spawnRow1(){
	int row = 1;
	while(isGameOn()){
		Log* log = createLog(row);
		if(log != NULL){
			create_pthread(&log->thread, NULL, logDuties, (void*)log);
			srand(time(NULL));
			int sleep = rand()%350 + 250;
			quickSleep(sleep);
		}
	}
	pthread_exit(NULL);
}

void *spawnRow2(){
	int row = 2; 
	while(isGameOn()){
		Log* log = createLog(row);
		if(log != NULL){
			create_pthread(&log->thread, NULL, logDuties, (void*)log);

			srand(time(NULL));
			int sleep = rand()%300 +250;
			quickSleep(sleep);
		}
	}
	
	pthread_exit(NULL);
} 

void *spawnRow3(){
	int row = 3;
	while(isGameOn()){
		Log* log = createLog(row);
		if(log != NULL){
			create_pthread(&log->thread, NULL, logDuties, (void*)log);

			srand(time(NULL));
			int sleep = rand()%300 +250;
			quickSleep(sleep);
		}
	}
	
	pthread_exit(NULL);
}

void *spawnRow4(){
	int row = 4;
	while(isGameOn()){
		Log* log = createLog(row);
		if(log != NULL){
			create_pthread(&log->thread, NULL, logDuties, (void*)log);

			srand(time(NULL));
			int sleep = rand()%300 +250;
			quickSleep(sleep);
		}
	}
	
	pthread_exit(NULL);
}  

//////////////////////////////////////////////////////////////

int main (int argc, char * argv[]){

	if (consoleInit(GAME_ROWS, GAME_COLS, GAME_BOARD)){
		initializeLocks();
		initializeGameOnCV();

		mallocPlayer();
		startPlayer(getPlayer()); //initialize player to correct position 
		

		create_pthread(&threads[thread_count], NULL, player_animation, NULL);
		thread_count++;
		create_pthread(&threads[thread_count], NULL, refresh_screen, NULL);
		thread_count++; 
		create_pthread(&threads[thread_count], NULL, getKeyboard, NULL);
		thread_count++;
		create_pthread(&threads[thread_count], NULL, spawnRow1, NULL);
		thread_count++;
		create_pthread(&threads[thread_count], NULL, spawnRow3, NULL);
		thread_count++; 
		create_pthread(&threads[thread_count], NULL, spawnRow2, NULL);
		thread_count++; 
		create_pthread(&threads[thread_count], NULL, spawnRow4, NULL);
		thread_count++;  
		create_pthread(&threads[thread_count], NULL, cleanUpLogs, NULL);
		thread_count++; 
		create_pthread(&threads[thread_count], NULL, updateLives, NULL);
		thread_count++; 
		 //put in some glabal or perhaps the wrapper
		}
	lockGameOnLock();
	while(!isGameOn()){
		waitGameOnCV();
	}
	unlockGameOnLock();

	JoinThreads();

	destroyLocks();

	finalKeypress();

	consoleFinish();

	freePlayer();

	printf("\nDone!\n");

	pthread_exit(NULL);

	return 0;
}
