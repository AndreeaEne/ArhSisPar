
#make - cheama comiplatorul conform instructiunilor din Makefile 

#cateva variabile de mediu

#C Compiler
CC = /usr/bin/gcc

#Flaguri de compilare
CFLAGS = -O2

#Biblioteci externe
CLIBS = -lgslcblas -lgsl -lm

#Actiuni
#biblioteca libgp
lgp:gplot1.h gplot1.c
	$(CC) -c -o gplot.o -I. -fPIC gplot1.c
	$(CC) -shared -o libgp.so gplot.o
#am facut o noua biblioteca denumita lgp

ex:gplot1.h
	$(CC) -o prog ex1.c ${CLIBS} -I. -L. -lgp
	
clean: 
	rm -f gplot.o libgp.so prog
	
	