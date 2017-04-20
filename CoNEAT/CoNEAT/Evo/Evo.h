#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include "Individual.h"
#include "../Rng.h"

struct EvolutionDef {
	unsigned generationSize = 10;
	unsigned selectionSize = 4;

	float crossoverChance = 0.4;
	float weightChangeChancePerGene = 0.1;
	float weightChangeAmount = 0.2;

	float nodeAdditionChance = 0.01;
	float connectionAdditionChance = 0.01;

	float geneActivationChance = 0.1;
	float geneDeactivationChance = 0.1;
};

class Evolution{
private:
	int nextNodeIndex;

	unsigned generationSize;
	unsigned selectionSize;

	float crossoverChance;
	float weightChangeChancePerGene;
	float weightChangeAmount;

	float nodeAdditionChance;
	float connectionAdditionChance;

	float geneActivationChance;
	float geneDeactivationChance;

	std::vector<Individual> currentGenetation;


	std::vector<std::pair<Individual*, float>> testPlot;
	unsigned testIndex;

public:
	Evolution(const EvolutionDef &definition);
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
