/*
 * The goal of this question is to demonstrate that the evaluation order of
 * elements in an initializer list is specified (as opposed to the
 * arguments to a function call).
 *
 * [dcl.init.list]#4 [1]: Within the initializer-list of a
 * braced-init-list, the initializer-clauses, including any that result
 * from pack expansions, are evaluated in the order in which they appear.
 *
 * If h took two ints instead of a vector<int>, and was called like this:
 * h(f(), g());
 * the program would be unspecified, and could either pring fg or gf.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.init.list#4
 */

#include <iostream>
#include <vector>

int f() { std::cout << "f"; return 0; }
int g() { std::cout << "g"; return 0; }

void h(std::vector<int> v) {}

int main() {
	h({f(), g()});
}

