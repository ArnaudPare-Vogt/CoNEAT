#include "Node.h"
#include "Connection.h"

//Creates a node of the given type.
Node::Node(int nodeId) :
	nodeId_(nodeId),
	lastValue_(0),
	value_(0),
	activated_(false){

	activationFunction_ = &tanh;
	cummulationFunction_ = &sum;
}

//The copy constructor of the node.
//This should match the Node(node_type) constructor
Node::Node(const Node& other) :
	nodeId_(other.nodeId_),
	value_(other.getValue()),
	lastValue_(other.getLastValue()),
	activated_(other.activated_),
	activationFunction_(other.activationFunction_),
	cummulationFunction_(other.cummulationFunction_),
	inputs_(other.inputs_){

}

//Destroys this Node
Node::~Node() {
	//The activation and the incummulation functions should point toward 
	//static functions, and should NOT be deleted
}

void Node::freeze() {
	activated_ = true;
}

//Tries to fire the node
void Node::fire() {
	if (!activated_) {
		float incumulation = 0;
		for (Connection* c : inputs_) {
			incumulation = cummulate((*c).fetchValue(), incumulation);
		}
		this->process(incumulation);
		activated_ = true;
	}
}

//Resets the node. This has two impacts : flushes value into 
//lastValue, and prepares the node for the next pass
void Node::reset() {
	lastValue_ = value_;
	activated_ = false;
}

//Attaches c as an input
void Node::attachInput(Connection& c) {
	inputs_.push_back(&c);
}

//Detaches c from the input list
void Node::detatchInput(Connection& c) {
	std::vector<Connection*>::iterator it = std::find(inputs_.begin(), inputs_.end(), &c);
	if (it != inputs_.end()) {
		inputs_.erase(it);
	}
}

void Node::setValue(float value) {
	this->value_ = value;
	this->freeze();//Don't auto-delete our value upon processing!
}


//Gets the value of the node.
float Node::getValue() const {
	return value_;
}

//Gets the last value (the value of the last tick) of the node
float Node::getLastValue() const {
	return lastValue_;
}

//Returns the ID of the current Node
int Node::getId() const {
	return nodeId_;
}

//Returns the attached inputs of this node. Useful to navigate the graph
std::vector<Connection*> &Node::getInputs() {
	return inputs_;
}










void Node::process(float incummulation) 
{
	this->value_ = this->activationFunction_(incummulation);
}


float Node::cummulate(float n, float incummulation) 
{
	return this->cummulationFunction_(n, incummulation);
};