/*
 * c is an lvalue char. &c returns a pointer to the value c, but that
 * pointer itself is an rvalue, since it's just a nameless temporary
 * returned from operator&.
 *
 * The first overload of f takes an rvalue reference to char*, the second
 * takes an lvalue reference to char*. Since the pointer is an rvalue, the
 * first overload is selected, and 1 is printed.
 */

#include <iostream>

void f(char*&&) { std::cout << 1; }
void f(char*&) { std::cout << 2; }

int main() {
	char c = 'a';
	f(&c);
}

