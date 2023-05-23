/*
 * First, b1 is default initialized. All members are initialized before the
 * body of the constructor, so b1.a is default initialized first, and we
 * get the output 14.
 *
 * [class.base.init]#9 [1] int the standard: "In a non-delegating
 * constructor, if a given potentially constructed subobject designated by
 * a mem-initializer_id (...) then if the entity is a non-static data
 * member that has a default member initializer (12.2), (...) the entity is
 * initialized as specified in 11.6 (...) otherwise, the entity is default-
 * initialized."
 *
 * Then, b2 is initialized with the move constructor (since std::move(b1)
 * converts the reference to b1 to an xvalue, allowing it to be moved
 * from.) In B's move constructor, a is initialized in the member
 * initializer list. Even though b is an rvalue reference (and bound to an
 * rvalue), b itself is an lvalue, and cannot be moved from. b2.a is then
 * copy initialized, printing 2, and finally the body of B's move
 * constructor prints 6.
 *
 * (If the concept of rvalue references being lvalues is confusing,
 * read [2]. Search for "In widget".)
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/class.base.init#9
 * [2] http://isocpp.org/blog/2012/11/universal-references-in-c11-scott-
 * meyers
 */

#include <iostream>
#include <utility>

struct A
{
	A() { std::cout << "1"; }
	A(const A&) { std::cout << "2"; }
	A(A&&) { std::cout << "3"; }
};

struct B
{
	A a;
	B() { std::cout << "4"; }
	B(const B& b) : a(b.a) { std::cout << "5"; }
	B(B&& b) : a(b.a) { std::cout << "6"; }
};

int main()
{
	B b1;
	B b2 = std::move(b1);
}

