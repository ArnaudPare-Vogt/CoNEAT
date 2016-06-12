#pragma once

#include "Connection.h"
#include <vector>


//TODO Breeding
//Class that controlls the (physical) neural net. Is it technically the phenotype of the creature.
class Brain {
private:
	std::vector<Connection> connections;
	std::vector<Node> nodes;
	std::vector<Node*> input, output;


public:
	//Creates a neuralNet with the given number of input and outputs
	Brain(unsigned inputNumber, unsigned outputNumber);
	//Copies a brain into this brain. Should perform a Deep-Copy
	Brain(const Brain& other);
	//Destructor
	virtual ~Brain();


	//Causes a random node mutaion to occur
	void mutateAddNode();
	//Adds a new connection
	void mutateAddConnection();

	//Geenrates the input and output list from the current nodes
	void generateInOutList();
	//Pre-processes all the outputs nodes. In a sense 'bakes' the net so that it can be used for generation values.
	void preProcessNodes();
	//Processes the neuralNet, using the current input values, and sets the output values
	void processNodes();

	//Getter for the input nodes.
	inline std::vector<Node*> getInputs() { return input; };
	//Getter for the output nodes
	inline std::vector<Node*> getOutputs() { return output; };

};
