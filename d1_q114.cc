/*
 * According to [dcl.ptr]#1 [1] in the C++ standard, "The cv-qualifiers
 * [e.g., const] apply to the pointer and not to the object pointed to."
 *
 * That is, const-ness is shallow with regards to raw pointers and
 * references (and standard types that seek to emulate them, like
 * std::unique_ptr) but not with regard to standard containers such as
 * std::vector.
 *
 * In the code above, the object s is non-const, and so its members all
 * retain their default const-ness and all calls through them invoke the
 * non-const version of C::foo().
 *
 * However, r refers to its object as a const instance of S. That
 * const-ness changes the behaviour of its member v, and std::vector which
 * is "const-correct" in the sense that its operator[] returns const C&
 * (see [sequence.reqmts]#14 [2]) and therefore invokes the const version
 * of C::foo().
 *
 * The const-ness of r's referent is also propagated to its members u and p
 * (meaning one could not perform a mutating operation on u, e.g., calling
 * r.u.reset()), but this has no effect on the instance of C that they both
 * point to. That is, the pointers themselves become const, but the
 * pointed-to objects remain non-const. Hence, they both still call the
 * non-const version of C::foo().
 *
 * The const-ness of the member S::p is the same for both s and r. Because
 * it is declared as a const pointer, it does not change const-ness to
 * follow the const-ness of its instance of S but remains a const pointer
 * to a non-const object.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.ptr#1
 * [2] https://timsong-cpp.github.io/cppwp/n4659/sequence.reqmts#14
 */

#include <iostream>
#include <memory>
#include <vector>

class C {
public:
	void foo() { std::cout << "A"; }
	void foo() const { std::cout << "B"; }
};

struct S {
	std::vector<C> v;
	std::unique_ptr<C> u;
	C* const p;

	S()
		: v(1)
		, u(new C())
		, p(u.get())
	{}
};

int main() {
	S s;
	const S& r = s;

	s.v[0].foo();
	s.u->foo();
	s.p->foo();

	r.v[0].foo();
	r.u->foo();
	r.p->foo();
}

