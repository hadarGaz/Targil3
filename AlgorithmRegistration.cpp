#pragma init_seg(lib)
#include "AlgorithmRegistration.h"

std::map<std::string, std::function<AbstractPlayer*(void)>> AlgorithmRegistration::AlgoFactory;

AlgorithmRegistration::AlgorithmRegistration(const std::string& id, std::function<AbstractPlayer*(void)> func) {

	AlgoFactory[id] = func;

}


AbstractPlayer* AlgorithmRegistration::getAlgoForId(const std::string& id) {

	auto id_func = AlgoFactory.find(id);
	auto& func = id_func->second;
	return func();

}
