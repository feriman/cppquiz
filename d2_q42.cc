/*
 * a1 is default initialized, as described in [dcl.init]#12 [1].
 *
 * a2 doesn't actually use the initializer_list constructor with a list of
 * zero elements, but the default constructor:
 * [dcl.init.list]#3 [2]:
 * List-initialization of an object or reference of type T is defined
 * as follows:
 * - (...)
 * - Otherwise, if the initializer list has no elements and T is a class
 *   type with a default constructor, the object is value-initialized.
 * - Otherwise, if T is a specialization of std::initializer_list, the
 *   object is constructed as described below.
 *
 * a3's and a4's constructor is chosen in overload resolution, as described
 * in [over.match.list] [3]:
 *
 * "When objects of non-aggregate class type T are list-initialized (...),
 * overload resolution selects the constructor in two phases:
 * -- Initially, the candidate functions are the initializer-list
 *  constructors ([dcl.init.list] [4]) of the class T and the argumentlist
 *  consists of the initializer list as a single argument.
 * -- If no viable initializer-list constructor is found, overload
 *  resolution is performed again, where the candidate functions are all
 *  the constructors of the class T and the argument list consists of the
 *  elements of the initializer list."
 *
 * Initializer list constructors are greedy, so even though A(int)
 * constructor is available, the standard mandates that
 * initializer_list<int> is prioritized, and if - and only if - it's not
 * available, the compiler is allowed to look for other constructors. (This
 * is why it is not recommended to provide a constructor that ambiguously
 * overloads with an initializer_list constructor. See the answer to #4 in
 * http://herbsutter.com/2013/05/09/gotw-1-solution/ )
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/dcl.init#12
 * [2] https://timsong-cpp.github.io/cppwp/n4659/dcl.init.list#3
 * [3] https://timsong-cpp.github.io/cppwp/n4659/over.match.list
 * [4] https://timsong-cpp.github.io/cppwp/n4659/dcl.init.list
 */

#include <iostream>
#include <initializer_list>

struct A {
	A() { std::cout << "1"; }
	A(int) { std::cout << "2"; }
	A(std::initializer_list<int>) { std::cout << "3"; }
};

int main(int argc, char *argv[]) {
	A a1;
	A a2{};
	A a3{ 1 };
	A a4{ 1, 2 };
}

