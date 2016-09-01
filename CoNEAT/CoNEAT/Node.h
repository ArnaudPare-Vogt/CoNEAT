#pragma once

#include "Function.h"
#include <vector>

class Connection;

class Node {
public:
private:
	int nodeId;

	float lastValue, value;
	float incummulation;
	//A flag to check if the current node is activated or if it should be. Internally used only.
	bool activated;
	float (*activationFunction)(float incumulation);
	float (*cummulationFunction)(float n, float total);

	std::vector<Connection*> inputs;

public:
	//Creates a node with the given id
	Node(int nodeId);
	//The copy constructor of the node.
	Node(const Node& other);
	~Node();
	//Processes the nodes values using the activation function
	inline void process() { this->value = this->activationFunction(this->incummulation); };
	//Cumulates the value provided in the node
	inline void cummulate(float n) { this->incummulation = this->cummulationFunction(n, this->incummulation); };
	
	//Tries to fire the node (if it has not been fired yet)
	void fire();

	//Resets the node. This has two impacts : flushes value into 
	//lastValue, and prepares the node for the next pass
	void reset();

	//Attaches c as an input
	void attachInput(Connection& c);
	//Detaches c from the input list
	void detatchInput(Connection& c);

	//gets the value of the node.
	float getValue() const;
	//Gets the last value (the value of the last tick) of the node
	float getLastValue() const;
	//Returns the ID of the current Node
	int getId() const;
	//Returns the attached inputs of this node. Useful to navigate the graph
	std::vector<Connection*> getInputs();
};