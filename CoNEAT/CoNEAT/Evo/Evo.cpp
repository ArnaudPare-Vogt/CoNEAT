#include "Evo.h"


Evolution::Evolution(const EvolutionDef &def) 
	: generationSize(def.generationSize),
	selectionSize(def.selectionSize),
	crossoverChance(def.crossoverChance),
	weightChangeChancePerGene(def.weightChangeChancePerGene),
	weightChangeAmount(def.weightChangeAmount),
	nodeAdditionChance(def.nodeAdditionChance),
	connectionAdditionChance(def.connectionAdditionChance),
	geneActivationChance(def.geneActivationChance),
	geneDeactivationChance(def.geneDeactivationChance),
	testIndex(0)
{

}

//Creates the first generation of individuals based on the given parameters.
void Evolution::createFirstGen(IndividualDef& definition) {
	nextNodeIndex = definition.inputNumber + definition.outputNumber;
	this->currentGenetation.clear();
	Individual ind(definition);
	for (unsigned i = 0; i < generationSize; i++) 
	{
		currentGenetation.push_back(ind);
	}
	prepareTestGeneration();
}

std::ostream& Evolution::printInfo(std::ostream &in) const {
	in << "Evo information (" << this << ")" << std::endl;
	in << "Contains " << currentGenetation.size() << " elements." << std::endl;

	if (currentGenetation.size() > 0) {

		in << std::endl << "----- LIST OF IND -----" << std::endl;

		for (std::vector<Individual>::const_iterator it = currentGenetation.begin(); it != currentGenetation.end(); it++)
		{
			in << "Indiv " << &(*it) << std::endl;
			in << "\t" << (*it) << std::endl;
		}
		in << std::endl << "----- ENDS OF IND -----" << std::endl;

	} else {
		in << "No individuals to display..." << std::endl;
	}

	return in;
}

std::pair<Individual*, float>& Evolution::getTestIndividual() {
	std::pair<Individual*, float>& pair = testPlot.at(testIndex);
	testIndex++;
	return pair;
}

bool Evolution::hasNextTestIndividual() const{
	return testIndex < testPlot.size();
}

const std::vector<Individual>& Evolution::getCurrentGeneration() const {
	return currentGenetation;
}

void Evolution::nextGen() {
	
	std::uniform_real_distribution<float> fract(0.0, 1.0);

	//Step A - selection of apt individuals.
	std::vector<Individual> toCrossover;
	{
		float fitSum = 0;
		for each (std::pair<Individual*, float> pair in testPlot) {
			fitSum += pair.second;
		}
		if (fitSum == 0.0f) {
			std::uniform_real_distribution<float> pick(0, testPlot.size());
			for (int i = 0; i < selectionSize; i++) {
				std::pair<Individual*, float> pair = testPlot.at(pick(rng));
				toCrossover.push_back(*pair.first);
			}
		}
		else {
			for each (std::pair<Individual*, float> pair in testPlot) {
				pair.second /= fitSum;
			}
			std::sort(testPlot.begin(), testPlot.end(),
				[](const std::pair<Individual*, float> p1, const std::pair<Individual*, float> p2) {
				return p1.second > p2.second;
			});
			std::vector<float> selected;
			for (int i = 0; i < testPlot.size(); i++) {
				float cummul = 0;
				for (int j = i; j >= 0; j--) {
					cummul += testPlot.at(j).second;
				}
				selected.push_back(cummul);
			}


			for (int i = 0; i < selectionSize; i++) {
				float r = fract(rng);
				for (int j = 0; j < selected.size(); j++) {
					if (selected.at(j) > r) {
						std::pair<Individual*, float> pair = testPlot.at(j);
						toCrossover.push_back(*pair.first);

						selected[j] = -1;
						break;
					}
				}
			}
		}
	}

	

	//Step B - crossover and filling current gen
	//populates currentGeneration
	{
		currentGenetation.clear();
		unsigned size = toCrossover.at(0).getGenes().size();
		std::uniform_int_distribution<int> splitPos(0, size);
		for (int i = 0; i < generationSize; i+=2)
		{
			Individual parentA = toCrossover.at((i + 0) % toCrossover.size());
			Individual parentB = toCrossover.at((i + 1) % toCrossover.size());

			const std::vector<Link> &linksA = parentA.getGenes();
			const std::vector<Link> &linksB = parentB.getGenes();
			assert(linksA.size() == linksB.size());
			
			std::vector<Link> newGenesA;
			std::vector<Link> newGenesB;

			unsigned split = 0;
			if (fract(rng) < crossoverChance) {
				split = splitPos(rng);
			}

			for (unsigned j = 0; j < split; j++)
			{
				newGenesA.push_back(linksA[j]);
				newGenesB.push_back(linksB[j]);
			}
			for (unsigned j = split; j < size; j++)
			{
				newGenesA.push_back(linksB[j]);
				newGenesB.push_back(linksA[j]);
			}

			Individual indA(newGenesA, parentA.getInputNumber(), parentA.getOutputNumber());
			currentGenetation.push_back(indA);

			if (i + 1 < generationSize) {
				Individual indB(newGenesB, parentB.getInputNumber(), parentB.getOutputNumber());
				currentGenetation.push_back(indB);
			}
		}
	}

	//Step C - mutations
	{
		//a) change weights
		{
			unsigned size = currentGenetation[0].genes.size();
			std::uniform_real_distribution<float> wheightChange(-weightChangeAmount, weightChangeAmount);
			for (unsigned i = 0; i < currentGenetation.size(); i++)
			{
				Individual &ind = currentGenetation[i];
				for (unsigned j = 0; j < ind.genes.size(); j++)
				{
					if (fract(rng) < weightChangeChancePerGene) {
						ind.genes[j].weight += wheightChange(rng);
					}
				}
			}
		}

		//b) mutate node additions
		{
			if (currentGenetation[0].genes.size() > 0) {
				for (unsigned i = 0; i < currentGenetation.size(); i++)
				{
					if (fract(rng) < nodeAdditionChance) {
						std::uniform_int_distribution<> geneToSplit(0, currentGenetation[i].genes.size() - 1);
						int geneID = geneToSplit(rng);


						int newNeuronId = nextNodeIndex;
						nextNodeIndex++;

						Link& oldLnk = currentGenetation[i].genes[geneID];
						int inputNeuronId = oldLnk.in;
						int outputNeuronId = oldLnk.out;

						Link newLinkA;
						newLinkA.in = inputNeuronId;
						newLinkA.out = newNeuronId;
						newLinkA.activated = false;

						Link newLinkB;
						newLinkB.in = newNeuronId;
						newLinkB.out = outputNeuronId;
						newLinkB.activated = false;

						for (unsigned j = 0; j < currentGenetation.size(); j++)
						{
							Individual &ind = currentGenetation[j];
							if (j == i) {
								ind.genes[geneID].activated = false;
								newLinkA.activated = true;
								newLinkB.activated = true;
								ind.genes.push_back(newLinkA);
								ind.genes.push_back(newLinkB);
								newLinkA.activated = false;
								newLinkB.activated = false;
							}
							else {
								ind.genes.push_back(newLinkA);
								ind.genes.push_back(newLinkB);
							}
						}
					}
				}
			}
		}

		//c) mutate connection additions
		{
			int inputNumber = currentGenetation[0].getInputNumber();
			int outputNumber = currentGenetation[0].getOutputNumber();
			std::uniform_int_distribution<> inputNeuron(0, nextNodeIndex - 1 - outputNumber);
			std::uniform_int_distribution<> outputNeuron(0, nextNodeIndex - 1 - inputNumber);
			for (unsigned i = 0; i < currentGenetation.size(); i++)
			{
				if (fract(rng) < connectionAdditionChance) {

					int inputNeuronId = inputNeuron(rng);
					if (inputNeuronId >= inputNumber) {
						inputNeuronId += outputNumber;
					}

					int outputNeuronId = outputNeuron(rng);
					outputNeuronId += inputNumber;

					Link link;
					link.in = inputNeuronId;
					link.out = outputNeuronId;
					for (unsigned j = 0; j < currentGenetation.size(); j++)
					{
						link.activated = (j == i);
						currentGenetation[j].genes.push_back(link);
					}
				}
			}
		}
	}

	//d) mutate genes activation/deactivation
	{
		for (int i = 0; i < currentGenetation.size(); i++)
		{
			Individual &ind = currentGenetation[i];
			for (int j = 0; j < ind.genes.size(); j++)
			{
				Link &l = ind.genes[j];
				if (l.activated) {
					if (fract(rng) < geneDeactivationChance) {
						l.activated = false;
					}
				}
				else {
					if (fract(rng) < geneActivationChance) {
						l.activated = true;
					}
				}
			}
		}
	}


	//set currentGenetation


	prepareTestGeneration();
}


void Evolution::prepareTestGeneration() {
	testPlot.clear();
	testIndex = 0;
	for (Individual &ind : currentGenetation) {
		Individual* indPtr = &ind;
		std::pair<Individual*, float> pair(indPtr, 0);
		testPlot.push_back(pair);
	}
}

