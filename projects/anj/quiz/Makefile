##############################################################################
# File: Makefile
# Author: Ju An
# Date: 5/3/2018
# Description: A makefile that creates compile and executes the testme.c file
##############################################################################

CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c 
	gcc -o testme testme.c -g  $(CFLAGS)
	./testme

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno
