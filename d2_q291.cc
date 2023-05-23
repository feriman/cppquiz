/*
 * The program is undefined.
 * The standard defines some identifiers as reserved to the implementation.
 *
 * [lex.name]#3 [1]:
 *
 * In addition, some identifiers are reserved for use by C++
 * implementations and shall not be used otherwise; no diagnostic is
 * required.
 *
 * - Each identifier that contains a double underscore __ or begins with an
 * underscore followed by an uppercase letter is reserved to the
 * implementation for any use.
 *
 * - Each identifier that begins with an underscore is reserved to the
 * implementation for use as a name in the global namespace.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/lex.name#3
 */

#include <iostream>

int _global = 1;

int main() {
	std::cout << _global;
}

