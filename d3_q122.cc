/*
 * [dcl.spec]#3 [1] in the C++ standard states, "If a type-name is
 * encountered while parsing a decl-specifier-seq, it is interpreted as
 * part of the decl-specifier-seq."
 *
 * [dcl.spec]#4 [2] also has a note: "Since signed, unsigned, long, and
 * short by default imply int, a type-name appearing after one of those
 * specifiers is treated as the name being (re)declared."
 *
 * In void foo(unsigned ll), since unsigned implies int, ll is being
 * redeclared as a parameter name.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.spec#3
 * [2] https://timsong-cpp.github.io/cppwp/n4659/dcl.spec#4
 */

#include <iostream>

typedef long long ll;

void foo(unsigned ll) {
	std::cout << "1";
}

void foo(unsigned long long) {
	std::cout << "2";
}

int main() {
	foo(2ull);
}

