/*
 * Integer division by zero is undefined behaviour. According to
 * [expr.mul]#4 [1] in the standard: "If the second operand of / or % is
 * zero the behaviour is undefined."
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.mul#4
 */

#include <iostream>

int main() {
	int i = 42;
	int j = 1;
	std::cout << i / --j;
}

