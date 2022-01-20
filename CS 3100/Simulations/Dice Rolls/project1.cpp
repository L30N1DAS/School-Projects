// Anmol Saini
// Project 1: Simulating Dice Rolls
/* This program rolls 2 dice a specified number of times and adds the 2 tosses
    together to determine the overall result of the roll. At the end, these results
    are displayed to the user.
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

#define ROLL_COMBINATIONS 11 // 11 possible outcomes when 2 dice are rolled

using namespace std;

int main() {
    
    int numRolls; // number of times to roll 2 dice as determined by the user
    cout << "How many rolls? ";
    cin >> numRolls;
    cout << "Simulating " << numRolls << " rolls..." << endl;
    cout << "Results:" << endl;
 
    // creates an int array of length 11 to hold all the results of the dice rolls
    // initializes each value in the array to 0
    int rolls[ROLL_COMBINATIONS];
    for (int i = 0; i < ROLL_COMBINATIONS; i++) {
        rolls[i] = 0;
    }

    srand(time(NULL)); // seeds the random number generator with the time

    // performs dice rolls and records results in the array
    for (int i = 0; i < numRolls; i++) {
        int firstToss = (rand() % 6) + 1;
        int secondToss = (rand() % 6) + 1;
        int rollResult = firstToss + secondToss;
        rolls[rollResult-2]++;
    }

    // displays all results
    for (int i = 0; i < ROLL_COMBINATIONS; i++) {
        cout << i+2 << " was rolled " << rolls[i] << " times" << endl;
    }
}