#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include "Individual.h"
#include "../Rng.h"



class Evolution{
private:
	int nextNodeIndex;

	unsigned generationSize;
	unsigned initialGenes;

	unsigned selectionSize;

	float crossoverChance;
	float weightChangePerGene;
	float weightChangeAmount;

	float nodeAdditionChance;
	float connectionAdditionChance;

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
