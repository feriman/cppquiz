/*
 * The comma operator is applied on two expressions: a and b.
 *
 * According to [expr.comma]#1 [1] in the standard: "A pair of expressions
 * separated by a comma is evaluated left-to-right; the left expression is
 * a discarded-value expression (...) The type and value of the result are
 * the type and value of the right operand".
 *
 * The right operand here being b, with the value 20. This is then the
 * resulting value of the expression (a, b), and 20 is assigned to x.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.comma#1
 */

#include <iostream>

int main() {
	int a = 10;
	int b = 20;
	int x;
	x = (a, b);
	std::cout << x;
}

