#pragma once

#include "Node.h"
	

class Connection {
	Node *in;//input node of connection
	Node *out;//output node of connection
	float wt;//weight of the connection 
	bool recursive;//is the connection recursive?


public:
	//Creates a connection with the two input and output nodes, and the weight
	Connection(Node &_in, Node &_out, float _wt);
	//Creates a new Connection by performing a Deep-Copy
	Connection(const Connection& toDupe);
	~Connection();

	//getters
	Node* getIn();
	Node* getOut();
	float getWt();
	bool isRecursive();

	//setters
	void setIn(Node &n);
	void setOut(Node &n);
	void setWt(float w);
	void setRecursivity(bool r);


};
