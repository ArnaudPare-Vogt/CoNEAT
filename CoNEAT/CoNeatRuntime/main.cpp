#include <fstream>
#include <Function.h>
#include <Evo\Evo.h>
#include <Brain.h>

#define WE_ARE_TESITNG 0

#if WE_ARE_TESITNG
int test();
#endif

#define TEST_GEN 100
#define TEST_AMOUNT 50

int main(int argc, char** argv) {
#if WE_ARE_TESITNG
	{
		int i = test();
		if (i != 0) {
			return i;
		}
	}
#endif
	std::ofstream out("output.csv");
	out << "generation, test_mean_val" << std::endl;

	EvolutionDef evoDef;
	evoDef.weightChangeChancePerGene = 0.5;
	evoDef.nodeAdditionChance = 0.001;
	evoDef.connectionAdditionChance = 0.001;
	evoDef.generationSize = 100;
	evoDef.selectionSize = 10;
	evoDef.geneActivationChance = 0.1;
	evoDef.geneDeactivationChance = 0.1;
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
		while (evo.hasNextTestIndividual())
		{
			std::pair<Individual*, float> &test = evo.getTestIndividual();
			Individual ind = *(test.first);
			Brain neuralNet(ind);

			for (size_t i = 0; i < TEST_AMOUNT; i++)
			{
				neuralNet.preProcessNodes();

				int a = binaryNum(rng);
				int b = binaryNum(rng);
				(*(neuralNet.getInputs()[0])).setValue(a);
				(*(neuralNet.getInputs()[1])).setValue(b);

				neuralNet.processNodes();
				float result = (*(neuralNet.getOutputs()[0])).getValue();

				//std::cout << "#" << i << " = " << a << "->" << result << std::endl;

				if ((result > 0.5 && a == 1 && b == 1)
					|| (result < 0.5 && (a == 0 || b == 0))) {
					test.second += 1;
					//std::cout << "SUCESS" << std::endl;
				}
			}

			sum += test.second;
			++count;

			if (i == TEST_GEN-1) {
				std::cout << "Result is " << (double(test.second) / TEST_AMOUNT) << std::endl;
			}
		}

		double mean = double(sum) / count;
		std::cout << mean << std::endl;

		out << i << "," << mean << std::endl;

		if (i < TEST_GEN) {
			evo.nextGen();
		}
	}

	out.close();

	evo.printInfo(std::cout);


	system("PAUSE");
}


#if WE_ARE_TESITNG
int test() {
	Link l;
	std::vector<Link> genes;

	//TESTING #1
	IFDEBUGV(::cout << "  - Testing #1 (returns 1)" << std::endl;)
	l.in = 0;
	l.out = 1;
	l.weight = 3.14;
	genes.push_back(l);
	Individual ind(genes, 1, 1);
	Brain brain(ind);
	float in1 = 1;
	float expectedOut1 = tanh(3.14);
	brain.preProcessNodes();
	(*(brain.getInputs()[0])).setValue(1);
	brain.processNodes();
	float realOut1 = (*(brain.getOutputs()[0])).getValue();

	if (abs(expectedOut1 - realOut1) < 0.0001) {
		std::cout << "G - Test #1 success!. Expected " << expectedOut1 << " got " << realOut1 << std::endl;
	}
	else {
		std::cout << "B - Test #1 failed. Expected " << expectedOut1 << " got " << realOut1 << std::endl;
	}


	
	return 0;
}
#endif
