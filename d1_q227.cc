/*
 * using Func = int() is an alias-declaration introducing the typedef-name
 * Func for a function taking no parameters and returning an int.
 *
 * This typedef-name can be used both for free functions and, as in this
 * question, for member functions. [class.mfct]#8 [1] in the C++ standard:
 *
 * [Note: A member function can be declared (but not defined) using a
 * typedef for a function type. The resulting member function has exactly
 * the same type as it would have if the function declarator were provided
 * explicitly.
 *
 * The use of Func f in struct S is therefore equivalent to int f().
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/class.mfct#8
 */

#include <iostream>

using Func = int();

struct S {
	Func f;
};

int S::f() { return 1; }

int main() {
	S s;
	std::cout << s.f();
}

