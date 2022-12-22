# Identificarea-numerelor-prime

<div align="center"><img src="https://media.tenor.com/E6WFIZg8-sEAAAAC/prime-numbers-power-rangers.gif" width="500px"></div>

## Structura temei

* in/ - director pentru input-uri
* out/ - director pentru ref-uri
* outFermat/ - director cu output-urile programului Fermat.c creat prin rularea comenzilor make build-all și make all
* outRabin/ - director cu output-urile programului Rabin.c creat prin rularea comenzilor make build-all și make all
* 8.pdf - pdf-ul care conține toată tema
* 8.tex - programul latex în care am scris pdf-ul
* Fermat.c - program C pentru testarea tuturor input-urilor din in/
* fermat.sh - script pentru generarea acurateții totale a programului anterior
* FermatTest.c - program C pentru testarea unui singur input
* Makefile
* Rabin.c - program C pentru testarea tuturor input-urilor din in/
* rabin.sh - script pentru generarea acurateții totale a programului anterior
* RabinTest.c - program C pentru testarea unui singur input
* README.md
* test.in - pentru testarea FermatTest / RabinTest
* test.out - output test FermatTest / RebinTest

## Explicații privind implementările

Implementarea pentru Fermat am luat-o de pe : https://www.sanfoundry.com/c-program-perform-fermat-primality-test/
Implementarea pentru Miller-Rabin am luat-o de pe : https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/?ref=lbp
Acestora le-am adăugat mici detalii, precum și funcția main care practic testează un input anume, pentru care calculează
și timpul de execuție cât și memoria consumată în timpul execuției.

Anumite definiții sau descrieri au fost luate de pe site-urile puse în bibliografie, traduse din engleză în română. Prin
urmare este posibil să se mai găsească anumite greșeli gramaticale, greșeli pe care mi le asum.

Înaintea rulării unor comenzi din Makefile, v-aș ruga să vă uitați și în el, deoarece sunt mai multe comenzi, după cum
am zis anterior, pentru testarea tuturor input-urilor, dar și pentru testarea unui singur input.
