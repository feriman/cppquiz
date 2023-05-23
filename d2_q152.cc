/*
 * [basic.fundamental]#1 [1]
 * Plain char, signed char, and unsigned char are three distinct types
 * (...).
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/basic.fundamental#1
 */

#include <iostream>
#include <type_traits>

int main() {
	if (std::is_signed<char>::value) {
		std::cout << std::is_same<char, signed char>::value;
	} else {
		std::cout << std::is_same<char, unsigned char>::value;
	}
}

