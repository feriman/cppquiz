/*
 * [dcl.fct]#8 [1] says:
 *
 * The return type, the parameter-type-list, the ref-qualifier, the
 * cv-qualifier-seq, and the exception specification, but not the default
 * arguments, are part of the function type.
 *
 * This means that the ref-qualifier (in this case const&&) is part of the
 * type and thus the type of ptr is int(X::*)() const&&.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.fct#8
 */

#include <type_traits>
#include <iostream>

using namespace std;

struct X {
	int f() const&& {
		return 0;
	}
};

int main() {
	auto ptr = &X::f;
	cout << is_same_v<decltype(ptr), int()>
		 << is_same_v<decltype(ptr), int(X::*)()>;
}

