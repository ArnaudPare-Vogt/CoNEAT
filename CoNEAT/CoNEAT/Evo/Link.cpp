#include "Link.h"

Link::Link() :
	Link(0,0) {}

Link::Link(int in, int out) :
	in(in), out(out), weight(1), activated(true){}
	

Link::Link(const Link& other) :
	in(other.in), out(other.out), weight(other.weight), activated(other.activated) {}


Link::Pair Link::splitThisLink(int middleNodeId) const {
	Link first;
	Link second;

	first.in = in;
	first.out = middleNodeId;

	first.weight = weight;

	second.in = middleNodeId;
	second.out = out;

	return std::make_pair(first, second);
}



std::ostream& operator<<(std::ostream& os, const Link& link) {
	if (link.activated) {
		os << "Gene from N";
	}
	else {
		os << "Unactive  N";
	}

	os << link.in << " to N" << link.out << " and weights " << link.weight << std::endl;
	return os;
}
