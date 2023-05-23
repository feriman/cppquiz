/*
 * In f(), an E object is constructed, and 1 is printed. This object is
 * then returned to main(), and one could expect the copy constructor to be
 * called, printing 2.
 *
 * However, E() is prvalue and as such does not constitute an object just
 * yet by [basic.lval]#1 [1]
 *
 * A prvalue is an expression whose evaluation initializes an object or a
 * bit-field, or computes the value of the operand of an operator, as
 * specified by the context in which it appears.
 *
 * A prvalue only creates a temporary when needed, for instance to create
 * an xvalue. In those cases, a temporary meterialization conversion
 * happens ([conv.rval]#1 [2]). In this case however, no temporary is
 * needed, and none is created.
 *
 * [stmt.return]#2 [3] says:
 *
 * (...) the return statement initializes the glvalue result or prvalue
 * result object of the (explicit or implicit) function call by
 * copy-initialization from the operand.
 *
 * And copy-initialization for a class-type by [dcl.init]#17 [4] goes
 * through:
 *
 * If the initializer expression is a prvalue and the cv-unqualified
 * version of the source type is the same class as the class of the
 * destination, the initializer expression is used to initialize the
 * destination object.
 *
 * Which means that no copy or move constructor is called at all. This
 * implies that the copy and move constructor could very well be deleted,
 * and the code would still compile just fine.
 *
 * The output is thus 13 because of the constructor followed by the
 * destructor call.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/basic.lval#1
 * [2] https://timsong-cpp.github.io/cppwp/n4659/conv.rval#1
 * [3] https://timsong-cpp.github.io/cppwp/n4659/stmt.return#2
 * [4] https://timsong-cpp.github.io/cppwp/n4659/dcl.init#17
 */

#include <iostream>

struct E
{
	E() { std::cout << "1"; }
	E(const E&) { std::cout << "2"; }
	~E() { std::cout << "3"; }
};

E f()
{
	return E();
}

int main()
{
	f();
}

