#pragma once

#include "Function.h"
#include <vector>

class Connection;

class Neuron {
public:
	//Creates a node with the given id
	Neuron(int nodeId);
	//The copy constructor of the node.
	Neuron(const Neuron& other);
	~Neuron();
public:
	//Tries to fire the node (if it has not been fired yet)
	void fire();

	//Freezes the node, making it so thet is dosen't recalculate before resetting
	void freeze();

	//Resets the node. This has two impacts : flushes value into 
	//lastValue, and prepares the node for the next pass
	void reset();

	//Attaches c as an input
	void attachInput(Connection& c);
	//Detaches c from the input list
	void detatchInput(Connection& c);

	void setValue(float value);

	//gets the value of the node.
	float getValue() const;
	//Gets the last value (the value of the last tick) of the node
	float getLastValue() const;
	//Returns the ID of the current Node
	int getId() const;
	//Returns the attached inputs of this node. Useful to navigate the graph
	std::vector<Connection*> &getInputs();

private:
	//Processes the nodes values using the activation function
	void process(float incummulation);
	//Cumulates the value provided in the node
	float cummulate(float n, float incummulation);

private:
	int nodeId_;

	float lastValue_, value_;
	//A flag to check if the current node is activated or if it should be. Internally used only.
	bool activated_;
	float(*activationFunction_)(float incumulation);
	float(*cummulationFunction_)(float n, float total);

	std::vector<Connection*> inputs_;
};