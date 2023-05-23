/*
 * The question here is whether a is a reference to i or not. If it is,
 * the value of a changes when we do i = 2. If not, a is not modified by
 * that line.
 *
 * The type and value category of the conditional expression depends on the
 * types and value categories of the second and third expressions, in this
 * case i and 1. For instance, if both were lvalue ints, the result would
 * be an lvalue int. In this case however, i is an lvalue, and 1 is a
 * prvalue, so things are a bit more complicated.
 *
 * [expr.cond] [1] in the standard has the details. After ruling out a
 * bunch of options in #2-#5 (none of them are void, none of them are of
 * class type, they don't have the same value category, they aren't both a
 * glvalue) [expr.cond]#6 [2] says: "Otherwise, the result is a prvalue".
 *
 * So the expression i > 0 ? i : 1; is a prvalue, in other words a
 * temporary. The reference a is bound to that temporary, not to i itself,
 * and i = 2 ends up not modifying a. After i = 2, i is now 2, but a is
 * still 1, and the output of the program is 21.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.cond
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr.cond#6
 */

#include <iostream>

int main() {
	int i = 1;
	int const& a = i > 0 ? i : 1;
	i = 2;
	std::cout << i << a;
}

