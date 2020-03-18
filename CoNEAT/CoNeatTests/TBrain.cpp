#include <Catch/catch.hpp>
#include "Brain.h"

TEST_CASE("Brain constructor", "[Brain]") {
	std::vector<Link> topology;
	topology.push_back(Link(0, 3, 0));
	topology.push_back(Link(1, 2, 1));
	topology.push_back(Link(1, 3, 2));
	topology.push_back(Link(3, 2, 3));

	topology[0].weight = 16.f;
	topology[1].weight = -0.6f;
	topology[2].weight = -1.f;
	topology[3].weight = 1.f;

	Individual ind(topology, 2, 1);

	Brain b(ind);

	REQUIRE(b.getInputs().size() == 2);
	REQUIRE(b.getInputs()[0]->getId() == 0);
	REQUIRE(b.getInputs()[1]->getId() == 1);
	REQUIRE(b.getOutputs().size() == 1);
	REQUIRE(b.getOutputs()[0]->getId() == 2);

	std::vector<Connection*>& in2 = b.getOutputs()[0]->getInputs();
	REQUIRE(in2.size() == 2);
	Neuron* n3;
	if (in2[0]->getIn()->getId() == 1) {
		n3 = in2[1]->getIn();
		REQUIRE(n3->getId() == 3);
	} else {
		n3 = in2[0]->getIn();
		REQUIRE(n3->getId() == 3);
		REQUIRE(in2[1]->getIn()->getId() == 1);
	}

	std::vector<Connection*>& in3 = n3->getInputs();
	REQUIRE(in3.size() == 2);

	if (in3[0]->getIn()->getId() == 0) {
		REQUIRE(in3[1]->getIn()->getId() == 1);
	}
	else {
		REQUIRE(in3[0]->getIn()->getId() == 1);
		REQUIRE(in3[1]->getIn()->getId() == 0);
	}
}

TEST_CASE("Brain fire/reset", "[Brain") {
	std::vector<Link> topology;
	topology.push_back(Link(0, 2, 0));
	topology.push_back(Link(0, 3, 1));
	topology.push_back(Link(1, 2, 2));
	topology.push_back(Link(1, 3, 3));


	Individual ind(topology, 2, 2);

	Brain b(ind);
	b.preProcessNodes();
	b.getInputs()[0]->setValue(100);
	b.getInputs()[1]->setValue(0);
	b.processNodes();
	REQUIRE(b.getOutputs()[0]->getValue() > 0);
	REQUIRE(b.getOutputs()[1]->getValue() > 0);

	b.preProcessNodes();
	REQUIRE(b.getInputs()[0]->getLastValue() == 100);
	REQUIRE(b.getInputs()[1]->getLastValue() == 0);
	REQUIRE(b.getOutputs()[0]->getLastValue() > 0);
	REQUIRE(b.getOutputs()[1]->getLastValue() > 0);

	b.getInputs()[0]->setValue(0);
	b.getInputs()[1]->setValue(0);

	b.processNodes();
	REQUIRE(b.getOutputs()[0]->getValue() == 0);
	REQUIRE(b.getOutputs()[1]->getValue() == 0);

}



TEST_CASE("Brain, 'and' gate test", "[Brain]") {
	std::vector<Link> topology;
	topology.push_back(Link(0, 2, 0));
	topology.push_back(Link(1, 2, 1));

	topology[0].weight = 0.6f;
	topology[1].weight = 0.6f;

	Individual ind(topology, 2, 1);

	Brain b(ind);

	//Some tests on the format of the network
	REQUIRE(b.getInputs().size() == 2);
	REQUIRE(b.getInputs()[0]->getId() == 0);
	REQUIRE(b.getInputs()[1]->getId() == 1);
	REQUIRE(b.getOutputs().size() == 1);
	REQUIRE(b.getOutputs()[0]->getId() == 2);

	float treshold = 0.7f;

	//tests on 0,0
	b.preProcessNodes();
	b.getInputs()[0]->setValue(0);
	b.getInputs()[1]->setValue(0);
	b.processNodes();
	REQUIRE(b.getOutputs()[0]->getValue() < treshold);

	//tests on 1,0
	b.preProcessNodes();
	b.getInputs()[0]->setValue(1);
	b.getInputs()[1]->setValue(0);
	b.processNodes();
	REQUIRE(b.getOutputs()[0]->getValue() < treshold);

	//tests on 0,1
	b.preProcessNodes();
	b.getInputs()[0]->setValue(0);
	b.getInputs()[1]->setValue(1);
	b.processNodes();
	REQUIRE(b.getOutputs()[0]->getValue() < treshold);

	//tests on 1,1
	b.preProcessNodes();
	b.getInputs()[0]->setValue(1);
	b.getInputs()[1]->setValue(1);
	b.processNodes();
	REQUIRE(b.getOutputs()[0]->getValue() > treshold);

}