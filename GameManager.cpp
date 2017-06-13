#include "GameManager.h"

void GameManager::paramMenager()
{
	char* tempPath;
	if (path == "NULL") //it mean current directory
	{
		openFolder("cd");
		size_t size = path.find_last_of("\n");
		path[size] = '\0';
	}

	char str[4095] = "2>NUL dir /a-d /b ";
	tempPath = strcat(str, path.c_str());
	openFolder(tempPath);

	currFileBoard = boardFile.begin();

	while (GameOver == false)
	{
		setBoard();
		if (GameOver == false)
		{
			init();
			run();
			clearTheGame();
			Sleep(50 * delay);
		}
	}
	endMessage();
}

void GameManager::openFolder(char* tempPath)
{
	char buffer[4096];
	FILE* fp = _popen(tempPath, "r");
	while (fgets(buffer, 4095, fp))
	{
		if (path == "NULL")
			path = buffer; //new 13.5
		else
			divideToFile(buffer);
	}
	_pclose(fp);
}


void GameManager::divideToFile(char *buffer)
{
	string fileName;
	int i = 0;
	while (strncmp(buffer + i, ".", 1) != 0) //פונקציה שבודקת את הסיומת
		i++;

	char* str = &buffer[i + 1];
	if (strncmp(str, "gboard", 6) == 0)
		boardFile[buffer]++;
}

void GameManager::commandLine(int argc, char* argv[])
{
	for (int i = 1; i < argc; i = i + 2)
	{
		if (strcmp(argv[i], "-board") == 0)
		{
			if (strcmp(argv[i + 1], "f") == 0)
				ifBoardFile = true;
		}
		
		else if (strcmp(argv[i], "-path") == 0)
		{
			path = argv[i + 1];
		}
		else if (strcmp(argv[i], "-quiet") == 0)
		{
			if (ifBoardFile == true)
				quietMode = true;
			i--; // beacuse there is no parameter after quite
		}
		else if (strcmp(argv[i], "-delay") == 0)
		{
			if (quietMode == false)
				delay = *argv[i + 1];
		}
	}
	paramMenager();

}

void GameManager::setBoard() //סידור לוח וחיילים
{
	//clearTheGame(); //צריך למחוק את החיילים מהמשחק הקודם
	if (ifBoardFile == true)
		uploadBoardFromFile();
	else
		setRandomBoard();
}

void GameManager::setRandomBoard()
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

void GameManager::uploadBoardFromFile() //אתחולים
{
	bool isBoardOk = false;

	if (currFileBoard == boardFile.end())
		GameOver = true;
	
	else
	{
		ifstream fileNameforBoard = openfile(currFileBoard);
		setBoardFromFile(fileNameforBoard);
		isBoardOk = printAndCheckBoardFromFileErrors(currFileBoard->first);
		if (isBoardOk == false)
		{
			GameOver = true;
		}
	}
}


ifstream GameManager::openfile(map<string, int>::iterator file)
{
	
	const char* tempPath = path.c_str();
	string fullPath = tempPath;
	fullPath.append("\\");
	fullPath.append(file->first);
	size_t indexstr1 = fullPath.find_last_of("\n");
	fullPath[indexstr1] = '\0';
	ifstream boardFile(fullPath);
	bool ok = boardFile.is_open();
	return boardFile;
}

void GameManager::init()
{
	//clear the board from soldier
	//init soldier place
	if(!ifBoardFile)
		setSoldiersRandom();
	soldierDeadPlayer1 = 0;
	soldierDeadPlayer2 = 0;
	SetACounter = 0, SetBCounter = 0;
	setSol1 = 0, setSol2 = 0, setSol3 = 0, setSol7 = 0, setSol8 = 0, setSol9 = 0;
	wrongCharsSet.clear();
	PBoardForPlayer1.setPointerAndNumOfGamer(board,1);
	PBoardForPlayer2.setPointerAndNumOfGamer(board,2);
	gamers[0]->init(PBoardForPlayer1);
	gamers[1]->init(PBoardForPlayer2);
	

	if (!quietMode)
		printing();
}
void GameManager::setSoldiersRandom()
{
	int x = 0, y = 0, found = 0;
	int j = 1;
	for (int i = 1; i <= 6; i++) {
		found = 0;
		while (!found)
		{
			x = (rand() % 13) + 1;
			if (i > 3)
				y = rand() % 5 + 9;
			else
				y = (rand() % 5) + 1;
			if ((board[x][y]).isCellEmpty())
				found = 1;
		}
		if (j == 4)
			j = j + 3;
		(board[x][y]).soldier = new Soldier;
		(board[x][y]).soldier->isAlive = true;
		(board[x][y]).soldier->setCondition(j);
		(board[x][y]).soldier->set(x, y, j);
		j++;
	}
}

void GameManager::run()
{
	bool win = false;
	GameMove* tempGameMove2 = new GameMove(1, 1, 1, 1);
	while (!win)
	{
		GameMove tempGameMove1 = gamers[0]->play(*tempGameMove2);
		if (movementValidation(tempGameMove1, board[tempGameMove1.from_x][tempGameMove1.from_y].soldier));
		win = move(tempGameMove1, 1);

		if (!win)
		{
			GameMove tempGameMove2 = gamers[1]->play(tempGameMove1);
			if (movementValidation(tempGameMove2, board[tempGameMove2.from_x][tempGameMove2.from_y].soldier));
			win = move(tempGameMove2, 2);
		}
	}
	delete(tempGameMove2);

	if(ifBoardFile)
		currFileBoard++;
}
bool GameManager::move(GameMove& gameMove, int gamerNum)
{
	bool Win = false;
	bool WinTheGame = false;
	if (board[gameMove.to_x][gameMove.to_y].returnedCellType() > 2) //הגיע לדגל
	{
		win(gamerNum);
		return WinTheGame=true;
	}
	else if (board[gameMove.to_x][gameMove.to_y].soldier)
	{
		Win = attack(board[gameMove.from_x][gameMove.from_y].soldier->soldierNum, board[gameMove.to_x][gameMove.to_y].soldier->soldierNum, gameMove.to_x, gameMove.to_y);
		if (Win) {
			board[gameMove.to_x][gameMove.to_y].soldier->earse(gameMove.to_x, gameMove.to_y);
			delete(board[gameMove.to_x][gameMove.to_y].soldier);
			soliderMovementOnBoard(gameMove.from_x, gameMove.from_y, gameMove.to_x, gameMove.to_y);
			WinTheGame = updateDeadSoliderCounter(gamerNum, Win);
		}
		else {
			board[gameMove.from_x][gameMove.from_y].soldier->earse(gameMove.from_x, gameMove.from_y);
			delete(board[gameMove.from_x][gameMove.from_y].soldier);
			board[gameMove.from_x][gameMove.from_y].soldier = nullptr;
			WinTheGame = updateDeadSoliderCounter(gamerNum, Win);
		}
	}
	else
	{
		soliderMovementOnBoard(gameMove.from_x, gameMove.from_y, gameMove.to_x, gameMove.to_y);
	}
	return WinTheGame;
}

void GameManager::soliderMovementOnBoard(int from_x,int from_y,int to_x ,int to_y) {
	board[from_x][from_y].soldier->move(to_x, to_y);
	board[to_x][to_y].soldier = board[from_x][from_y].soldier;
	board[from_x][from_y].soldier = nullptr;
}

bool GameManager::updateDeadSoliderCounter(int gamerNum,bool Win) {
	if (gamerNum == 1 && Win)
		soldierDeadPlayer2++;
	else if (gamerNum == 1 && !Win)
		soldierDeadPlayer1++;
	else if (gamerNum == 2 && Win)
		soldierDeadPlayer1++;
	else if (gamerNum == 2 && !Win)
		soldierDeadPlayer2++;

	if (soldierDeadPlayer1 == 3)
	{
		win(2);
		return true;
	}
	else if (soldierDeadPlayer2 == 3)
	{
		win(1);
		return true;
	}
	return false;
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
			if (sol->gamerNum == (board[to_x][to_y]).soldier->gamerNum)
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

void GameManager::setBoardFromFile(ifstream& inFile) {
	string line;
	char currentChar;
	std::map<char, int> wrongCharMap;

	for (int i = 1; i < (int)Sizes::size; i++) {
		getline(inFile, line);
		for (int j = 1; j < (int)Sizes::size; j++) {
			currentChar = line.at(j - 1);
			if (currentChar == 'T') {
				board[j][i].setCellType((int)Type::fr);
			}
			else if (currentChar == 'S') {
				board[j][i].setCellType((int)Type::sea);
			}
			else if (currentChar == 'A') {
				if (SetACounter == 0) {
					board[j][i].setCellType((int)Type::flagA);
				}
				SetACounter++;
			}
			else if (currentChar == 'B') {
				if (SetBCounter == 0) {
					board[j][i].setCellType((int)Type::flagB);
				}
				SetBCounter++;
			}
			else if ((currentChar - '0' >= (int)GamerA::soldier1) && (currentChar - '0' <= (int)GamerA::soldier3)) {
				updateSetSoliderCounter(currentChar - '0');
				if (setSol1 <= 1 || setSol2 <= 1 || setSol3 <= 1)
				{
					(board[j][i]).soldier = new Soldier;
					board[j][i].soldier->setCondition(currentChar - '0');
					board[j][i].soldier->set(j,i, currentChar - '0');
				}
				
			}
			else if (currentChar - '0' >= (int)GamerB::soldier7 && currentChar - '0' <= (int)GamerB::soldier9) {
				updateSetSoliderCounter(currentChar - '0');
				if (setSol7 <= 1 || setSol8 <= 1 || setSol9 <= 1)
				{
					(board[j][i]).soldier = new Soldier;
					board[j][i].soldier->setCondition(currentChar - '0');
					board[j][i].soldier->set(j, i, currentChar - '0');
				}
			}
			else {
				if (currentChar != ' ') {
					if (wrongCharMap.count(currentChar) != 0) {//if the char exists
						wrongCharMap[currentChar]++;
					}
					else {
						wrongCharsSet.push_back(currentChar);
						wrongCharMap[currentChar]++;
					}
				}
			}
		}
	}

}

void GameManager::updateSetSoliderCounter(int solider) {
	if (solider == (int)GamerA::soldier1) {
		setSol1++;
	}
	if (solider == (int)GamerA::soldier2) {
		setSol2++;
	}
	if (solider == (int)GamerA::soldier3) {
		setSol3++;
	}
	if (solider == (int)GamerB::soldier7) {
		setSol7++;
	}
	if (solider == (int)GamerB::soldier8) {
		setSol8++;
	}
	if (solider == (int)GamerB::soldier9) {
		setSol9++;
	}
}

bool GameManager::printAndCheckBoardFromFileErrors(string fileName) const {
	bool isBoardOk = true;
	if (SetACounter != 1 || setSol1 != 1 || setSol2 != 1 || setSol3 != 1) {
		cout << "Wrong settings for player A tools in file " << fileName << endl;
		isBoardOk = false;
	}
	if (SetBCounter != 1 || setSol7 != 1 || setSol8 != 1 || setSol9 != 1) {
		cout << "Wrong settings for player B tools in file " << fileName << endl;
		isBoardOk = false;
	}
	if (wrongCharsSet.size() > 0) {
		cout << "Wrong character on board : " << wrongCharsSet << " in file " << fileName << endl;
		isBoardOk = false;
	}
	return isBoardOk;
}

void GameManager::endMessage() const
{
	clearScreen();
	cout << "Game Summary" << endl;
	cout << "A points - " << scorePlayer1 << endl;
	cout << "B points - " << scorePlayer2 << endl;
}

void GameManager::printBoard() const
{
	char flag = 167;
	int typeofcell;
	int num = 1;
	printLetters();
	printEndLine();
	for (int i = 1; i < (int)Sizes::size; i++) {
		for (int j = 0; j < (int)Sizes::size; j++) {
			cout << "|";
			if (j == 0)
				printNumber(num++);
			else {
				typeofcell = board[j][i].returnedCellType();
				if (typeofcell == (int)Type::emptyType) {
					cout << "   ";
				}
				else if (typeofcell == (int)Type::fr) {
					setTextColor(BLACK, PURPLE);
					cout << "FR ";
					setTextColor(WHITE);
				}
				else if (typeofcell == (int)Type::sea) {
					setTextColor(BLACK, YELLOW);
					cout << "SEA";
					setTextColor(WHITE);
				}
				else if (typeofcell == (int)Type::flagA) {
					cout << " " << flag << "A";
				}
				else {
					cout << " " << flag << "B";
				}
			}
		}
		cout << "|" << endl;
		printEndLine();
	}
	cout << "SCORE: " << endl;
	for (int i = 0; i < (int)Sizes::sizeOfGamers; i++) {
		//cout << "Gamer: " << gamers[i].name;
		//cout << " = " << gamers[i].score << endl;
	}

}

void GameManager::printLetters() const
{
	char ch = 'A';
	cout << "|" << "   ";
	for (int p = 1; p<(int)Sizes::size; p++)
		cout << "| " << ch++ << " ";
	cout << "|" << endl;
}

void GameManager::printEndLine()const
{
	for (int l = 0; l < (int)Sizes::size; l++)
		cout << "====";
	cout << endl;
}


void GameManager::printNumber(int num) const
{

	if (num >= 10)
		cout << " " << num;
	else
		cout << " " << num << " ";
}

void GameManager::printing() const
{
	clearScreen();
	printBoard();
	drowSoldiers();
}

void GameManager::drowSoldiers() const
{
	for (int i = 0; i < (int)Sizes::size; i++)
	{
		for (int j = 0; j < (int)Sizes::size; j++)
		{
			if (board[i][j].soldier != nullptr)
				board[i][j].soldier->draw();
		}
	}
}

void GameManager::clearTheGame()
{
	
		for (int i = 0; i < (int)Sizes::size; i++)
		{
			for (int j = 0; j < (int)Sizes::size; j++)
			{
				board[i][j].soldier = nullptr;
				board[i][j].setCellType(0);
				board[i][j].setGamerType(0);
			}
		}
}