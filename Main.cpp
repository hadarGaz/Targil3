#include <iostream>
#include "AlgorithmRegistration.h"
#include "GameManager.h"
int main(int argc, char* argv[]) {
	AlgorithmRegistration algo_NofarKedemID("algo_NofarAndHadar",
		[] {return new AlgoPalyer();}
	);
	GameManager().commandLine(argc,argv);

}