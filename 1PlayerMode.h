#pragma once

void placeRandomShip(char** fleetGrid, int gridSize, int startX, int startY, int endX, int endY, int index);
void startGame1Player(char** pl1Fleet, char** pl2Fleet, char** pl1Shots, char** pl2Shots, int* pl1Health, int* pl2Health, int fleetSize, int boardSize, int round);
