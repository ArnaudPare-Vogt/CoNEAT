#pragma once

#include <vector>

class Node {
public:
	enum class node_type { INPUT, OUTPUT, HIDDEN };
private:
	node_type type;
	float lastValue, value;
	float incummulation;
	float (*activationFunction)(float incumulation);
	float (*cummulationFunction)(float n, float total);
public:
	//Creates a node of the given type.
	Node(node_type n_type);
	//The copy constructor of the node.
	Node(const Node& other);
	~Node();
	inline void process() { this->value = this->activationFunction(this->incummulation); };
	inline void cummulate(float n) { this->incummulation = this->cummulationFunction(n, this->incummulation); };
	
	//setters
	void setType(node_type t) {
		this->type = t;
	};
	
	//gets the value of the node. If the node is not fired yet, it tries to do so.
	float getValue() const;
	//Gets the last value (the value of the last tick) of the node
	float getLastValue() const;
	//Returns the type of the node.
	node_type getType();

};