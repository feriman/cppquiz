/*
 * The program is unspecified / implementation defined.
 * The evaluation order of function argument expressions is unspecified,
 * all we know is that they will all happen before ("be sequenced before")
 * the contents of the called function.
 *
 * In particular, in the expression g(f1(), f2()), we don't know wherher f1
 * or f2 will be sequenced first, we only know that they will both be
 * sequenced before the body of g.
 *
 * Also: There isn't even a requirement on the implementation that f1 and
 * f2 gets evaluated in the same order each time. So after calling h twice,
 * v can contain 1212, 2121, 1221 or 2112.
 *
 * [expr.call]#5 [1] in the C++ standard:
 *
 * "The initialization of a parameter, including every associated value
 * computation and side effect, is indeterminately sequenced with respect
 * to that of any other parameter."
 *
 * And the helpful note in [intro.executation]#17 [2]:
 *
 * "In an expression that is evaluated more than once during the execution
 * of a program, unsequenced and indeterminately sequenced evaluations of
 * its subexpressions need not be performed consistently in different
 * evaluations."
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.call#5
 * [2] https://timsong-cpp.github.io/cppwp/n4659/intro.executation#17
 */

#include <vector>
#include <iostream>

std::vector<int> v;

int f1() {
	v.push_back(1);
	return 0;
}

int f2() {
	v.push_back(2);
	return 0;
}

void g(int, int) {}

void h() {
	g(f1(), f2());
}

int main() {
	h();
	h();
	std::cout << (v[0] == v[2]);
}

