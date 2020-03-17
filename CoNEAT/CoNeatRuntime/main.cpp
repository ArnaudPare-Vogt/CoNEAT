#include <fstream>
#include <iomanip>
#include <set>
#include <string>
#include <stdexcept>

#include <Function.h>
#include <Evo\Evo.h>
#include <Brain.h>

static const unsigned TEST_GEN = 400;
static const unsigned TEST_AMOUNT = 4;

void saveToCSV(const Individual& ind, const std::string& fileName) {
	std::ofstream out(fileName);
	out << "Source,Target,Weight,Activated,i,o\n";
	for (const Link& l : ind.getGenes()) {
		out << l.in << "," << l.out << "," << l.weight << "," << l.activated << "," << ind.isInput(l.in) << "," << ind.isOutput(l.out) << "\n";
	}
}
void saveAsDot(const Individual& ind, const std::string& fileName) {
	std::ofstream out(fileName);
	out << "digraph {\n";
	std::set<int> nodes = {};
	for (const Link& l : ind.getGenes()) {
		nodes.insert(l.in);
		nodes.insert(l.out);
	}
	for (const int& nodeId : nodes) {
		out << "N" << nodeId << ";\n";
	}
	for (const Link& l : ind.getGenes()) {
		out << "N" << l.in << " -> " << "N" << l.out << ";\n";
	}
	out << "}";
}



int main(int argc, char** argv) {
	std::ofstream out("output.csv");
	out << "generation, test_mean_val" << std::endl;

	EvolutionDef evoDef;
	evoDef.weightChangeChancePerGene = 0.1;
	evoDef.nodeAdditionChance = 0.0001;
	evoDef.connectionAdditionChance = 0.0001;
	evoDef.generationSize = 100;
	evoDef.selectionSize = 20;
	evoDef.geneActivationChance = 0.01;
	evoDef.geneDeactivationChance = 0.01;
	Evolution evo(evoDef);

	IndividualDef def;
	def.genesNum = 0;
	def.inputNumber = 2;
	def.outputNumber = 1;
	evo.createFirstGen(def);

	std::uniform_int_distribution<> binaryNum(0,1);

	for (unsigned i = 0; i < TEST_GEN; i++)
	{
		float sum = 0;
		float count = 0;
		for (auto it = evo.getTestPlotBeginIterator(); it != evo.getTestPlotEndIterator(); ++it)
		{
			std::pair<Individual*, float> &test = (*it);
			const Individual& ind = *(test.first);
			Brain neuralNet(ind);

			for (size_t i = 0; i < TEST_AMOUNT; i++)
			{
				neuralNet.preProcessNodes();

				int a = i & 0x1;
				int b = (i & 0x2) >> 1;
				(*(neuralNet.getInputs()[0])).setValue(a);
				(*(neuralNet.getInputs()[1])).setValue(b);

				neuralNet.processNodes();
				float result = (*(neuralNet.getOutputs()[0])).getValue();

				//std::cout << "#" << i << " = " << a << "->" << result << std::endl;

				if ((result > 0.5 && (a == b))
					|| (result < 0.5 && (a != b))) {
					test.second += 1;
					//std::cout << "SUCESS" << std::endl;
				}
			}

			sum += test.second;
			++count;

			if (i == TEST_GEN-1) {
				std::cout << std::setw(3) << count << " - Result is " << (double(test.second) / TEST_AMOUNT) << std::endl;
			}
		}

		double mean = double(sum) / count / TEST_AMOUNT;
		std::cout << mean << std::endl;

		out << i << "," << mean << std::endl;

		if (i < TEST_GEN) {
			evo.nextGen();
		}
	}

	out.close();

	std::cout << "To save an individual, enter its number.\nTo save a dot file of an idividual, enter 'd' and the idividuals number.\nTo quit, enter 'q'" << std::endl;
	
	std::string command;
	while ((std::cin >> command), (command != "q")) {
		try {
			bool saveAsDotFile = command.size() >= 1 && command.rfind("d", 0) == 0;
			if (saveAsDotFile) {
				command = command.substr(1, command.size() - 1);
			}

			int num = std::stoi(command);
			num--;

			int maxSize = evo.getCurrentGeneration().size();

			if (num < 0 || num >= evo.getCurrentGeneration().size()) {
				std::cout << "The number must be between 1 and " << maxSize << std::endl;
				continue;
			}

			if (saveAsDotFile) {
				std::string fileName = std::string("Individual_") + std::to_string(num) + ".dot";
				saveAsDot(evo.getCurrentGeneration()[num], fileName);
			}
			else {
				std::string fileName = std::string("Individual_") + std::to_string(num) + ".csv";
				saveToCSV(evo.getCurrentGeneration()[num], fileName);
			}
		}
		catch (const std::invalid_argument& e) {

		}
	}

	//evo.printInfo(std::cout);

}
