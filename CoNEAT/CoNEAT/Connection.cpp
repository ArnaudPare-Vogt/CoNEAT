#include "Connection.h"

Connection::Connection(Node &_in, Node &_out, float _wt) :
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


Node* Connection::getIn() {
	return in;
}

Node* Connection::getOut() {
	return out;
}

float Connection::getWt() {
	return wt;
}

bool Connection::isRecursive() {
	return recursive;
}


void Connection::setIn(Node &n) {
	in = &n;
}
void Connection::setOut(Node &n) {
	out = &n;
}
void Connection::setWt(float w) {
	wt = w;
}
void Connection::setRecursivity(bool r) {
	recursive = r;
}

