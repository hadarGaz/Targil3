#pragma once
#include "BoardData.h"
#include "Cell.h"
#include "enums.h"
class PBoard : public BoardData {
	Cell (*pBoard)[(int)Sizes::size];
	int gamerNum;
public:
	PBoard () {}
	virtual char charAt(int x, int y) const
	{
		if ((pBoard)[x][y].soldier != NULL)
		{
			char numOfSoldier = (pBoard)[x][y].soldier->getsoldierNum();
			if ((gamerNum == 1 && numOfSoldier <= (int)GamerA::soldier3) || (gamerNum == 2 && numOfSoldier >= (int)GamerB::soldier7))
				return numOfSoldier;
			else
				return '#';
		}
		else
		{
			int ch = (pBoard)[x][y].returnedCellType();
			if (ch == 1)
				return 'S';
			else if (ch == 2)
				return 'F';
			else if (ch == 3)
				return 'A';
			else if (ch == 4)
				return 'B';
		}
	}
	void setPointerAndNumOfGamer(Cell _pboard[14][14], int _gamerNum)
	{
		pBoard = _pboard;
		gamerNum = _gamerNum;
	}

};
