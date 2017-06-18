#include "HadarNofarSoldier.h"

extern bool quietMode = false;



void HadarNofarSoldier::set(int x, int y, int ch)
{
	_x = x;
	_y = y;
	soldierNum = ch;
	if (soldierNum >= (int)GamerA::soldier1 && soldierNum <= (int)GamerA::soldier3)
		gamerNum = 1;
	else
		gamerNum = 2;

}

void HadarNofarSoldier::draw(int soldierNum) const
{
	gotoxy(4 * _x + 1, 2 * _y);
	if (soldierNum >= (int)GamerA::soldier1 && soldierNum <= (int)GamerA::soldier3)
		setTextColor(GREEN);
	else
		setTextColor(BLUE);
	if (soldierNum == 0)
		cout << " ";
	else
		cout << " " << soldierNum << " ";

	setTextColor(WHITE);
	cout.flush();
}

void HadarNofarSoldier::earse(int oldX, int oldY) {
	gotoxy(4 * oldX + 2, 2 * oldY);
	cout << " ";
}

void HadarNofarSoldier::setCondition(int soldierNum)
{
	switch (soldierNum)
	{
	case 1:
		seaPass = 0;
		frPass = 0;
		break;
	case 2:
		seaPass = 1;
		frPass = 1;
		break;
	case 3:
		seaPass = 1;
		frPass = 0;
		break;
	case 7:
		seaPass = 1;
		frPass = 1;
		break;
	case 8:
		seaPass = 0;
		frPass = 1;
		break;
	case 9:
		seaPass = 0;
		frPass = 0;
		break;
	}
}

void HadarNofarSoldier::move(int newx, int newy)
{
	earse(_x, _y); // earse the old point
	_x = newx;
	_y = newy;
	if (quietMode == false) {
		//printSpecialCell(_x, _y, board);
		draw();
	}
}

void HadarNofarSoldier::draw() const
{
	draw(soldierNum);
}

int HadarNofarSoldier::getsoldierNum()
{
	return soldierNum;
}

