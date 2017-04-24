#include <Catch/catch.hpp>
#include <Connection.h>
#include <Neuron.h>

TEST_CASE("Connection constructor", "[Connection]")
{
	Neuron n1(0);
	Neuron n2(1);

	Connection c = Connection(n1, n2, 1.12f);
	REQUIRE(c.getIn() == &n1);
	REQUIRE(c.getOut() == &n2);
	REQUIRE(c.getWt() == Approx(1.12f));

	Connection c2 = Connection(c);
	REQUIRE(c2.getIn() == &n1);
	REQUIRE(c2.getOut() == &n2);
	REQUIRE(c2.getWt() == Approx(1.12f));
	
	Neuron n3(2);
	c.setIn(n3);
	REQUIRE(c2.getIn() == &n1);
}

TEST_CASE("Connection::fetchValue()", "[Connection]")
{
	Neuron n1(0);
	Neuron n2(1);
	n1.setValue(10);

	Connection* c1 = n2.createConnectionFrom(n1, 3.f);

	REQUIRE(c1->fetchValue() == Approx(30));

	n1.reset();
	n2.reset();

	Neuron n3(2);

	Connection* c2 = n3.createConnectionFrom(n2, 0.33f);
	
	n1.setValue(5);

	float expectedOut = 0.33f * tanh(15);
	REQUIRE(c2->fetchValue() == Approx(expectedOut));

	n1.reset();
	n2.reset();
	n3.reset();

	n1.setValue(10);
	c1->setRecursivity(true);

	REQUIRE(c2->fetchValue() == Approx(expectedOut));

}

TEST_CASE("Destructor order stuff", "[Connection]")
{
	Neuron* n1 = new Neuron(0);
	Neuron* n2 = new Neuron(1);

	Connection* c = n2->createConnectionFrom(*n1, 1);

	delete n1;
	delete n2;

	n1 = new Neuron(0);
	n2 = new Neuron(1);
	c = n2->createConnectionFrom(*n1, 1);

	delete n2;
	delete n1;

	n1 = new Neuron(0);
	n2 = new Neuron(1);
	c = n2->createConnectionFrom(*n1, 1);
	{ Neuron n(*n2); }

	REQUIRE(c->getOut() != nullptr);

	delete n1;
	delete n2;
}