/*
* Author: Ju An
* Date: May 12, 2018
* OSU CS 362 - Assignment 4: Random Tester for Adventurer Card
* This is a random tester for Adventurer card. 
* It tests to see if the implemented code actually reveals 2 Treasure cards from deck and 
* put those Treasure cards into current player's hand and discard the other revealed cards.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TRIES 1000		// number of tests 

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
	
	int treasure_pre;  // num of treasures before adventurer card used
	int treasure_post; // num of treasures after adventurer card used
	int goldCount = 0;
    int silverCount = 0;
    int copperCount = 0;
        
	int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    
	struct gameState G;
	
	srand(time(NULL));
	

	for (i = 0; i < NUM_TRIES; i++){
		printf("\n************ Testing Adventurer Card: %d/%d ****************\n", i+1, NUM_TRIES);
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
			if (j % 5 == 0)
			{
				// treasure cards start with 4(copper), 5(silver) and 6(gold)
				G.deck[player1][j] = rand() % 3 + 4; 
			} 
			else 
			{
				// place randomly chosen kingdom cards to the deck
				G.deck[player1][j] = k[rand()%10];
			}
		}

		// randomize hand count and the player's hand
		treasure_pre = 0;
		G.handCount[player1] = rand() % MAX_HAND;
		G.hand[player1][0] = adventurer;	// first card on hand will be adventurer card
		for (j = 1; j < G.handCount[player1]; j++) 
		{
			// fill the player's hand with random cards
			G.hand[player1][j] = rand() % 27;
			
			// count treasures
			if (G.hand[player1][j] == copper) copperCount++;
			if (G.hand[player1][j] == silver) silverCount++;
			if (G.hand[player1][j] == gold) goldCount++;
        	if ((G.hand[player1][j] == gold) ||(G.hand[player1][j] == silver)||(G.hand[player1][j] == copper)) 
        	{
        		treasure_pre++;
        	}
        }

		//adventurer card effect	
		cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

		//check number of treasures in hand after adventurer card
		treasure_post = 0;
		for(j = 0; j < G.handCount[player1]; j++){
			if ((G.hand[player1][j] == gold) ||(G.hand[player1][j] == silver)||(G.hand[player1][j] == copper)) 
        	{
        		treasure_post++;
			}
		}
		
		printf("Treasures in Player %d's HAND before using the adventurer card: %d\n", player1, treasure_pre);
		printf("Treasures in Player %d's HAND after using the adventurer card: %d\n", player1, treasure_post);
		if(treasure_pre+2 < treasure_post)
    	{
           failed++;
           printf(" ! TEST FAILED: Player %d added %d cards to hand, instead of 2.\n\n", player1, (treasure_post-treasure_pre));
        }
	}
	printf("\n***************** RANDOM TESTING RESULTS *******************\n");
	printf("\nFailed Tests: %d \n", failed);
	printf("\nPassed Tests: %d \n", (NUM_TRIES-failed));
	printf("\n***************** END OF RANDOM TESTING ********************\n");
	return 0;
}