#include <iostream>
#include "Files.h"
using namespace std;


void printFleetGrid(char** grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void printShotGrid(char** grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
void printFleetHealth(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Ship " << i << ": " << arr[i] << " points" << endl;
    }
    cout << endl;
}

bool isFleetDestroyed(int* fleetHealth, int size) {
    bool isDestroyed = true;
    for (int i = 0; i < size; i++) {
        if (fleetHealth[i] != 0) {
            isDestroyed = false;
        }
    }
    return isDestroyed;
}
int countLostShips(int* fleetHealth, int size) {
    int lostShipsCount = 0;
    for (int i = 0; i < size; i++) {
        if (fleetHealth[i] == 0) lostShipsCount++;
    }
    return lostShipsCount;
}

bool shootAt(char** FleetGrid, int* shipHealth, unsigned X, unsigned Y, char** ShotGrid) {
    bool hit = false;
    if (FleetGrid[X][Y] != '*') {
        hit = true;
        shipHealth[FleetGrid[X][Y] - '0']--;
        FleetGrid[X][Y] = 'X';
    }
    if (hit == true) ShotGrid[X][Y] = 'I';//symbol for hit shot
    else ShotGrid[X][Y] = 'X';//symbol for missed shot
    return hit;
}

void startGame2Player(char** pl1FleetBoard, char** pl2FleetBoard,
    char** pl1ShotBoard, char** pl2ShotBoard,
    int* pl1Health, int* pl2Health, 
    int fleetSize, int gridSize,int round) {
    const int gamemode = 1;//gamemode 1 is 2 player mode, gamemode 2 is 1 player PvE mode
    bool hasWinner = false;
    int winner = 0;
    int roundCnt = round;//roundCnt not always starts from zero when loading from a file, rounds are stored and restart
    while (hasWinner == false) {
        int currentPlayer = (roundCnt % 2 != 0) ? 1 : 2;//player 1 is on odd turns, player 2 - on even turns
        char(**currentFleet) = (roundCnt % 2 != 0) ? pl1FleetBoard : pl2FleetBoard;
        char(**currentShots) = (roundCnt % 2 != 0) ? pl1ShotBoard : pl2ShotBoard;
        int(*currentHealth) = (roundCnt % 2 != 0) ? pl1Health : pl2Health;

        int(*enemyHealth) = (roundCnt % 2 != 0) ? pl2Health : pl1Health;
        char(**enemyFleet) = (roundCnt % 2 != 0) ? pl2FleetBoard : pl1FleetBoard;

        cout << "Turn " << roundCnt << ": PLAYER " << abs(currentPlayer) << "\'s turn!" << endl;
        cout << "Your fleet:" << endl;
        printFleetGrid(currentFleet, gridSize);
        cout << endl;
        cout << "Your ships'health:" << endl;
        printFleetHealth(currentHealth, fleetSize);
        cout << endl;
        cout << "Your shots at the enemy:" << endl;
        printShotGrid(currentShots, gridSize);
        cout << endl;
        cout << "Where do you order cannons to fire? Pick a quadrant on the map" << endl;
        char charX, charY;
        cout << "Grid space: ";
        std::cin >> charX >> charY;
        unsigned X = charX - 'A' + 1;
        unsigned Y = charY - '0' + 1;
        while (X < 0 || X > gridSize || Y < 0 || Y > gridSize) {
            std::cout << "Invalid input, re-enter" << endl;
            std::cout << "End grid space: ";
            std::cin >> charX >> charY;
            X = charX - 'A' + 1;
            Y = charY - '0' + 1;
        }
        bool isHit = shootAt(enemyFleet, enemyHealth, X, Y, currentShots);
        if (isHit == true) {
            cout << "Enemy warship at " << X << Y << " hit!" << endl<<endl;
        }
        else {
            cout << "The gunners have missed the target" << endl;
        }
        if (isFleetDestroyed(enemyHealth, fleetSize)) {
            cout << "You have defeated the enemy!!" << endl;
            cout << "You lost " << countLostShips(currentHealth, fleetSize) << " ships in the battle"<< endl ;
            winner = currentPlayer;
            hasWinner = true;
            break;
        }
        int continueVal;
        cout << "If you wish to end your turn, press 1, to save your game, press 2." << endl;
        cin >> continueVal;
        while (continueVal != 1) {
            cout << "Invalid input: Press 1 to end your turn." << endl;
            cin >> continueVal;
        }
        if (continueVal == 1) {
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";//buffer so you can't see the other player's ships
            roundCnt++;
        }
        else {
            std::cout << "Game saved to file";
            std::cout << "Thank you for playing Damyan's battleships" << endl;
            int round = roundCnt;
            saveGame(gamemode, round, fleetSize, gridSize, pl1FleetBoard, pl2FleetBoard, pl1ShotBoard, pl2ShotBoard, pl1Health, pl2Health);
            return;
        }
    }
    cout << "The game has ended! The winner is " << winner << ", won in " << roundCnt << " turns." << endl;;
    cout << "Thank you for playing Damyan's battleships!" << endl;
    cout << endl;
}