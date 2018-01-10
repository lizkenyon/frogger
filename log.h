/////////////////////////////////////////////
//log.h
//Comp 3430
//A2
//Elizabeth Kenyon
////////////////////////////////////////////


#ifndef LOG_H
#define LOG_H

//////////////////////////////////////////

typedef struct LOG Log;

///////////////////////////////////////////

struct LOG{
	int row;
	int column;
	int tile;
	pthread_t thread;
	int frog_on;
};

//////////////////////////////////////

//Move log one postion depending on the row the log is in
void moveLog(Log *log);

//Animate log given the current position
void animateLog(Log *log);

//Set the log to postion given row and column
void initializeLog(Log *log, int row, int column);

//clears position where log is
void clearLog(Log *log);

//creates a log given the row is should be in, rows 1-4
Log* createLog(int row);

//Moves and animates the log depending on the row.
void* logDuties(void *log);

void frogLogDuties(Log *log);

//Moves through list of logs and deletes any that are off screen
void* cleanUpLogs();

//helper method to check if log is off screen
int isOffScreen(Log *log);

///////////////////////////////////////

#endif 
