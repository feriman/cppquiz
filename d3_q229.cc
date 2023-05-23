/*
 * It is clear that a is not captured explicitly, so the question is
 * whether a should be captured implicitly (and if yes, then a default
 * capture has to be specified). [expr.prim.lambda.capture]#7 [1] says:
 *
 * A lambda-expression with an associated capture-default that does not
 * explicitly capture *this or a variable with automatic storage duration
 * [...], is said to implicitly capture the entity (i.e., *this or a
 * variable) if the compound-statement:
 * 
 * - odr-uses the entity (int the case of a variable)
 * - [...]
 *
 * The use of a constitutes an odr-use. But since a has static storage
 * duration rather than automatic storage duration, it is not implicitly
 * captured.
 *
 * Since a is neither explicitly nor implicitly captured, a in the lambda
 * expression simply refers to the global variable a.
 *
 * (Note: It is also disallowed to capture a explicitly, because of
 * [expr.prim.lambda.capture]#4 [2]):
 *
 * The identifier in a simple-capture is looked up using the usual rules
 * for unqualified name lookup; each such lookup shall find an entity. An
 * entity that is designated by a simple-capture is said to be explicitly
 * captured, and shall be *this (when the simple-capture is "this" or
 * "*this") or a variable with automatic storage duration declared in the
 * reaching scope of the local lambda expression.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.prim.lambda.capture#7
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr.prim.lambda.capture#4
 */

#include <iostream>

int a = 1;

int main() {
	auto f = [](int b) { return a + b; };

	std::cout << f(4);
}

