#pragma once
#include "BoardData.h"
#include "HadarNofarCell.h"
#include "HadarNofarEnums.h"
#include <stdio.h>
#include <stdlib.h>
class PBoard : public BoardData {
	HadarNofarCell(*pBoard)[(int)Sizes::size];
	int gamerNum;
public:
	PBoard () {}
	virtual char charAt(int x, int y) const
	{
		if ((pBoard)[x][y].soldier != NULL)
		{
			int numOfSoldier = (pBoard)[x][y].soldier->getsoldierNum();
			if ((gamerNum == 1 && numOfSoldier <= (int)GamerA::soldier3) || (gamerNum == 2 && numOfSoldier >= (int)GamerB::soldier7))
				return numOfSoldier+'0';
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
	void setPointerAndNumOfGamer(HadarNofarCell _pboard[14][14], int _gamerNum)
	{
		pBoard = _pboard;
		gamerNum = _gamerNum;
	}

};
