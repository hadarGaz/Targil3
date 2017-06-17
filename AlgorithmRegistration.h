#pragma once
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include "AbstractPlayer.h"
#define _CRT_SECURE_NO_WARNINGS


class AlgorithmRegistration{
	static std::map<std::string, std::function<AbstractPlayer*(void)>> AlgoFactory;

public:
	AlgorithmRegistration(const std::string& id, std::function<AbstractPlayer*(void)> func);
	~AlgorithmRegistration() {};

	static AbstractPlayer* getAlgoForId(const std::string& id);

};