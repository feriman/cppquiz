/*
 * [temp.param]#14 in the C++ standard says: "A template-parameter of a
 * template template-parameter is permitted to have a default
 * template-argument. When such default arguments are specified, they apply
 * to the template-parameter in the scope of the template
 * template-parameter."
 *
 * In this case, the template template-parameter is C, and the scope of C
 * is the function g(), so the default arguments of C (i.e. T = B) are
 * applied and C::f() is called inside g().
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/temp.param#14
 */

#include <iostream>

using namespace std;

struct A {};
struct B {};

template<typename T = A>
struct X;

template<>
struct X<A> {
	static void f() { cout << 1 << endl; }
};

template<>
struct X<B> {
	static void f() { cout << 2 << endl; }
};

template<template<typename T = B> class C>
void g() {
	C<>::f();
}

int main() {
	g<X>();
}

