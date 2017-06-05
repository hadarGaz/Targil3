#pragma once
#include "AbstractPlayer.h"
#include <string>
#include "BoardData.h"
class AlgoPalyer : public AbstractPlayer {
	enum { rows = 13, cols = 13 };
	const BoardData* pboardData;
	char boardOfChar[rows][cols];
public:
	virtual void setPlayer(int player)
	{
		int i = 0;
	}
	virtual void init(const BoardData& board) //get pboard
	{
		pboardData = &board;
		pboardData->charAt(1, 1);
	}
	virtual GameMove play(const GameMove& opponentsMove)
	{
		 GameMove gameMove(3,3,4,3);
		 return gameMove;
	}
	virtual string getName() const
	{
		return "a";
	}

};
