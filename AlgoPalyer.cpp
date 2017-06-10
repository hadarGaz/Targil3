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
	 int from_x, from_y;
	 int to_x, to_y;
	 int found = 0;
	if (convertCharToInt(pboardData->charAt(tools[currSoldier - 1]._x, tools[currSoldier - 1]._y)) != currSoldier)
		currSoldier = calcNewSol();
	from_x = tools[currSoldier - 1]._x;
	from_y = tools[currSoldier - 1]._y;

	while (!found)
	{
		int getNewMove = calcNewMove(from_x, from_y, to_x, to_y);
		if (!getNewMove)
			currSoldier = calcNewSol();
		else
			found = 1;
	}
	
	GameMove* gameMove = new GameMove(from_x, from_y, to_x, to_y);
	return *gameMove;
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

bool AlgoPalyer::calcNewMove(int from_x, int from_y, int &to_x, int& to_y)
{
	int found = 0;
	int counter = 0;
	int x_dir = findDir(from_x);
	int y_dir = findDir(from_y);
	while (!found)
	{
		if (moveIsValid(from_x+ x_dir, from_y+ y_dir))
			found = 1;
		else if (counter != 3)
		{
			Direction d = convertToDir(x_dir, y_dir);
			int index = d;
			index = index++ % 4;
			getdir(arr[index], x_dir, y_dir);
			counter++;
		}
		else
			return false;
	}
	
	return true;
}

void AlgoPalyer::getdir(Direction d, int& _x_dir, int& _y_dir)
{
	switch (d)
	{
	case Direction::UP:
		_x_dir = 0;
		_y_dir = -1;
		break;
	case Direction::DOWN:
		_x_dir = 0;
		_y_dir = 1;
		break;
	case Direction::LEFT:
		_x_dir = -1;
		_y_dir = 0;
		break;
	case Direction::RIGHT:
		_x_dir = 1;
		_y_dir = 0;
		break;
	}
}

AlgoPalyer::Direction AlgoPalyer::convertToDir(const int& _x_dir, const int& _y_dir)
{
	Direction p;
	if (_x_dir == 0 && _y_dir == -1)
			p = UP;
	else if(_x_dir == 0 && _y_dir == 1)
			p = DOWN;
	else if(_x_dir == -1 && _y_dir == 0)
			p = LEFT;
	else if(_x_dir == 1 && _y_dir == 0)
		p = RIGHT;

	return p;
}

int AlgoPalyer::findDir(int from_Point)
{
	int dir;
	if ((enemyFlag[0] - from_Point) > 0)
		dir = 1;
	else if ((enemyFlag[0] - from_Point) == 0)
		dir = 0;
	else
		dir = -1;

	return dir;
}

int AlgoPalyer::calcNewSol()
{
	int found = 0;
	while (!found)
	{
		if (numOfPlayer == 1)
			currSoldier = currSoldier++ % 3;

		else if (numOfPlayer == 2)
			currSoldier = currSoldier++ % 3;

		if (convertCharToInt(pboardData->charAt(tools[currSoldier - 1]._x, tools[currSoldier - 1]._y)) == currSoldier)
			found = 1;
	}
	return 0; // if sol stuck
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
		copyBoard[x][y].setCellType ((int)Type::flagB);
		if (numOfPlayer == (int)GamerA::GamerA) {
			enemyFlag[0] = x;
			enemyFlag[1] = y;
		}
	}
	if (curr == 'A') {
		copyBoard[x][y].setCellType ((int)Type::flagA);
		if (numOfPlayer == (int)GamerB::GamerB) {
			enemyFlag[0] = x;
			enemyFlag[1] = y;
		}
	}
	if (curr == 'S') {
		copyBoard[x][y].setCellType((int)Type::sea);
	}
	if (curr == 'F') {
		copyBoard[x][y].setCellType ((int)Type::fr);
	}
	if (curr == '#') {
		if (numOfPlayer == (int)GamerB::GamerB) {
			copyBoard[x][y].setGamerType ((int)GamerA::GamerA);
		}
		else {
			copyBoard[x][y].setGamerType ((int)GamerB::GamerB);
		}
	}
}

bool AlgoPalyer::moveIsValid(int to_x, int to_y)
{
	//check the board bounderies 
	if (to_x < MIN_X || to_x > MAX_X || to_y < MIN_Y || to_y > MAX_Y)
		return false;

	//check if the cell is empty and clear to movement
	if ((copyBoard[to_x][to_y]).isCellEmpty())
		return true;

	else //if not empty
	{
		int typeReturnd = (copyBoard[to_x][to_y]).returnedCellType();
		if (typeReturnd == (int)Type::emptyType) //its soldier
		{
			if ((copyBoard[to_x][to_y]).returnNumOfGamer() == numOfPlayer)
				return false;
			else
				return true;
		
		}
		else if (typeReturnd == (int)Type::sea) {
			if (tools[currSoldier-1].seaPass == 1)
				return true;
			else
				return false;
		}
		else if (typeReturnd == (int)Type::fr) {
			if (tools[currSoldier - 1].frPass == 1)
				return true;
			else
				return false;
		}

		else if (typeReturnd == (int)Type::flagA) {
			if (tools[currSoldier - 1].soldierNum >= (int)GamerB::soldier7 && tools[currSoldier - 1].soldierNum <= (int)GamerB::soldier9)
				return true;
			else
				return false;

		}

		else if (typeReturnd == (int)Type::flagB) {
			if (tools[currSoldier - 1].soldierNum >= (int)GamerA::soldier1 && tools[currSoldier - 1].soldierNum <= (int)GamerA::soldier3)
				return true;
			else
				return false;
		}

	}
}