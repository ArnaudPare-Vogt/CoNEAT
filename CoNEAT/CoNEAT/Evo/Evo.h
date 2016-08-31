#pragma once

#include <iostream>
#include <vector>
#include "Individual.h"

class Evolution{
private:
	unsigned generationSize;
	unsigned initialGenes;
	std::vector<Individual> currentGenetation;
public:
	Evolution(unsigned generationSize, unsigned initialGenesNum);
	void createFirstGen();
	std::ostream& printInfo(std::ostream &cout) const;
};
