#pragma once
#include "AbstractPlayer.h"
#include <string>
#include "BoardData.h"
#include "Soldier.h"
class AlgoPalyer : public AbstractPlayer {
	enum { rows = 13, cols = 13 };
	const BoardData* pboardData;
	char boardOfChar[rows][cols];
	Soldier tools[3];
	int currSoldier;
public:
	int numOfPlayer;
	virtual void setPlayer(int player);
	virtual void init(const BoardData& board); //get pboard
	virtual GameMove play(const GameMove& opponentsMove);
	virtual string getName() const;
	int convertCharToInt(char x);
	int calcNewSol();
};
