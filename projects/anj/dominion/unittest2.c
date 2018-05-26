/*
* Author: Ju An
* Date: April 29, 2018
* OSU CS 362 - Assignment 3: Unit Test 2
* This program is a unit test for getCost() function in dominion.c
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


// testing the updateCoins() from dominion.c
int main()
{
    // counts failed tests
	int failure = 0;
    
    // check to see if the getCost() function returns correct cost value of all the cards used in the game
	printf("**********************************************\n");
    printf("Testing -> getCost()\n");
	printf("\nTest 1: curse card \n");
	failure  += asserttrue (getCost(0), 0); 
	
	printf("\nTest 2: estate card \n");
	failure  += asserttrue (getCost(1), 2); 
	
	printf("\nTest 3:  duchy card \n");
	failure  += asserttrue (getCost(2), 5); 
	
	printf("\nTest 4:  province card \n");
	failure  += asserttrue (getCost(3), 8); 
	
	printf("\nTest 5:  copper card \n");
	failure  += asserttrue (getCost(4), 0); 
	
	printf("\nTest 6:  silver card \n");
	failure  += asserttrue (getCost(5), 3); 

	printf("\nTest 7:  gold card \n");
	failure  += asserttrue (getCost(6), 6); 
	
	printf("\nTest 8:  adventurer card \n");
	failure  += asserttrue (getCost(7), 6); 

	printf("\nTest 9:  council_room card \n");
	failure  += asserttrue (getCost(8), 5); 
	
	printf("\nTest 10:  feast card \n");
	failure  += asserttrue (getCost(9), 4); 
	
	printf("\nTest 11:  gardens card \n");
	failure  += asserttrue (getCost(10), 4); 
	
	printf("\nTest 12:  mine card \n");
	failure  += asserttrue (getCost(11), 5); 
	
	printf("\nTest 13:  remodel card \n");
	failure  += asserttrue (getCost(12), 4); 
	
	printf("\nTest 14:  smithy card \n");
	failure  += asserttrue (getCost(13), 4); 
	
	printf("\nTest 15:  village card \n");
	failure  += asserttrue (getCost(14), 3); 
	
	printf("\nTest 16:  baron card \n");
	failure  += asserttrue (getCost(15), 4);

	printf("\nTest 17:  great_hall card \n");
	failure  += asserttrue (getCost(16), 3); 
	
	printf("\nTest 18:  minion card \n");
	failure  += asserttrue (getCost(17), 5); 

	printf("\nTest 19:  steward card \n");
	failure  += asserttrue (getCost(18), 3); 
	
	printf("\nTest 20:  tribute card \n");
	failure  += asserttrue (getCost(19), 5); 

	printf("\nTest 21:  ambassador card \n");
	failure  += asserttrue (getCost(20), 3); 
	
	printf("\nTest 22:  cutpurse card \n");
	failure  += asserttrue (getCost(21), 4); 
	
	printf("\nTest 23:  embargo card \n");
	failure  += asserttrue (getCost(22), 2); 
	
	printf("\nTest 24:  outpost card \n");
	failure  += asserttrue (getCost(23), 5); 
	
	printf("\nTest 25:  salvager card \n");
	failure  += asserttrue (getCost(24), 4); 
	
	printf("\nTest 26:  sea_hag card \n");
	failure  += asserttrue (getCost(25), 4); 
	
	printf("\nTest 27:  treasure_map card \n");
	failure  += asserttrue (getCost(26), 4); 
	
	printf("\nTest 28:  Invalid card number. Card number of -1 should return -1\n");
	failure  += asserttrue (getCost(-1), -1);  	
	
	printf("\nTest 29:  Invalid card number card. Card number of 30 should return -1\n");
	failure  += asserttrue (getCost(30), -1); 
	
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

