/*
 * In the first line of main, we create a new B object, with an A pointer a
 * pointing to it.
 *
 * On the next line, we call b->foo(), where b has the static type A, and
 * the dynamic type B. Since foo() is virtual, the dynamic type of b is
 * used to ensure B::foo() gets called rather than A::foo().
 *
 * However, which default argument is used for the int a parameter to
 * foo()? [dcl.fct.default]#10 [1] in the standard:
 *
 * A virtual function call (#13.3) uses the default arguments in the
 * declaration of the virtual function determined by the static type of the
 * pointer or reference denoting the object. An overriding function in a
 * derived class does not acquire default arguments from the function it
 * overrides.
 *
 * So B::foo() is called, but with the default argument from A::foo(), and
 * the output is B1.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.fct.default#10
 */

#include <iostream>

struct A {
	virtual void foo(int a = 1) {
		std::cout << "A" << a;
	}
};

struct B : A {
	virtual void foo(int a = 2) {
		std::cout << "B" << a;
	}
};

int main() {
	A *b = new B;
	b->foo();
}

