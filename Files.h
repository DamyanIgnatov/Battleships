#pragma once

void saveGame(int gameMode, int round, int fleetSize, int boardSize, char** pl1Fleet, char** pl2Fleet, char** pl1Shots, char** pl2Shots, int* pl1Health, int* pl2Health);
void getSizes(int &gameMode, int &round, int &fleetSize, int &boardSize);
void getBoards(char** pl1Fleet, char** pl1Shots, int* pl1Health, char** pl2Fleet, char** pl2Shots, int* pl2Health, int boardSize, int fleetSize);