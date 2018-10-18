menu: menu.o indexFirstEven.o indexLastOdd.o sumBeforeEvenAfterOdd.o sumBetweenEvenOdd.o
	gcc menu.o indexFirstEven.o indexLastOdd.o sumBeforeEvenAfterOdd.o sumBetweenEvenOdd.o -o menu
menu.o: menu.c indexFirstEven.h indexLastOdd.h sumBeforeEvenAfterOdd.h sumBetweenEvenOdd.h
	 gcc -c menu.c
indexFirstEven.o: indexFirstEven.c indexFirstEven.h
	 gcc -c indexFirstEven.c
iindexLastOdd.o: indexLastOdd.c indexLastOdd.h
	gcc -c indexLastOdd.c
sumBeforeEvenAfterOdd.o: sumBeforeEvenAfterOdd.c indexLastOdd.h indexFirstEven.h sumBeforeEvenAfterOdd.h
	gcc -c sumBeforeEvenAfterOdd.c
sumBetweenEvenOdd.o: sumBetweenEvenOdd.c indexLastOdd.h indexFirstEven.h sumBetweenEvenOdd.h
	gcc -c sumBetweenEvenOdd.c

