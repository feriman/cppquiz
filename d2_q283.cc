/*
 * The core of the question is "in what order are the objects destroyed?".
 * In C++, objects are generally destroyed in the reverse order that they
 * were constructed. delete[] is no exception.
 *
 * [expr.delete]#6 [1]:
 *
 * In the case of an array, the elements will be destroyed in order of
 * decreasing address (that is, in reverse order of the completion of their
 * constructor (...).
 *
 * So the objects are destroyed in the order 2, 1, 0, and 210 is printed.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.delete#6
 */

#include <iostream>

class show_id
{
public:
	~show_id() { std::cout << id; }
	int id;
};

int main()
{
	delete[] new show_id[3]{ {0}, {1}, {2} };
}

