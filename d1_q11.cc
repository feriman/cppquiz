/*
 * Since a has static storage duration and no initializer, it is
 * guaranteed to be zero-initialized. Had a been defined as a local
 * non-static variable inside main(), this would not have happened.
 *
 * Note: int a has static storage duration bacause it is declared at
 * namespace scope. It does not need to have static in front of it, that
 * would only denote internal linkage.
 */

#include <iostream>

int a;

int main() {
	std::cout << a;
}

