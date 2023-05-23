/*
 * Starting from the right, "" is a string literal, which gets converted to
 * a pointer, which gets converted to a bool with the value true. This then
 * gets passed to two operator!s, which flip it to false and back to true
 * again.
 * Finally, operator+ converts the bool true to the int 1, which gets
 * printed.
 *
 * Detailed explanation:
 *
 * Starting from the right:
 * "" is a string literal. [lex.string]#8:
 * 
 * A narrow string literal has type "array of n const char"
 *
 * Then comes operator!. We have an array of n const char, but this
 * operator only exists for bool: [over.built]#24 [2]:
 *
 * There also exist candidate operator functions of the form
 * bool operator!(bool);
 *
 * But, we can implicitly convert the operand of operator!! [conv]#2 [3]:
 *
 * expressions with a given type will be implicitly converted to other
 * types in several contexts:
 * - When used as operands of operators
 *
 * In this case we need a standard conversion sequence.
 *
 * [conv]#1 [4]:
 *
 * A standard conversion sequence is a sequence of standard conversions in
 * the following order:
 * (1.1) -- Zero or one conversion from the following set: lvalue-to-rvalue
 * conversion, array-to-pointer conversion, and function-to-pointer
 * conversion.
 * (1.2) -- Zero of one conversion from the following set: integral-point
 * conversions, floating-integral conversions, pointer conversions, pointer
 * to member conversions, and boolean conversions.
 * -- [...]
 *
 * So we can first use an array-to-pointer conversion (1.1) to get from
 * "array of n const char" to a pointer. We can then use a boolean
 * conversion (1.2) to get from pointer to bool.
 *
 * First, the array-to-pointer conversion, [conv.array]#1 [5]:
 *
 * An lvalue or rvalue of type "array of N T" [...] can be converted to a
 * prvalue of type "pointer to T". The result is a pointer to the first
 * element of the array.
 *
 * So we now have a pointer to the first element (the terminating ").
 *
 * And then the boolean conversion [conv.bool]#1 [6]:
 *
 * A prvalue of arithmetic, unscoped enumeration, pointer, or pointer to
 * member type can be converted to a prvalue of type bool. A zero value,
 * null pointer value, or null member pointer value is converted to false;
 * any other value is converted to true.
 *
 * Since our pointer is not a null pointer, its value converts to true.
 *
 * Negating this twice with two operator!s is trivial, we end up back at
 * true.
 *
 * Finally, true is passed to operator+. This operator only exists for
 * promoted arithmetic types (which bool is not): [over.built]#10 [7]:
 *
 * For every promoted arithmetic type T, there exist candidate operator
 * functions of the form
 * T operator+(T);
 *
 * So we need to promote the bool true. [conv.prom]#6 [8]:
 *
 * A prvalue of type bool can be converted to a prvalue of type int, with
 * false becoming zero and true becoming one.
 *
 * So the bool true becomes the int 1, which is printed.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/lex.string#8
 * [2] https://timsong-cpp.github.io/cppwp/n4659/over.built#24
 * [3] https://timsong-cpp.github.io/cppwp/n4659/conv#2
 * [4] https://timsong-cpp.github.io/cppwp/n4659/conv#1
 * [5] https://timsong-cpp.github.io/cppwp/n4659/conv.array#1
 * [6] https://timsong-cpp.github.io/cppwp/n4659/conv.bool#1
 * [7] https://timsong-cpp.github.io/cppwp/n4659/over.built#10
 * [8] https://timsong-cpp.github.io/cppwp/n4659/conv.prom#6
 */

#include <iostream>

int main() {
	std::cout << +!!"";
}

