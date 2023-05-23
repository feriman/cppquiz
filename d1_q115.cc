/*
 * According to [lex.fcon]#1 [1] in the standard: "The type of a floating
 * literal is double unless explicitly specified by a suffix."
 * The best overload is therefore void f(double).
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/lex.fcon#1
 */

#include <iostream>

void f(int) { std::cout << "i"; }
void f(double) { std::cout << "d"; }
void f(float) { std::cout << "f"; }

int main() {
	f(1.0);
}

