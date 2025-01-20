playlife: crossfunc.o crossword.o
	gcc crossfunc.o crossword.o -o runcrossword

lifefunc.o: lifefunc.c lifefunc.h
	gcc -c crossfunc.c -o crossfunc.o

playlife.o: playlife.c lifefunc.h
	gcc -c crossword.c -o crossword.o

clean:
	rm *.o
	rm runcrossword
