/*
 * As long as A::f() is not virtual, A::f() will always be called, even if
 * the reference or pointer is actually referring to an object of type B.
 */

#include <iostream>

class A {
public:
	void f() { std::cout << "A"; }
};

class B : public A {
public:
	void f() { std::cout << "B"; }
};

void g(A &a) { a.f(); }

int main() {
	B b;
	g(b);
}

