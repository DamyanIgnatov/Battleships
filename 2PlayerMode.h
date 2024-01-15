#pragma once

const int SIZE = 10;

bool isFleetDestroyed(int* fleetHealth, int size);
int countLostShips(int* fleetHealth, int size);

bool shootAt(char** FleetGrid, int* shipHealth, unsigned X, unsigned Y, int** ShotGrid);
void startGame2Player(char** pl1FleetBoard, char** pl2FleetBoard,
    int** pl1ShotBoard, int** pl2ShotBoard,
    int* pl1Health, int* pl2Health, 
    int fleetSize, int gridSize);