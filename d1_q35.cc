/*
 * To answer this we need to look at overload resolution of vector's
 * constructors:
 *
 * [vector.cons]#6 [1] says (somewhat redacted):
 * vector(size_type n, const T& value);
 * Effects: Constructs a vector with n copies of value, using the specified
 * allocator
 *
 * So v1 contains one "2".
 *
 * [over.match.list] [2] says (in summary) that when non-aggregate classes
 * (such as vector) are list-initialized [3] and have an initializer list
 * constructor (again, like vector), that constructor is chosen, and the
 * argument list consists of the initializer list as a single argument.
 *
 * So v2 is initialized from the elements (aka initializer-clauses) in the
 * braced-init-list, and contains the elements "1" and "2".
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/vector.cons#6
 * [2] https://timsong-cpp.github.io/cppwp/n4659/over.match.list
 * [3] [dcl.init.list]#1 [4]: List-initialization is initialization of an
 * object or reference from a braced-init-list.
 * [4] https://timsong-cpp.github.io/cppwp/n4659/dcl.init.list#1
 */

#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v1(1, 2);
	std::vector<int> v2{ 1, 2 };
	std::cout << v1.size() << v2.size();
}

