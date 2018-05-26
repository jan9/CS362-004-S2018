/*
* Author: Ju An
* Date: April 29, 2018
* OSU CS 362 - Assignment 3: Unit Test 4
* This program is a unit test for updateCoin() function in dominion.c
* Modified version of testUpdateCoins.c (provided by the instructor)
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
			//printf("\n	Actual value: %d, Expected value: %d\n", testedVal, expectedVal);
			printf("\n	PASS (assertion true)\n");
		#endif
		return 0;
	} else {
		#if (NOISY_TEST == 1)
			//printf("\n	Actual value: %d, Expected value: %d\n", testedVal, expectedVal);	
			printf("\n	FAIL (assertion false)\n");
		#endif
		return 1;
	}
}

// testing the updateCoins() from dominion.c
int main()
{
    // counts failed tests
	int failure = 0;
    
    // test game variable initialization
    int i;
    int seed = 12321;	
    int numPlayer = 2;
    int bonus, maxBonus = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int handCount, maxHandCount = 5;
    
	// arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    
	printf("**********************************************\n");
    printf("Testing -> updateCoins()\n");
    int j = 0;
	for (i = 0; i < numPlayer; i++) {
		for (handCount = 1; handCount <= maxHandCount; handCount++) {
			for (bonus = 1; bonus <= maxBonus; bonus++){
                memset(&G, 23, sizeof(struct gameState));   		 // clear the game state
                initializeGame(numPlayer, k, seed, &G);   // initialize a new game
				
				
                printf("\nTest %d: Test player %d with %d treasure card(s) and %d bonus.\n", j++,  i+1, handCount, bonus);
				
                G.handCount[i] = handCount;                 		 // set the number of cards on hand
                
                // TEST 1
                memcpy(G.hand[i], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(i, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("All Copper:  ");
                	printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
				#endif
                failure += asserttrue(G.coins, (handCount * 1 + bonus)); // check if the number of coins is correct
                
                // TEST 2
                memcpy(G.hand[i], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(i, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("All Silver:  ");
                	printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
				#endif
                failure += asserttrue(G.coins, (handCount * 2 + bonus)); // check if the number of coins is correct
				
				// TEST 3
                memcpy(G.hand[i], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(i, &G, bonus);
				#if (NOISY_TEST == 1)
					printf("All   Gold:  ");
					printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
				#endif
                failure += asserttrue(G.coins, (handCount * 3 + bonus)); // check if the number of coins is correct
                }
            }
		}
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
