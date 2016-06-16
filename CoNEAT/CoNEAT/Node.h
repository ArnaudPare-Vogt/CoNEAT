#pragma once

#include "Function.h"
#include <vector>

class Node {
public:
	enum class node_type { INPUT, OUTPUT, HIDDEN };
private:
	node_type type;
	float lastValue, value;
	float incummulation;
	//A flag to check if the current node is activated of of it should be. Internally used only.
	bool activated;
	float (*activationFunction)(float incumulation);
	float (*cummulationFunction)(float n, float total);
public:
	//Creates a node of the given type.
	Node(node_type n_type);
	//The copy constructor of the node.
	Node(const Node& other);
	~Node();
	//Processes the nodes values using the activation function
	inline void process() { this->value = this->activationFunction(this->incummulation); };
	//Cumulates the value provided in the node
	inline void cummulate(float n) { this->incummulation = this->cummulationFunction(n, this->incummulation); };
	
	//setters
	void setType(node_type t) {
		this->type = t;
	};
	
	//Tries to fire the node (if it has not been fired yet)
	void fire();

	//Resets the node. This has two impacts : flushes value into 
	//lastValue, and prepares the node for the next pass
	void reset();

	//gets the value of the node.
	float getValue() const;
	//Gets the last value (the value of the last tick) of the node
	float getLastValue() const;
	//Returns the type of the node.
	node_type getType();

};