#include <Catch/catch.hpp>
#include <Neuron.h>
#include <Connection.h>

TEST_CASE("Neuron constructors work", "[Neuron]") {
	Neuron node(0);
	REQUIRE(node.getId() == 0);
	REQUIRE(node.getValue() == 0);
	REQUIRE(node.getLastValue() == 0);

	Neuron input(1);
	Connection connection = Connection(input, node, 1);

	Neuron copiedNode = node;
	REQUIRE(copiedNode.getId() == node.getId());
	REQUIRE(copiedNode.getInputs().size() == 1);
	REQUIRE(copiedNode.getInputs()[0]->getIn()->getId() == input.getId());

	node.setValue(10);
	REQUIRE(copiedNode.getValue() != 10);
}

TEST_CASE("Neuron fireing works", "[Neuron]") {
	Neuron input1(0);
	Neuron input2(1);
	Neuron input3(2);

	Neuron testSubject(3);

	Connection c1 = Connection(input1, testSubject, 0.5f);
	Connection c2 = Connection(input2, testSubject, 1.f);
	Connection c3 = Connection(input3, testSubject, 33.f);

	input1.setValue(10);
	input2.setValue(-10);
	input3.setValue(2);

	testSubject.fire();

	float finalValue = tanh(5 - 10 + 66);

	REQUIRE(testSubject.getValue() == finalValue);

	input1.reset();
	input2.reset();
	input3.reset();
	testSubject.reset();

	input1.setValue(1);
	input2.setValue(-1);
	input3.setValue(0.01);

	testSubject.fire();

	float finalValue2 = tanh(0.5 -1 + 0.33);
	REQUIRE(testSubject.getLastValue() == finalValue);
	REQUIRE(testSubject.getValue() == Approx(finalValue2));

}

TEST_CASE("Simple net recursivity", "[Neuron]") {
	Neuron out = Neuron(0);
	Neuron middle = Neuron(1);
	Neuron in  = Neuron(2);

	Connection c1(middle, out, 1);
	Connection c2(middle, middle, 1);
	c2.setRecursivity(true);
	Connection c3(in, middle, 1);

	in.setValue(0.5f);

	out.fire();//Recursivity bug crashes here

	float outVal = tanh(tanh(0.5));
	REQUIRE(out.getValue() == Approx(outVal));
	
	in.reset();
	middle.reset();
	out.reset();

	in.setValue(-0.1);
	out.fire();
	float outVal2 = tanh(tanh(tanh(0.5f) + -0.1));
	REQUIRE(out.getValue() == Approx(outVal2));
}

TEST_CASE("Method Neuron::freeze()", "[Neuron]") {
	Neuron n1(0);
	Neuron n2(1);

	Connection c(n1, n2, 1);

	n1.setValue(10);
	n2.freeze();

	n2.fire();

	REQUIRE(n2.getValue() == 0);

}

TEST_CASE("", "") {

}