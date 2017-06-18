#pragma once
#include "HadarNofarSoldier.h"
#include "HadarNofarEnums.h"
#include <iostream>
class HadarNofarCell {
	int cellType = 0;
	int GamerA = 0;
	int GamerB = 0;
public:
	HadarNofarSoldier* soldier = nullptr;

	void setCellType(int num);
	void setGamerType(int gamer);
	bool isCellEmpty();
	int returnedCellType() const;
	int returnNumOfGamer();
	

};
