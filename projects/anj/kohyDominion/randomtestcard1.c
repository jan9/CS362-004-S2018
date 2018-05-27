/*
* Author: Ju An
* Date: May 12, 2018
* OSU CS 362 - Assignment 4: Random Tester for Smithy Card
* This is a random tester for Smithy card. 
* It tests to see if the implemented code actually allows a player to get 3 extra cards
* from the player's deck pile on the same turn.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TRIES 1000	// number of tests 
#define NUM_QUESTIONS 2

int main(){
	int i, j, r;
	int failed = 0;
	
	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	
	int numPlayers;
	int player1 = 0; // current player

	int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    
	struct gameState G, orig;
	
	srand(time(NULL));
	
	for (i = 0; i < NUM_TRIES; i++){
		printf("\n************ Testing Smithy Card: %d/%d ****************\n", i+1, NUM_TRIES);
		// randomize and setup the variables 
		numPlayers = rand() % 3 + 2;
		int seed = rand()%RAND_MAX;
		memset(&G, 23, sizeof(struct gameState));	//clean gamestate
		r = initializeGame (numPlayers, k, seed, &G);	

		
		player1 = rand() % numPlayers;	// current player
		G.whoseTurn = player1;
		
		// randomize deck count and the player's deck 
		G.deckCount[player1] = rand() % MAX_DECK;
		for(j = 0; j < G.deckCount[player1]; j++){			
			// place randomly chosen kingdom cards to the deck
			G.deck[player1][j] = k[rand()%10];
		}

		// randomize hand count and the player's hand
		//treasure_pre = 0;
		G.handCount[player1] = rand() % MAX_HAND;
		G.hand[player1][0] = smithy;	// first card on hand will be smithy card
		for (j = 1; j < G.handCount[player1]; j++) 
		{
			// fill the player's hand with random cards
			G.hand[player1][j] = rand() % 27;
        }
		
		memcpy(&orig, &G, sizeof(struct gameState));
		
		//adventurer card effect	
		cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);

		
		printf("1. Checking card on the Player %d's HAND\n", player1);
		printf("Card on HAND before using the adventurer card: %d\n", orig.handCount[player1]);
		printf("Card on HAND after using the adventurer card: %d\n", G.handCount[player1]);
		if((orig.handCount[player1])+2 != G.handCount[player1])
    	{
           failed++;
           printf(" ! TEST FAILED: Player %d added %d cards to hand, instead of 3.\n\n", player1, ((G.handCount[player1])-(orig.handCount[player1])+1));
        }
        
        printf("\n2.Checking card on the Player %d's DECK\n", player1);
        printf("Card on DECK before using the adventurer card: %d\n", orig.deckCount[player1]);
		printf("Card on DECK after using the adventurer card: %d\n", G.deckCount[player1]);
		if((orig.deckCount[player1]) != G.deckCount[player1]+3)
    	{
           failed++;
           printf(" ! TEST FAILED: Player %d took %d cards from deck, instead of 3.\n", player1, ((G.deckCount[player1])-(orig.deckCount[player1])));
        }
        
	}
	printf("\n***************** RANDOM TESTING RESULTS *******************\n");
	printf("\nFailed Tests: %d/%d\n", failed, (NUM_TRIES*NUM_QUESTIONS));
	printf("\nPassed Tests: %d/%d\n", ((NUM_TRIES*NUM_QUESTIONS)-failed),(NUM_TRIES*NUM_QUESTIONS));
	printf("\n***************** END OF RANDOM TESTING ********************\n");
	return 0;
}