/*
 * Is foo called both times or just once? The C++ standard says this in
 * [dcl.fct.default]#9 [1]: "A default argument is evaluated each time the
 * the function is called with no argument for the corresponding
 * parameter."
 *
 * Thus, foo is called twice.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.fct.default#9
 */

#include <iostream>

using namespace std;

int foo() {
	cout << 1;
	return 1;
}

void bar(int i = foo()) {}

int main() {
	bar();
	bar();
}

