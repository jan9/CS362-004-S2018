/*
* Author: Ju An
* Date: April 29, 2018
* OSU CS 362 - Assignment 3: Unit Test 3
* This program is a unit test for gainCard() function in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

// for more detailed results, use NOISY_TEST 1
#define NOISY_TEST 0

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

// runs the tests
int main () {
    // counts failed tests
	int failure = 0;
        
    // test game variable initialization
	int seed = 12321;
	int numPlayer = 2;
	int curPlayer = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
	struct gameState G;
    
	printf("**********************************************\n");
    printf("Testing -> gainCard()\n");
    
    // (int supplyPos, struct gameState, int toFlag, int player)
    // check to see if supply pile ie empty or card is not used in the game -> returns -1
    printf("\nTest 1: empty supply pile\n");
    memset(&G, 23, sizeof(struct gameState));   		 // clear the game state
    initializeGame(numPlayer, k, seed, &G);   // initialize a new game
    printf("\n   1-A Ran out of copper card\n");
    G.supplyCount[copper] = 0;
    failure  += asserttrue(gainCard(copper,&G,0,curPlayer),-1);
    
    printf("\n   1-B Ran out of silver card\n");
    G.supplyCount[silver] = 0;
    failure  += asserttrue(gainCard(silver,&G,0,curPlayer),-1);
    
    printf("\n   1-C Ran out of gold card\n");
    G.supplyCount[gold] = 0;
    failure  += asserttrue(gainCard(gold,&G,0,curPlayer),-1);
    
    printf("\n\nTest 2: supply card not used in the game\n");
    memset(&G, 23, sizeof(struct gameState));   		 // clear the game state
    initializeGame(numPlayer, k, seed, &G);   			 // initialize a new game
    // fill up the supply card
    G.supplyCount[copper] = 30;
    G.supplyCount[silver] = 30;
    G.supplyCount[gold] = 30;
    printf("\n   2-A Copper card not used in the game\n");
    G.supplyCount[copper] = -1;
    failure  += asserttrue(gainCard(copper,&G,0,curPlayer),-1);
    
    printf("\n   2-B Silver card not used in the game\n");
    G.supplyCount[silver] = -1;
    failure  += asserttrue(gainCard(silver,&G,0,curPlayer),-1);
    
    printf("\n   2-C Gold card not used in the game \n");
    G.supplyCount[gold] = -1;
    failure  += asserttrue(gainCard(gold,&G,0,curPlayer),-1);
	
	printf("\n\nTest 3: check if flags work correctly\n");
    memset(&G, 23, sizeof(struct gameState));   		 // clear the game state
    initializeGame(numPlayer, k, seed, &G);   			 // initialize a new game
    
    printf("\n   3-A check if toFlag == 0, then add a card to discard on current player. \n    Return value should be 0.\n");
    G.supplyCount[gold] = 30;
    #if (NOISY_TEST == 1)
    	printf("\n  Initial discardCount = %d\n", G.discardCount[curPlayer]);
    	printf("\n  Initial # of gold card = %d (should be 30)\n", G.supplyCount[gold]);
    #endif
    failure  += asserttrue(gainCard(gold,&G,0,curPlayer),0);
    #if (NOISY_TEST == 1)
		printf("\n  New discardCount = %d\n", G.discardCount[curPlayer]);
    	printf("\n  New # of gold card = %d\n", G.supplyCount[gold]);
    #endif
    
    printf("\n   3-B check if toFlag == 1, then add a card to deck on current player. \n    Return value should be 0.\n");
    G.supplyCount[gold] = 30;    
    #if (NOISY_TEST == 1)
    	printf("\n  Initial deckCount = %d\n", G.deckCount[curPlayer]);
    	//printf("\n  Initial # of gold card = %d (should be 30)\n", G.supplyCount[gold]);
    #endif
    failure  += asserttrue(gainCard(gold,&G,1,curPlayer),0);
	#if (NOISY_TEST == 1)
		printf("\n  New deckCount = %d\n", G.deckCount[curPlayer]);
    	//printf("\n  New # of gold card = %d\n", G.supplyCount[gold]);
    #endif
    
    printf("\n   3-C check if toFlag == 2, then add a card to hand on current player. \n    Return value should be 0. \n");
    G.supplyCount[gold] = 30;
    #if (NOISY_TEST == 1)
    	printf("\n  Initial handCount = %d\n", G.handCount[curPlayer]);
    	//printf("\n  Initial # of gold card = %d (should be 30)\n", G.supplyCount[gold]);
    #endif
    failure  += asserttrue(gainCard(gold,&G,2,curPlayer),0);
	#if (NOISY_TEST == 1)
		printf("\n  New handCount = %d\n", G.handCount[curPlayer]);
    	//printf("\n  New # of gold card = %d\n", G.supplyCount[gold]);
    #endif
    
    printf("\n   3-D if toFlag < 0 (i.e. invalid), then discard a card and return 0.\n");
    #if (NOISY_TEST == 1)
    	printf("\n  Initial discardCount = %d\n", G.discardCount[curPlayer]);
    	printf("\n  Initial deckCount = %d\n", G.deckCount[curPlayer]);
    	printf("\n  Initial handCount = %d\n", G.handCount[curPlayer]);
    	printf("\n  Initial # of gold card = %d (should be 30)\n", G.supplyCount[gold]);
    #endif
    failure  += asserttrue(gainCard(gold,&G,-1,curPlayer), 0);
    #if (NOISY_TEST == 1)
    	printf("\n  New discardCount = %d\n", G.discardCount[curPlayer]);
    	printf("\n  New deckCount = %d\n", G.deckCount[curPlayer]);
    	printf("\n  New handCount = %d\n", G.handCount[curPlayer]);
    	printf("\n  New # of gold card = %d (should be 30)\n", G.supplyCount[gold]);
    #endif
    
    printf("\n   3-E if toFlag > 2 (i.e. invalid) return 0.\n");
    #if (NOISY_TEST == 1)
    	printf("\n  Initial discardCount = %d\n", G.discardCount[curPlayer]);
    	printf("\n  Initial deckCount = %d\n", G.deckCount[curPlayer]);
    	printf("\n  Initial handCount = %d\n", G.handCount[curPlayer]);
    	printf("\n  Initial # of gold card = %d (should be 30)\n", G.supplyCount[gold]);
    #endif
    failure  += asserttrue(gainCard(gold,&G,3,curPlayer), 0);
    #if (NOISY_TEST == 1)
    	printf("\n  New discardCount = %d\n", G.discardCount[curPlayer]);
    	printf("\n  New deckCount = %d\n", G.deckCount[curPlayer]);
    	printf("\n  New handCount = %d\n", G.handCount[curPlayer]);
    	printf("\n  New # of gold card = %d (should be 30)\n", G.supplyCount[gold]);
    #endif
    
	printf("\n\nTest 4: check if the function decrease the number in supply pile and return 0\n");
    memset(&G, 23, sizeof(struct gameState));   		 // clear the game state
    initializeGame(numPlayer, k, seed, &G);   			 // initialize a new game
    // fill up the supply card
    G.supplyCount[copper] = 30;
    G.supplyCount[silver] = 30;
    G.supplyCount[gold] = 30;
    
    printf("\n   4-A Check to see if number of copper card decreased\n");
    int copperSupply = G.supplyCount[copper];
    failure  += asserttrue(gainCard(copper,&G,0,0), 0);
    failure  += asserttrue(copperSupply-1,G.supplyCount[copper]);
    
    printf("\n   4-B Check to see if number of silver card decreased\n");
    int silverSupply = G.supplyCount[silver];
    failure  += asserttrue(gainCard(silver,&G,0,0), 0);
    failure  += asserttrue(silverSupply-1,G.supplyCount[silver]);
    
    printf("\n   4-C Check to see if number of gold card decreased\n");
    int goldSupply = G.supplyCount[gold];
    failure  += asserttrue(gainCard(gold,&G,0,0), 0);
    failure  += asserttrue(goldSupply-1,G.supplyCount[gold]);

	printf("\n***************** RESULTS *********************\n");
    if (failure) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",failure);
    }
    else {
        printf("\nPASSED ALL THE TESTS\n");
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }
	printf("**********************************************\n");
    return 0;
}