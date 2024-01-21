#pragma once

const int SIZE = 10;

bool isFleetDestroyed(int* fleetHealth, int size);
int countLostShips(int* fleetHealth, int size);

bool shootAt(char** FleetGrid, int* shipHealth, unsigned X, unsigned Y, char** ShotGrid);
void startGame2Player(char** pl1FleetBoard, char** pl2FleetBoard,
    char** pl1ShotBoard, char** pl2ShotBoard,
    int* pl1Health, int* pl2Health, 
    int fleetSize, int gridSize);