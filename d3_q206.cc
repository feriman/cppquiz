/*
 * We have several pieces of the puzzle, so let's peel away the layers.
 *
 * The grammar for sizeof is in [expr.unary]#1 [1]:
 *
 * unary-expression:
 * ...
 * sizeof unary-expression
 * sizeof ( type-id )
 * sizeof ... ( identifier )
 * ...
 *
 * We have three cases and the one that applies here si sizeof
 * unary-expression. The unary expression is (0)["abcdefghij"], which looks
 * odd but is just array indexing of string literal which is a const char
 * array.
 *
 * We can see that (0)["abcdefghij"] is identical to ("abcdefghij")[0] from
 * [expr.sub]#1 [2] which says:
 *
 * ... The expression E1[E2] is identical (by definition) to * ((E1)+(E2))
 * ...
 *
 * So we end up with 0th element of "abcdefghij", which is a, which is a
 * char. And theresult of sizeof('a') will be 1 since [expr.sizeof]#1 [3]
 * says:
 *
 * ... sizeof(char), sizeof(signed char) and sizeof(unsigned char) are 1
 * ...
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.unary#1
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr.sub#1
 * [3] https://timsong-cpp.github.io/cppwp/n4659/expr.sizeof#1
 */

#include <iostream>

int main() {
	int n = sizeof(0)["abcdefghij"];
	std::cout << n;
}

