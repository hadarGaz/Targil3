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
	 int from_x, from_y;
	 int to_x, to_y;
	 int found = 0;
	if (convertCharToInt(pboardData->charAt(tools[currSoldier - 1].getsoldierX, tools[currSoldier - 1].getsoldierY)) != currSoldier)
		currSoldier = calcNewSol();
	from_x = tools[currSoldier - 1].getsoldierX;
	from_y = tools[currSoldier - 1].getsoldierY;

	while (!found)
	{
		int getNewMove = calcNewMove(to_x, to_y);
		if (!getNewMove)
			currSoldier = calcNewSol();
		else
			found = 1;
	}
	
	GameMove gameMove(from_x, from_y, to_x, to_y);
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

int AlgoPalyer::calcNewMove(int &to_x, int& to_y)
{
	int found = 0;
	while (!found)
	{
		if (numOfPlayer == 1)
			currSoldier = currSoldier++ % 3;
		
		else if(numOfPlayer == 2)
			currSoldier = currSoldier++ % 3;
		
		if (convertCharToInt(pboardData->charAt(tools[currSoldier - 1].getsoldierX, tools[currSoldier - 1].getsoldierY)) == currSoldier)
			found = 1;
	}
	return 0; // if sol stuck
}
