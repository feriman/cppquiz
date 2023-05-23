/*
 * In summary: z and y are both converted to another type before being
 * multiplied. On most systems (64 bit Windows/Linux/MacOS for instance),
 * that type is int, which is commonly 32 bits signed. 0xFFFF * 0xFFFF
 * can't fit in a signed 32 bit type, and we get signed integer overflow,
 * which is undefined behaviour.
 *
 * Details:
 *
 * Before being passed to operator *, the operands (x and y) go through a
 * conversion.
 *
 * [expr.mul]#2 [1]:
 *
 * (...) The usual arithmetic conversions are performed on the operands and
 * determine the type of the result.
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
 * - [a bunch of rules for floats, enums etc]
 * - Otherwise, the integral promotions (7.6) shall be performed on both
 * operands
 *
 * So both unsigned shorts go through integral promotions. Those are
 * defined in [conv.prom]#1 [3]:
 *
 * A prvalue of an integer type other than bool, char16_t, char32_t, or
 * wchar_t whose integer conversion rank (7.15) is less than the rank of
 * int can be converted to a prvalue of type int if int can represent all
 * the values of the source type; otherwise, the source prvalue can be
 * converted to a prvalue of type unsigned int.
 *
 * And the rank of unsigned short is indeed less than the rank of int.
 * [conv.rank] [4]:
 *
 * The rank of (...) int (...) shall be greater than the rank of short int
 * (...) [and] The rank of any unsigned integer type shall equal the rank
 * of the corresponding signed integer type.
 *
 * So the unsigned short will be converted to int if int can represent all
 * the values of unsigned short, or unsigned int otherwise.
 *
 * On most systems, an int can represent all the values of unsigned short
 * (typically int is 32 bits signed, and unsigned short is 16 bits
 * unsigned). So x and y are both promoted to int before being multiplied.
 * The maximum int value on these systems is 2147483647, but 0xFFFF *
 * 0xFFFF = 4294836225. So we get signed integer overflow, which is
 * undefined behaviour.
 *
 * Note:
 *
 * One could imagine systems where this wouldn't cause undefined behaviour.
 * - If you have 64 bit ints, you don't get overflow.
 * - If short and int both are 32 bits, all values of unsigned short can't
 *   fit in an int, and they promote to unsigned int instead, for which
 *   overflow isn't undefined behaviour.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.mul#2
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr#11
 * [3] https://timsong-cpp.github.io/cppwp/n4659/conv.prom#1
 * [4] https://timsong-cpp.github.io/cppwp/n4659/conv.rank
 */

#include <iostream>

int main() {
	unsigned short x = 0xFFFF;
	unsigned short y = 0xFFFF;
	auto z = x * y;
	std::cout << (z > 0);
}

