#include <iostream>
#include<time.h>
#include <cstdlib>
#include "2PlayerMode.h" 
#include "1PlayerMode.h"
#include "Files.h"
using namespace std;

void initialiseGrids(char** shotGrid, char** fleetGrid, int size) {
    shotGrid[0][0] = fleetGrid[0][0] = '#';
    for (int i = 1; i < size; i++) {
        shotGrid[0][i] = fleetGrid[0][i] = '0' + i - 1;
    }
    for (int i = 1; i < size; i++) {
        shotGrid[i][0] = fleetGrid[i][0] = 'A' + i - 1;
    }
    for (int i = 1; i < size; i++) {
        for (int j = 1; j < size; j++) {
            fleetGrid[i][j] = shotGrid[i][j] = '*';
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
    const int MIN_SIZE = 3;
    const int MAX_SIZE = 10;
    std::cout << "First of all, you need to set the size of the playing field" << endl;
    std::cout << "Enter playing field size (minimum is 3, max is 10): ";
    while (true) {
        std::cin >> playingFieldSize;
        if (std::cin.fail() || playingFieldSize < MIN_SIZE || playingFieldSize > MAX_SIZE) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Playing field size invalid, enter a number between 3 and 10" << endl;
        }
        else {
            break;
        }
    }
    std::cout << "Playing field for both players set to size " << playingFieldSize << " x " << playingFieldSize << endl;

    return playingFieldSize + 1;
}
int setFleetSize(int fieldSize) {
    const int MIN_SIZE = 1;
    const int MAX_SIZE = fieldSize / 2;
    std::cout << "Before playing, you need to place your ships (Max amount is "<< MAX_SIZE << ")" << endl;
    std::cout<<". How many do you want to place? (Fleet size will be equal for both players)" << endl;
    int fleetSize;
    while (true) {
        std::cin >> fleetSize;
        if (std::cin.fail() || fleetSize > MAX_SIZE || fleetSize < MIN_SIZE) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Fleet size invalid, please enter a number from 1 to " << fieldSize / 2 << endl;
        }
        else {
            break;
        }
    }
    std::cout << "Fleet size is set to " << fleetSize << " ships for both players." << endl;
    return fleetSize;
}

void deleteCharMatrix(char** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printCharFleetGrid(char** grid, int gridSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << endl;
    }
    std::cout << endl;
}

bool isSpotFree(char** FleetGrid, unsigned startX, unsigned startY, unsigned endX, unsigned endY) {
    if (startX == endX) {   //ship is trying to place horisontally
        int startPoint = (startY < endY) ? startY : endY;
        int endPoint = (startPoint == startY) ? endY : startY;
        for (int i = startPoint;i <= endPoint; i++) {
            if (FleetGrid[startX][i] != '*') return 0;
        }
        return 1;
    }
    else {  //Y coordinates are the same - ship is trying to place vertically
        int startPoint = (startX < endX) ? startX : endX;
        int endPoint = (startPoint == startX) ? endX : startX;
        for (int i = startPoint; i <= endPoint; i++) {
            if (FleetGrid[i][startY] != '*') return 0;
        }
        return 1;
    }
}
int placeShips(char** FleetGrid, const unsigned gridSize, unsigned const shipIndex) {
    char charStartX, charStartY;
    char charEndX, charEndY;
    
    std::cout << "Please enter the coordinates of the ship's ends" << endl;
    std::cout << "Start grid space: ";
    std::cin >> charStartX >> charStartY;
    std::cout << "End grid space: ";
    std::cin >> charEndX >> charEndY;

    int startX = charStartX - 'A' + 1;
    int startY = charStartY - '0' + 1;
    //in case start coordinates go out of bounds
    while (startX < 0 || startX > gridSize || startY < 0 || startY > gridSize) {
        std::cout << "Your input seems to be invalid, please rethink it" << endl;
        std::cout << "Start grid space: ";
        std::cin >> charStartX >> charStartY;
        startX = charStartX - 'A' + 1;
        startY = charStartY - '0' + 1;
    }
    int endX = charEndX - 'A' + 1;
    int endY = charEndY - '0' + 1;
    //in case end coordinates go out of bounds
    while (endX < 0 || endX > gridSize || endY < 0 || endY > gridSize) {
        std::cout << "Your input seems to be invalid, please rethink it" << endl;
        std::cout << "End grid space: ";
        std::cin >> charEndX >> charEndY;
        endX = charEndX - 'A' + 1;
        endY = charEndY - '0' + 1;
    }
    int num1 = endX - startX;
    int num2 = endY - startY;
    bool isValidCoords = true;

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
        std::cout << "Your input seems to be invalid, please rethink it" << endl;
        std::cout << "Start grid space: ";
        std::cin >> charStartX >> charStartY;
        while (charStartX < 'A' || charStartX > 'A' + gridSize - 1 || charStartY < '0' || charStartY > '0' + gridSize - 1) {
            std::cout << "Your input seems to be invalid, please rethink it" << endl;
            std::cout << "Start grid space: ";
            std::cin >> charStartX >> charStartY;
        }
        std::cout << "End grid space: ";
        std::cin >> charEndX >> charEndY;
        while (charEndX < 'A' || charEndX > 'A' + gridSize - 1 || charEndY < '0' || charEndY > '0' + gridSize - 1) {
            std::cout << "Your input seems to be invalid, please rethink it" << endl;
            std::cout << "End grid space: ";
            std::cin >> charEndX >> charEndY;
        }

        startX = charStartX - 'A' + 1;
        startY = charStartY - '0' + 1;
        endX = charEndX - 'A' + 1;
        endY = charEndY - '0' + 1;
        num1 = endX - startX;
        num2 = endY - startY;
        if (startX > 0 && endX < gridSize && startY > 0 && endY < gridSize  //0 9 0 9 - OK
            && (abs(num1) <= 4 || abs(num2) <= 4)                           //0 0, 0 4 - OK (max length)
            && (startX == endX && startY != endY                            //1 0, 1 2 - OK (horizontal)
                || startY == endY && startX != endX)                        //1 3, 3 3 - OK (vertical)
            && isSpotFree(FleetGrid, startX, startY, endX, endY)            //placed ship not going over another
            && abs(num1) <= gridSize                                        //placed ship fits into the playing field
            && abs(num2) <= gridSize) {
            isValidCoords = 1;
        }
            
    }

    if (startX == endX) {//A0 A3 - Horizontal ship
        if (startY > endY) swap(startY, endY);
        for (unsigned i = startY; i <= endY; i++) {
            FleetGrid[startX][i] = shipIndex + '0';
        }
        return(abs(startY -= endY) + 1);
    }
    else if (startY == endY) {//A0 C0 - Vertical ship
        if (startX > endX) swap(startX, endX);
        for (unsigned j = startX; j <= endX; j++) {
            FleetGrid[j][startY] = shipIndex + '0';
        }
        return(abs(startX -= endX) + 1);
    }
}
void placingShipsUI(int playerNumber, int fleetSize, int* fleetHealth, char** fleetGrid, int gridSize) {
    std::cout << "Player " << playerNumber << "'s turn:" << endl;
    std::cout << "Your fleet board:" << endl;
    printCharFleetGrid(fleetGrid, gridSize);
    std::cout << "You need to place " << fleetSize << " ships"<<endl;
    int index = 0;
    while (index < fleetSize) {
        int shipLength = placeShips(fleetGrid, gridSize, index);
        switch (shipLength) {
        case 2: {
                fleetHealth[index] = 2;
                std::cout << "You placed Patrol boat" << endl;
                std::cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid, gridSize);
                break;
            }
            case 3: {
                fleetHealth[index] = 3;
                std::cout << "You placed submarine" << endl;
                std::cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid, gridSize);
                break;
            }
            case 4: {
                fleetHealth[index] = 4;
                std::cout << "You placed destroyer" << endl;
                std::cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid, gridSize);
                break;
            }
            case 5: {
                fleetHealth[index] = 5;
                std::cout << "You placed aircraft carrier" << endl;
                std::cout << "Your fleet currently: " << endl;
                printCharFleetGrid(fleetGrid, gridSize);
                break;
            }
            default: {
                std::cout << "Something went wrong here, please restart or check your inputs" << endl;
                break;
            }
        }
        if ((fleetSize - index - 1) > 0) std::cout << "You have to place " << fleetSize - index - 1 << " more ships" << endl;
        index++;
    }
    std::cout << "Player " << playerNumber << " has finished placing ships" << endl;
    std::cout << "Your ships' health: " << endl;
    for (int i = 0; i < fleetSize; i++) {
        std::cout << "Ship " << i << ": " << fleetHealth[i] << " points" << endl;
    }
    std::cout << "--------------------------------------------------------------------------" << endl;

}



int main()
{
    int menuSelector;  //used for various confirmations and choosing options in the UI
    std::cout << "Welcome to Damyan's Battleships" << endl;
    std::cout << "Would you like to load a previous game (enter 1) or start a new one (enter 2)?" << endl;

    //input validation
    while (true) {
        std::cin >> menuSelector;
        if (std::cin.fail() || (menuSelector != 1 && menuSelector != 2)) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input, please enter 1 or 2" << endl;
        }
        else break;
    }
    //load game save
    if (menuSelector == 1) {        
        //load gamemode, round, fleet size and board size from file
        int gamemode = 0, round = 0, fleetSize = 0, playingFieldSize = 0;
        getSizes(gamemode, round, fleetSize, playingFieldSize);
        
        //create the boards
        char** pl1FleetBoard = new char* [playingFieldSize];
        for (int i = 0; i < playingFieldSize; i++) {
            pl1FleetBoard[i] = new char[playingFieldSize];
        }
        char** pl1ShotBoard = new char* [playingFieldSize];
        for (int i = 0; i < playingFieldSize; i++) {
            pl1ShotBoard[i] = new char[playingFieldSize];
        }
        int* pl1FleetHealth = new int[fleetSize];

        char** pl2FleetBoard = new char* [playingFieldSize];
        for (int i = 0; i < playingFieldSize; i++) {
            pl2FleetBoard[i] = new char[playingFieldSize];
        }
        char** pl2ShotBoard = new char* [playingFieldSize];
        for (int i = 0; i < playingFieldSize; i++) {
            pl2ShotBoard[i] = new char[playingFieldSize];
        }
        int* pl2FleetHealth = new int[fleetSize];
        //load all boards and arrays from file
        getBoards(pl1FleetBoard, pl1ShotBoard, pl1FleetHealth, pl2FleetBoard, pl2ShotBoard, pl2FleetHealth,playingFieldSize,fleetSize);

        if (gamemode == 1) {//2 player mode
            cout << "2 player mode starting, player " << ((round % 2 != 0) ? 1 : 2) << " is first. Press 1 to continue" << endl;
            while (true) {
                cin >> menuSelector;
                if (cin.fail() || menuSelector != 1) {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input, press 1 to continue" << endl;
                }
                else break;
            }
            startGame2Player(pl1FleetBoard,pl2FleetBoard,pl1ShotBoard,pl2ShotBoard,pl1FleetHealth,pl2FleetHealth,fleetSize,playingFieldSize,round);
        }
        else {
            cout << "Player vs AI mode starting, player " << ((round % 2 != 0) ? 1 : 2) << " is first. Press 1 to continue" << endl;
            while (true) {
                cin >> menuSelector;
                if (cin.fail() || menuSelector != 1) {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input, press 1 to continue" << endl;
                }
                else break;
            }
            startGame1Player(pl1FleetBoard, pl2FleetBoard, pl1ShotBoard, pl2ShotBoard, pl1FleetHealth, pl2FleetHealth, fleetSize, playingFieldSize, round);
        }

        delete[] pl1FleetHealth;
        delete[] pl2FleetHealth;
        deleteCharMatrix(pl1ShotBoard, playingFieldSize);
        deleteCharMatrix(pl2FleetBoard, playingFieldSize);
        deleteCharMatrix(pl2ShotBoard, playingFieldSize);
        deleteCharMatrix(pl2FleetBoard, playingFieldSize);
        return 0;
    }

    //start new game
    if (menuSelector == 2) {           
        //setting field size
        int playingFieldSize = setFieldSize();
        //creating and initialising boards
        char** pl1FleetBoard = new char* [playingFieldSize];
        for (int i = 0; i < playingFieldSize; i++) {
            pl1FleetBoard[i] = new char[playingFieldSize];
        }
        char** pl1ShotBoard = new char* [playingFieldSize];
        for (int i = 0; i < playingFieldSize; i++) {
            pl1ShotBoard[i] = new char[playingFieldSize];
        }
        initialiseGrids(pl1ShotBoard, pl1FleetBoard, playingFieldSize);

        char** pl2FleetBoard = new char* [playingFieldSize];
        for (int i = 0; i < playingFieldSize; i++) {
            pl2FleetBoard[i] = new char[playingFieldSize];
        }
        char** pl2ShotBoard = new char* [playingFieldSize];
        for (int i = 0; i < playingFieldSize; i++) {
            pl2ShotBoard[i] = new char[playingFieldSize];
        }
        initialiseGrids(pl2ShotBoard, pl2FleetBoard, playingFieldSize);
        std::cout << "Here is how the playing fields will look:" << endl;
        printCharFleetGrid(pl1FleetBoard, playingFieldSize);

        int fleetSize = setFleetSize(playingFieldSize);
        int* pl1FleetHealth = new int[fleetSize];
        int* pl2FleetHealth = new int[fleetSize];
        initialiseArrays(fleetSize, pl1FleetHealth, pl2FleetHealth);        

        std::cout << "All set. Choose your gamemode: " << endl;
        std::cout << "Play with a friend on this device - press 1" << endl;
        std::cout<< "Play with a simple AI - press 2" << endl;
        //Invalid input handling
        while (true) {
            std::cin >> menuSelector;
            if (std::cin.fail() || (menuSelector != 1 && menuSelector != 2)) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Invalid input, please enter 1 or 2" << endl;
            }
            else break;
        }
        int gamemode = menuSelector;
        //Player vs Player gamemode
        if (menuSelector == 1) {            
            //player 1 place ships:
            placingShipsUI(1, fleetSize, pl1FleetHealth, pl1FleetBoard, playingFieldSize);
            std::cout << "Ship placement ended! When you wish to continue, press 1" << endl;
            while (true) {
                std::cin >> menuSelector;
                if (std::cin.fail() || menuSelector != 1) {
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Invalid input, press 1" << endl;
                }
                else break;
            }
            
            //std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

            //player 2 placing ships:
            placingShipsUI(2, fleetSize, pl2FleetHealth, pl2FleetBoard, playingFieldSize);
            std::cout << "Player 2\'s ship placement has ended! To start game, press 1 (player 2 is first) or save game for later (press 2)" << endl;


            //game starting or saving current progress          
            while (true) {
                std::cin >> menuSelector;
                if (std::cin.fail() || (menuSelector != 1 && menuSelector != 2)) {
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Invalid input: Press 1 to start game or 2 to save" << endl;
                }
                else break;
            }
            if(menuSelector == 1) {
                std::cout << "------------------------------------------------" << endl;
                std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                startGame2Player(pl1FleetBoard,pl2FleetBoard,
                                pl1ShotBoard,pl2ShotBoard,
                    pl1FleetHealth,pl2FleetHealth, 
                    fleetSize, playingFieldSize, 1);
                return 0;
            }
            else {
                std::cout << "Game saved to file";
                int round = 0;//saving game before it has started
                saveGame(gamemode, round, fleetSize, playingFieldSize, pl1FleetBoard, pl2FleetBoard, pl1ShotBoard, pl2ShotBoard, pl1FleetHealth, pl2FleetHealth);
            }

            delete[] pl1FleetHealth;
            delete[] pl2FleetHealth;
            deleteCharMatrix(pl1ShotBoard, playingFieldSize);
            deleteCharMatrix(pl2FleetBoard, playingFieldSize);
            deleteCharMatrix(pl2ShotBoard, playingFieldSize);
            deleteCharMatrix(pl2FleetBoard, playingFieldSize);

            return 0;
        }

        //Player vs bot gamemode
        else if (menuSelector == 2) {
            placingShipsUI(1, fleetSize, pl1FleetHealth, pl1FleetBoard, playingFieldSize);
            std::cout << "Ship placement ended! When you wish to continue, press 1" << endl;            
            while (true) {
                std::cin>>menuSelector;
                if (std::cin.fail() || menuSelector != 1) {
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Invalid input, please enter 1" << endl;
                }
                else break;
            }         

            srand(time(0));
            const int range = playingFieldSize - 1;
            const int minVal = 1;
            const int lengthRange = 4;

            //setting random starting points and saving them
            for (int i = 0; i < fleetSize; i++) {
                //generation of start position
                int endX, endY;
                int xDiff, yDiff;
                int startX, startY;
                int length = 0;
                int orientation = rand() % 2; //this variable chooses whether to place the ship horisontally (0) or vertically (1)
                if (orientation == 0) { //horisontal ship
                    startX = rand() % range + minVal;
                    startY = rand() % range + minVal;
                    endX = startX;
                    endY = rand() % range + minVal;//let's say we have a startY coordinate of 4 - endY can be 5, 6, 7 or 8
                    yDiff = startY - endY;                    
                    length = abs(yDiff) + 1;
                }
                else {  //vertical ship
                    startX = rand() % range + minVal;
                    startY = rand() % range + minVal;
                    endY = startY;
                    endX = rand() % range + minVal;
                    xDiff = startX - endX;
                    length = abs(xDiff) + 1;
                }                
                //if coordinates are invalid
                while (startX < 1 || startY < 1 || endX < 1 || endY < 1
                    || startX >= playingFieldSize || endX >= playingFieldSize || startY >= playingFieldSize || endY >= playingFieldSize 
                    || length < 2 || length > 5 
                    || (startX != endX && startY != endY) 
                    || !isSpotFree(pl2FleetBoard, startX, startY, endX, endY)) {
                    //regenerate direction and ends
                    int orientation = rand() % 2;
                    if (orientation == 0) {
                        startX = rand() % range + minVal;
                        startY = rand() % range + minVal;
                        endX = startX;
                        endY = rand() % range + minVal;
                        yDiff = startY - endY;
                        length = abs(yDiff) + 1;
                    }
                    else {
                        startX = rand() % range + minVal;
                        startY = rand() % range + minVal;
                        endY = startY;
                        endX = rand() % range + minVal;
                        xDiff = startX - endX;
                        length = abs(xDiff) + 1;
                    }                    
                }
                if (startX == endX) {
                    yDiff = startY - endY;
                    length = abs(yDiff) + 1;
                }
                else if(startY == endY) {
                    xDiff = startX - endX;
                    length = abs(xDiff) + 1;
                }
                pl2FleetHealth[i] = length;               
                placeRandomShip(pl2FleetBoard, playingFieldSize, startX,startY, endX, endY, i);
            }            

            std::cout << "AI\'s fleet:" << endl;
            printCharFleetGrid(pl2FleetBoard, playingFieldSize);

            std::cout << "AI\'s health:" << endl;
            for (int i = 0; i < fleetSize; i++) {
                std::cout << pl2FleetHealth[i] << " ";
            }
            std::cout << endl;

            std::cout << "AI has placed their " << fleetSize << " ships" << endl;
            std::cout << "Press 1 to start game or press 2 to save progress" << endl;
            std::cin >> menuSelector;
            while (true || (menuSelector != 1 && menuSelector != 2)) {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Invalid input, please enter 1 or 2" << endl;
                }
                else break;
            }
            if (menuSelector == 1) {
                startGame1Player(pl1FleetBoard, pl2FleetBoard, pl1ShotBoard, pl2ShotBoard, pl1FleetHealth, pl2FleetHealth, fleetSize, playingFieldSize, 1);
            }
            else {
                std::cout << "Game saved to file";
                int round = 0;//saving game before it has started
                saveGame(gamemode, round, fleetSize, playingFieldSize, pl1FleetBoard, pl2FleetBoard, pl1ShotBoard, pl2ShotBoard, pl1FleetHealth, pl2FleetHealth);
            }

            delete[] pl1FleetHealth;
            delete[] pl2FleetHealth;
            deleteCharMatrix(pl1ShotBoard, playingFieldSize);
            deleteCharMatrix(pl2FleetBoard, playingFieldSize);
            deleteCharMatrix(pl2ShotBoard, playingFieldSize);
            deleteCharMatrix(pl2FleetBoard, playingFieldSize);

            return 0;
        }
    } 
}

