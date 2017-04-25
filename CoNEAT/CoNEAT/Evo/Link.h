#pragma once
#include <ostream>
#include <utility>

struct Link {
	typedef std::pair<Link, Link> Pair;

	int in;
	int out;
	float weight;
	bool activated;

	Link();
	Link(int in, int out);
	Link(const Link &other);

	//Splits this link in two parts.
	Pair splitThisLink(int middleNodeId) const;

	friend std::ostream& operator<<(std::ostream& os, const Link& ind);
};