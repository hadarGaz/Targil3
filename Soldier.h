#pragma once
#include <cstdlib>
#include <stdlib.h> 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "Utils.h"
#include "enums.h"
using namespace std;

extern bool quietMode;

class Soldier {
	int _x = 0, _y = 0;
	int _x_dir = 0, _y_dir = 0;
	int oldX = 0, oldY = 0;
	int soldierNum = 0;
	int gamerNum = 0;
	int seaPass = 0;
	int frPass = 0;
	bool isAlive = true;
	friend class GameManager;
	friend class AlgoPalyer;
public:
	void set(int x, int y, int ch);
	void move(int x, int y);
	void draw() const;
	void earse(int oldX, int oldY);
	void draw(int soldierNum) const;
	void setCondition(int soldierNum);
	int getsoldierNum();
	//int getsoldierX();
	//int getsoldierY();


};
