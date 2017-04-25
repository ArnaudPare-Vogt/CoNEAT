#include <Catch/catch.hpp>
#include <Evo/Link.h>

TEST_CASE("Link constructors", "[Link]") {
	Link l;
	REQUIRE(l.in == 0);
	REQUIRE(l.out == 0);
	REQUIRE(l.weight == 1);
	REQUIRE(l.activated == true);

	l.in = 2;
	l.out = 3;
	l.activated = false;
	l.weight = 0.2f;

	Link l2 = l;

	REQUIRE(l2.in == 2);
	REQUIRE(l2.out == 3);
	REQUIRE(l2.weight == 0.2f);
	REQUIRE(l2.activated == false);

	Link l3(1, 2);
	REQUIRE(l3.in == 1);
	REQUIRE(l3.out == 2);
	REQUIRE(l3.weight == 1);
	REQUIRE(l3.activated == true);
}

TEST_CASE("Link splitting", "[Link]") {
	Link l(2,3);
	l.weight = 10;
	Link::Pair ls = l.splitThisLink(4);

	REQUIRE(ls.first.in == 2);
	REQUIRE(ls.first.out == 4);
	REQUIRE(ls.first.weight == 10);
	REQUIRE(ls.first.activated == true);

	REQUIRE(ls.second.in == 4);
	REQUIRE(ls.second.out == 3);
	REQUIRE(ls.second.weight == 1);
	REQUIRE(ls.second.activated == true);
}