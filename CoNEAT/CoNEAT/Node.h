#pragma once

#include <vector>

class Node {
	enum class node_type {INPUT, OUTPUT, HIDDEN};
	node_type type;
	float lastValue, value;
	float incummulation;
	float (*activationFunction)(float incumulation);
	float (*cummulationFunction)(float n, float total);
public:
	Node(node_type n_type) :type(n_type) { this->lastValue = 0; this->value = 0; this->incummulation = 0; };
	~Node();
	inline void process() { this->value = this->activationFunction(this->incummulation); };
	inline void cummulate(float n) { this->incummulation = this->cummulationFunction(n, this->incummulation); };
	
	//setters
	void setType(node_type t) {
		this->type = t;
	};
	

};