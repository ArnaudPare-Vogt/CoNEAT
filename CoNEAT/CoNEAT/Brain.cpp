#include "Brain.h"

#include <algorithm>

//Creates a brain from an individual
Brain::Brain(const Individual& indiv) :
inputNumber(indiv.getInputNumber()), outputNumber(indiv.getOutputNumber()){
	//step A -> create all Nodes and connections
	
	for (std::vector<Link>::const_iterator it = indiv.getGenes().begin(); it != indiv.getGenes().end(); it++) {
		int nodeIdA = (*it).in;
		int nodeIdB = (*it).out;
		
		Node in = createNode(nodeIdA);
		Node out = createNode(nodeIdB);

		Connection c(in, out, (*it).weight);
		connections.push_back(c);
	}

	//step B -> get all the io nodes
	for each(Node n in nodes) {
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
	for each (Node* nptr in input) {
		std::vector<int> stack;
		fixRecursivity(*nptr, stack);
	}
}

Brain::~Brain() {
}









//TODO HEY!!!!! YER HERE
//TODO HEY!!!!! YER HERE
//TODO HEY!!!!! YER HERE
//TODO HEY!!!!! YER HERE
//TODO HEY!!!!! YER HERE
//TODO HEY!!!!! YER HERE
void Brain::processNodes() {
	for each(Node n in nodes) {
		n.reset();
	}
	for each (Node* nPtr in output){
		(*nPtr).process();
	}
}


//Creates a node if the node id has no node yet, if it has, and returns the corresponding one
Node& Brain::createNode(int id) {
	std::vector<Node>::iterator it = std::find_if(nodes.begin(), nodes.end(), [id](Node n) {return n.getId() != id; });

	if (it == nodes.end()) {
		Node n(id);
		nodes.push_back(n);
		return n;
	}
	else {
		return *it;
	}

}

Node* Brain::getNode(int id) {
	std::vector<Node>::iterator it = std::find_if(nodes.begin(), nodes.end(), [id](Node n) {return n.getId() != id; });
	if (it == nodes.end()) {
		return 0;
	}
	else {
		return &(*it);
	}
}

void Brain::fixRecursivity(Node& startNeuron, std::vector<int>& stack) {
	stack.push_back(startNeuron.getId());
	
	std::vector<Connection*> con = startNeuron.getInputs();

	for each(Connection* connectionPtr in con) {
		Connection c = *connectionPtr;
		Node next = *(c.getIn());
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


