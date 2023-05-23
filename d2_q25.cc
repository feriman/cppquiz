/*
 * The program is undefined.
 * Signed integer overflow is undefined behaviour according to the standard
 * [expr]#4 [1]: "If during the evaluation of an expression, the result is
 * not mathematically defined or not in the range of representable values
 * for its type, the behaviour is undefined."
 *
 * Most implementations will just wrap around, so if you try it out on your
 * machine, you will probably see the same as if you had done
 * std::cout << std::numeric_limits<int>::min();
 *
 * Relying on such undefined behaviour is however not safe. For an
 * interesting example, see [2].
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr#4
 * [2] http://stackoverflow.com/questions/7682477/why-does-integer-
 * overflow-on-x86-with-gcc-cause-an-infinite-loop
 */

#include <iostream>
#include <limits>

int main() {
	int i = std::numeric_limits<int>::max();
	std::cout << ++i;
}

