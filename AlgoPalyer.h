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
	int numOfPlayer;
	int enemyFlag[2];
public:
	virtual void setPlayer(int player)
	{
		numOfPlayer = player;
	}
	virtual void init(const BoardData& board) //get pboard
	{
		pboardData = &board; //now pboardData point to PBoard class
		for (int y = 0; y < (int)Sizes::size;y++) {
			for (int x = 0; x < (int)Sizes::size;x++ ) {
				char curr = pboardData->charAt(x, y);
				boardOfChar[y][x] = curr;
				if (curr == '1' || curr == '7') {
					tools[0].set(x, y, curr);
					tools[0].setCondition(curr);
				}
				if (curr == '2' || curr == '8') {
					tools[1].set(x, y, curr);
					tools[1].setCondition(curr);
				}
				if (curr == '3' || curr == '9') {
					tools[2].set(x, y, curr);
					tools[2].setCondition(curr);
				}
				if (numOfPlayer == (int)GamerA::GamerA || curr == 'B') {
					enemyFlag[0] = x;
					enemyFlag[1] = y;
				}
				if (numOfPlayer == (int)GamerB::GamerB || curr == 'A') {
					enemyFlag[0] = x;
					enemyFlag[1] = y;
				}
			}
		}
		
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
