CC = gcc

.PHONY: build
build:
	$(CC) Fermat.c -o Fermat
	$(CC) Rabin.c -o Rabin

all: run-best run-p1 run-p2

run-best: Rabin.o
	./Rabin > run-best.txt
	./rabin.sh > run-best-accuracy.txt

run-p1: Fermat.o
	./Fermat > run-p1.txt
	./fermat.sh > run-p1-accuracy.txt

run-p2: Rabin.o
	./Rabin > run-p2.txt
	./rabin.sh > run-p2-accuracy.txt

.PHONY: clean
clean:
	-rm -rf outRabin/
	-rm -rf outFermat/
	-rm -rf Rabin Rabin.o
	-rm -rf Fermat Fermat.o
	-rm -rf run-best.txt run-p1.txt run-p2.txt run-best-accuracy.txt run-p1-accuracy.txt run-p2-accuracy.txt