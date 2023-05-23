/*
 * The program is unspecified / implementation defined.
 * The type of the sum of two chars is actually not uniquely specified. We
 * do however know it's not char.
 *
 * Before being passed to operator+, the operands (x and y) go through a
 * conversion.
 * [expr.add]#1 [1]:
 *
 * The additive operators + and - group left-to-right. The usual arithmetic
 * conversions are performed for operands of arithmetic or enumeration
 * type.
 *
 * What are "the usual arithmetic conversions"?
 *
 * [expr]#11 [2]:
 *
 * Many binary operators that expect operands of arithmetic or enumeration
 * type cause conversions and yield result types in a similar way. The
 * purpose is to yield a common type, which is also the type of the result.
 * This pattern is called the usual arithmetic conversions, which are
 * defined as follows:
 * - [a bunch of rules for floats, enums etc.]
 * - Otherwise, the integral promotions (7.6) shall be performed on both
 * operands
 *
 * So both chars go through integral promotions. Those are defined in
 * [conv.prom]#1 [3]:
 *
 * A prvalue of an integer type other than bool, char16_t, char32_t, or
 * wchar_t whose integer conversion rank (7.15) is less than the rank of
 * int can be converted to a prvalue of type int if int can represent all
 * the values of the source type; otherwise, the source prvalue can be
 * converted to a prvalue of type unsigned int.
 *
 * So a char gets converted to an int if int can fit all possible values of
 * a char. But that's not necessarily the case!
 *
 * First, int could actually be the same as char. [basic.fundamental]#2
 * [4]:
 *
 * There are five standard signed integer types: "signed char",
 * "short int", "int", "long int", and "long long int". In this list, each
 * type provides at least as much storage as those preceding the list.
 *
 * Note that it says "at least as much storage", it doesn't have to be
 * more. So for instance you could have an sixteen bit system where both
 * char and int are sixteen bits.
 *
 * Second, char can be either signed or unsigned, it's up to the
 * implementation [basic.fundamental]#1 [5]:
 *
 * It is implementation-defined whether a char object can hold negative
 * values.
 *
 * int is signed, so if char is also signed, all possible values of char
 * will fit in an int. However, if char is unsigned, and int and char is
 * the same size, char can actually hold larger values than int! In the
 * former case, chars get promoted to unsigned int before being summed.
 *
 * So in practice, most systems will call f(int) and print i, but some
 * might call f(unsigned int) and print u, and they would both be
 * confirming to the standard.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.add#1
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr#11
 * [3] https://timsong-cpp.github.io/cppwp/n4659/conv.prom#1
 * [4] https://timsong-cpp.github.io/cppwp/n4659/basic.fundamental#2
 * [5] https://timsong-cpp.github.io/cppwp/n4659/basic.fundamental#1
 */

#include <iostream>

void f(unsigned int) { std::cout << "u"; }
void f(int) { std::cout << "i"; }
void f(char) { std::cout << "c"; }

int main() {
	char x = 1;
	char y = 2;
	f(x + y);
}

