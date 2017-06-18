#include "HadarNofarCell.h"

void HadarNofarCell::setCellType(int num)
{
	this->cellType = num;
}

void HadarNofarCell::setGamerType(int gamer)
{
	if (gamer == 0)
	{
		GamerA = 0;
		GamerB = 0;
	}
	if (gamer == (int)GamerA::soldier1 || gamer == (int)GamerA::soldier2 || gamer == (int)GamerA::soldier3 || gamer == (int)GamerA::GamerA) {
		GamerA = gamer;
	}
	else {
		GamerB = gamer;
	}
}

bool HadarNofarCell::isCellEmpty()
{
	if (this->cellType == (int)Type::emptyType && this->soldier == nullptr && GamerA ==0 && GamerB ==0)
		return true;
	else
		return false;
}

int HadarNofarCell::returnedCellType() const
{
	return this->cellType;

}

int HadarNofarCell::returnNumOfGamer()
{
	if (GamerA != 0)
		return 1;
	else if (GamerB != 0)
		return 2;
	else
		return 0;
}
