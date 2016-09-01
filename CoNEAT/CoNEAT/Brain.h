#pragma once

#include "Connection.h"
#include "Evo\Individual.h"
#include <vector>


//TODO Breeding
//Class that controlls the (physical) neural net. Is it technically the phenotype of the creature.
class Brain {
private:
	std::vector<Connection> connections;
	std::vector<Node> nodes;
	std::vector<Node*> input, output;

	int inputNumber, outputNumber;

	//Flag to see if pre process was called
	bool preProcessed = false;

public:
	//Creates a brain from an individual
	Brain(const Individual& i);
#if 0
	//Copies a brain into this brain. Should perform a Deep-Copy
	Brain(const Brain& other);
#endif
	//Destructor
	virtual ~Brain();

	//Processes the neuralNet, using the current input values, and sets the output values
	void processNodes();

	//Getter for the input nodes.
	inline const std::vector<Node*> getInputs() const { return input; };
	//Getter for the output nodes
	inline const std::vector<Node*> getOutputs() const { return output; };

private:
	//Creates a node if the node id has no node yet, if it has, and returns the corresponding one
	Node& createNode(int nodeId);
	//Gets the node referenced (or a null pointer)
	Node* getNode(int nodeID);
	//Fixed and sets the correct flags in case the net is recursive
	void fixRecursivity(Node& s, std::vector<int>& stack);
};
