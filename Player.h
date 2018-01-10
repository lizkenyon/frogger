///////////////////////////////////////////////
//Player.h
//Comp 3430
//A2
//Elizabeth Kenyon
//7739830
///////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H

//////////////////////////////////////////

typedef struct PLAYER Player;

///////////////////////////////////////////

struct PLAYER{
	int x;
	int y;
	int tile;
};

//////////////////////////////////////

//Controls the player animation until game off
void *player_animation();

//moves player upwards on screen
void movePlayerUp(Player *player);

//moves player left on screen
void movePlayerLeft(Player *player);

//moves player right on screen
void movePlayerRight(Player *player);

//moves player down on screen
void movePlayerDown(Player *player);

// moves player to starting postion 
void startPlayer(Player *player);

//clears the player from the screen
void clearFrogger(Player *player);

//checks to see if the player is currently on a log,
//and sets the log to have the player if this is true.
void playerOnLog(Player *player);

//draws the player on the screen at its current position
void drawFrog(Player *player);

void animateFrog(Player *player);

//performs actions that must occur when frogger dies
void frogDead();

//checks to see if the frog is in a "valid" position
void isFroggerDead(Player *player);

void* updateLives();

///////////////////////////////////////

#endif 