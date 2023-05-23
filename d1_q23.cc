/*
 * When the array is initialized, the default constructor is called once
 * for each of the two object in it.
 *
 * Then we iterate over the array using auto, which in our case is deduced
 * to be A. This means the copy constructor will be called before f() for
 * each iteration, printing BCBC. (Just as if we had written for (A x: a).
 *
 * If we want to avoid the copy constructor, we can write for (auto& x : a)
 * instead. Then the loop would print CC. (Just as if we had written
 * for (A& x: a).
 */

#include <iostream>

struct A {
	A() { std::cout << "A"; }
	A(const A& a) { std::cout << "B"; }
	virtual void f() { std::cout << "C"; }
};

int main() {
	A a[2];
	for (auto x : a) {
		x.f();
	}
}

