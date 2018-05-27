/*
* Author: Ju An
* Date: April 29, 2018
* OSU CS 362 - Assignment 3: Card Test 1
* This is a unit test for Adventurer card in dominion.c
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
	
	int seed = 72645;
	
	printf("**********************************************\n");
    printf("Testing -> Adventurer Card\n");
    memset(&G, 23, sizeof(struct gameState));   		 // clear the game state
    initializeGame(numPlayer, k, seed, &G);   // initialize a new game
    memcpy(&savedData, &G, sizeof(struct gameState));
    
	printf("\n< P1 Data BEFORE Adventurer Card is Played >\n");
	// 1. check player 1's # of card in hand
	printf("Player 1 has %d cards in hand.\n", savedData.handCount[player1]);
	
	// 2. check player 1's # of card in deck
	printf("Player 1 has %d cards in deck.\n", savedData.deckCount[player1]);
	int numDeckCards = savedData.deckCount[player1];
	// 3. check player 1's # of treasure cards in hand
	for (i = 0; i < savedData.handCount[player1]; i++) {
		card = savedData.hand[player1][i];
		if (card == copper || card == silver || card == gold) {
			origTreasureCount++;
		}
	}
	int origHandTreasure = origTreasureCount;
	printf("Player 1 has %d treasure cards in hand.\n", origHandTreasure);
	
	
	
	origTreasureCount = 0;
	// 4. check player 1's # of treasure cards in hand
	for (i = 0; i < savedData.deckCount[player1]; i++) {
		card = savedData.deck[player1][i];
		if (card == copper || card == silver || card == gold) {
			origTreasureCount++;
		}
	}
	int origDeckTreasure = origTreasureCount;
	printf("Player 1 has %d treasure cards in deck.\n", origDeckTreasure);
	
	// 5. check player 1's # of actions left to do
	printf("Player 1 has %d actions.\n", savedData.numActions);
	
	// 6. Play Adventurer Card
	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
	
	printf("\n< P1 Data AFTER Adventurer Card is Played >\n");
	// 7. check player 1's # of card in hand
	printf("Player 1 has %d cards in hand.\n", G.handCount[player1]);
	
	// 8. check player 1's # of card in deck
	printf("Player 1 has %d cards in deck.\n", G.deckCount[player1]);
	
	// 9. check player 1's # of treasure cards in hand
	for (i = 0; i < G.handCount[player1]; i++) {
		card = G.hand[player1][i];
		if (card == copper || card == silver || card == gold) {
			newTreasureCount++;
		}
	}
	int newHandTreasure = newTreasureCount;
	printf("Player 1 has %d treasure cards in hand.\n", newHandTreasure);
	
	newTreasureCount = 0;
	// 10. check player 1's # of treasure cards in hand
	for (i = 0; i < G.deckCount[player1]; i++) {
		card = G.deck[player1][i];
		if (card == copper || card == silver || card == gold) {
			newTreasureCount++;
		}
	}
	int newDeckTreasure = newTreasureCount;
	printf("Player 1 has %d treasure cards in deck.\n", newDeckTreasure);
	
	// 11. check player 1's # of actions left to do
	printf("Player 1 has %d actions.\n", G.numActions);
	
	printf("\n***************** RESULTS *********************\n");
	
	printf("\nTEST 1. Player 1's Treasure counts should increase by 2 after card is played \n");
	printf("\n   Checking Player 1's handCount\n");
	failure  += asserttrue (savedData.handCount[player1]+2,G.handCount[player1]);
	/*printf("\n   Checking Player 1's deckCount\n");
	failure  += asserttrue (savedData.deckCount[player1],G.deckCount[player1] + 2);
	*/
	printf("\n   Checking Player 1's treasure count in hand\n");
	failure  += asserttrue (newHandTreasure,origHandTreasure+2);
	
	printf("\nTEST 2. Player 2's handCount and deckCount remains the same\n");
	printf("\n   Checking Player 2's handCount\n");
	failure  += asserttrue (savedData.handCount[player2],G.handCount[player2]);
	printf("\n   Checking Player 2's deckCount\n");
	failure  += asserttrue (savedData.deckCount[player2],G.deckCount[player2]);
	
	printf("\nTEST 3. Check if kingdom and victory cards have any bugs\n");
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
