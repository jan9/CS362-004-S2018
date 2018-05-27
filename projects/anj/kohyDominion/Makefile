CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o  $(CFLAGS)

unittest2: unittest2.c dominion.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o  $(CFLAGS)
	
unittest3: unittest3.c dominion.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o  $(CFLAGS)
	
unittest4: unittest4.c dominion.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o  $(CFLAGS)
	
cardtest1: cardtest1.c dominion.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o  $(CFLAGS)

cardtest2: cardtest2.c dominion.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o  $(CFLAGS)

cardtest3: cardtest3.c dominion.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o  $(CFLAGS)

cardtest4: cardtest4.c dominion.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o  $(CFLAGS)
	
unittestresults.out: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "ASSIGNMENT 3: UNIT TEST RESULTS" > unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov cardtest1.c -b >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov cardtest2.c -b >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov cardtest3.c -b >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov cardtest4.c -b >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestadventurer: randomtestadventurer.c dominion.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o  $(CFLAGS)
	
randomtestcard1: randomtestcard1.c dominion.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o  $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o  $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o
	gcc -o randomtestcard3 randomtestcard3.c -g dominion.o rngs.o  $(CFLAGS)

randomtestresults.out: randomtestadventurer.c randomtestcard1.c randomtestcard2.c rngs.c
	echo "randomtestadventurer.c:" >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov randomtestadventurer.c -b >> randomtestresults.out
	cat randomtestadventurer.c.gcov >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	
	echo "randomtestcard1.c:" >> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	gcov randomtestcard1.c -b >> randomtestresults.out
	cat randomtestcard1.c.gcov >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

	echo "randomtestcard2.c:" >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov randomtestcard2.c -b >> randomtestresults.out
	cat randomtestcard2.c.gcov >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	
	echo "randomtestcard3.c:" >> randomtestresults.out
	./randomtestcard3 >> randomtestresults.out
	gcov randomtestcard3.c -b >> randomtestresults.out
	cat randomtestcard3.c.gcov >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: randomtestcard1 randomtestcard2 randomtestcard3 randomtestadventurer cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out randomtestresults.out 

clean:
	rm -f *.o *.exe playdom player *.exe  *.gcov *.gcda *.gcno *.so