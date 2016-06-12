#pragma once

#include "Node.h"
	


class Connection {
	typedef unsigned int uint;
	Node *in, *out;
	float wt;
	bool recursive;
	const uint HEV;//historical evolution index
	static uint HEV_COUNTER;//historical evolution index counter


public:
	Connection(Node &_in, Node &_out, int _wt, uint _HEV = HEV_COUNTER++) : in(&_in), out(&_out), wt(_wt), HEV(_HEV), recursive(false) {};
	~Connection();

	//getters
	Node* getIn();
	Node* getOut();
	float getWT();
	bool isRecursive();

	//setters
	void setIn(Node &n);
	void setOut(Node &n);
	void setWt(float w);
	void setRecursivity(bool r);


};
