#include <iostream>
using namespace std;

const int GRID_SIZE = 10;

char pl1FleetBoard[GRID_SIZE][GRID_SIZE];
int pl1ShotBoard[GRID_SIZE][GRID_SIZE];


char pl2FleetBoard[GRID_SIZE][GRID_SIZE];
int pl2ShotBoard[GRID_SIZE][GRID_SIZE];


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

int placeShips(char FleetGrid[][GRID_SIZE], unsigned const shipIndex) {
    unsigned startX, startY, endX, endY;

    cout << "Please enter the coordinates of the ship's ends" << endl;
    cout << "Start grid space (Format: x y): ";
    std::cin >> startX >> startY;
    cout << "End grid space (Format: x y): ";
    std::cin >> endX >> endY;

    int isValidCoords = 1;
    int num1 = endX - startX;
    int num2 = endY - startY;
    if(startX < 0 || endX >= GRID_SIZE || startY < 0 || endY >= GRID_SIZE   //-3 0, 3 0 or 10 0, 4 0 - out of bounds
        || abs(num1) > 4 || abs(num2) > 4                                   //0 0, 0 5 - too long
        || (startX == endX && startY == endY)                               //1 1 1 1 - too short
        || (startX != endX && startY != endY)) isValidCoords = 0;           //1 2 2 1 - diagonal/invalid orientation

    if (abs(num1) > 5 || abs(num2) > 5) isValidCoords = -2;
    while (isValidCoords <= 0) {
        cout << "Invalid input, please re-enter coordinates" << endl;
        cout << "Start grid space (Format: x y): ";
        std::cin >> startX >> startY;
        cout << "End grid space (Format: x y): ";
        std::cin >> endX >> endY;
        num1 = endX - endY;
        num2 = startX - startY;
        if (startX > 0 && endX < GRID_SIZE && startY > 0 && endY < GRID_SIZE //0 9 0 9 - OK
            && abs(num1) <= 4 && abs(num2) <= 4                         //0 0, 0 4 - OK (max length)
            && (startX == endX && startY != endY                        //1 0, 1 2 - OK (horizontal)
                || startY == endY && startX != endX)) isValidCoords = 1;//1 3, 3 3 - OK (vertical)
    }

    if (startX == endX) {//placing ship vertically
        int num = startY - endY;
        if (startY > endY) swap(startY, endY);
        for (unsigned i = startY; i <= endY; i++) {
            FleetGrid[startX][i] = shipIndex + '0';
        }
        return(abs(num) + 1);
    }
    else if (startY == endY) {//placing ship horisontally
        int num = startX - endX;
        if (startX > endX) swap(startX, endX);
        for (unsigned j = startX; j <= endX; j++) {
            FleetGrid[j][startY] = shipIndex + '0';
        }
        return(abs(num) + 1);
    }
}
void placingShipsUI(int playerNumber, int fleetSize, int* fleetHealth, char fleetGrid[][GRID_SIZE]) {
    cout << "Player "<<playerNumber<<"'s turn:" << endl;

    int index = 0;
    while (index < fleetSize) {
        int shipLength = placeShips(fleetGrid, index);
        switch (shipLength) {
            case 2: {
                fleetHealth[index] = 2;
                cout << "You placed Patrol boat" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid);
                break;
            }
            case 3: {
                fleetHealth[index] = 3;
                cout << "You placed submarine" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid);
                break;
            }
            case 4: {
                fleetHealth[index] = 4;
                cout << "You placed destroyer" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid);
                break;
            }
            case 5: {
                fleetHealth[index] = 5;
                cout << "You placed aircraft carrier" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid);
                break;
            }
            default: {
                cout << "Something went wrong here, please restart or check your inputs" << endl;
                break;
            }
        }
        if((fleetSize - index - 1)>0) cout << "You have to place " << fleetSize - index - 1 << " more ships" << endl;
        index++;
    }
    cout << "Player " <<playerNumber<< " has finished placing ships" << endl;
    cout << "Your ships' health: "<<endl;
    for (int i = 0; i < fleetSize; i++) {
        cout << "Ship " << i << ": " << fleetHealth[i] << " points" << endl;
    }
    cout << endl;

}

bool startGame2Player() {
    //bool hasWinner = false;
    //int winner = 0;
    //while (hasWinner == false) {
    //    cout << "Player 1's fleet and shots" << endl;
    //}
    return 0;
}

int main()
{
    unsigned menuSelector;  //used for various confirmations and choosing options in the UI
    cout << "Welcome to Damyan's Battleships" << endl;
    cout << "Would you like to load a previous game (enter 1) or start a new one (enter 2)?" << endl;

    std::cin >> menuSelector;
    //load game save
    if (menuSelector == 1) {
        menuSelector = 0; //selector resets so it can be used again for something else
        //load from file
        cout << "Not done yet :(";
        return 0;
    }
    //start new game
    else if (menuSelector == 2) {

        menuSelector = 0; //selector resets so it can be used again for something else
        cout << "Do you want to play with a friend on this device (press 1) or play with a simple AI (press 2)" << endl;
        std::cin >> menuSelector;

        //Player vs Player gamemode
        if (menuSelector == 1) {
            menuSelector = 0;

            cout << "Before playing, you need to place your ships (Max amount is 16). How many do you want to place? (Fleet size will be equal for both players)" << endl;
            int fleetSize;
            std::cin >> fleetSize;
            bool isFleetSizeValid = (fleetSize <= 16 && fleetSize >= 1) ? 1 : 0;
            while (isFleetSizeValid == 0) {
                cout << "Invalid input, please enter a number from 1 to 16" << endl;
                cin >> fleetSize;
                if (fleetSize <= 16 && fleetSize >= 1) isFleetSizeValid = 1;
            }
            int* pl1FleetHealth = new int[fleetSize];
            int* pl2FleetHealth = new int[fleetSize];
            initialiseGrids(pl1ShotBoard, pl1FleetBoard);
            initialiseGrids(pl2ShotBoard, pl2FleetBoard);
            initialiseArrays(fleetSize, pl1FleetHealth, pl2FleetHealth);

            //player 1 place ships:
            placingShipsUI(1, fleetSize, pl1FleetHealth, pl1FleetBoard);
            cout << endl;

            cout << "To proceed, Player 2 - press 1" << endl;
            menuSelector = 0;
            cin >> menuSelector;
            while (menuSelector != 1) {
                cout << "Invalid input" << endl;
            }

            //player 2 placing ships:
            cout << "Player 2's turn: " << endl;
            cout << "Fleet size: " << fleetSize << endl;
            placingShipsUI(2, fleetSize, pl2FleetHealth, pl2FleetBoard);

            menuSelector = 0;
            cout << "Start game (press 1, player 1 is first) or save game for later (press 2)" << endl;
            cin >> menuSelector;
            switch (menuSelector) {
            case 1: {
                int winner = startGame2Player();
                cout << "Player " << winner << " wins this match!";

            }
            case 2: {
                cout << "not done yet";

            }
            default:
                cout << "Invalid input" << endl;
                cin >> menuSelector;
                int isInputValid = (menuSelector == 1 || menuSelector == 2) ? 1 : 0;
                while (isInputValid == 0) {
                    cout << "Invalid input: Press 1 to start game or 2 to save" << endl;
                    cin >> menuSelector;
                    if (menuSelector == 1 || menuSelector == 2) isInputValid = 1;
                }
                break;
            }

            delete[] pl1FleetHealth;
            delete[] pl2FleetHealth;

            return 0;
        }
        //Player vs bot gamemode
        else if (menuSelector == 2) {
            cout << "Not done yet :(";
            return 0;
        }
        //Invalid input handling
        else {
            while (menuSelector != 1 && menuSelector != 2) {
                cout << "Invalid input, please enter 1 or 2" << endl;
                cin >> menuSelector;
            }
        }
    } 
    //input handling
    else {
        while (menuSelector != 1 && menuSelector != 2) {
            cout << "Invalid input, please enter 1 or 2" << endl;
            std::cin >> menuSelector;
        }
    }
}

