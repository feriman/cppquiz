/*
 * First, a global X object is created, printing 1.
 *
 * Then main is called, and we get to the line X(object);. This can be
 * interpreted in two ways:
 * 1. As creating a temporary unnamed copy of object.
 * 2. As creating a new variable of type X named object. This is easier to
 * see if you remove the parentheses, and it becomes just X object.
 *
 * [stmt.ambig]#1 [1] in the C++ standard says:
 *
 * An expression-statement with a function-style explicit type conversion
 * (#8.2.3) as its leftmost subexpression can be indistinguishable from a
 * declaration where the first declarator starts with a (. In those cases
 * the statement is a declaration.
 *
 * So X(object) is in fact a declaration of a new variable object (which
 * shadows the global object). The constructor is called, and 1 is printed
 * again.
 *
 * We then call f(), and 4 is printed.
 *
 * Next, main exits, and the local object is destroyed, printing 2.
 * Finally, the global object is destroyed, again printing 2.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/stmt.ambig#1
 */

#include <iostream>

struct X {
	X() { std::cout << "1"; }
	X(const X&) { std::cout << "3"; }
	~X() { std::cout << "2"; }

	void f() { std::cout << "4"; }
} object;

int main() {
	X(object);
	object.f();
}

