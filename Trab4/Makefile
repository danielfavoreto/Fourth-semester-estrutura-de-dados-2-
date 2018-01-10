all: compile

compile:
	
	gcc gera.c -c -O0 -g3 -Wall -fmessage-length=0 -std=c99
	gcc utility.c -c -O0 -g3 -Wall -fmessage-length=0 -std=c99
	gcc trab4.c -c -O0 -g3 -Wall -fmessage-length=0 -std=c99
	gcc gera.o -Wall -g -lm -o gera
	gcc utility.o trab4.c -Wall -g -lm -o trab4
run:
		
	./trab4
	
clean:
	rm trab4 gera.o
		
