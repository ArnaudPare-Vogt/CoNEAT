#include "Node.h"


//Creates a node of the given type.
Node::Node(node_type type) :
	type(type),
	lastValue(0),
	value(0),
	incummulation(0) {

}

//The copy constructor of the node.
//This should match the Node(node_type) constructor
Node::Node(const Node& other) :
	type(other.type),
	value(other.getValue()),
	lastValue(other.getLastValue()),
	incummulation(other.incummulation) {

}


