/*
 * The program is guaranteed to output: 00100
 *
 * [expr.prim.lambda.capture]#14 [1] says
 * Every occurence of decltype((x)) where x is a possibly parenthesized
 * id-expression that names an entity of automatic storage duration is
 * treated as if x were transformed into an access to a corresponding data
 * member of the closure type that would have been declared if x were an
 * odr-use of the denoted entity.
 *
 * So additional parentheses, as the in the code snippet above, are
 * ignored.
 *
 * The member of the closure type corresponding to the as-if-captured j
 * will be not a reference, but will have the referenced type of the
 * reference, since it is captured by copy ([expr.prim.lambda.capture]#10
 * [2]).
 *
 * Since the lambda is not declared mutable, the overloaded operator() of
 * the closure type will be a const member function.
 * [expr.prim.lambda.closure]#4 [3]: "The function call operator or
 * operator template is declared const if and only if the
 * lambda-expression's parameter-declaration-clause is not followed by
 * mutable."
 *
 * Since the expression for decltype is a parenthesized lvalue expression,
 * [dcl.type.simple]#4 [4] has this to say: "The type denoted by
 * decltype(e) is (...) T&, where T is the type of e;" As the expression
 * occurs inside a const member function, the expression is const, and
 * decltype((j)) denotes int const&. See also the example in
 * [expr.prim.lambda.capture]#14 [5].
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/expr.prim.lambda.
 * capture#14
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr.prim.lambda.
 * capture#10
 * [3] https://timsong-cpp.github.io/cppwp/n4659/expr.prim.lambda.closure#4
 * [4] https://timsong-cpp.github.io/cppwp/n4659/dcl.type.simple#4
 * [5] https://timsong-cpp.github.io/cppwp/n4659/expr.prim.lambda.
 * capture#14
 */

#include <iostream>
#include <type_traits>

using namespace std;

int main()
{
	int i, &j = i;
	[=]
	{
		cout << is_same<decltype    ((j)),     int         >::value
			 << is_same<decltype   (((j))),    int      &  >::value
			 << is_same<decltype  ((((j)))),   int const&  >::value
			 << is_same<decltype (((((j))))),  int      && >::value
			 << is_same<decltype((((((j)))))), int const&& >::value;
	}();
}

