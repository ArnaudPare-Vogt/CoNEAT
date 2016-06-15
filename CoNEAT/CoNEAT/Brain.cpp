#include "Brain.h"

//Creates a fresh neuralNet with the given number of input and outputs
//We create all the input/output neurons, and then we do not touch them anymore
Brain::Brain(unsigned inputNumber, unsigned outputNumber) :
	inputNumber(inputNumber),
	outputNumber(outputNumber) {

	//These will be copied in the node vectors :)
	const Node innputNode(Node::node_type::INPUT);
	const Node outputNode(Node::node_type::OUTPUT);

	//Generate the input/output nodes
	for (unsigned i = 0; i < inputNumber; i++) {
		this->nodes.push_back(innputNode);
	}
	for (unsigned i = 0; i < outputNumber; i++) {
		this->nodes.push_back(outputNode);
	}


}

//Generates the list of input/outputs from the general node list
//To do so we loop trough all nodes and check it's type
void Brain::generateInOutList() {

	input.clear();
	output.clear();

	for (std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		Node current = *it;

		switch (current.getType()) {
		case Node::node_type::INPUT:
			input.push_back(&current);
			break;
		case Node::node_type::OUTPUT:
			output.push_back(&current);
			break;
		}
	}
}