#pragma once
#include "HadarNofarCell.h"
#include "HadarNofarEnums.h"
#include "AbstractPlayer.h"
#include "HadarNofarAlgoPalyer.h"
#include "AlgorithmRegistration.h"
#include "HadarNofarSoldier.h"
#include "GameMove.h"
#include <map>
#include <list>
#include "PBoard.h"
#include <iostream>
#include <stdlib.h> 
#define _CRT_SECURE_NO_WARNINGS


class GameManager {
	enum { MIN_X = 1, MAX_X = 13, MIN_Y = 1, MAX_Y = 13 };
	HadarNofarCell board[(int)Sizes::size][(int)Sizes::size]; //13
	AbstractPlayer* gamers[(int)Sizes::sizeOfGamers]; //2
	int soldierDeadPlayer1 = 0, soldierDeadPlayer2 =0;
	int scorePlayer1=0, scorePlayer2 = 0;
	std::map<string, int> boardFile;
	map<string, int>::iterator currFileBoard;
	string path = "NULL";
	bool GameOver = false, ifBoardFile = false;
	int SetACounter = 0, SetBCounter = 0;
	int setSol1 = 0, setSol2 = 0, setSol3 = 0, setSol7 = 0, setSol8 = 0, setSol9 = 0;
	string wrongCharsSet;
	int delay = 20;
	PBoard PBoardForPlayer1;
	PBoard PBoardForPlayer2;
	char winner = 0;
	int numberOfGame = 10;
public:
	//ctor
	GameManager() {

		initPlayers();
		gamers[0]->setPlayer(1);
		gamers[1]->setPlayer(2);
		hideCursor();
	}
	//functions
	void setRandomBoard();
	void paramMenager();
	void init();
	void initPlayers();
	void setSoldiersRandom();
	void run();
	bool movementValidation(GameMove& gameMove, HadarNofarSoldier* sol);
	void soliderMovementOnBoard(int from_x, int from_y, int to_x ,int to_y);
	bool move(GameMove& gameMove, int gamerNum);
	bool attack(int currSoldierNum, int enemyNum, int _x, int _y);
	bool oneIsAttack(int _x, int _y);
	bool twoIsAttack(int enemyNum, int _x, int _y);
	bool threeIsAttack(int _x, int _y);
	bool sevenIsAttack(int enemyNum, int _x, int _y);
	bool eightIsAttack(int enemyNum, int _x, int _y);
	bool nineIsAttack(int enemyNum, int _x, int _y);
	void win(int gamerNum);
	void openFolder(char* tempPath);
	void setBoard();
	void uploadBoardFromFile();
	void setBoardFromFile(ifstream& inFile);
	void updateSetSoliderCounter(int solider);
	bool printAndCheckBoardFromFileErrors(string fileName) const;
	void divideToFile(char *buffer);
	void commandLine(int argc, char* argv[]);
	ifstream openfile(map<string, int>::iterator file);
	void endMessage() const;
	bool updateDeadSoliderCounter(int gamerNum, bool win);
	void printBoard() const;
	void printLetters() const;
	void printEndLine()const;
	void printNumber(int num) const;
	void printing() const;
	void drowSoldiers()const;
	void clearTheGame();
	void endMessagePerGame(int GameCycle, int numOfMoves) const;
	void printSpecialCell(int oldX, int oldY);
};
