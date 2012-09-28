
#Descomente caso o default não funcione para o Intel Compiler
#CC = icc

.PHONY: all
all: fase1 fase2 fase3

fase1: fase1.c
	$(CC) -fopenmp -O3 fase1.c -o fase1

fase2: fase2.c
	$(CC) -fopenmp -O3 fase2.c -o fase2

fase3: fase3.c
	$(CC) -pthread -O3 fase3.c -o fase3

.PHONY: clean
clean:
	rm -rf fase1 fase2 fase3
