#include "Individual.h"


std::uniform_int_distribution<> IndividualDef::getInputDistrib() {
	std::uniform_int_distribution<> dis(0, inputNumber-1);
	return dis;
}

std::uniform_int_distribution<> IndividualDef::getOutputDistrib() {
	std::uniform_int_distribution<> dis(inputNumber, inputNumber + outputNumber - 1);
	return dis;
}

Individual::Individual(IndividualDef geneNum) : 
	inputNumber(geneNum.inputNumber),
	outputNumber(geneNum.outputNumber) 
{
	Link temp;

	std::uniform_int_distribution<> inputDis = geneNum.getInputDistrib();
	std::uniform_int_distribution<> outputDis = geneNum.getOutputDistrib();


	for (int i = 0; i < geneNum.genesNum; i++)
	{
		temp.in = inputDis(rng);
		temp.out = outputDis(rng);
		genes.push_back(temp);
	}

}

Individual::Individual(std::vector<Link> &genes, int inputNumber, int outputNumber) :
	inputNumber(inputNumber),
	outputNumber(outputNumber)
{
	this->genes = genes;
}

Individual::Individual(const Individual& other) :
	inputNumber(other.inputNumber),
	outputNumber(other.outputNumber) 
{
	for (std::vector<Link>::const_iterator it = other.genes.begin(); it != other.genes.end(); it++) {
		genes.push_back(*it);
	}
}

Individual::~Individual() 
{

}


std::ostream& operator<<(std::ostream& os, const Individual& ind) {
	os << ind.genes.size() << " genes" << std::endl;

	int i=0;
	for (std::vector<Link>::const_iterator it = ind.genes.begin(); it != ind.genes.end(); it++) {
		i++;
		os << "G" << i << " : " << (*it);
	}

	return os;
}

bool Individual::isInput(int nodeId) const {
	return 0 <= nodeId && nodeId < inputNumber;
}

bool Individual::isOutput(int nodeId) const {
	return inputNumber <= nodeId && nodeId < inputNumber + outputNumber;
}

const std::vector<Link>& Individual::getGenes() const {
	return genes;
}

const int Individual::getInputNumber() const {
	return inputNumber;
}

const int Individual::getOutputNumber() const {
	return outputNumber;
}


