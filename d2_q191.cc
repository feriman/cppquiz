/*
 * Due to the extern "C" specifications, A::x and B::x actually refer to
 * the same variable.
 *
 * x is first initialized to 0, then main() starts, 0 is printed, x is
 * incremented to 1, and finally 1 is printed.
 *
 * [dcl.link]#6 [1] in the C++ standard:
 * "Two declarations for a variable with C language linkage with the same
 * name (ignoring the namespace names that qualify it) that appear in
 * defferent namespace scopes refer to the same variable."
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.link#6
 */

#include <iostream>

namespace A {
	extern "C" int x;
};

namespace B {
	extern "C" int x;
};

int A::x = 0;

int main() {
	std::cout << B::x;
	A::x = 1;
	std::cout << B::x;
}

