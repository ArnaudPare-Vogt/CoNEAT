#include "Evo.h"

Evolution::Evolution(unsigned generationSize, unsigned initialGenesNum) 
: generationSize(generationSize), initialGenes(initialGenesNum), testIndex(0) {

}


//Creates the first generation of individuals based on the given parameters.
void Evolution::createFirstGen(IndividualDef& definition) {
	this->currentGenetation.clear();
	Individual ind(definition);
	for (unsigned i = 0; i < initialGenes; i++) 
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
	
	//Step A - selection of apt individuals.
	float fitSum = 0;
	for each (std::pair<Individual*, float> pair in testPlot) {
		fitSum += pair.second;
	}
	for each (std::pair<Individual*, float> pair in testPlot) {
		pair.second /= fitSum;
	}
	std::sort(testPlot.begin(), testPlot.end(),
		[](const std::pair<Individual*, float> p1, const std::pair<Individual*, float> p2){
		return p1.second > p2.second;
	});
	std::vector<float> selected;
	for (int i = 0; i < testPlot.size(); i++){
		float cummul = 0;
		for (int j = i; j >= 0; j--) {
			cummul += testPlot.at(j).second;
		}
		selected.push_back(cummul);
	}
#if 0
	for (int i = 0; i < selectionSize; i++) {
		r = rand
	}
#endif
}


void Evolution::prepareTestGeneration() {
	testPlot.clear();
	testIndex = 0;
	for each(Individual ind in currentGenetation) {
		Individual* indPtr = &ind;
		std::pair<Individual*, float> pair(indPtr, 0);
		testPlot.push_back(pair);
	}
}

