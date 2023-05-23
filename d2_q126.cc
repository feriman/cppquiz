/*
 * [basic.lookup.unqual]#13 [1] states "A name used in the definition of a
 * static data member of class X (...) is looked up as if the name was used
 * in a member function of X."
 *
 * Even though the call foo() occurs outside the class, since foo is used
 * in the definition of the static data member foobar::x, it is looked up
 * as if foo() was called in a member function of foobar. If foo() was
 * called in a member function of foobar, foobar:foo() would be called, not
 * the global foo().
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/basic.lookup.unqual#13
 */

#include <iostream>

int foo()
{
	return 10;
}

struct foobar
{
	static int x;
	static int foo()
	{
		return 11;
	}
};

int foobar::x = foo();

int main()
{
	std::cout << foobar::x;
}

