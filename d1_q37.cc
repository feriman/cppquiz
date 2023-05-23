/*
 * According to [dcl.type.simple]#4 in the C++ standard:
 * "The type denoted by decltype(e) is defined as follows:
 * -- if e is an unparenthesized id-expression [...], decltype(e) is the
 * type of the entity named by e."
 *
 * The type of a is int, so the type of b is also int.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.type.simple#4
 */

#include <iostream>

int main() {
	int a = 0;
	decltype(a) b = a;
	b++;
	std::cout << a << b;
}

