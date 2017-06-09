#pragma once
#include "AbstractPlayer.h"
//#include <string>
#include "BoardData.h"
#include "Soldier.h"
#include "Cell.h"
using namespace std;

class AlgoPalyer : public AbstractPlayer {
	enum { rows = 13, cols = 13 };
	enum Direction { UP, RIGHT, DOWN, LEFT };
	enum { MIN_X = 1, MAX_X = 13, MIN_Y = 1, MAX_Y = 13 };
	const BoardData* pboardData;
	Cell copyBoard[rows][cols];
	Soldier tools[3];
	int numOfPlayer =0;
	int enemyFlag[2];
	int currSoldier =1;
	Direction arr[4];
public:
	virtual void setPlayer(int player);
	virtual void init(const BoardData& board); //get pboard
	virtual GameMove play(const GameMove& opponentsMove);
	virtual string getName() const;
	int convertCharToInt(char x);
	int calcNewSol();
	bool calcNewMove(int from_x, int from_y, int &to_x, int& to_y);
	void updateBoardAndTools(char curr, int x, int y);
	int findDir(int from_Point);
	Direction convertToDir(const int& x_dir, const int& y_dir);
	void getdir(Direction d, int& _x_dir, int& _y_dir);
	bool AlgoPalyer::moveIsValid(int to_x, int to_y);

};
