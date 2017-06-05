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
			updateBoardAndTools(curr, x, y);
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

void AlgoPalyer::updateBoardAndTools(char curr, int x, int y) {
	if (curr == '1' || curr == '7') {
		tools[0].set(x, y, curr);
		tools[0].setCondition(curr);
		if (curr == '1') {
			copyBoard[x][y].setGamerType((int)GamerA::soldier1);
		}
		else {
			copyBoard[x][y].setGamerType((int)GamerB::soldier7);
		}
	}
	if (curr == '2' || curr == '8') {
		tools[1].set(x, y, curr);
		tools[1].setCondition(curr);
		if (curr == '2') {
			copyBoard[x][y].setGamerType((int)GamerA::soldier2);
		}
		else {
			copyBoard[x][y].setGamerType((int)GamerB::soldier8);
		}
	}
	if (curr == '3' || curr == '9') {
		tools[2].set(x, y, curr);
		tools[2].setCondition(curr);
		if (curr == '3') {
			copyBoard[x][y].setGamerType((int)GamerA::soldier3);
		}
		else {
			copyBoard[x][y].setGamerType((int)GamerB::soldier9);
		}
	}
	if (curr == 'B') {
		copyBoard[x][y].setCellType = (int)Type::flagB;
		if (numOfPlayer == (int)GamerA::GamerA) {
			enemyFlag[0] = x;
			enemyFlag[1] = y;
		}
	}
	if (curr == 'A') {
		copyBoard[x][y].setCellType = (int)Type::flagA;
		if (numOfPlayer == (int)GamerB::GamerB) {
			enemyFlag[0] = x;
			enemyFlag[1] = y;
		}
	}
	if (curr == 'S') {
		copyBoard[x][y].setCellType = (int)Type::sea;
	}
	if (curr == 'F') {
		copyBoard[x][y].setCellType = (int)Type::fr;
	}
	if (curr == '#') {
		if (numOfPlayer == (int)GamerB::GamerB) {
			copyBoard[x][y].setGamerType = (int)GamerA::GamerA;
		}
		else {
			copyBoard[x][y].setGamerType = (int)GamerB::GamerB;
		}
	}
}
