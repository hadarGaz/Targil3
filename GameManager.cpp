#include "GameManager.h"

void GameManager::setBoard()
{
	board[1][7].setCellType((int)Type::fr);
	board[1][8].setCellType((int)Type::fr);
	board[2][7].setCellType((int)Type::fr);
	board[3][4].setCellType((int)Type::fr);
	board[3][5].setCellType((int)Type::fr);
	board[3][6].setCellType((int)Type::fr);
	board[3][7].setCellType((int)Type::fr);
	board[4][6].setCellType((int)Type::fr);
	board[4][7].setCellType((int)Type::fr);
	board[4][8].setCellType((int)Type::fr);
	board[4][9].setCellType((int)Type::fr);

	board[8][6].setCellType((int)Type::sea);
	board[9][5].setCellType((int)Type::sea);
	board[9][6].setCellType((int)Type::sea);
	board[10][4].setCellType((int)Type::sea);
	board[10][5].setCellType((int)Type::sea);
	board[10][6].setCellType((int)Type::sea);
	board[10][7].setCellType((int)Type::sea);
	board[10][8].setCellType((int)Type::sea);
	board[10][9].setCellType((int)Type::sea);
	board[10][10].setCellType((int)Type::sea);
	board[11][7].setCellType((int)Type::sea);
	board[11][8].setCellType((int)Type::sea);
	board[11][9].setCellType((int)Type::sea);
	board[12][8].setCellType((int)Type::sea);

	board[11][1].setCellType((int)Type::flagA);
	board[2][13].setCellType((int)Type::flagB);

}

void GameManager::init()
{
	//clear the board from soldier
	//init soldier place
	setSoldiersRandom();
	soldierDeadPlayer1 = 0;
	soldierDeadPlayer2 = 0;
	//gamers[0]->init(pboard);
}
void GameManager::setSoldiersRandom()
{
	int x = 0, y = 0, found = 0;
	for (int i = 1; i <= 6; i++) {
		while (!found)
		{
			x = (rand() % 13) + 1;
			if (i >= 3)
				y = rand() % 5 + 9;
			else
				y = (rand() % 5) + 1;
			if ((board[x][y]).isCellEmpty())
				found = 1;
		}
		(board[x][y]).soldier = new Soldier;
		(board[x][y]).soldier->isAlive = true;
		(board[x][y]).soldier->setCondition(i);
		(board[x][y]).soldier->set(x, y, i);
	}
}

void GameManager::run()
{
	int win = 0;
	GameMove tempGameMove2(0, 0, 0, 0);
	while (!win)
	{
		GameMove tempGameMove1 = gamers[0]->play(tempGameMove2);
		if (board[tempGameMove1.from_x][tempGameMove1.from_y].soldier->isAlive == true) //need to check if relavent 
		{
			if (movementValidation(tempGameMove1,board[tempGameMove1.from_x][tempGameMove1.from_y].soldier));
			{
				move(tempGameMove1,1);
			}

		}
		//check move
		//if valid sol.mvoe
		GameMove tempGameMove2 = gamers[1]->play(tempGameMove1);
	}
}
void GameManager::move(GameMove& gameMove, int gamerNum)
{
	bool Win = false;
	if (board[gameMove.to_x][gameMove.to_y].returnedCellType > 2)
		win(gamerNum);
	else if (board[gameMove.to_x][gameMove.to_y].soldier != nullptr)
	{
		Win = attack(board[gameMove.from_x][gameMove.from_y].soldier->soldierNum, board[gameMove.to_x][gameMove.to_y].soldier->soldierNum, gameMove.to_x, gameMove.to_y);
		if (Win)
			win(gamerNum);
	}
	else
	{
		board[gameMove.from_x][gameMove.from_y].soldier->move(gameMove.to_x,gameMove.to_y);
		board[gameMove.to_x][gameMove.to_y].soldier = board[gameMove.from_x][gameMove.from_y].soldier;
		board[gameMove.from_x][gameMove.from_y].soldier = nullptr;
	}
		
}


bool GameManager::attack(int currSoldierNum,int enemyNum, int _x, int _y) {
	switch (currSoldierNum) {
	case 1:
		return oneIsAttack(_x,_y);
		break;
	case 2:
		return twoIsAttack(enemyNum, _x, _y);
		break;
	case 3:
		return threeIsAttack(_x, _y);
		break;
	case 7:
		return sevenIsAttack(enemyNum, _x, _y);
		break;
	case 8:
		return eightIsAttack(enemyNum, _x, _y);
		break;
	case 9:
		return nineIsAttack(enemyNum, _x, _y);
		break;
	default:
		return true;
	}

}
bool GameManager::movementValidation(GameMove& gameMove, Soldier* sol)
{
	int from_x = gameMove.from_x;
	int from_y = gameMove.from_y;
	int to_x = gameMove.to_x;
	int to_y = gameMove.to_y;
	//check the board bounderies 
	if (to_x < MIN_X || to_x > MAX_X || to_y < MIN_Y || to_y > MAX_Y)
		return false;

	if ((to_x - from_x) > 1 || (to_x - from_x) < -1 || (to_y - from_y) > 1 || (to_y - from_y) < -1)
		return false;

	//check if the cell is empty and clear to movement
	if ((board[to_x][to_y]).isCellEmpty())
		return true;

	else //if not empty
	{
		int typeReturnd = (board[to_x][to_y]).returnedCellType();
		if (typeReturnd == (int)Type::emptyType) //its soldier
		{
			if (sol->gamerNum == (board[to_x][to_y]).returndGamer())
				return false;
			else
				return true;
		}
		else if (typeReturnd == (int)Type::sea) {
			if (sol->seaPass == 1)
				return true;
			else
				return false;
		}
		else if (typeReturnd == (int)Type::fr) {
			if (sol->frPass == 1)
				return true;
			else
				return false;

		}

		else if (typeReturnd == (int)Type::flagA) {
			if (sol->soldierNum >= (int)GamerB::soldier7 && sol->soldierNum <= (int)GamerB::soldier9)
				return true;
			else
				return false;

		}

		else if (typeReturnd == (int)Type::flagB) {
			if (sol->soldierNum >= (int)GamerA::soldier1 && sol->soldierNum <= (int)GamerA::soldier3)
				return true;
			else
				return false;
		}

	}
}


//Attack results per solider conditions 
bool GameManager::oneIsAttack(int _x, int _y) {
	if ((_y >= 10 && _y <= 13) || _x == 4)
		return false;
	else
		return true;
}
bool GameManager::twoIsAttack(int enemyNum, int _x, int _y) {
	if (enemyNum == 9)
		return false;
	else if ((enemyNum == 7 || enemyNum == 8) && ((_y >= 3 && _y <= 4) || _x == 11))
		return true;
	else
		return false;
}
bool GameManager::threeIsAttack(int _x, int _y) {
	if (_y == 8 || _x == 7)
		return true;
	else
		return false;
}
bool GameManager::sevenIsAttack(int enemyNum, int _x, int _y) {
	if ((((_y >= 10 && _y <= 13) || (_x == 4)) && enemyNum == 1) ||
		(((_y != 4 && _y != 3) && _x != 11) && enemyNum == 2) ||
		((_y != 8 && _x != 7) && enemyNum == 3))
		return true;
	else
		return false;
}
bool GameManager::eightIsAttack(int enemyNum, int _x, int _y) {
	if ((((_y >= 10 && _y <= 13) || (_x == 4)) && enemyNum == 1) ||
		(((_y != 4 && _y != 3) && _x != 11) && enemyNum == 2) ||
		((_y != 8 && _x != 7) && enemyNum == 3))
		return true;
	else
		return false;
}
bool GameManager::nineIsAttack(int enemyNum, int _x, int _y) {
	if ((((_y >= 10 && _y <= 13) || (_x == 4)) && enemyNum == 1) ||
		(enemyNum == 2) ||
		((_y != 8 && _x != 7) && enemyNum == 3))
		return true;
	else
		return false;
}


void GameManager::win(int gamerNum)
{
	clearScreen();
	if (quietMode == false)
		cout << "The gamer: " << gamerNum << " won this game" << endl;
	if (gamerNum == 1)
		scorePlayer1++;
	else
		scorePlayer2++;

}
