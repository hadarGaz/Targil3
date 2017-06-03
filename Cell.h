#pragma once
#include "Soldier.h"
#include "enums.h"
class Cell {
	int cellType = 0;
	//int GamerA = 0;
	//int GamerB = 0;
	
public:
	Soldier* soldier = nullptr;
	void Cell::setCellType(int num)
	{
		this->cellType = num;
	}
	bool Cell::isCellEmpty()
	{
		if (this->cellType == (int)Type::emptyType && this->GamerA == (int)GamerA::noGamerA && this->GamerB == (int)GamerB::noGamerB)
			return true;
		else
			return false;
	}

	int Cell::returnedCellType() const
	{
		return this->cellType;

	}
	int Cell::returndGamer()
	{
		if (this->GamerA != 0) {
			return 1;
		}
		else if (this->GamerB != 0)
		{
			return 2;
		}
		return 0;
	}
};
