#include "Evo.h"

Evolution::Evolution(unsigned generationSize, unsigned initialGenesNum) 
: generationSize(generationSize), initialGenes(initialGenesNum) {

}


//Creates the first generation of individuals based on the given parameters.
void Evolution::createFirstGen() {
	this->currentGenetation.clear();

	//TODO settable def
	IndividualDef def;
	def.genesNum = 10;
	def.inputNumber = 4;
	def.outputNumber = 2;
	Individual ind(def);
	for (unsigned i = 0; i < initialGenes; i++) 
	{
		currentGenetation.push_back(ind);
	}
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

