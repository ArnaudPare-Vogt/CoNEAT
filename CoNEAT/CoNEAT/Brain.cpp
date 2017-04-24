#include "Brain.h"

#include <algorithm>

//Creates a brain from an individual
Brain::Brain(const Individual& indiv) :
inputNumber(indiv.getInputNumber()), outputNumber(indiv.getOutputNumber()){
	//step A -> create all Nodes
	
	for (std::vector<Link>::const_iterator it = indiv.getGenes().begin(); it != indiv.getGenes().end(); it++) {
		if ((*it).activated) {
			int nodeIdA = (*it).in;
			int nodeIdB = (*it).out;

			createNode(nodeIdA);
			createNode(nodeIdB);
		}
	}

	for (size_t i = 0; i < inputNumber + outputNumber; i++)
	{
		createNode(i);
	}

	//Step B -> create all connections

	for (Link link : indiv.getGenes()) {
		if (link.activated) {
			Neuron* in = getNode(link.in);
			Neuron* out = getNode(link.out);

			Connection c(*in, *out, link.weight);
			connections.push_back(c);
		}
	}

	//step B -> get all the io nodes
	for (Neuron &n : nodes) {
		int id = n.getId();
		if (id < inputNumber && id >= 0) {
			//we got an input node
			input.push_back(&n);
		}
		else if (id < inputNumber + outputNumber && id >= inputNumber) {
			//we got an output node
			output.push_back(&n);
		}
	}

	//step C -> fix recursivity problems
	for (Neuron* nptr : output) {
		std::vector<int> stack;
		fixRecursivity(*nptr, stack);
	}
}

Brain::~Brain() {
}







void Brain::preProcessNodes() {
	for each(Neuron n in nodes) {
		n.reset();
	}
}

void Brain::processNodes() {
	for each(Neuron* nPtr in input) {
		(*nPtr).freeze();
	}
	for each (Neuron* nPtr in output){
		(*nPtr).fire();
	}
}


//Creates a node if the node id has no node yet
void Brain::createNode(int id) {
	std::vector<Neuron>::iterator it = std::find_if(nodes.begin(), nodes.end(), [id](Neuron n) {
		return n.getId() == id;
	});

	if (it == nodes.end()) {
		Neuron n(id);
		nodes.push_back(n);
	}
}

Neuron* Brain::getNode(int id) {
	std::vector<Neuron>::iterator it = std::find_if(nodes.begin(), nodes.end(), [id](Neuron n) {return n.getId() == id; });
	if (it == nodes.end()) {
		return 0;
	}
	else {
		return &(*it);
	}
}

void Brain::fixRecursivity(Neuron& startNeuron, std::vector<int>& stack) {
	stack.push_back(startNeuron.getId());
	
	std::vector<Connection*> &con = startNeuron.getInputs();

	for (Connection* connectionPtr : con) {
		Connection &c = *connectionPtr;
		Neuron &next = *(c.getIn());
		if (std::find(stack.begin(), stack.end(), next.getId()) != stack.end()) {
			//Neuron is recursive!!!
			c.setRecursivity(true);
		}
		else {
			//TODO chack if the neuron has been visited before
			fixRecursivity(next, stack);
		}
	}

	stack.pop_back();
}


