#include "Function.h"
#include "Evo\Evo.h"
#include "Brain.h"

#define WE_ARE_TESITNG 0


#define NO_DEBUG 0
#define DEBUG_LEVEL_REGULAR 1
#define DEBUG_LEVEL_VERBROSE 2
#define DEBUG DEBUG_LEVEL_REGULAR

#if DEBUG == NO_DEBUG
#define IFDEBUG(x)
#define IFDEBUGV(x)
#elif DEBUG == DEBUG_LEVEL_REGULAR
#define IFDEBUG(x) x
#define IFDEBUGV(x)
#elif DEBUG == DEBUG_LEVEL_VERBROSE
#define IFDEBUG(x) x
#define IFDEBUGV(x) x
#endif

#if WE_ARE_TESITNG
int test();
#endif

int main(int argc, char** argv) {
#if WE_ARE_TESITNG
	{
		int i = test();
		if (i != 0) {
			return i;
		}
	}
#endif

	Evolution evo(10, 10);

	IndividualDef def;
	def.genesNum = 10;
	def.inputNumber = 4;
	def.outputNumber = 2;
	evo.createFirstGen(def);
	evo.printInfo(std::cout);

	Individual i = evo.getCurrentGeneration()[0];
	Brain b(i);



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
