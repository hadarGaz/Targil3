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
public:
	int numOfPlayer;
	virtual void setPlayer(int player)
	{
		numOfPlayer = player;
	}
	virtual void init(const BoardData& board) //get pboard
	{
		pboardData = &board; //now pboardData point to PBoard class
		
	}
	virtual GameMove play(const GameMove& opponentsMove)
	{
		 GameMove gameMove(3,3,4,3);
		 pboardData->charAt(3, 3);
		 return gameMove;
	}
	virtual string getName() const
	{
		return "a";
	}

};
