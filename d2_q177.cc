/*
 * This program is unspecified / implementation defined.
 * Although this program probably outputs 8 on your computer, it's not
 * guaranteed to do so by the standard. All we can be sure of is what's
 * specified in [basic.fundamental]#1 [1]:
 *
 * "Objects declared as characters (char) shall be large enough to store
 * any member of the implementation's basic character set. (...) A char,
 * a signed char, and an unsigned char occupy the same amount of storage."
 *
 * So unsigned char is the same size as char, which is large enough to
 * store any member of the implementation's basic character set - but not
 * cecessarily 8.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/basic.fundamental#1
 */

#include <limits>
#include <iostream>

int main() {
	std::cout << std::numeric_limits<unsigned char>::digits;
}

