#pragma once

#include <random>
#include <vector>

struct Link;

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

public:
	Individual(IndividualDef def);

	~Individual();

	Individual(const Individual &other);
	friend std::ostream& operator<<(std::ostream& os, const Individual& ind);
};

struct Link {

	int in;
	int out;

	Link();
	Link(const Link &other);

	friend std::ostream& operator<<(std::ostream& os, const Link& ind);
};