#pragma once

#include <random>
#include <vector>
#include <iostream>
#include "../Rng.h"

struct Link;
class Evolution;

struct IndividualDef {
	int genesNum;

	//From [0 to inputNumber[
	int inputNumber;
	//From [inputNumber to inputNumber + outputNumber[
	int outputNumber;

	std::uniform_int_distribution<> getInputDistrib();
	std::uniform_int_distribution<> getOutputDistrib();
};

class Individual {
	std::vector<Link> genes;
	int inputNumber, outputNumber;

public:
	Individual(IndividualDef def);
	Individual(std::vector<Link> &genes, int inputNumber, int outputNumber);

	~Individual();

	Individual(const Individual &other);
	friend std::ostream& operator<<(std::ostream& os, const Individual& ind);


	const std::vector<Link>& getGenes() const;
	const int getInputNumber() const;
	const int getOutputNumber() const;

	friend Evolution;
};

struct Link {

	int in;
	int out;
	float weight;
	bool activated;

	Link();
	Link(const Link &other);

	friend std::ostream& operator<<(std::ostream& os, const Link& ind);
};