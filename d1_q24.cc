/*
 * Unsigned integers have well defined behaviour when they overflow. When
 * you go one above the largest representable unsigned int, you end up back
 * to zero.
 *
 * According to [basic.fundamental]#4 [1] in the C++ standard: "Unsigned
 * integers, declared unsigned, shall obey the laws of arithmetic modulo
 * 2^n where n is the number of bits in the value representation of that
 * particular size of integer."
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/basic.fundamental#4
 */

#include <iostream>
#include <limits>

int main() {
	unsigned int i = std::numeric_limits<unsigned int>::max();
	std::cout << ++i;
}

