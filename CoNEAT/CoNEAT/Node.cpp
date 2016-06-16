#include "Node.h"


//Creates a node of the given type.
Node::Node(node_type type) :
	type(type),
	lastValue(0),
	value(0),
	incummulation(0),
	activated(false){

	activationFunction = &tanh;
	cummulationFunction = &sum;
}

//The copy constructor of the node.
//This should match the Node(node_type) constructor
Node::Node(const Node& other) :
	type(other.type),
	value(other.getValue()),
	lastValue(other.getLastValue()),
	incummulation(other.incummulation),
	activated(other.activated){

}

//Destroys this Node
Node::~Node() {
	//The activation and the incummulation functions should point toward 
	//static functions, and should NOT be deleted
}

//Tries to fire the node
void Node::fire() {
	if (!activated) {
		this->process();
		activated = true;
	}
}

//Resets the node. This has two impacts : flushes value into 
//lastValue, and prepares the node for the next pass
void Node::reset() {
	incummulation = 0;
	lastValue = value;
	activated = false;
}

//Gets the value of the node.
float Node::getValue() const {
	return value;
}

//Gets the last value (the value of the last tick) of the node
float Node::getLastValue() const {
	return lastValue;
}

//Returns the type of the node.
Node::node_type Node::getType() {
	return this->type;
}

