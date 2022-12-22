CC = gcc
CFLAG = -o

.PHONY: build
build:
	$(CC) Fermat.c $(CFLAG) Fermat
	$(CC) Rabin.c $(CFLAG) Rabin
	$(CC) FermatTest.c $(CFLAG) FermatTest
	$(CC) RabinTest.c $(CFLAG) RabinTest

all: run-all-best run-all-p1 run-all-p2

test: run-best run-p1 run-p2

run-best: RabinTest
	./RabinTest > run-test-best.txt

run-p1: FermatTest
	./FermatTest > run-test-p1.txt

run-p2: RabinTest
	./RabinTest > run-test-p2.txt

run-all-best: Rabin
	./Rabin > run-all-best.txt
	./rabin.sh > run-all-best-accuracy.txt

run-all-p1: Fermat
	./Fermat > run-all-p1.txt
	./fermat.sh > run-all-p1-accuracy.txt

run-all-p2: Rabin
	./Rabin > run-all-p2.txt
	./rabin.sh > run-all-p2-accuracy.txt

.PHONY: clean
clean:
	-rm -rf outRabin/ outFermat/
	-rm -rf Rabin RabinTest Fermat FermatTest
	-rm -rf run-all-best.txt run-all-p1.txt run-all-p2.txt run-test-best.txt run-test-p1.txt run-test-p2.txt
	-rm -rf run-all-best-accuracy.txt run-all-p1-accuracy.txt run-all-p2-accuracy.txt