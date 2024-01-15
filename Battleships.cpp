#include <iostream>
#include "2PlayerMode.h" 
using namespace std;

void initialiseGrids(int** gridInt, char** gridChar, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
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

int setFieldSize() {
    int playingFieldSize;
    cout << "First of all, you need to set the size of the playing field" << endl;
    cout << "Enter playing field size (minimum is 2, max is 32): ";
    cin >> playingFieldSize;
    bool isFieldValid = true;
    if (playingFieldSize < 2 || playingFieldSize > 32) isFieldValid = false;
    while (isFieldValid == false) {
        cout << "Playing field size invalid, enter a number between 1 and 32" << endl;
        cin >> playingFieldSize;
        if (playingFieldSize >= 2 && playingFieldSize <= 32) isFieldValid = true;
    }
    cout << "Playing field for both players set to size " << playingFieldSize << " x " << playingFieldSize << endl;

    return playingFieldSize;
}
int setFleetSize(int fieldSize) {
    cout << "Before playing, you need to place your ships (Max amount is "<< fieldSize/2 << ")" << endl;
    cout<<". How many do you want to place? (Fleet size will be equal for both players)" << endl;
    int fleetSize;
    std::cin >> fleetSize;
    bool isFleetSizeValid = (fleetSize <= fieldSize/2 && fleetSize >= 1) ? true : false;
    while (isFleetSizeValid == false) {
        cout << "Invalid input, please enter a number from 1 to " << fieldSize/2 << endl;
        cin >> fleetSize;
        if (fleetSize <= 16 && fleetSize >= 1) isFleetSizeValid = 1;
    }

    return fleetSize;
}

void deleteMatrix(int** intMatrix, char** charMatrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] intMatrix[i];
        delete[] charMatrix[i];
    }
    delete[] intMatrix;
    delete[] charMatrix;
}

void printCharFleetGrid(char** grid, int gridSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isSpotFree(char** FleetGrid, unsigned startX, unsigned startY, unsigned endX, unsigned endY) {
    if (startX == endX) {   //ship is trying to place horisontally
        int startPoint = (startY < endY) ? startY : endY;
        int endPoint = (startPoint == startY) ? endY : startY;
        for (int i = startPoint;i < endPoint; i++) {
            if (FleetGrid[startX][i] != '*') return 0;
        }
        return 1;
    }
    else {  //Y coordinates are the same - ship is trying to place vertically
        int startPoint = (startX < endX) ? startX : endX;
        int endPoint = (startPoint == startX) ? endX : startX;
        for (int i = startPoint; i < endPoint; i++) {
            if (FleetGrid[i][startY] != '*') return 0;
        }
        return 1;
    }
}
int placeShips(char** FleetGrid, const unsigned gridSize, unsigned const shipIndex) {
    int startX, startY, endX, endY;

    cout << "Please enter the coordinates of the ship's ends" << endl;
    cout << "Start grid space (Format: x y): ";
    std::cin >> startX >> startY;
    cout << "End grid space (Format: x y): ";
    std::cin >> endX >> endY;

    bool isValidCoords = true;
    int num1 = endX - startX;
    int num2 = endY - startY;
    if (startX < 0 || endX >= gridSize || startY < 0 || endY >= gridSize    //-3 0, 3 0 or 10 0, 4 0 - out of bounds
        || abs(num1) > 4 || abs(num2) > 4                                   //0 0, 0 5 - too long
        || (startX == endX && startY == endY)                               //1 1 1 1 - too short
        || (startX != endX && startY != endY)                               //1 2 2 1 - diagonal/invalid orientation
        || !isSpotFree(FleetGrid, startX, startY, endX, endY)               //trying to place a ship over another ship 
        || (unsigned)abs(num1) > gridSize                                   //ship too long to fit into playing field
        || (unsigned)abs(num2) > gridSize) {                                //ship too long to fit into playing field
        isValidCoords = false;
    }   
        

    while (isValidCoords == false) {
        cout << "Your input seems to be invalid, please rethink it" << endl;
        cout << "Start grid space (Format: x y): ";
        std::cin >> startX >> startY;
        cout << "End grid space (Format: x y): ";
        std::cin >> endX >> endY;
        if (startX > 0 && endX < gridSize && startY > 0 && endY < gridSize //0 9 0 9 - OK
            && abs(endX -= endY) <= 4 && abs(startX -= startY) <= 4     //0 0, 0 4 - OK (max length)
            && (startX == endX && startY != endY                        //1 0, 1 2 - OK (horizontal)
                || startY == endY && startX != endX)                    //1 3, 3 3 - OK (vertical)
                && isSpotFree(FleetGrid,startX,startY,endX,endY)        //placed ship not going over another
                && abs(endX -= endY) <= gridSize                        //placed ship fits into the playing field
                && abs(startX -= startY) <= gridSize)      
            isValidCoords = 1;
    }

    if (startX == endX) {//placing ship vertically
        if (startY > endY) swap(startY, endY);
        for (unsigned i = startY; i <= endY; i++) {
            FleetGrid[startX][i] = shipIndex + '0';
        }
        return(abs(startY -= endY) + 1);
    }
    else if (startY == endY) {//placing ship horisontally
        if (startX > endX) swap(startX, endX);
        for (unsigned j = startX; j <= endX; j++) {
            FleetGrid[j][startY] = shipIndex + '0';
        }
        return(abs(startX -= startY) + 1);
    }
}
void placingShipsUI(int playerNumber, int fleetSize, int* fleetHealth, char** fleetGrid, int gridSize) {
    cout << "Player " << playerNumber << "'s turn:" << endl;
    cout << "You need to place " << fleetSize << " ships";
    int index = 0;
    while (index < fleetSize) {
        int shipLength = placeShips(fleetGrid, gridSize, index);
        switch (shipLength) {
        case 2: {
                fleetHealth[index] = 2;
                cout << "You placed Patrol boat" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid, gridSize);
                break;
            }
            case 3: {
                fleetHealth[index] = 3;
                cout << "You placed submarine" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid, gridSize);
                break;
            }
            case 4: {
                fleetHealth[index] = 4;
                cout << "You placed destroyer" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid, gridSize);
                break;
            }
            case 5: {
                fleetHealth[index] = 5;
                cout << "You placed aircraft carrier" << endl;
                cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid, gridSize);
                break;
            }
            default: {
                cout << "Something went wrong here, please restart or check your inputs" << endl;
                break;
            }
        }
        if ((fleetSize - index - 1) > 0) cout << "You have to place " << fleetSize - index - 1 << " more ships" << endl;
        index++;
    }
    cout << "Player " << playerNumber << " has finished placing ships" << endl;
    cout << "Your ships' health: " << endl;
    for (int i = 0; i < fleetSize; i++) {
        cout << "Ship " << i << ": " << fleetHealth[i] << " points" << endl;
    }
    cout << "--------------------------------------------------------------------------" << endl;

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
        cout << "Game loading from save, home screen. Not done yet.";
        return 0;
    }

    //start new game
    else if (menuSelector == 2) {
        menuSelector = 0; //selector resets so it can be used again for something else        
        int playingFieldSize = setFieldSize();
        int fleetSize = setFleetSize(playingFieldSize);

        cout << "All set. Choose your gamemode: " << endl;
        cout << "Play with a friend on this device - press 1" << endl;
        cout<< "Play with a simple AI - press 2" << endl;
        std::cin >> menuSelector;

        //Player vs Player gamemode
        if (menuSelector == 1) {
            menuSelector = 0;

            int* pl1FleetHealth = new int[fleetSize];
            int* pl2FleetHealth = new int[fleetSize];
            initialiseArrays(fleetSize, pl1FleetHealth, pl2FleetHealth);

            char** pl1FleetBoard = new char* [playingFieldSize];
            for (int i = 0; i < playingFieldSize; i++) {
                pl1FleetBoard[i] = new char[playingFieldSize];
            }
            int** pl1ShotBoard = new int* [playingFieldSize];
            for (int i = 0; i < playingFieldSize; i++) {
                pl1ShotBoard[i] = new int[playingFieldSize];
            }
            initialiseGrids(pl1ShotBoard, pl1FleetBoard, playingFieldSize);

            char** pl2FleetBoard = new char* [playingFieldSize];
            for (int i = 0; i < playingFieldSize; i++) {
                pl2FleetBoard[i] = new char[playingFieldSize];
            }
            int** pl2ShotBoard = new int* [playingFieldSize];
            for (int i = 0; i < playingFieldSize; i++) {
                pl2ShotBoard[i] = new int[playingFieldSize];
            }
            initialiseGrids(pl2ShotBoard, pl2FleetBoard, playingFieldSize);


            //player 1 place ships:
            placingShipsUI(1, fleetSize, pl1FleetHealth, pl1FleetBoard, playingFieldSize);

            cout << "Ship placement ended! When you wish to continue, press 1" << endl;
            menuSelector = 0;
            cin >> menuSelector;
            while (menuSelector != 1) {
                cout << "Invalid input" << endl;
            }
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

            //player 2 placing ships:
            placingShipsUI(2, fleetSize, pl2FleetHealth, pl2FleetBoard, playingFieldSize);
            cout << "Player 2\'s ship placement has ended! To start game, press 1 (player 2 is first) or save game for later (press 2)" << endl;


            //game starting or saving current progress
            menuSelector = 0;            
            cin >> menuSelector;
            switch (menuSelector) {
            case 1: {
                cout << "------------------------------------------------" << endl;
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                startGame2Player(pl1FleetBoard,pl2FleetBoard,
                                pl1ShotBoard,pl2ShotBoard,
                    pl1FleetHealth,pl2FleetHealth, 
                    fleetSize, playingFieldSize);
                break;
                return 0;
            }
            case 2: {
                cout << "This is the saving game UI, not done";
                break;
                return 0;
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
            deleteMatrix(pl1ShotBoard, pl1FleetBoard, playingFieldSize);
            deleteMatrix(pl2ShotBoard, pl2FleetBoard, playingFieldSize);

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

