#include "Function.h"
#include "Evo\Evo.h"

int main(int argc, char** argv) {
	Evolution evo(10, 10);

	evo.createFirstGen();
	evo.printInfo(std::cout);

	system("PAUSE");
}