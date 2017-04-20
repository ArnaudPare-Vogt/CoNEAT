#include "Node.h"
#include "Connection.h"

//Creates a node of the given type.
Node::Node(int nodeId) :
	nodeId(nodeId),
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
	nodeId(other.nodeId),
	value(other.getValue()),
	lastValue(other.getLastValue()),
	incummulation(other.incummulation),
	activated(other.activated),
	activationFunction(other.activationFunction),
	cummulationFunction(other.cummulationFunction){

}

//Destroys this Node
Node::~Node() {
	//The activation and the incummulation functions should point toward 
	//static functions, and should NOT be deleted
}

void Node::freeze() {
	activated = true;
}

//Tries to fire the node
void Node::fire() {
	if (!activated) {
		for (Connection* c : inputs) {
			cummulate((*c).fetchValue());
		}
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

//Attaches c as an input
void Node::attachInput(Connection& c) {
	inputs.push_back(&c);
}

//Detaches c from the input list
void Node::detatchInput(Connection& c) {
	std::vector<Connection*>::iterator it = std::find(inputs.begin(), inputs.end(), &c);
	if (it != inputs.end()) {
		inputs.erase(it);
	}
}

void Node::setValue(float value) {
	this->value = value;
}


//Gets the value of the node.
float Node::getValue() const {
	return value;
}

//Gets the last value (the value of the last tick) of the node
float Node::getLastValue() const {
	return lastValue;
}

//Returns the ID of the current Node
int Node::getId() const {
	return nodeId;
}

//Returns the attached inputs of this node. Useful to navigate the graph
std::vector<Connection*> &Node::getInputs() {
	return inputs;
}
