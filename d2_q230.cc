/*
 * int var1 : 3; declares a bit-field, and you can not apply operator& to a
 * bit-field. [class.bit]#3 [1] in the C++ standard:
 *
 * The address-of operator & shall not be applied to a bit-field, so there
 * are no pointers to bit-fields.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/class.bit#3
 */

#include <iostream>

struct X {
	int var1 : 3;
	int var2;
};

int main() {
	X x;
	std::cout << (&x.var1 < &x.var2);
}

