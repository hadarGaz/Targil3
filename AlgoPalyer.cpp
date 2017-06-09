#include "AlgoPalyer.h"
void AlgoPalyer::setPlayer(int player)
{
	numOfPlayer = player;
}
void AlgoPalyer::init(const BoardData& board) //get pboard
{
	pboardData = &board; //now pboardData point to PBoard class
	for (int y = 0; y < (int)Sizes::size; y++) {
		for (int x = 0; x < (int)Sizes::size; x++) {
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
