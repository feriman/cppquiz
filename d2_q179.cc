/*
 * The program is undefined.
 * Modifying a const object results in undefined behaviour. Casting away
 * constness does not help.
 *
 * [dcl.type.cv]#4 [1] in the standard:
 *
 * Any attempt to modify a const object during its lifetime (3.8) results
 * in undefined behaviour.
 *
 * But we're modifying r, not i, so [expr.const.cast]#4 [2] is also
 * relevant:
 *
 * The result of a reference const_cast refers to the original object.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.type.cv#4
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr.const.cast#4
 */

#include <iostream>

int main() {
	const int i = 0;
	int& r = const_cast<int&>(i);
	r = 1;
	std::cout << r;
}


