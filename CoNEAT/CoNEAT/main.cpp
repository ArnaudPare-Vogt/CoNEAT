#include "Function.h"
#include "Evo\Evo.h"
#include "Brain.h"

int main(int argc, char** argv) {
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