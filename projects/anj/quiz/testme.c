/*
* Author: Ju An
* Date: May 3rd, 2018
* OSU CS 362 - Assignment: Random Testing Quiz
* Implementation of a random tester for the function testme()
* Including only the letters used in the target statment
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Using ASCII char #32 (' ') - 125 ('}')
    //char randChar = rand () % (125 - 32) + 32;
    //return randChar;
    char array [9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']' };
    return array [rand() % 9];
}

char *inputString()
{
    char array [5] = {'r', 'e', 's', 'e', 't'};
    static char randStr [6];
    randStr[5] = '\0';
    int i;
    for (i = 0; i < 5; i++) {
    	randStr [i] = array[rand()%5];
    	}
    return randStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error \n");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
