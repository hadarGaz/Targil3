#pragma once
#include "BoardData.h"
#include "Cell.h"
class PBoard : public BoardData {
	Cell **pBoard[14];
public:
	PBoard () {}
	virtual char charAt(int x, int y) const
	{
		int i = 0;
		//(*pBoard)[1][2].
		return 'a';
	}
	void setAdressToBoard(Cell* _pboard[][14])
	{
		//*pBoard = _pboard;
	
	}
};
