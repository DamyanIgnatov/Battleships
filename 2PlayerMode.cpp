#include <iostream>
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
    bool isDestroyed = 1;
    for (int i = 0; i < size; i++) {
        if (fleetHealth[i] != 0) isDestroyed = 0;
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
    ShotGrid[X][Y] = 'X';
    bool hit = false;
    if (FleetGrid[X][Y] != '*') {
        hit = true;
        shipHealth[FleetGrid[X][Y] - '0']--;
        FleetGrid[X][Y] = 'X';
    }
    return hit;
}

void startGame2Player(char** pl1FleetBoard, char** pl2FleetBoard,
    char** pl1ShotBoard, char** pl2ShotBoard,
    int* pl1Health, int* pl2Health, 
    int fleetSize, int gridSize) {
    bool hasWinner = false;
    int winner = 0;
    int roundCnt = 1;
    while (hasWinner == false) {
        int currentPlayer = (roundCnt % 2 != 0) ? 1 : 2;
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
        cout << "Grid space (Format: x y): ";
        std::cin >> charX >> charY;
        unsigned X = charX - 'A' + 1;
        unsigned Y = charY - '0' + 1;
        bool isHit = shootAt(enemyFleet, enemyHealth, X, Y, currentShots);
        if (isHit == true) {
            cout << "Enemy warship at " << X << " " << Y << " hit!" << endl<<endl;
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
        cout << "If you wish to end your turn, press 1 and look away!" << endl;
        cin >> continueVal;
        while (continueVal != 1) {
            cout << "Invalid input: Press 1 to end your turn." << endl;
            cin >> continueVal;
        }
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        roundCnt++;
    }
    cout << "The game has ended! The winner is " << winner << ", won in " << roundCnt << " turns." << endl;;
    cout << "Thank you for playing Damyan's battleships!" << endl;
    cout << endl;
}