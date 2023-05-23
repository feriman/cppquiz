/*
 * [class.temporary]#4 [1] in the standard: "Temporary objects are
 * destroyed as the last step in evaluating the full-expression (...) that
 * (lexically) contains the point where they were created." This means that
 * normally the temporaries returned from C(1), C(2), and C(3) should be
 * destroyed at the end of the line.
 *
 * However: [class.temporary]#6 states: "(...) when a reference is bound to
 * a temporary. The temporary to which the reference is bound (...)
 * persists for the lifetime of the reference", so the lifetime of the
 * temporary returned by C(1) is extended for the lifetime of c, to the end
 * of main(). The temporaries returned by C(2) and C(3) are still destroyed
 * at the end of their lines of creation, so they get destroyed before the
 * one returned by C(1).
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/class.temporary#4
 * [2] https://timsong-cpp.github.io/cppwp/n4659/class.temporary#6
 */

#include <iostream>

class C {
public:
	C(int i) : i(i) { std::cout << i; }
	~C() { std::cout << i + 5; }

private:
	int i;
};

int main() {
	const C &c = C(1);
	C(2);
	C(3);
}

