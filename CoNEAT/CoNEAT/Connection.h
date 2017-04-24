#pragma once

#include "Neuron.h"
	

class Connection {
	Neuron *in;//input node of connection
	Neuron *out;//output node of connection
	float wt;//weight of the connection 
	bool recursive;//is the connection recursive?


public:
	//Creates a connection with the two input and output nodes, and the weight
	Connection(Neuron &_in, Neuron &_out, float _wt);
	//Creates a new Connection by performing a Deep-Copy
	Connection(const Connection& toDupe);
	~Connection();

	float fetchValue();

	//getters
	Neuron* getIn();
	Neuron* getOut();
	float getWt();
	bool isRecursive();

	//setters
	void setIn(Neuron &n);
	void setOut(Neuron &n);
	void setWt(float w);
	void setRecursivity(bool r);


};
