#pragma once

#include <math.h>

//A header destined to create static functions that can be used in the nodes cumulation
//and activation functions

//Two types of function exsist: cumulation and activation. Cumulaion fuctions take in
//two parameters, the cumulated value, and the next value to cumulate. The activation
//function is simlpy a mathematical function defined as follows : f(x) : R->R. It
//takes a float and outputs another.

//Cumulative functions

//Computes the sum of n and total
float sum(float n, float total) {
	return total + n;
}

//Activation functions
