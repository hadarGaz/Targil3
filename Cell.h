#pragma once
#include "Soldier.h"
#include "enums.h"
#include <iostream>
class Cell {
	int cellType = 0;

public:
	Soldier* soldier = nullptr;

	void setCellType(int num);
	bool isCellEmpty();
	int returnedCellType() const;
};
