#include "AlgoPalyer.h"
void AlgoPalyer::setPlayer(int player)
{
	numOfPlayer = player;
}
void AlgoPalyer::init(const BoardData& board) //get pboard
{
	pboardData = &board; //now pboardData point to PBoard class

}
 GameMove AlgoPalyer::play(const GameMove& opponentsMove)
{
	GameMove gameMove(3, 3, 4, 3);
	if (convertCharToInt(pboardData->charAt(tools[currSoldier - 1].getsoldierX, tools[currSoldier - 1].getsoldierY)) != currSoldier)
		currSoldier = calcNewSol();

	return gameMove;
}
 string AlgoPalyer::getName() const
{
	return "a";
}

int AlgoPalyer::convertCharToInt(char x)
{
	if (x >= 'A' && x <= 'Z')
		return x - 'A' + 1;
	else
		return x - 'a' + 1;
}
int AlgoPalyer::calcNewSol()
{
	return 0;
}
