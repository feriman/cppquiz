/*
 * '0' is a character literal, with type char. (The value of '0' is
 * actually implementation defined, but will typically be 48.) This value
 * is then promoted to an int, and stored in a.
 *
 * We then take a reference b to a. But b is a char reference, not an int
 * reference, which means they are not reference related. [dcl.init.ref]#4
 * [1]:
 *
 * Given types "cv1 T1" and "cv2 T2", "cv1 T1" is reference-related to "cv2
 * T2" if T1 is the same type as T2, or T1 is a base class of T2.
 *
 * "cv1 T1" here being char const, and "cv2 T2" being int, so they're not
 * related. Since they're not, [dcl.init.ref]#5.2.2.2 [2] applies:
 *
 * Otherwise, the initializer expression is implicitly converted to a
 * prvalue of type "cv1 T1". The temporary materialization conversion is
 * applied and the reference is bound to the result.
 *
 * So the initializer expression a is converted to a temporary char const,
 * which b refers to.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.init.ref#4
 * [2] https://timsong-cpp.github.io/cppwp/n4659/dcl.init.ref#5.2.2.2
 */

#include <iostream>

using namespace std;

int main() {
	int a = '0';
	char const &b = a;
	cout << b;
	a++;
	cout << b;
}

