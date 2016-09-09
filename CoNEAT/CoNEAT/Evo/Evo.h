#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "Individual.h"



class Evolution{
private:
	unsigned generationSize;
	unsigned initialGenes;

	unsigned selectionSize;

	std::vector<Individual> currentGenetation;


	std::vector<std::pair<Individual*, float>> testPlot;
	unsigned testIndex;

public:
	Evolution(unsigned generationSize, unsigned initialGenesNum);
	void createFirstGen(IndividualDef& definition);
	std::ostream& printInfo(std::ostream &cout) const;

	const std::vector<Individual>& getCurrentGeneration() const;

	//Get the next text individual, and the pointer to this individual's fitness
	std::pair<Individual*, float>& getTestIndividual();
	//Returns if there is an individual left to test
	bool hasNextTestIndividual() const;

	//goes to the next generation
	void nextGen();

private:
	//prepares the test generation from the current one
	void prepareTestGeneration();
};
