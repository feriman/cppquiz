/*
 * g(A a) takes an object of type A by value, not by reference or pointer.
 * This means that A's copy constructor is called on the object passed to
 * g() (no matter if the object we passed was of type B), and we get a
 * brand new object of type A inside g(). This is commonly referred to as
 * slicing.
 */

#include <iostream>

class A {
public:
	virtual void f() { std::cout << "A"; }
};

class B : public A {
public:
	void f() { std::cout << "B"; }
};

void g(A a) { a.f(); }

int main() {
	B b;
	g(b);
}

