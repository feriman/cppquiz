/*
 * In both calls A::fn is overridden, so B::fn will be alled. The first
 * call a.fn(1) is trivial, the argument 1 is used, and 3 is printed.
 *
 * The second call a.fn() is less trivial. The implementation doesn't care
 * about the "virtuality" of a function when determining the default
 * argument, but instead uses the static type of the referenced object.
 * Thus, the default argument 5 from A::fn will be used even if B::fn is
 * called, and 7 is printed.
 *
 * [dcl.fct.default]#10 [1] in the C++ standard:
 *
 * "A virtual function call (#13.3) uses the default arguments in the
 * declaration of the virtual function determinded by the static type of
 * the pointer or reference denoting the object. An overriding function in
 * a derived class does not acquire default arguments from the function it
 * overrides."
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.fct.default#10
 */

#include <iostream>

struct A
{
	virtual int fn(int i = 5) const { return i + 1; }
};

struct B : A
{
	virtual int fn(int i = 7) const override { return i + 2; }
};

void run(const A& a)
{
	std::cout << a.fn(1) << a.fn();
}

int main()
{
	run(B());
}

