/*
 * [basic.fundamental]#1 [1]
 *
 * It is implementation-defined whether a char object can hold negative
 * values.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/basic.fundamental#1
 */

#include <iostream>
#include <type_traits>

int main() {
	std::cout << std::is_signed<char>::value;
}

