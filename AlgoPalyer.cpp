#include "AlgoPalyer.h"
#include "AlgorithmRegistration.h"

AlgorithmRegistration algo_NofarKedemID("algo_NofarAndHadar",
	[] {return new AlgoPalyer();}
);

void AlgoPalyer::setPlayer(int player)
{
	numOfPlayer = player;
}
void AlgoPalyer::init(const BoardData& board) //get pboard
{
	//clearTheGame();
	pboardData = &board; //now pboardData point to PBoard class
	initDirArr();
	for (int y = 0; y < (int)Sizes::size; y++) {
		for (int x = 0; x < (int)Sizes::size; x++) {
			char curr = pboardData->charAt(x, y);
			updateBoardAndTools(curr, x, y);
		}
	}

}
void AlgoPalyer::initDirArr()
{
	arr[0] = Direction::UP;
	arr[1] = Direction::RIGHT;
	arr[2] = Direction::DOWN;
	arr[3] = Direction::LEFT;

}
 GameMove AlgoPalyer::play(const GameMove& opponentsMove)
{
	 int from_x, from_y;
	 int to_x, to_y;
	 int found = 0;
	 int trueSol = convertCharToInt(pboardData->charAt(tools[currSoldier - 1]._x, tools[currSoldier - 1]._y));
	 if ((trueSol != currSoldier ) && (trueSol =! (currSoldier + 6)))
		currSoldier = calcNewSol();
	from_x = tools[currSoldier - 1]._x;
	from_y = tools[currSoldier - 1]._y;

	while (!found)
	{
		int getNewMove = calcNewMove(from_x, from_y, to_x, to_y);
		if (!getNewMove)
			currSoldier = calcNewSol();
		else
		{
			found = 1;
			tools[currSoldier - 1].oldX = from_x;
			tools[currSoldier - 1].oldY = from_y;
		}
	}
	
	//GameMove* gameMove = new GameMove(from_x, from_y, to_x, to_y);
	//return *gameMove;
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
	else if (x >= 'a' && x <= 'z')
		return x - 'a' + 1;
	else
		return x - '0';
}

bool AlgoPalyer::calcNewMove(int from_x, int from_y, int &to_x, int& to_y)
{
	int found = 0;
	int counter = 0;
	int x_dir, y_dir;
	Direction d = findDir(from_x, from_y, x_dir, y_dir);
	while (!found)
	{
		if (moveIsValid(from_x + x_dir, from_y + y_dir))
		{
			found = 1;
			to_x = from_x + x_dir;
			to_y = from_y + y_dir;
			updatePosSoldier(to_x, to_y);
		}
		else if (counter != 4)
		{
			//Direction d = convertToDir(x_dir, y_dir);
			int index = d;
			index++;
			index = index % 4;
			getdir((arr[index]), x_dir, y_dir);
			counter++;
			d = (arr[index++]);
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

AlgoPalyer::Direction AlgoPalyer::findDir(int from_x,int from_y,int& x_dir,int& y_dir)
{
	Direction d;
	// calc x_dir
	if ((enemyFlag[0] - from_x) > 0)
		x_dir = 1;
	else if ((enemyFlag[0] - from_x) == 0)
		x_dir = 0;
	else
		x_dir = -1;

	//calc y_dir
	if ((enemyFlag[1] - from_y) > 0)
		y_dir = 1;
	else if ((enemyFlag[1] - from_y) == 0)
		y_dir = 0;
	else
		y_dir = -1;

	if ((x_dir == 1 && y_dir == -1) || (x_dir == 0 && y_dir == -1))
		d = Direction::UP;
	else if ((x_dir == 1 && y_dir == 0) || (x_dir == 1 && y_dir == 1))
		d = Direction::RIGHT;
	else if ((x_dir == 0 && y_dir == 1) || (x_dir == -1 && y_dir == 1))
		d = Direction::DOWN;
	else if ((x_dir == -1 && y_dir == 0) || (x_dir == -1 && y_dir == -1))
		d = Direction::LEFT;

	getdir(d, x_dir, y_dir);

	
	return d;
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
		tools[0].set(x, y, curr - '0');
		tools[0].setCondition(curr - '0');
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
		if (numOfPlayer == 1) {
			enemyFlag[0] = x;
			enemyFlag[1] = y;
		}
	}
	if (curr == 'A') {
		copyBoard[x][y].setCellType ((int)Type::flagA);
		if (numOfPlayer == 2) {
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
		if (numOfPlayer == 1) {
			copyBoard[x][y].setGamerType((int)GamerB::GamerB);
		}
		else {
			copyBoard[x][y].setGamerType ((int)GamerA::GamerA);
		}
	}
}

bool AlgoPalyer::moveIsValid(int to_x, int to_y)
{
	//check the board bounderies 
	if (to_x < MIN_X || to_x > MAX_X || to_y < MIN_Y || to_y > MAX_Y)
		return false;

	if (to_x == tools[currSoldier - 1].oldX && to_y == tools[currSoldier - 1].oldY)
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

void AlgoPalyer::updatePosSoldier(const int& to_x, const int& to_y)
{
	copyBoard[tools[currSoldier - 1]._x][tools[currSoldier - 1]._y].setGamerType(0);
	copyBoard[to_x][to_y].setGamerType(currSoldier);
	tools[currSoldier - 1]._x = to_x;
	tools[currSoldier - 1]._y = to_y;
}

void AlgoPalyer::clearTheGame()
{
	for (int i = 0; i < (int)Sizes::size; i++)
	{
		for (int j = 0; j < (int)Sizes::size; j++)
		{
			//copyBoard[i][j].soldier = nullptr;
			copyBoard[i][j].setCellType(0);
			copyBoard[i][j].setGamerType(0);
		}
	}
}