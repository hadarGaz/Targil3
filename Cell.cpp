#include "Cell.h"

void Cell::setCellType(int num)
{
	this->cellType = num;
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