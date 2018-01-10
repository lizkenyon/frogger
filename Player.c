///////////////////////////////////////////////
//Player.c
//Comp 3430
//A2
//Elizabeth Kenyon
//7739830
///////////////////////////////////////////////

#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "Player.h"
#include "globals.h"
#include "console.h"
#include "list.h"

////////////////////////////////////////////////

#define LEFT -1
#define RIGHT 1
#define MOVEUP -4
#define MOVEUPFINAL -3
#define MOVEDOWN 4
#define STARTX 21
#define STARTY 40
#define ZERO 0
#define EIGHTY 80
#define BOTTOM 24

#define PORT1L 2
#define PORT1R 7
#define PORT2L 19
#define PORT2R 25
#define PORT3L 37
#define PORT3R 43
#define PORT4L 55
#define PORT4R 61
#define PORT5L 73
#define PORT5R 79

#define LIVESCOLUMN 40

#define ROW1 16
#define ROW2 12
#define ROW3 8
#define ROW4 4

#define LOGLENGTH 24

#define PLAYER_ANIM_TILES 2
#define PLAYER_HEIGHT 2


//24 rows 
//80 colums
//x = rows
//y = columns

////////////////////////////////////////////////

static char* PLAYER_GRAPHIC[PLAYER_ANIM_TILES][PLAYER_HEIGHT+1] = {
  {"@@",
   "<>"},
  {"--",
   "<>"}
};

static int port1 = 0;
static int port2 = 0;
static int port3 = 0;
static int port4 = 0;
static int port5 = 0;

static char* loser = "Looooooooser!";
static char* winner = "Winner winner chicken dinner!";
///////////////////////////////////////////////


void movePlayerUp(Player *player){
	if(player != NULL){
		char **tile = PLAYER_GRAPHIC[player->tile];
		clearFrogger(player);
		lockFrogLock();
		if(player->x >= ROW3){
			player->x = player->x + MOVEUP;
		}
		else{
			player->x = player->x + MOVEUPFINAL;
		}
		unlockFrogLock();
		lockDrawLock();
		consoleDrawImage(player->x, player->y, tile, PLAYER_HEIGHT);
		unlockDrawLock();
		isFroggerDead(getPlayer());
	}
}

void movePlayerLeft(Player *player){
	if(player != NULL){
		char **tile = PLAYER_GRAPHIC[player->tile];
		if(player->y != ZERO){
			clearFrogger(player);
			lockFrogLock();
			player->y = player->y + LEFT;
			unlockFrogLock();
			lockDrawLock();
			consoleDrawImage(player->x, player->y, tile, PLAYER_HEIGHT);
			unlockDrawLock();
			isFroggerDead(getPlayer());
		}
	}
}

void movePlayerRight(Player *player){
	if(player != NULL){
		char **tile = PLAYER_GRAPHIC[player->tile];
		if(player->y != EIGHTY){
			clearFrogger(player);
			lockFrogLock();
			player->y = player->y + RIGHT;
			unlockFrogLock();
			lockDrawLock();
			consoleDrawImage(player->x, player->y, tile, PLAYER_HEIGHT);
			unlockDrawLock();
			isFroggerDead(getPlayer());
		}
	}
}

void movePlayerDown(Player *player){
	if(player != NULL){
		char **tile = PLAYER_GRAPHIC[player->tile];
		if(player->x != BOTTOM){
			clearFrogger(player);
			lockFrogLock();
			player->x = player->x + MOVEDOWN;
			unlockFrogLock();
			lockDrawLock();
			consoleDrawImage(player->x, player->y, tile, PLAYER_HEIGHT);
			unlockDrawLock();
			isFroggerDead(getPlayer());
		}

	}
}

void startPlayer(Player *player){
	if(player != NULL){
		lockFrogLock();
		player->x = STARTX;
		player->y = STARTY;
		player->tile = 0;
		unlockFrogLock();
	}
}

void clearFrogger(Player *player){
	lockDrawLock();
	consoleClearImage(player->x, player->y, PLAYER_ANIM_TILES, PLAYER_HEIGHT);
	unlockDrawLock();
}

void drawFrog(Player *player){
	if(player != NULL){
		char** tile = PLAYER_GRAPHIC[1];
		lockDrawLock();
		consoleDrawImage(player->x, player->y, tile, PLAYER_HEIGHT);
		unlockDrawLock();
	}
}

void animateFrog(Player *player){
	if(player != NULL){
		if(player->tile == 0){
			player->tile = 1;
		}
		else{
			player->tile = 0;
		}
		clearFrogger(player);
		lockDrawLock();
		consoleDrawImage(player->x, player->y, PLAYER_GRAPHIC[player->tile], PLAYER_HEIGHT);
		unlockDrawLock();
	}
}


void playerOnLog(Player *player){
	Node *curr = getHead();
	int found = 0;
	if(curr != NULL && player != NULL){
		int row = player->x -1;
		if(row == ROW1 || row == ROW2 || row == ROW3 || row == ROW4){
			int column = player->y;
			while(!found && curr != NULL){
				if(column > curr->log->column && column <= curr->log->column + LOGLENGTH && curr->log->row == row){
					lockListLock();
					curr->log->frog_on = 1;
					unlockListLock();
					found = 1; 
				}
				else{
					curr = curr->next;
				}
			}
			if(found){
				found = 0;
			}
			else{
				frogDead();
			}
		}
	}
}

void playerInPort(Player *player){
	if(player != NULL){
		if(player->x <= 3){
			if(player->y >=PORT5L && player->y<=PORT5R && !port5){
				port1 = 1;
				startPlayer(getPlayer());
			}
			else if(player->y >=PORT1L && player->y<=PORT1R && !port1){
				port2 = 1;
				startPlayer(getPlayer());
			}
			else if(player->y >=PORT2L && player->y<=PORT2R && !port2){
				port3 = 1;
				startPlayer(getPlayer());
			}
			else if(player->y >=PORT3L && player->y<=PORT3R && !port3){
				port4 = 1;
				startPlayer(getPlayer());
			}
			else if(player->y >=PORT4L && player->y<=PORT4R && !port4){
				port5 = 1;
				startPlayer(getPlayer());
			}
			else{
			frogDead();
		    }
		}
	}

}

void isFroggerDead(Player *player){
	if(player != NULL){
		playerOnLog(player);
		playerInPort(player);
		if(player->y >= EIGHTY || player->y <= ZERO){
			frogDead();
		}
	}
}

void frogDead(){
	startPlayer(getPlayer());
	loseLife();

}

void* updateLives(){
	while(isGameOn()){
		int lives = getLives();
		char num_lives[2];
		sprintf(num_lives, "%d", lives);

		lockDrawLock();
		putString(num_lives, ZERO, LIVESCOLUMN, 2);
		unlockDrawLock();

		if(lives <= 0){
			lockDrawLock();
			putBanner(loser);
			disableConsole(1);
			unlockDrawLock();
			gameOff();
		}
		if(port1 && port2 && port3 && port4 && port5){
			lockDrawLock();
			putBanner(winner);
			disableConsole(1);
			unlockDrawLock();
			gameOff();
		}
		quickSleep(50);
	}
	pthread_exit(NULL);

}