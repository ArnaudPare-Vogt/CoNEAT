#include "Neuron.h"
#include "Connection.h"

//Creates a node of the given type.
Neuron::Neuron(int nodeId) :
	nodeId_(nodeId),
	lastValue_(0),
	value_(0),
	activated_(false){

	activationFunction_ = &tanh;
	cummulationFunction_ = &sum;
}

//The copy constructor of the node.
//This should match the Node(node_type) constructor
Neuron::Neuron(const Neuron& other) :
	nodeId_(other.nodeId_),
	value_(other.getValue()),
	lastValue_(other.getLastValue()),
	activated_(other.activated_),
	activationFunction_(other.activationFunction_),
	cummulationFunction_(other.cummulationFunction_),
	inputs_(){

	for (Connection* ptr : other.inputs_) {
		createConnectionFrom(*(ptr->getIn()), ptr->getWt());
	}
}

//Destroys this Node
Neuron::~Neuron() {
	//The activation and the incummulation functions should point toward 
	//static functions, and should NOT be deleted
	for (Connection* ptr : inputs_) {
		delete ptr;
	}
}

void Neuron::freeze() {
	activated_ = true;
}

//Tries to fire the node
void Neuron::fire() {
	if (!activated_) {
		float incumulation = 0;
		for (Connection* c : inputs_) {
			incumulation = cummulate(c->fetchValue(), incumulation);
		}
		this->process(incumulation);
		activated_ = true;
	}
}

//Resets the node. This has two impacts : flushes value into 
//lastValue, and prepares the node for the next pass
void Neuron::reset() {
	lastValue_ = value_;
	activated_ = false;
}

//Attaches c as an input
//void Neuron::attachInput(Connection& c) {
//	inputs_.push_back(&c);
//}

//Detaches c from the input list
void Neuron::detatchInput(Connection* c) {
	std::vector<Connection*>::iterator it = std::find(inputs_.begin(), inputs_.end(), c);
	if (it != inputs_.end()) {
		delete *it;
		inputs_.erase(it);
	}
}

//creates a connection from in to this neuron
Connection* Neuron::createConnectionFrom(Neuron& input, float weight) {
	inputs_.push_back(new Connection(input, *this, weight));
	return inputs_.back();
}

void Neuron::setValue(float value) {
	this->value_ = value;
	this->freeze();//Don't auto-delete our value upon processing!
}


//Gets the value of the node.
float Neuron::getValue() const {
	return value_;
}

//Gets the last value (the value of the last tick) of the node
float Neuron::getLastValue() const {
	return lastValue_;
}

//Returns the ID of the current Node
int Neuron::getId() const {
	return nodeId_;
}

//Returns the attached inputs of this node. Useful to navigate the graph
std::vector<Connection*> &Neuron::getInputs() {
	return inputs_;
}










void Neuron::process(float incummulation)
{
	this->value_ = this->activationFunction_(incummulation);
}


float Neuron::cummulate(float n, float incummulation)
{
	return this->cummulationFunction_(n, incummulation);
};