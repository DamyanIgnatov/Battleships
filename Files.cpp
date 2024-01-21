#include <iostream>
#include <fstream>
using namespace std;


void getSizes(int &gameMode, int &round, int &fleetSize, int &boardSize) {
	ifstream saveFile("battleshipsGameSaveSizes.txt");
	if (!saveFile.is_open()) {
		cout << "No save state found" << endl;
		return;
	}
		
	const size_t stringSize = 2;
	char currentElement[stringSize];
	saveFile.getline(currentElement, stringSize);
	gameMode = currentElement[0] - '0';
	saveFile.getline(currentElement, stringSize);
	round = currentElement[0] - '0';
	saveFile.getline(currentElement, stringSize);
	fleetSize = currentElement[0] - '0';
	saveFile.getline(currentElement, stringSize);
	boardSize = currentElement[0] - '0';

	saveFile.close();
	return;
}
void getBoards(char** pl1Fleet, char** pl1Shots, int* pl1Health, char** pl2Fleet, char** pl2Shots, int* pl2Health, int boardSize, int fleetSize) {
	ifstream saveFile("battleshipsGameSaveBoards.txt");
	if (!saveFile.is_open()) {
		cout << "No save state found" << endl;
		return;
	}
	const size_t stringSize = 2;
	char currentElement[stringSize];
	//loading player 1 fleet
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			saveFile.getline(currentElement, stringSize);
			pl1Fleet[i][j] = currentElement[0];
		}
	};
	//loading player 2 fleet
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			saveFile.getline(currentElement, stringSize);
			pl2Fleet[i][j] = currentElement[0];
		}
	}
	//loading player 1 shots
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			saveFile.getline(currentElement, stringSize);
			pl1Shots[i][j] = currentElement[0];
		}
	}
	//loading player 2 shots
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			saveFile.getline(currentElement, stringSize);
			pl2Shots[i][j] = currentElement[0];
		}
	}
	//loading player 1 health
	for (int i = 0; i < fleetSize; i++) {
		saveFile.getline(currentElement, stringSize);
		pl1Health[i] = currentElement[0] - '0';
	}
	//loading player 2 health
	for (int i = 0; i < fleetSize; i++) {
		saveFile.getline(currentElement, stringSize);
		pl2Health[i] = currentElement[0] - '0';
	}
}

void saveGame(int gameMode, int round, 
	int fleetSize, int boardSize, 
	char** pl1Fleet, char** pl2Fleet, 
	char** pl1Shots, char** pl2Shots, 
	int* pl1Health, int* pl2Health) {

	ofstream sizesSaveFile("battleshipsGameSaveSizes.txt");
	if (!sizesSaveFile.is_open()) return;
	sizesSaveFile << gameMode << endl;
	sizesSaveFile << round << endl;
	sizesSaveFile << fleetSize << endl;
	sizesSaveFile << boardSize << endl;

	sizesSaveFile.close();

	ofstream saveFile("battleshipsGameSaveBoards.txt");
	if (!saveFile.is_open()) return;
	//save player 1's fleet
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			saveFile << pl1Fleet[i][j] << endl;
		}
	}
	//save player 2's fleet
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			saveFile << pl2Fleet[i][j] << endl;
		}
	}

	//save player 1's shots:
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			saveFile << pl1Shots[i][j] << endl;
		}
	}
	//save player 2's shots:
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			saveFile << pl2Shots[i][j] << endl;
		}
	}

	//save player 1's health:
	for (int i = 0; i < fleetSize; i++) {
		saveFile << pl1Health[i] << endl;
	}
	//save player 2's health:
	for (int i = 0; i < fleetSize; i++) {
		saveFile << pl2Health[i] << endl;
	}

	saveFile.close();
}