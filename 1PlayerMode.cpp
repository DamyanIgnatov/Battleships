#include <iostream>
#include <ctime>
#include <cstdlib> 
#include "Files.h"
using namespace std;

void placeRandomShip(char** fleetGrid, int gridSize, int startX, int startY, int endX, int endY, int index) {
	if (startX != endX && startY != endY) return;

    if (startX > endX) swap(startX, endX);
    if (startY > endY) swap(startY, endY);

	if (startX == endX) {//horisontal
		for (int i = startY; i <= endY; i++) {
			fleetGrid[startX][i] = index + '0';
		}
	}
	else { //vertical
		for (int i = startX; i <= endX; i++) {
			fleetGrid[i][startY] = index + '0';
		}
	}	
}

void printFleet(char** grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void printShot(char** grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
void printHealth(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Ship " << i << ": " << arr[i] << " points" << endl;
    }
    cout << endl;
}

bool isDestroyed(int* fleetHealth, int size) {
    bool isDestroyed = 1;
    for (int i = 0; i < size; i++) {
        if (fleetHealth[i] != 0) isDestroyed = 0;
    }
    return isDestroyed;
}
int countLost(int* fleetHealth, int size) {
    int lostShipsCount = 0;
    for (int i = 0; i < size; i++) {
        if (fleetHealth[i] == 0) lostShipsCount++;
    }
    return lostShipsCount;
}

bool shoot(char** FleetGrid, int* shipHealth, unsigned X, unsigned Y, char** ShotGrid) {    
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
void startGame1Player(char** pl1Fleet, char** pl2Fleet, char** pl1Shots, char** pl2Shots, int* pl1Health, int* pl2Health, int fleetSize, int boardSize, int round) {
    const int gamemode = 2;
	bool hasWinner = false;
	int winner = 0;
	int roundCnt = round;
	while (hasWinner == false) {
		int currentPlayer = (roundCnt % 2 != 0) ? 1 : 2;

		cout << "Turn " << roundCnt << ": PLAYER " << abs(currentPlayer) << "\'s turn!" << endl;
		if (currentPlayer == 1) { //human's turn
            cout << "Your fleet:" << endl;
            printFleet(pl1Fleet, boardSize);
            cout << endl;
            cout << "Your ships'health:" << endl;
            printHealth(pl1Health, fleetSize);
            cout << endl;
            cout << "Your shots at the enemy:" << endl;
            printShot(pl1Shots, boardSize);
            cout << endl;
            cout << "Where do you order cannons to fire? Pick a quadrant on the map" << endl;
            char charX, charY;
            cout << "Grid space: ";
            std::cin >> charX >> charY;
            unsigned X = charX - 'A' + 1;
            unsigned Y = charY - '0' + 1;
            while (X < 0 || X > boardSize || Y < 0 || Y > boardSize) {
                std::cout << "Invalid input, re-enter" << endl;
                std::cout << "End grid space: ";
                std::cin >> charX >> charY;
                X = charX - 'A' + 1;
                Y = charY - '0' + 1;
            }
            bool isHit = shoot(pl2Fleet, pl2Health, X, Y, pl1Shots);
            if (isHit == true) { //hit
                cout << "Enemy warship at " << charX << charY << " hit!" << endl << endl;
            }
            else { //miss
                cout << "The gunners have missed the target" << endl;
            }
            //end current turn
            int continueVal;
            cout << "If you wish to end your turn, press 1, to save current progress, press 2" << endl;
            cin >> continueVal;
            while (continueVal != 1 && continueVal != 2) {
                cout << "Invalid input: Press 1 to end your turn, Press 2 to save progress." << endl;
                cin >> continueVal;
            }
            if (continueVal == 1) {
                cout << "\n\n\n\n\n";//a small buffer for readability
            }
            else {
                std::cout << "Game saved to file" << endl;
                std::cout << "Thank you for playing Damyan's battleships" << endl;
                int round = roundCnt;
                saveGame(gamemode, round, fleetSize, boardSize, pl1Fleet, pl2Fleet, pl1Shots, pl2Shots, pl1Health, pl2Health);
                return;
            }
            
		}
        else {
            //generate random grid square, that has not been already chosen
            srand(time(0));
             const int range = boardSize - 1; //due to the numerical grid indexes, the board is technically size+1 x size+1 with the first column being unusable
             const int minValue = 1;
            int randomX = rand() % range + minValue;
            int randomY = rand() % range + minValue;
            while(randomX < 0 || randomY < 0 || randomX > boardSize || randomY > boardSize || pl2Shots[randomX][randomY] != '*') {
                //regenerate
                randomX = rand() % range + minValue;
                randomY = rand() % range + minValue;
            }            
            bool isHit = shoot(pl1Fleet, pl1Health, randomX, randomY, pl2Shots);
            cout << "AI shoots at " << (char)(randomX + 'A' - 1) << " " << (char)(randomY + '0' + 1) << endl;
            if (isHit == 1) cout << "One of your ships is hit!" << endl;
            else cout << "They missed" << endl;
        }
        //iterate round
        roundCnt++;
        //end game
        if (isDestroyed(pl2Health, fleetSize)) {
            cout << "\n\n\n\n\n";
            cout << "You have defeated the enemy!!" << endl;
            cout << "You lost " << countLost(pl1Health, fleetSize) << " ships in the battle." << endl;
            winner = 1;
            hasWinner = true;
            break;
        }
        if (isDestroyed(pl1Health, fleetSize)) {
            cout << "\n\n\n\n\n";
            cout << "You have lost to the brainless AI!!" << endl;
            winner = 2;
            hasWinner = true;
            break;
        }
	}
    cout << "The game has ended! The winner is player " << winner << ", won in " << roundCnt << " turns." << endl;;
    cout << "Thank you for playing Damyan's battleships!" << endl;
    cout << endl;
}