#pragma once
#include "Cell.h"
#include "enums.h"
#include "AbstractPlayer.h"
#include "AlgoPalyer.h"
#include "Soldier.h"
#include "GameMove.h"
#include <map>
#include "PBoard.h"
#define _CRT_SECURE_NO_WARNINGS

class GameManager {
	enum { MIN_X = 1, MAX_X = 13, MIN_Y = 1, MAX_Y = 13 };
	Cell board[(int)Sizes::size][(int)Sizes::size]; //13
	AbstractPlayer* gamers[(int)Sizes::sizeOfGamers]; //2
	AlgoPalyer algoPlayer[(int)Sizes::sizeOfGamers];
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
	PBoard mainPboard;
public:
	//ctor
	GameManager() {
		//setRandomBoard();
		gamers[0] = &algoPlayer[0];
		gamers[0]->setPlayer(1);
		gamers[1] = &algoPlayer[1];
		gamers[1]->setPlayer(2);
	}
	//functions
	void setRandomBoard();
	void paramMenager();
	void init();
	void setSoldiersRandom();
	void run();
	bool movementValidation(GameMove& gameMove, Soldier* sol);
	void soliderMovementOnBoard(int from_x, int from_y, int to_x ,int to_y);
	void move(GameMove& gameMove, int gamerNum);
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
	void GameManager::uploadBoardFromFile();
	void GameManager::setBoardFromFile(ifstream& inFile);
	void GameManager::updateSetSoliderCounter(int solider);
	bool GameManager::printAndCheckBoardFromFileErrors(string fileName) const;
	void GameManager::divideToFile(char *buffer);
	void GameManager::commandLine(int argc, char* argv[]);
	ifstream GameManager::openfile(map<string, int>::iterator file);
	void GameManager::endMessage() const;
	void updateDeadSoliderCounter(int gamerNum, bool win);
	void GameManager::printBoard() const;
	void GameManager::printLetters() const;
	void GameManager::printEndLine()const;
	void GameManager::printNumber(int num) const;
	void GameManager::printing() const;
	void GameManager::drowSoldiers()const;
};
