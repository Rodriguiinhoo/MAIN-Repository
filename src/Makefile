all: prog

funcoes.o: funcoes.h  dados.h funcoes.c
	gcc -c funcoes.c

prog: funcoes.o main.c
	gcc funcoes.o main.c -o prog

run: 
	./prog
	
clean: 
	rm *.o prog