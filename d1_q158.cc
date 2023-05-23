/*
 * Since C++11, std::vector has a one parameter constructor (+ allocator).
 * [vector.cons]#3 [1] in the standard:
 *
 * 		explicit vector(size_type n, const Allocator& = Allocator())
 *
 * which constructs a vector with n value-initialized elements. Each
 * value-initialization calls the default Foo constructor, resulting in the
 * output aaaaa.
 *
 * The "trick" is, that before C++11, std::vector had a 2 parameter
 * constructor (+ allocator), which constructed the container with n copies
 * of the second parameter, which is defaulted to T().
 *
 * So this code before C++11 would ouput abbbbb, because the call would be
 * equivalent to std::vector<Foo> bar(5, T()).
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/vector.cons#3
 */

#include <iostream>
#include <vector>

struct Foo
{
	Foo() { std::cout << "a"; }
	Foo(const Foo&) { std::cout << "b"; }
};

int main()
{
	std::vector<Foo> bar(5);
}

