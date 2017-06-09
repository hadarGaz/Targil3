#include "Cell.h"

void Cell::setCellType(int num)
{
	this->cellType = num;
}

void Cell::setGamerType(int gamer)
{
	if (gamer == (int)GamerA::soldier1 || gamer == (int)GamerA::soldier2 || gamer == (int)GamerA::soldier3 || gamer == (int)GamerB::GamerB) {
		GamerA = gamer;
	}
	else {
		GamerB = gamer;
	}
}

bool Cell::isCellEmpty()
{
	if (this->cellType == (int)Type::emptyType)
		return true;
	else
		return false;
}

int Cell::returnedCellType() const
{
	return this->cellType;

}