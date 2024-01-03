#include <iostream>
using namespace std;

const int GRID_SIZE = 10;

char pl1FleetBoard[10][10];
int pl1ShotBoard[10][10];


char pl2FleetBoard[10][10];
int pl2ShotBoard[10][10];


void initialiseGrids(int gridInt[][GRID_SIZE], char gridChar[][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            gridInt[i][j] = 0;
            gridChar[i][j] = '*';
        }
    }
}
void initialiseArrays(int fleetSize, int* pl1FleetHealth, int* pl2FleetHealth) {
        for (int i = 0; i < fleetSize;i++) {
            pl1FleetHealth[i] = 0;
            pl2FleetHealth[i] = 0;
        }
}

void printCharFleetGrid(char grid[][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void printIntShotGrid(int grid[][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void placeShips(char FleetGrid[][GRID_SIZE], unsigned const ShipType, unsigned const shipNum) {
    unsigned beginX, beginY, endX, endY, shipLength;
    if (ShipType == 1) {
        cout << "Placing patrol boats: takes up 2 slots" << endl;
        shipLength = 2;
    } 
    else if (ShipType == 2) {
        cout << "Placing submarine: takes up 3 slots" << endl;
        shipLength = 3;
    }
    else if (ShipType == 3) {
        cout << "Placing destroyer: takes up 4 slots" << endl;
        shipLength = 4;
    }
    else if(ShipType == 4) {
        cout << "Placing aircraft carrier: takes up 5 slots" << endl;
    }
    else {
        return;
    }
    cout << "Please enter the coordinates of the ship's ends" << endl;
    cout << "Start grid space: ";
    std::cin >> beginX >> beginY;
    cout << "End grid space: ";
    std::cin >> endX >> endY;
    while (beginX < 0 || beginX > GRID_SIZE - 1 || beginY < 0 || beginY > GRID_SIZE - 1
        || endX < 0 || endX > GRID_SIZE - 1 || endY < 0 || endY > GRID_SIZE - 1
        || (beginX != endX && beginY != endY)
        || (beginX + ShipType - 1) != endX || (beginY + ShipType - 1) != endY) {
        cout << "Invalid input" << endl;
        std::cin >> beginX >> beginY >> endX >> endY;
    }    
    if (beginX == endX) {//placing ship vertically
        for (int i = beginY; i <= endY; i++) {
            FleetGrid[beginX][i] = shipNum + '0';
        }
    }
    else if (beginY == endY) {//placing ship horisontally
        for (int j = beginX; j <= endX; j++) {
            FleetGrid[j][beginY] = shipNum + '0';
        }
    }
}
void placingShipsUI(int playerNumber, int fleetSize, int* fleetHealth, char fleetGrid[][GRID_SIZE]) {
    int shipSelector;
    cout << "Player "<<playerNumber<<"'s turn:" << endl;
    cout << "Place:" << endl << "Patrol boat (press 1)" << endl
        << "Submarine (press 2)" << endl
        << "Destroyer (press 3)" << endl
        << "Aircraft carrier (press 4)" << endl;

    int index = 0;
    while (index < fleetSize) {
        cout << "Ship type: ";
        std::cin >> shipSelector;
        switch (shipSelector) {
            case 1: {
                placeShips(fleetGrid, 1, index);
                fleetHealth[index] = 2;
                cout << "You placed Patrol boat" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid);
                break;
            }
            case 2: {
                placeShips(fleetGrid, 2, index);
                fleetHealth[index] = 3;
                cout << "Player 1 placed submarine" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid);
                break;
            }
            case 3: {
                placeShips(fleetGrid, 3, index);
                fleetHealth[index] = 4;
                cout << "Player 1 placed destroyer" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid);
                break;
            }
            case 4: {
                placeShips(fleetGrid, 4, index);
                fleetHealth[index] = 5;
                cout << "Player 1 placed aircraft carrier" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid);
                break;
            }
            default: {
                cout << "Invalid input for ship type" << endl;
                break;
                break;
            }
        }
        if((fleetSize - index - 1)>0) cout << "You have to place " << fleetSize - index - 1 << " more ships" << endl;
        index++;
    }
    cout << "Player " <<playerNumber<< " has finished placing ships" << endl;
}
int startGame2Player() {
    bool hasWinner = false;//variable to end the game
    int winningPlayer = 0;//at the end of the game has a value -  either 1 or 2
    initialiseGrids(pl1ShotBoard, pl1FleetBoard);
    initialiseGrids(pl2ShotBoard, pl2FleetBoard);
    int turnCount = 1, currentPlayer;
    while (hasWinner == false) {
        currentPlayer = (turnCount % 2) + 1;
        cout << "TURN " << turnCount << endl;
        cout << "Player " << currentPlayer << endl;
        if (currentPlayer == 1) {
            cout << "Your fleet: " << endl;
            printCharFleetGrid(pl1FleetBoard);
            cout << endl;
            cout << "Map of your shots: " << endl;
            printIntShotGrid(pl1ShotBoard);
        }
        else {
            cout << "Your fleet: " << endl;
            printCharFleetGrid(pl2FleetBoard);
            cout << endl;
            cout << "Map of your shots: " << endl;
            printIntShotGrid(pl2ShotBoard);
        }
    }
    return 1;
}

int main()
{
    unsigned menuSelector;  //used for various confirmations and choosing options in the UI
    int fleetSize;
    cout << "Welcome to Damyan's Battleships" << endl << 
        "Would you like to load a previous game (enter 1) or start a new one (enter 2)?" << endl;

    std::cin >> menuSelector;
    while (menuSelector != 1 && menuSelector != 2) {
        cout << "Invalid input, please enter 1 or 2" << endl;
        std::cin >> menuSelector;
    }

    if (menuSelector == 1) {
        menuSelector = 0; //selector resets so it can be used again for something else
        //load from file
        cout << "Not done yet :(";
        return 0;
    }

    else if (menuSelector == 2) {
        menuSelector = 0; //selector resets so it can be used again for something else
        //start new game
        cout << "Do you want to play with a friend on this device (press 1) or play with a simple AI (press 2)" << endl;
        
        std::cin >> menuSelector;

        if (menuSelector == 1) {
            //Player vs Player gamemode
            menuSelector = 0;

            cout << "Before playing, you need to place your ships (Max amount is 16). How many do you want to place? (Fleet size will be equal for both players)" << endl;           
            std::cin >> fleetSize;
            while (fleetSize > 16 && fleetSize < 1) {
                cout << "Invalid input, please enter a number from 1 to 16" << endl;
                cin >> fleetSize;
            }
            int* pl1FleetHealth = new int[fleetSize];
            int* pl2FleetHealth = new int[fleetSize];
            initialiseGrids(pl1ShotBoard, pl1FleetBoard);
            initialiseGrids(pl2ShotBoard, pl2FleetBoard);
            initialiseArrays(fleetSize, pl1FleetHealth,pl2FleetHealth);
            for (int i = 0; i < fleetSize; i++) {
                cout << pl1FleetHealth[i] << " ";
            }
            cout << endl;

            //player 1 place ships:
            cout << "Player 2, please look away" << endl << endl;
            placingShipsUI(1, fleetSize, pl1FleetHealth, pl1FleetBoard);
            cout << endl;

            cout << "To proceed, Player 1 should look away, player 2 - press 1" << endl;
            menuSelector = 0;
            cin >> menuSelector;
            while (menuSelector != 1) {
                cout << "Invalid input" << endl;
            }

            //player 2 placing ships:
            cout << "Player 2's turn: " << endl;
            cout << "Fleet size: " << fleetSize << endl;
            placingShipsUI(2, fleetSize, pl2FleetHealth, pl2FleetBoard);

           /* int winner = startGame2Player();
            cout << "Player " << winner << " wins this match!";*/

            delete[] pl1FleetHealth;
            delete[] pl2FleetHealth;

            return 0;
        }
        else if (menuSelector == 2) {
            //Player vs bot gamemode
            cout << "Not done yet :(";
            return 0;
        }
    }


}
