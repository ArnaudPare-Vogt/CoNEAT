#include "Connection.h"

Connection::Connection(Neuron &_in, Neuron &_out, float _wt) :
in(&_in), out(&_out), wt(_wt), recursive(false) {
	_out.attachInput(*this);
}

Connection::Connection(const Connection &other) :
	in(other.in), out(other.out), wt(other.wt), recursive(other.recursive) {
	out->attachInput(*this);
}

Connection::~Connection() {
	out->detatchInput(*this);
}


float Connection::fetchValue() {
	if (recursive) {
		return (*in).getLastValue();
	}
	else {
		(*in).fire();
		return (*in).getValue() * wt;
	}
}


Neuron* Connection::getIn() {
	return in;
}

Neuron* Connection::getOut() {
	return out;
}

float Connection::getWt() {
	return wt;
}

bool Connection::isRecursive() {
	return recursive;
}


void Connection::setIn(Neuron &n) {
	in = &n;
}
void Connection::setOut(Neuron &n) {
	out = &n;
}
void Connection::setWt(float w) {
	wt = w;
}
void Connection::setRecursivity(bool r) {
	recursive = r;
}

