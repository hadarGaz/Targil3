#pragma once
#include <iostream>
#include "BoardData.h"
#include "GameMove.h"
#include <string>

class AbstractPlayer {
public:
	virtual ~AbstractPlayer() {}
	virtual void setPlayer(int player) = 0;
	virtual void init(const BoardData& board) = 0;
	virtual GameMove play(const GameMove& opponentsMove) = 0;
	virtual string getName() const = 0;
};
