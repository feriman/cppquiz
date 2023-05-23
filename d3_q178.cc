/*
 * Some might expect the lexer to parse the series of characters a+++++b as
 * follows:
 *
 * a++ + ++b
 *
 * but according to the maximal munch principle [1], the lexer will take
 * the longest sequence of characters to produce the next token (with a few
 * exceptions).
 *
 * [lex.pptoken]#3 [2] in the C++ standard:
 * "the next preprocessing token is the longest sequence of characters that
 * could constitute a preprocessing token, even if that would cause further
 * lexical analysis to fail (...)."
 *
 * So after parsing a++, it is not allowed to just parse +, is has to parse
 * ++. The sequence is thus parsed as:
 *
 * a ++ ++ + b
 *
 * which is ill-formed since post-increment requires a modifiable lvalue
 * but the first post-increment will produce a prvalue, as per
 * [expr.post.incr]#1 [2] in the C++ standard: "The value of a postfix ++
 * expression is the value of its operand. (...) The result is a prvalue."
 *
 * [1] https://en.wikipedia.org/wiki/Maximal_munch
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr.post.incr#1
 */

#include <iostream>

int main() {
	int a = 5, b = 2;
	std::cout << a+++++b;
}

