/*
 * [expr.sub]#1 [1] in the standard says "The expression E1[E2] is
 * identical (by definition) to *((E1)+(E2))".
 *
 * In our case 1["ABC"] is identical to *(1+"ABC"). Since the plus operator
 * is commutative, this is identical to *("ABC"+1), which is identical to
 * the more familiar "ABC"[1].
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.sub#1
 */

#include <iostream>

int main() {
	std::cout << 1["ABC"];
}

