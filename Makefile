
all:	frogger
frogger: frogger.c Player.c log.c list.c globals.c console.c pthreadwrapper.c 
	clang -Wall frogger.c Player.c log.c list.c globals.c console.c pthreadwrapper.c  -lcurses -pthread -o FROGGER
clean:
	rm -f *.o FROGGER 
