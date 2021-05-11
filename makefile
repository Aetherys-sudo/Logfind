CFLAGS = -g -Wall -DNDEBUG

logfind: logfind.o
	cc $(CFLAGS) logfind.c -o logfind
	

clean: 
	rm logfind.o logfind
