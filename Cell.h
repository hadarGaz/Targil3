#pragma once
#include "Soldier.h"
#include "enums.h"
#include <iostream>
class Cell {
	int cellType = 0;
	int GamerA = 0;
	int GamerB = 0;
public:
	Soldier* soldier = nullptr;

	void setCellType(int num);
	void setGamerType(int gamer);
	bool isCellEmpty();
	int returnedCellType() const;
	int returnNumOfGamer();
	

};
