/*
* Author: Ju An
* Date: May 27, 2018
* OSU CS 362 - Assignment 5: Random Tester for Great Hall Card
* This is a random tester for Great Hall card. 
* It tests to see if the implemented code actually allows a player to get one card from
* the player's deck and do an extra actions instead of one on the same turn.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TRIES 1000	// number of tests 
#define NUM_QUESTIONS 3
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
		printf("\n************ Testing Great Hall Card: %d/%d ****************\n", i+1, NUM_TRIES);
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
		G.handCount[player1] = rand() % MAX_HAND;
		G.hand[player1][0] = great_hall;	// first card on hand will be village card
		for (j = 1; j < G.handCount[player1]; j++) 
		{
			// fill the player's hand with random cards
			G.hand[player1][j] = rand() % 27;
        }
		
		memcpy(&orig, &G, sizeof(struct gameState));
		
		//Great_Hall card effect	
		cardEffect(great_hall, choice1, choice2, choice3, &G, handpos, &bonus);

		
		printf("1. Checking card on the Player %d's HAND\n", player1);
		printf("Card on HAND before using the Great_Hall card: %d\n", orig.handCount[player1]);
		printf("Card on HAND after using the Great_Hall card: %d\n", G.handCount[player1]);
		if((orig.handCount[player1]) != G.handCount[player1])
    	{
           failed++;
           printf(" ! TEST FAILED: Player %d added %d cards to hand, instead of 1.\n\n", player1, (((G.handCount[player1])-(orig.handCount[player1]))));
        }
        
        
        printf("\n2.Checking card on the Player %d's DECK\n", player1);
        printf("Card on DECK before using the Great_Hall card: %d\n", orig.deckCount[player1]);
		printf("Card on DECK after using the Great_Hall card: %d\n", G.deckCount[player1]);
		if((orig.deckCount[player1]) == G.deckCount[player1])
    	{
           failed++;
           printf(" ! TEST FAILED: Player %d took %d cards from deck, instead of 1.\n", player1, ((orig.deckCount[player1])-(G.deckCount[player1])));
        }
        
    	printf("\n3. Checking if the player took the extra cards on the same turn\n");
        printf("NumActions left before using the Great_Hall card: %d\n", orig.numActions);
		printf("NumActions left after using the Great_Hall card: %d\n", G.numActions);
		if((orig.numActions+1) != G.numActions)
    	{
           failed++;
           printf(" ! TEST FAILED: Player %d has %d actions left, instead of 1.\n", player1, (G.numActions-orig.numActions));
        }
        
        
	}
	printf("\n***************** RANDOM TESTING RESULTS *******************\n");
	printf("\nFailed Tests: %d/%d \n", failed, NUM_TRIES*NUM_QUESTIONS);
	printf("\nPassed Tests: %d/%d \n", ((NUM_TRIES*NUM_QUESTIONS)-failed), NUM_TRIES*NUM_QUESTIONS);
	printf("\n***************** END OF RANDOM TESTING ********************\n");
	return 0;
}