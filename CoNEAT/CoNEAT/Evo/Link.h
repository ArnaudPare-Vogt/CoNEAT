#pragma once
#include <ostream>
#include <utility>

struct Link {
	typedef std::pair<Link, Link> Pair;

	int in;
	int out;
	float weight;
	bool activated;
	unsigned historical_innovation_number;

	Link();
	Link(int in, int out, unsigned historical_innovation_number);
	Link(const Link &other) = default;

	//Splits this link in two parts.
	Pair splitThisLink(int middleNodeId) const;

	friend std::ostream& operator<<(std::ostream& os, const Link& ind);
};