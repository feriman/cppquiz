/*
 * This program has no ouput.
 *
 * X x(); is a funtion prototype, not a variable definition. Remove the
 * parentheses (or since C++11, replace them with {}), and the program will
 * ouput X.
 */

#include <iostream>

struct X {
	X() { std::cout << "X"; }
};

int main() { X x(); }

