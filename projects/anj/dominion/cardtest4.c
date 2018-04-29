/*
* Author: Ju An
* Date: April 29, 2018
* OSU CS 362 - Assignment 3: Card Test 4
* This is a unit test for Village card in dominion.c
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
int asserttrue (int expectedVal, int testedVal) 
{
	if (testedVal == expectedVal) {
		#if (NOISY_TEST == 1)
			printf("\n	Expected value: %d, actual value: %d\n", expectedVal, testedVal);
			printf("\n	PASS (assertion true)\n");
		#endif
		return 0;
	} else {
		#if (NOISY_TEST == 1)
			printf("\n	Expected value: %d, actual value: %d\n", expectedVal, testedVal);	
			printf("\n	FAIL (assertion false)\n");
		#endif
		return 1;
	}
}

// testing the cardEffect() function (refactored) from dominion.c
// test should work whether a card is implemented inside cardEffect or in its own function
int main()
{
    // counts failed tests
	int failure = 0;
    
    // test variable initialization
	int i;
	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	
	int numPlayer = 2;
	int player1 = 0;
	int player2 = 1;
	
	int card;
	int origTreasureCount = 0;
	int newTreasureCount = 0;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
	struct gameState G, savedData;
	
	int seed = 5656;
	
	printf("**********************************************\n");
    printf("Testing -> Village Card\n");
    memset(&G, 23, sizeof(struct gameState));   		 // clear the game state
    initializeGame(numPlayer, k, seed, &G);   // initialize a new game
    memcpy(&savedData, &G, sizeof(struct gameState));
	
	printf("\n< P1 Data BEFORE Village Card is Played >\n");
	// 1. check player 1's # of card in hand
	printf("Player 1 has %d cards in hand.\n", savedData.handCount[player1]);
	
	// 2. check player 1's # of card in deck
	printf("Player 1 has %d cards in deck.\n", savedData.deckCount[player1]);
	
	// 3. check player 1's # of card in discard pile
	printf("Player 1 has %d cards in discard pile.\n", savedData.discardCount[player1]);
	
	// 4. Play Village Card
	cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
	
	printf("\n< P1 Data AFTER Village Card is Played >\n");
	// 5. check player 1's # of card in hand
	printf("Player 1 has %d cards in hand.\n", G.handCount[player1]);
	
	// 6. check player 1's # of card in deck
	printf("Player 1 has %d cards in deck.\n", G.deckCount[player1]);
	
	// 7. check player 1's # of card in discard pile
	printf("Player 1 has %d cards in discard pile.\n", G.discardCount[player1]);
	
	
	printf("\n***************** RESULTS *********************\n");
	
	printf("\nTEST 1. Check player 1 gets to draw 1 card \n");
	printf("\n   Check player 1's deckCount\n");
	failure  += asserttrue (savedData.handCount[player1], G.handCount[player1]);
	printf("\n   Check player 1's deckCount\n");
	failure  += asserttrue (savedData.deckCount[player1]-1,G.deckCount[player1]);
	
	printf("\nTEST 2. Check to see discardCard() function within Village Card's code worked\n");
	// NOTE: used card sent to discardCard() to be added on to a played pile
	printf("\n   Checking... \n");
	printf("\n   Prev # of discard count = %d\n", savedData.playedCardCount);
	printf("\n   Current # of discard count = %d\n", G.playedCardCount);
	failure  += asserttrue (savedData.playedCardCount+1,G.playedCardCount);
	
	printf("\nTEST 3. Check if player1's numActions increased by +2\n");
	printf("\n   Checking... \n");
	printf("\n   Prev numActions = %d\n", savedData.numActions);
	printf("\n   Current of numActions = %d\n", G.numActions);
	failure  += asserttrue (savedData.numActions+2,G.numActions);
	
	printf("\nTEST 4. Check if player 2's hand and deck cards remains the same\n");
	printf("\n   Check player 2's handCount\n");
	failure  += asserttrue (savedData.handCount[player2],G.handCount[player2]);
	printf("\n   Check player 2's deckCount\n");
	failure  += asserttrue (savedData.deckCount[player2],G.deckCount[player2]);
	
	printf("\nTEST 5. Check if kingdom and victory cards have any bugs\n");
	printf("\n   Checking kingdom cards' supply piles\n");
	for (i = 0; i < 10; i++) {
		failure  += asserttrue (savedData.supplyCount[k[i]], G.supplyCount[k[i]]);
	}
	printf("\n   Checking province card pile:\n");
	failure  += asserttrue (savedData.supplyCount[province], G.supplyCount[province]);
	printf("\n   Checking duchy card pile:\n");
	failure  += asserttrue (savedData.supplyCount[duchy], G.supplyCount[duchy]);
	printf("\n   Checking estate card pile:\n");
	failure  += asserttrue (savedData.supplyCount[estate], G.supplyCount[estate]);
	
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