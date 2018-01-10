//////////////////////////////////////////////
//log.c
//Comp 3430
//A2
//Elizabeth Kenyon
/////////////////////////////////////////////

#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "list.h"
#include "Player.h"
#include "globals.h"
#include "console.h"
#include "pthreadwrapper.h"

//////////////////////////////////////////

#define MOVERIGHT 1
#define MOVELEFT -1
#define ROW1 16
#define ROW2 12
#define ROW3 8
#define ROW4 4
#define STARTCOLUMN1 -20
#define STARTCOLUMN2 100
#define ZERO 0
#define LOG_HEIGHT 4
#define LOG_LENGTH 24
#define LOG_ANIM_TILES 2
#define SPEEDMODIFIER 2
#define MINCOL -25
#define MAXCOL 100

//24 rows 
//80 colums



////////////////////////////////////////

static char* LOG_GRAPHIC[LOG_ANIM_TILES][LOG_HEIGHT +1]= {
	{"|======================|",
	"+                      +",
	"+                      +",
	"|======================|"},

	{"|======================|",
	"|                      |",
	"|                      |",
	"|======================|"}
};

/////////////////////////////////////////

void moveLog(Log *log){
	if(log != NULL){

		char **tile = LOG_GRAPHIC[log->tile];
		lockDrawLock();
		clearLog(log);
		if(log->row == ROW1 || log->row == ROW3){
			log->column = (log->column + MOVERIGHT);
		}
		else{
			log->column = log->column + MOVELEFT;
		}
		consoleDrawImage(log->row, log->column, tile, LOG_HEIGHT);
		unlockDrawLock();
	}
}

void animateLog(Log *log){
	if(log != NULL){
		if(log->tile == 0){
			log->tile = 1;
		}
		else{
			log->tile = 0;
		}
		lockDrawLock();
		clearLog(log);
		consoleDrawImage(log->row, log->column, LOG_GRAPHIC[log->tile], LOG_HEIGHT);
		unlockDrawLock();
	}
}

void initializeLog(Log *log, int row, int column){
	if(log != NULL){
		log->row = row;
		log->column = column;
		log->tile = 0; 
	}
}

void clearLog(Log *log){
	consoleClearImage(log->row, log->column, LOG_HEIGHT, LOG_LENGTH);
}

Log* createLog( int row){
	Log *newLog = (Log*)malloc(sizeof(Log));
	if(row > 0 && row < 5){
		if(newLog != NULL){
			if(row == 1){
				initializeLog(newLog, ROW1, STARTCOLUMN1);
			}
			else if(row == 3){
				initializeLog(newLog, ROW3, STARTCOLUMN1);
			}
			else if(row == 2){
				initializeLog(newLog, ROW2, STARTCOLUMN2);
			}
			else if(row == 4){
				initializeLog(newLog, ROW4, STARTCOLUMN2);
			} 
			lockListLock();
			insert(newLog);
			unlockListLock();
		}
	}
	return newLog;
}

void* logDuties( void * log){
	Log *this_log = (Log *)log;
	int row;
	if(this_log != NULL){
		row = this_log->row;
		while(isGameOn()){

			if(this_log->frog_on == 1){
				Player *currPlayer = getPlayer();
				int oldRow = currPlayer->x;
				int row = this_log->row;
				moveLog(this_log);
				if(row == ROW1 || row == ROW3){
					movePlayerRight(currPlayer); 
				}
				else{
					movePlayerLeft(currPlayer);
				}
				quickSleep(row/SPEEDMODIFIER);
				animateLog(this_log);
				if(currPlayer->x != oldRow || currPlayer->y < this_log->column || currPlayer->y > this_log->column + LOG_LENGTH){
					this_log->frog_on = 0;
				}
			}
			else{  
				moveLog(this_log);
				quickSleep(row/SPEEDMODIFIER);
				animateLog(this_log);
				if(isOffScreen(this_log)){
					pthread_exit(NULL);
					{}
				}

			}
		}
		pthread_exit(NULL);
	}
	return 0;
}

void* cleanUpLogs(){
	Node *node = getHead();
	Node *nextNode;
	while(isGameOn()){
		if(node != NULL){
			if(isOffScreen(node->log)){
				join_pthread(node->log->thread);
				lockListLock();
				deleteNode(node);
				unlockListLock();
			}
			node = node->next;
		}
		else{
			node = getHead();
		}
		sleepTicks(1);
	}
	node = getHead();
	while(node != NULL){
		if(node->next != NULL){
		nextNode = node->next;
		join_pthread(node->log->thread);
		lockListLock();
		deleteNode(node);
		unlockListLock();
		node = nextNode;
	  }
	  else{
	  	lockListLock();
	  	deleteNode(node);
	  	unlockListLock();
	  	node = NULL; 
	  } 
	} 
	pthread_exit(NULL);
}

int isOffScreen(Log *log){
	int ret = 0;
	if(log != NULL){
		if(log->row == ROW1 || log ->row == ROW3){
			if(log->column > MAXCOL){
				ret = 1;
			}
		}
		else{
			if(log->column < MINCOL){
				ret = 1;
			}
		}
	}
	return ret; 
}

/////////////////////////////////////////////////
