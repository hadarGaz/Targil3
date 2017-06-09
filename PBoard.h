#pragma once
#include "BoardData.h"
#include "Cell.h"
class PBoard : public BoardData {
	Cell (*pBoard)[14];
	int gamerNum;
public:
	PBoard () {}
	virtual char charAt(int x, int y) const
	{
		//סתם ניסיתי לראות שזה עובד
		int ch = (pBoard)[x][y].returnedCellType();
		if (ch == 0)
			return 'h';
	}
	void setAdressToBoard(Cell _pboard[14][14])
	{
		pBoard = _pboard;
		//(pBoard)[1][1].setCellType(2);
	}

	void setGamerNum(int _gamerNum) {
		gamerNum = _gamerNum;
	}
};
