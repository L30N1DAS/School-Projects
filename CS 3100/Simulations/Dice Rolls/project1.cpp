#include <iostream>
#include <stdlib.h>
#include <time.h>

#define ROLL_COMBINATIONS 11
using namespace std;

int main() {
    
    int numRolls;
    cout << "How many rolls? ";
    cin >> numRolls;
    cout << "Simulating " << numRolls << " rolls..." << endl;
    cout << "Results:" << endl;

    int rolls[ROLL_COMBINATIONS];
    for (int i = 0; i < ROLL_COMBINATIONS; i++) {
        rolls[i] = 0;
        //cout << rolls[i] << endl;
    }

    srand(time(NULL));

    for (int i = 0; i < numRolls; i++) {
        int firstToss = (rand() % 6) + 1;
        int secondToss = (rand() % 6) + 1;
        int rollResult = firstToss + secondToss;
        //cout << "rollResult: " << rollResult << endl;
        rolls[rollResult-2]++;
    }

    for (int i = 0; i < ROLL_COMBINATIONS; i++) {
        cout << i+2 << " was rolled " << rolls[i] << " times" << endl;
    }
}