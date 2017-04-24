#pragma once

#include "Neuron.h"
#include "Evo\Individual.h"
#include <vector>


//TODO Breeding
//Class that controlls the (physical) neural net. Is it technically the phenotype of the creature.
class Brain {
private:
	int inputNumber, outputNumber;

	//Flag to see if pre process was called
	bool preProcessed = false;

	std::vector<Neuron> nodes;
	std::vector<Neuron*> input, output;
	//std::vector<Connection*> connections;

public:
	//Creates a brain from an individual
	Brain(const Individual& i);
#if 0
	//Copies a brain into this brain. Should perform a Deep-Copy
	Brain(const Brain& other);
#endif
	//Destructor
	virtual ~Brain();
	
	//Pre-processes the nodes. Should be called before inputs are set.
	void preProcessNodes();
	//Processes the neuralNet, using the current input values, and sets the output values
	void processNodes();

	//Getter for the input nodes.
	inline const std::vector<Neuron*> getInputs() const { return input; };
	//Getter for the output nodes
	inline const std::vector<Neuron*> getOutputs() const { return output; };

private:
	//Creates a node if the node id has no node yet. DO NOT CALL IF YOU DON'T KNOW WHAT YOU ARE DOING. NOT SAFE!!!
	void createNode(int nodeId);
	//Gets the node referenced (or a null pointer)
	Neuron* getNode(int nodeID);
	//Fixed and sets the correct flags in case the net is recursive
	void fixRecursivity(Neuron& s, std::vector<int>& stack);
};
