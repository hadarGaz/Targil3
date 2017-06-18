#pragma once
#include "AbstractPlayer.h"
#include "BoardData.h"
#include "HadarNofarSoldier.h"
#include "HadarNofarCell.h"
using namespace std;

class HadarNofrtAlgoPalyer : public AbstractPlayer {
	enum { rows = 14, cols = 14 };
	enum Direction { UP, RIGHT, DOWN, LEFT };
	enum { MIN_X = 1, MAX_X = 13, MIN_Y = 1, MAX_Y = 13 };
	const BoardData* pboardData;
	HadarNofarCell copyBoard[rows][cols];
	HadarNofarSoldier tools[3];
	int numOfPlayer = 0;
	int enemyFlag[2];
	int currSoldier = 1;
	Direction arr[4];
public:
	HadarNofrtAlgoPalyer() : currSoldier(1) {}
	virtual void setPlayer(int player);
	virtual void init(const BoardData& board); //get pboard
	virtual GameMove play(const GameMove& opponentsMove);
	virtual string getName() const;
	int convertCharToInt(char x);
	int calcNewSol();
	bool calcNewMove(int from_x, int from_y, int &to_x, int& to_y);
	void updateBoardAndTools(char curr, int x, int y);
	Direction findDir(int from_x, int from_y, int& x_dir, int& y_dir);
	Direction convertToDir(const int& x_dir, const int& y_dir);
	void getdir(Direction d, int& _x_dir, int& _y_dir);
	bool moveIsValid(int to_x, int to_y);
	void updatePosSoldier(const int& to_x, const int& to_y);
	void initDirArr();
	void clearTheGame();
};
