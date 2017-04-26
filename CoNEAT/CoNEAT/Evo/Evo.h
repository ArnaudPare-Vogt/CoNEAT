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

	float crossoverChance = 0.4f;
	float weightChangeChancePerGene = 0.1f;
	float weightChangeAmount = 0.2f;

	float nodeAdditionChance = 0.01f;
	float connectionAdditionChance = 0.01f;

	float geneActivationChance = 0.1f;
	float geneDeactivationChance = 0.1f;
};

class Evolution{
public:
	typedef std::vector<std::pair<Individual*, float>>::iterator testplot_iterator;
	typedef std::vector<std::pair<Individual*, float>>::const_iterator const_testplot_iterator;

	Evolution(const EvolutionDef &definition);
	void createFirstGen(IndividualDef& definition);
	std::ostream& printInfo(std::ostream &cout) const;

	const std::vector<Individual>& getCurrentGeneration() const;

	//Returns an iterator over the test plot
	testplot_iterator getTestPlotBeginIterator();
	testplot_iterator getTestPlotEndIterator();
	const_testplot_iterator getTestPlotBeginIterator() const;
	const_testplot_iterator getTestPlotEndIterator() const;


	//goes to the next generation
	void nextGen();

private:
	//prepares the test generation from the current one
	void prepareTestGeneration();

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

};
