all : main

ex2.o : ex2.c
	gcc -c -std=c99 ex2.c -o ex2.o -O2

mem.o : mem.s
	gcc -c mem.s -o mem.o

main : ex2.o mem.o
	gcc ex2.o mem.o 
