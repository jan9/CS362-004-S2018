/*
* Author: Ju An
* Date: April 29, 2018
* OSU CS 362 - Assignment 3: Unit Test 1
* This program is a unit test for isGameOver() function in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

// for more detailed results, use NOISY_TEST 1
#define NOISY_TEST 1

// asserttrue function instead of the standard C assert
// if assert is not true return 1
int asserttrue (int testedVal, int expectedVal) 
{
	if (expectedVal == testedVal) {
		#if (NOISY_TEST == 1)
			printf("\n	Actual value: %d, Expected value: %d\n", testedVal, expectedVal);
			printf("\n	PASS (assertion true)\n");
		#endif
		return 0;
	} else {
		#if (NOISY_TEST == 1)
			printf("\n	Actual value: %d, Expected value: %d\n", testedVal, expectedVal);	
			printf("\n	FAIL (assertion false)\n");
		#endif
		return 1;
	}
}

// testing the isGameOver() from dominion.c
int main()
{
    // counts failed tests
	int failure = 0;
    
    // test game variable initialization
    int i;
	int seed = 12321;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
	struct gameState G;

	printf("**********************************************\n");
    printf("Testing -> isGameOver()\n");
	memset(&G, 23, sizeof(struct gameState));   		 // clear the game state
    i = initializeGame(numPlayer, k, seed, &G);   // initialize a new game
	
	// TEST 1: check to see if game is over when there are no more Province cards
	printf("\nTest 1: No more province cards + money supply available\n");
	G.supplyCount[province] = 0;
	G.supplyCount[0] = 1;
	G.supplyCount[1] = 1;
	G.supplyCount[2] = 1;
	failure  += asserttrue (isGameOver(&G), 1); 
	
	// TEST 2: check to see if game is over when there are no more money (copper, silver, AND gold) supply
	printf("\nTest 2: Province cards available + no money supply left\n");
	G.supplyCount[province] = 1;
	G.supplyCount[0] = 0;
	G.supplyCount[1] = 0;
	G.supplyCount[2] = 0;
	failure  += asserttrue (isGameOver(&G), 1); 
	
	// TEST 3: check to see if game is over when both ending conditions are met (no province cards & no money supply)
	printf("\nTest 3: No province cards left and empty money supply\n");
	G.supplyCount[province] = 0;
	G.supplyCount[0] = 0;
	G.supplyCount[1] = 0;
	G.supplyCount[2] = 0;
	failure  += asserttrue (isGameOver(&G), 1); 
	
	// TEST 4: check to see if game is over when one of three money supply is still available
	printf("\nTest 4: There is a province card and at least one money card available from money supply piles\n");
	G.supplyCount[province] = 1;
	G.supplyCount[0] = 0;
	G.supplyCount[1] = 1;
	G.supplyCount[2] = 0;
	failure  += asserttrue (isGameOver(&G), 0); 
	
	// TEST 5: check to see if game doesn't finish when ending conditions are not met
	printf("\nTest 5: There is a province card and non-empty supply piles\n");
	G.supplyCount[province] = 1;
	G.supplyCount[0] = 1;
	G.supplyCount[1] = 1;
	G.supplyCount[2] = 1;
	failure  += asserttrue (isGameOver(&G), 0); 
	
	// TEST 6: check to see if game is over when supply piles have invalid numbers
	printf("\nTest 6: Invalid number of cards (negative numbers)\n");
	G.supplyCount[province] = -1;
	G.supplyCount[0] = -6;
	G.supplyCount[1] = 0;
	G.supplyCount[2] = -3;
	failure  += asserttrue (isGameOver(&G), 0); 
	
	printf("\n***************** RESULTS *********************\n");
    if (failure > 0) {
        printf("\nTEST FAILED\n");
        printf("Count of failed tests: %d\n",failure);
    }
    else {
    	printf("\nPASSED ALL THE TESTS\n");
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }
    printf("**********************************************\n");
	return 0;
}
