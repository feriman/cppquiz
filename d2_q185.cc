/*
 * The functions called by f<int>() and f<const int>() actually have the
 * same function type, but they are still distinct functions, so each get
 * their own distinct static int stat.
 *
 * When we call f<int>() for the first time, stat is 0, and 0 is printed.
 * stat is then incremented to 1.
 * When we call f<int>() again, stat is 1, and 1 is printed. stat is then
 * incremented to 2.
 * We then call f<const int>(), which is a distinct function with its own
 * stat, which is 0, and 0 is printed.
 *
 * This example from [temp.deduct]#3 [1] in the standard is relevant:
 *
 * template<class T> void f(T t);
 * (...)
 * // #1: function type is f(int), t is non const
 * f<int>(1);
 * // #2: function type is f(int), t is const
 * f<const int>(1);
 *
 * So we can see that all calls to f() in the question are to a function of
 * the same type f(int). However, [temp.deduct]#4 [2] says:
 * "f<int>(1) and f<const int>(1) call distinct functions even though both
 * of the functions called have the same function type."
 *
 * So now we know that the functions are distinct. And [temp.fct.spec]#2
 * [3] says:
 * "Each functions template specialization instantiated from a template has
 * its own copy of any static variable."
 *
 * So now we know that the stat variables will also be distinct.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/temp.deduct#3
 * [2] https://timsong-cpp.github.io/cppwp/n4659/temp.deduct#4
 * [3] https://timsong-cpp.github.io/cppwp/n4659/temp.fct.spec#2
 */

#include <iostream>

template <typename T> void f() {
	static int stat = 0;
	std::cout << stat++;
}

int main() {
	f<int>();
	f<int>();
	f<const int>();
}

