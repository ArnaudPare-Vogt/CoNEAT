#include <Catch\catch.hpp>
#include <Evo\Individual.h>


TEST_CASE("Individual constructor", "[Individual]") {
	IndividualDef def;
	def.genesNum = 10;
	def.inputNumber = 4;
	def.outputNumber = 3;

	Individual in(def);
	REQUIRE(in.getInputNumber() == 4);
	REQUIRE(in.getOutputNumber() == 3);
	REQUIRE(in.getGenes().size() == 10);

	for (auto it = in.getGenes().begin(); it != in.getGenes().end(); ++it) {
		REQUIRE(it->activated);
	}

	Individual i2(in);
	REQUIRE(i2.getInputNumber() == 4);
	REQUIRE(i2.getOutputNumber() == 3);
	REQUIRE(i2.getGenes().size() == 10);
	
	for (size_t i = 0; i < i2.getGenes().size(); i++)
	{
		REQUIRE(i2.getGenes()[i].in == in.getGenes()[i].in);
		REQUIRE(i2.getGenes()[i].out == in.getGenes()[i].out);
		REQUIRE(i2.getGenes()[i].weight == in.getGenes()[i].weight);
		REQUIRE(i2.getGenes()[i].activated == in.getGenes()[i].activated);
	}


	std::vector<Link> testLinks;

	testLinks.push_back(Link(0, 1, 0));
	testLinks.push_back(Link(0, 2, 1));
	testLinks.push_back(Link(0, 3, 2));
	testLinks.push_back(Link(2, 1, 3));
	testLinks.push_back(Link(3, 1, 4));

	Individual ind(testLinks, 1, 1);

	REQUIRE(ind.getInputNumber() == 1);
	REQUIRE(ind.getOutputNumber() == 1);
	REQUIRE(ind.getGenes().size() == 5);

	for (size_t i = 0; i < ind.getGenes().size(); i++)
	{
		REQUIRE(testLinks[i].in == ind.getGenes()[i].in);
		REQUIRE(testLinks[i].out == ind.getGenes()[i].out);
		REQUIRE(testLinks[i].weight == ind.getGenes()[i].weight);
		REQUIRE(testLinks[i].activated == ind.getGenes()[i].activated);
	}

	testLinks[0].in = 1;
	REQUIRE(testLinks[0].in != ind.getGenes()[0].in);


}


TEST_CASE("Input and output verification", "[Individual]") {
	std::vector<Link> testLinks;

	testLinks.push_back(Link(0, 1, 0));
	testLinks.push_back(Link(0, 2, 1));
	testLinks.push_back(Link(0, 3, 2));
	testLinks.push_back(Link(2, 1, 3));
	testLinks.push_back(Link(3, 1, 4));
	testLinks.push_back(Link(4, 5, 5));
	testLinks.push_back(Link(3, 4, 6));

	Individual ind(testLinks, 2, 1);

	REQUIRE(ind.isInput(0) == true);
	REQUIRE(ind.isInput(1) == true);
	REQUIRE(ind.isInput(2) == false);
	REQUIRE(ind.isInput(3) == false);
	REQUIRE(ind.isInput(4) == false);
	REQUIRE(ind.isInput(5) == false);


	REQUIRE(ind.isOutput(0) == false);
	REQUIRE(ind.isOutput(1) == false);
	REQUIRE(ind.isOutput(2) == true);
	REQUIRE(ind.isOutput(3) == false);
	REQUIRE(ind.isOutput(4) == false);
	REQUIRE(ind.isOutput(5) == false);
}

