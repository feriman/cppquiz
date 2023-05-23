/*
 * [temp.fct.spec]#2 [1]: Each function template specialization
 * instantiated from a template has its own copy of any static variable.
 *
 * This means we get two instantiations of f, one for T=int, and one for
 * T=double. Thus, i is shared between the two int calls, but not with the
 * double call.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/temp.fct.spec#2
 */

#include <iostream>

using namespace std;

template<class T> void f(T) {
	static int i = 0;
	cout << ++i;
}

int main() {
	f(1);
	f(1.0);
	f(1);
}

