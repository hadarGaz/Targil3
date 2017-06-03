#pragma once
#pragma once
#include "Direction.h"
#include <cstdlib>
#include <stdlib.h> 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "Utils.h"
#include "Cell.h"
using namespace std;

extern bool quietMode;

class Soldier {
	int _x = 0, _y = 0;
	int _x_dir = 0, _y_dir = 0;
	int soldierNum;
	int gamerNum;
	int seaPass = 0;
	int frPass = 0;
	bool isAlive = true;
	void draw(int ch) const;
	friend class GameManager;
public:
	void set(int x, int y, int ch);
	void Soldier::move(int x, int y);
	void Soldier::draw() const;
	void Soldier::earse(int oldX, int oldY);
	void Soldier::draw(int soldierNum) const;
	void Soldier::setCondition(int soldierNum);

};
